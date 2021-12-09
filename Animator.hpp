#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include <vector>
#include "Component.hpp"
#include "Sprite.hpp"
#include <memory>

namespace spic {

    /**
     * @brief A component which can play animated sequences of sprites.
     */
    class Animator : public Component {
    public:
        Animator(double fps, std::vector<std::shared_ptr<Sprite>> sprites)
                : Component(), fps(fps), _looping(true), sprites(std::move(sprites)), secondsSinceLastFrame(0) {};

        /**
         * @brief Start playing the image sequence.
         * @param looping If true, will automatically start again when done.
         * @spicapi
         */
        void Play(bool looping);

        /**
         * @brief Stop playing the image sequence. Whatever sprite was displayed
         *        last will remain shown.
         * @spicapi
         */
        void Stop();

        void Fps(double fps);

        [[nodiscard]] double Fps() const;

        /**
        * @brief Get the next sprite from the animation (based on fps/time).\n
        * This could result in the same sprite depending looping & isPlaying\n
        * @return The currentsprite (after updating animation (time-based)
        * @spicapi
        */
        std::shared_ptr<spic::Sprite> GetSprite();

        /**
        * @brief Get the next sprite from the animation.\n
        * This could result in the same sprite depending looping & isPlaying\n
        * This \b forces the animation to update, regardless of timeframe since last animation update.
        * @return The currentsprite (after updating animation)
        * @spicapi
        */
        std::shared_ptr<spic::Sprite> NextSprite();

        /**
        * @brief Get the current sprite from the animation.\n
        * Can be used to manipulate the currentSprite (FlipX,FlipY etc.)
        * @return The current sprite
        * @spicapi
        */
        std::shared_ptr<spic::Sprite> CurrentSprite();

        /**
        * @brief Change FlipX of all sprites in the animator
        * @spicapi
        */
        void FlipX(bool newFlipX);

        /**
        * @brief Change FlipY of all sprites in the animator
        * @spicapi
        */
        void FlipY(bool newFlipY);
    private:
        /**
        * @brief reset the current frame if the last sprite is surpassed.\n
        * This function would start with the first frame if looping is true, or will stop at the last frame if looping is false.
        * @return The sprite that must be showed, or nullpointer if the animation starts over.
        * @spicapi
        */
        std::shared_ptr<spic::Sprite> resetCurrentFrame();

        /**
         * @brief frames per second (playing speed)
         * @spicapi
         */
        double fps;
        double secondsSinceLastFrame;
        bool isPlaying{};
        bool _looping;
        size_t currentFrame{};

        std::vector<std::shared_ptr<Sprite>> sprites{};
    };

}

#endif // ANIMATOR_H_
