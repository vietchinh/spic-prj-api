#ifndef BUTTON_H_
#define BUTTON_H_

#include "UIObject.hpp"
#include <functional>
#include <utility>

namespace spic {

    /**
     * @brief Instances of this class are clickable user interface items.
     */
    class Button : public UIObject {
    public:
        explicit Button(const std::vector<std::shared_ptr<Component>> &components, const std::string &parentName,
                        const std::string &name, const std::string &tag, bool active, int layer, double width,
                        double height, std::function<void()> callback);

        /**
             * @brief This function is called when the button is clicked, which
             *        will trigger a call to the registered onClick member.
             * @spicapi
             */
        void Click();

        /**
         * @brief Register the onClick handler to be used when the button is clicked.
         * @param callback The function to register, usually a lambda. But this can be
         *        any kind of callable.
         * @spicapi
         */
        void OnClick(std::function<void()> callback) { onClick = std::move(callback); }

        bool IsInteractable() const;

    private:
        /**
         * @brief When false, the button will not react to clicks.
         */
        bool interactable;

        /**
         * @brief The registered click handler.
         */
        std::function<void()> onClick;
    };

}

#endif // BUTTON_H_
