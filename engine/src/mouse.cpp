/**
    \file mouse.cpp
    This file define methods content of the Mouse class
*/

#include "mouse.hpp"
#include <assert.h>

using namespace engine;

/**
    Get mouse position
*/
void Mouse::set_position() {

    // Receives the coordinate of the x axis
    int X_AXIS = 0;

    // Receives the coordinate of the y axis
    int Y_AXIS = 0;

    Log::instance.info("Setting mouse position");

    SDL_GetMouseState(&X_AXIS, &Y_AXIS);
    mouse_position_x = X_AXIS;
    mouse_position_y = Y_AXIS;
}

/**
    Check if mouse cursor is over a defined object
    \param *gameObject
    \parblock
        Is a input parameter that represents an object of the game(!=NULL)
    \endparblock
    \return true is over
    \return false isn't over
*/
bool Mouse::is_over(engine::GameObject *gameObject) {

    assert( gameObject != NULL );

    /**
        /note This paragraph responsible for verifying that the mouse cursor
            is over a defined object, then returns true.
    */
    if( mouse_position_x > gameObject->main_positionX &&
        mouse_position_y > gameObject->main_positionY &&
        mouse_position_x < (gameObject->main_width + 
                            gameObject->main_positionX) &&
        mouse_position_y < (gameObject->main_height + 
                            gameObject->main_positionY) ) {
        return true;
    }
    else {
        return false;
    }

}

/**
    Check if mouse click is right button
    \return true is right button
    \return false isn't right button
*/
bool Mouse::is_right_button() {

    /**
        /note This paragraph is responsible for checking if the mouse
            click is the right mouse button, by mouse state and returns true.
    */
    if( SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) ) {
        return true;
    }
    else {
        return false;
    }
    
}

/**
    Check if mouse click is left button
    \return true is left button
    \return false isn't left button
*/
bool Mouse::is_left_button() {

    /**
        /note This paragraph is responsible for checking if the mouse
            click is the left mouse button, by mouse state and returns true.
    */
    if( SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT) ) {
        return true;
    }
    else {
        return false;
    }

}
