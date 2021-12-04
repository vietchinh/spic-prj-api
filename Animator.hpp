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
            Animator(double fps, std::vector<std::shared_ptr<Sprite>> sprites) : Component(), fps(fps), _looping(true), sprites(std::move(sprites)), secondsSinceLastFrame(0) {};

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

            std::shared_ptr<spic::Sprite> CurrentSprite();
        private:
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
