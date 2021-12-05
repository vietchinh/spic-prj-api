#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.hpp"
#include "Color.hpp"

namespace spic {

    /**
     * @brief Class representing a point of view towards the game scene.
     * @spicapi
     */
    class Camera : public GameObject {
    public:
        explicit Camera(Color backgroundColor, const std::vector<std::shared_ptr<Component>> &components = {},
                        const std::string &parentName = "", const std::string &name = "", const std::string &tag = "",
                        bool active = true, int layer = 0, double aspectWidth = 0, double aspectHeight = 0,
                        bool autoInsert = false);

        const Color &BackgroundColor() const;

        void BackgroundColor(const Color &newBackgroundColor);

        double AspectWidth() const;

        void AspectWidth(double newAspectWidth);

        double AspectHeight() const;

        void AspectHeight(double newAspectHeight);

    private:
        Color backgroundColor;
        double aspectWidth;
        double aspectHeight;
    };

}

#endif // CAMERA_H_
