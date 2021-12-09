#ifndef SPRITERENDERER_H_
#define SPRITERENDERER_H_

#include "Component.hpp"
#include "Color.hpp"
#include "Transform.hpp"
#include <string>
#include <o_real_physics/physics_vector.hpp>
#include <components/SizeComponent.hpp>

namespace spic {

    /**
     * @brief A component representing a sprite (small image)
     * @spicapi
     */
    class Sprite : public Component {
    private:
        std::string sprite;
        Color color;
        bool flipX;
        bool flipY;
        int sortingLayer;
        int orderInLayer;
        o_real_engine::SizeComponent _size;
    public:
        void SortingLayer(int newSortingLayer);

        int SortingLayer() const;

        void OrderInLayer(int newOrderInLayer);

        int OrderInLayer() const;

        void FlipX(bool newFlipX);

        bool FlipX() const;

        void FlipY(bool newFlipY);

        bool FlipY() const;

        void SpriteColor(Color newColor);

        Color SpriteColor() const;

        void SpriteSrc(const std::string &newSprite);

        std::string SpriteSrc() const;

        /**
        * Gets the sprites size information (with and height)
        * @return A const reference of the body's Size object
        */
        const o_real_engine::SizeComponent &GetSize();

        /**
        * Sets the sprites size information (with and height)
        */
        void SetSize(o_real_engine::SizeComponent newSizeComponent);

        Sprite(std::string sprite, Color color, bool flipX, bool flipY, int sortingLayer, int orderInLayer, o_real_engine::SizeComponent sizeComponent);
    };
}

#endif // SPRITERENDERER_H_
