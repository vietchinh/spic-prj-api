#ifndef UIOBJECT_H_
#define UIOBJECT_H_

#include "GameObject.hpp"

namespace spic {

    /**
     * @brief Base class for a user interface object like Button or Text.
     * @spicapi
     */
    class UIObject : public GameObject {
        private:
            double width;
            double height;
        public:
            UIObject(std::vector<std::shared_ptr<Component>> components, const std::string& parentName, const std::string& name, const std::string& tag, bool active, int layer, double newWidth, double newHeight);

            void Width(double newWidth);
            [[nodiscard]] double Width() const;

            void Height(double newHeight);
            [[nodiscard]] double Height() const;
    };

}

#endif // UIOBJECT_H_
