/**
    \file keyboard.hpp
    This file declares Keyboard class
*/
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include<iostream>
#include<list>
#include <algorithm>
#include <unordered_map>

#include "sdl2core.hpp"

namespace engine {

    /// Class for keyboard control
    /**
        \class Keyboard
        This class is responsible to map, listen and set keys pressed
    */
    class Keyboard {
        public:
            Keyboard();
            ~Keyboard();

            /**
                Set keys
                \param key this parameter define new event in game
                \return anything because the routine is void
            */
            void setKeys( SDL_Event* key );
            /**
                Verify key down
                \param key this parameter verify if key pressed is down
                \return returns bool to key down or not
            */
            bool isKeyDown( std::string key );
            /**
                Verify key up
                \param key this parameter verify if key pressed is up
                \return returns bool to key up or not
            */
            bool isKeyUp( std::string key );
            /**
                Clear key down and key up pressed by the player    
            */
            void clearKeyboard();

        private:
            /**
                Map all invalid and valid keys pressed by the player and
                what they do in game
            */
            void create_keyboard_mapping();
            std::list <Uint8> keycode_down;
            std::list <Uint8> keycode_up;
            Uint8 aux;
            std::unordered_map<std::string, int> m_buttons;

    };

}

#endif
