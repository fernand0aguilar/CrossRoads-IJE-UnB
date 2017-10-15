/**
    \file fireball.cpp
    This file implements the FireballController class
*/
#include "fireball.hpp"
#include "game.hpp"

#include <stdio.h>
#include <stdlib.h>

/**
    This method initiates the fireball in the game scene
    \return return a true value that make the fireball active
*/
bool FireballController::init() {

    /*
        last_position_player_x = m_player->main_positionX;
        _main_game_object->main_positionX = last_position_player_x;
    */

  return true;

}

/**
    This method is reponsable for controlling when the fireball dropps
*/
void FireballController::update() {

    if(ready_to_fall == true) {
        processPos();
    }
    else {
        last_position_player_x = m_player->main_positionX;
        _main_game_object->main_positionX = last_position_player_x;
        ready_to_fall = true;
    }

}

// Initial position of fireball
const int initial_position = -600;

/**
    This method is reponsable for the fireball dropping
*/
void FireballController::processPos() {

    AudioComponent* fireball_droping_audio = ( dynamic_cast<AudioComponent*>
            ( _main_game_object->get_component( "fireball_droping_audio" ) ) );

    if( ready_to_fall ) {

        // Current velocity components.

        _main_game_object->main_positionY += variation_position_y;
        fireball_droping_audio->play(0,-1);
    }
    else {

        // Do nothing

    }

    if( _main_game_object->main_positionY < 850 ) {

        // Do nothing
        
    }
    else {
        _main_game_object->main_positionY = initial_position;
        ready_to_fall = false; 
    }

}

FireballController::~FireballController(){}
