/**
  \file animation_controller.hpp
  This file contains header declaration for AnimationControllerComponent Class
*/

#ifndef FOO_BAR_ENGINE_COMPONENTS_ANIMATION_CONTROLLER_H_
#define FOO_BAR_ENGINE_COMPONENTS_ANIMATION_CONTROLLER_H_

#define NO_ANIMATION ""
#define HAVE_ANIMATION 1

#include <string>
#include <unordered_map>
#include <utility>
#include <assert.h>

#include "sdl2core.hpp"

#include "components/component.hpp"
#include "components/animation.hpp"
#include "gameobject.hpp"

namespace engine {

    /// Manages the exchange of animations
    /**
        \class AnimationControllerComponent
        This class manages the current animations and the transition with other animations
    */
    class AnimationControllerComponent : public Component {

        public:

            AnimationControllerComponent(GameObject &main_game_object, std::string id_animation) :
                                         Component(main_game_object, id_animation),
                                         current_animation(""), next_animation("") {

                // Default function call.

            }

            ~AnimationControllerComponent() {

            };

            bool init();
            bool shutdown();
            void update();
            int add_animation(std::string name, Animation &animation);

            int play_animation(std::string name, bool wait_to_finish = false);

            void flipping(bool is_flip);

        private:
            /**
                Control flip state of character, monsters and boss.
            */
            bool flip = false;

            /**
                Control animations of game.
            */
            std::unordered_map<std::string, Animation *> m_animations_map;
            std::string current_animation = "";
            std::string next_animation = "";

            int change_animations();

    };

}

#endif // FOO_BAR_ENGINE_COMPONENTS_ANIMATION_CONTROLLER_H_
