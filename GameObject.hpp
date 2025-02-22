#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Component.hpp"
#include <string>
#include <algorithm>
#include <vector>
#include <memory>
#include <iostream>
#include <functional>
#include <boost/range/algorithm/equal.hpp>

namespace spic {

    /**
     * @brief Any object which should be represented on screen.
     */
    class GameObject {
    public:
        /**
         * @brief Finds a GameObject by name and returns it.
         * @param name The name of the GameObject you want to find.
         * @return Pointer to GameObject, or nullptr if not found.
         * @spicapi
         */
        template<class T>
        static std::shared_ptr<T> Find(const std::string &name) {
            for (const std::shared_ptr<GameObject> &gameObject: GameObject::gameObjects) {
                if (boost::equal(gameObject->name, name)) {
                    return std::static_pointer_cast<T>(gameObject);
                }
            }

            return nullptr;
        }

        /**
         * @brief Returns a vector of active GameObjects tagged tag. Returns empty
         *        vector if no GameObject was found.
         * @param tag The tag to find.
         * @return std::vector of GameObject pointers. No ownership.
         * @spicapi
         */
        static std::vector<std::shared_ptr<GameObject>> FindGameObjectsWithTag(const std::string &tag);

        static std::shared_ptr<GameObject> FindGameObjectWithComponent(int componentId);

        /**
         * @brief Returns one active GameObject tagged tag. Returns nullptr if no GameObject was found.
         * @param tag The tag to find.
         * @return Pointer to GameObject, or nullptr if not found.
         * @spicapi
         */
        static std::shared_ptr<GameObject> FindWithTag(const std::string &tag);

        /**
         * @brief Returns the first active loaded object of Type type.
         * @spicapi
         */
        template<class T>
        static std::shared_ptr<T> FindObjectOfType(bool includeInactive = false) {
            std::vector<std::shared_ptr<T>> foundObjectsOfType = FindObjectsOfType<T>(includeInactive);

            if (foundObjectsOfType.empty()) return nullptr;


            return std::static_pointer_cast<T>(foundObjectsOfType.front());
        }

        /**
         * @brief Gets a list of all loaded objects of Type type.
         * @spicapi
         */
        template<class T>
        static std::vector<std::shared_ptr<T>> FindObjectsOfType(bool includeInactive = false) {
            std::vector<std::shared_ptr<spic::GameObject>> targetGameObjects;
            std::function<bool(const std::shared_ptr<GameObject> &gameObject)> predicate = [&includeInactive](
                    const std::shared_ptr<GameObject> &gameObject) {
                return gameObject.get() && dynamic_cast<T *>(gameObject.get()) != nullptr &&
                       (includeInactive || gameObject->Active());
            };
            std::copy_if(spic::GameObject::gameObjects.begin(), spic::GameObject::gameObjects.end(),
                         std::back_inserter(targetGameObjects), predicate);

            if (targetGameObjects.empty()) return std::vector<std::shared_ptr<T>>{};

            std::vector<std::shared_ptr<T>> convertedGameObjects;
            std::transform(targetGameObjects.cbegin(), targetGameObjects.cend(),
                           std::back_inserter(convertedGameObjects), [](const std::shared_ptr<GameObject> &gameObject) {
                        return std::dynamic_pointer_cast<T>(gameObject);
                    });

            return convertedGameObjects;
        }

        /**
         * @brief Removes a GameObject from the gameObjects.
         * @details TODO What happens if this GameObject is a parent to others? What happens
         *          to the Components it possesses?
         * @param obj The GameObject to be destroyed. Must be a valid pointer to existing Game Object.
         * @exception A std::runtime_exception is thrown when the pointer is not valid.
         * @spicapi
         */
        static void Destroy(std::shared_ptr<GameObject> obj);

        /**
         * @brief Removes a Component.
         * @details Will search for the Component among the GameObjects.
         * @param obj The Component to be removed.
         * @spicapi
         */
        static void Destroy(Component *obj);

        /**
         * @brief Constructor.
         * @details The new GameObject will also be added to a statically
         *          available collection, the gameObjects.  This makes the
         *          Find()-functions possible.
         * @param name The name for the game object.
         * @spicapi
         */
        explicit GameObject(std::vector<std::shared_ptr<Component>> components, std::string name);

        GameObject(std::vector<std::shared_ptr<Component>> components, std::string name, std::string tag, bool active,
                   int layer);

        GameObject(std::vector<std::shared_ptr<Component>> components, const std::string &parentName, std::string name,
                   std::string tag, bool active, int layer, bool autoInsert = true);

        /**
         * @brief Does the object exist?
         * @spicapi
         */
        explicit operator bool() const;

        /**
         * @brief Compare two GameObjects.
         * @param other The other object to compare this one with.
         * @return true if not equal, false otherwise.
         * @spicapi
         */
        bool operator!=(const GameObject &other) const;

        /**
         * @brief Compare two GameObjects
         * @param other The other object to compare this one with.
         * @return true if equal, false otherwise.
         * @spicapi
         */
        bool operator==(const GameObject &other) const;

        /**
         * @brief Add a Component of the specified type. Must be a valid
         *        subclass of Component. The GameObject assumes ownership of
         *        the Component.
         * @details This function places a pointer to the component in
         *          a suitable container.
         * @param component Reference to the component.
         * @spicapi
         */
        template<class T>
        void AddComponent(std::shared_ptr<T> component) {
            components.emplace_back(std::move(component));
        }

        /**
         * @brief Get the first component of the specified type. Must be
         *        a valid subclass of Component.
         * @return Pointer to Component instance.
         * @spicapi
         */
        template<class T>
        [[nodiscard]] std::shared_ptr<T> GetComponent() const {
            std::vector<std::shared_ptr<T>> foundComponents = GetComponents<T>();

            if (foundComponents.empty()) return nullptr;

            return foundComponents.front();
        }


        /**
         * @brief Get the first component of the specified type from
         *        contained game objects. Must be
         *        a valid subclass of Component.
         * @return Pointer to Component instance.
         * @spicapi
         */
        template<class T>
        [[nodiscard]] std::shared_ptr<Component> GetComponentInChildren() const {
            for (const std::shared_ptr<GameObject> &child: GameObject::gameObjects) {
                std::shared_ptr<Component> foundComponent = child->GetComponents<T>();

                if (foundComponent != nullptr) return foundComponent;
            }
            return nullptr;
        }

        /**
         * @brief Get the first component of the specified type from
         *        the parent game object. Must be
         *        a valid subclass of Component.
         * @return Pointer to Component instance.
         * @spicapi
         */
        template<class T>
        [[nodiscard]] std::shared_ptr<Component> GetComponentInParent() const {
            return parent == nullptr ? nullptr : parent->GetComponent<T>();
        }

        /**
         * @brief Get all components of the specified type. Must be
         *        a valid subclass of Component.
         * @return Vector with pointers to Component instances.
         * @spicapi
         */
        template<class T>
        [[nodiscard]] std::vector<std::shared_ptr<T>> GetComponents() const {
            std::vector<std::shared_ptr<Component>> foundComponents;
            std::copy_if(components.cbegin(), components.cend(), std::back_inserter(foundComponents),
                         [](const std::shared_ptr<Component> &component) {
                             return component.get() && dynamic_cast<T *>(component.get()) != nullptr;
                         });

            if (foundComponents.empty()) return std::vector<std::shared_ptr<T>>{};

            std::vector<std::shared_ptr<T>> convertedComponents;
            std::transform(foundComponents.cbegin(), foundComponents.cend(), std::back_inserter(convertedComponents),
                           [](const std::shared_ptr<Component> &component) {
                               return std::dynamic_pointer_cast<T>(component);
                           });

            return convertedComponents;
        }

        /**
         * @brief Get all components of the specified type from
         *        contained game objects. Must be
         *        a valid subclass of Component.
         * @return Vector with pointers to Component instances.
         * @spicapi
         */
        template<class T>
        [[nodiscard]] std::vector<std::shared_ptr<T>> GetComponentsInChildren() const {
            std::vector<std::shared_ptr<T>> foundComponents;

            for (const std::shared_ptr<GameObject> &child: GameObject::gameObjects) {
                if (child->parent != nullptr && *child->parent == *this) {
                    std::vector<std::shared_ptr<T>> childComponents = child->GetComponents<T>();

                    std::move(childComponents.cbegin(), childComponents.cend(), std::back_inserter(foundComponents));
                }
            }

            return foundComponents;
        }

        /**
         * @brief Get all components op the specified type from
         *        the parent game object. Must be
         *        a valid subclass of Component.
         * @return Vector with pointers to Component instances.
         * @spicapi
         */
        template<class T>
        [[nodiscard]] std::vector<std::shared_ptr<T>> GetComponentsInParent() const {
            return parent == nullptr ? std::vector<std::shared_ptr<T>>() : parent->GetComponents<T>();
        }

        /**
         * @brief Activates/Deactivates the GameObject, depending on the given true or false value.
         * @param active Desired value.
         * @spicapi
         */
        void Active(bool flag);

        /**
         * @brief Returns whether this game object is itself active.
         * @return true if active, false if not.
         * @spicapi
         */
        [[nodiscard]] virtual bool Active() const;

        /**
         * @brief Returns whether this game component is active, taking its parents
         *        into consideration as well.
         * @return true if game object and all of its parents are active,
         *        false otherwise.
         * @spicapi
         */
        [[nodiscard]] bool IsActiveInWorld() const;

        void Name(const std::string &name);

        [[nodiscard]] std::string Name() const;

        void Tag(const std::string &tag);

        [[nodiscard]] std::string Tag() const;

        void Layer(int layer);

        [[nodiscard]] int Layer() const;

        [[nodiscard]] int Id() const { return id; }

        void Id(int newId) { id = newId; }

    private:
        std::string name;
        std::string tag;
        bool active;
        int layer;
        static std::vector<std::shared_ptr<GameObject>> gameObjects;
        std::vector<std::shared_ptr<Component>> components;
        std::shared_ptr<GameObject> parent;
        int id = -1;
    protected:
        template<class T>
        void AddGameObject(const T &gameObject) {
            if (std::is_base_of_v<GameObject, T>) {
                this->id = static_cast<int>(GameObject::gameObjects.size());
                GameObject::gameObjects.emplace_back(std::make_shared<T>(gameObject));
            }
        }
    };
}

#endif // GAMEOBJECT_H_
