/**
    \file monsterAI.cpp
    This file implements the MonsterAI class
*/
#include "monsterAI.hpp"
#include "game.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/**
    Declares monsterAi constants.
*/
const int PLAYER_DISTANCE = 850;
const int PLAYER_ATTACK_DISTANCE = 150;
const int MAX_SCREEN_WIDTH = 800;
const int PLAYER_DISTANCE_ITERATOR = 100;
const int TIME_STEP_ITERATOR = 1000;

/**
    This method initiates the Class MonsterAI in the game
    \return return a true value that make the MonsterAI active
*/
bool MonsterAI::init() {

    /**
        Initializes the monster position, movement speed and life points.
    */
    _main_game_object->main_positionY = GROUND - _main_game_object->main_height; // Gets the current monster's y position.
    _main_game_object->main_positionX = 400; // Monster is initialized at the right side of the scene.
    horizontal_motion_units = ( rand() % 3 ) + 1; // Monster movement units varies from 1 to 3.
    setLifePoints(2);

    return true;
}

/**
    This method is responsible for updating the monster in walk and attack que monster in the game.
*/
void MonsterAI::update() {

    assert(_main_game_object != NULL);

    m_monster_controler->play_animation("monster_walk", true);

    apply_gravity();

    /**
        Updates the state and behavior of the monster object.
    */
    move_monster();
    receive_damage();
    process_position();
    jump_monster();

    /**
        \note Sets the state of the monster object to disable if it isn't
        on valid area.
    */
    if( _main_game_object->main_positionX < 0 || // If a monster is outter screen, its state is seted to disabled.
        _main_game_object->main_positionX +
        _main_game_object->main_width > MAX_SCREEN_WIDTH ) {
        _main_game_object->setState(GameObject::State::disabled);
    }

    /// \note Checks if monster is within player's range, and executes an attack
    if( Game::instance.collision_manager->checkCollision(
        _main_game_object, "player") ) {
        m_monster_controler->play_animation("monster_attack");
    }
}

/**
    This method is responsible for increment the vertical position of the monster
*/
void MonsterAI::apply_gravity() {
    /*
        if(_main_game_object->main_positionY > (ground -
        _main_game_object->main_height)){
            _main_game_object->main_positionY = ground -
            _main_game_object->main_height;
        }
    */
    assert(vertical_position < 40 && vertical_position > -40);

    // Verify if monsters are in the ground or not.
    if( !has_ground() ) {
        vertical_position += GRAVITY; // GRAVITY constant is added cause vertical_position increases upwards.
    }
    else {
        vertical_position = 0;
    }
}

/**
    This method is responsible for increment the vertical position of monster in game
*/
void MonsterAI::process_position() {

    // std::cout<<dy<<std::endl;

    _main_game_object->main_positionY += vertical_position; // Current velocity components.
}

/**
    This method is responsible for damage monster in the game
*/
void MonsterAI::receive_damage() {

    assert(Game::instance.collision_manager != NULL);

    bullet = Game::instance.collision_manager->checkCollision(
    _main_game_object, "bullet");

    /**
        \note Check if collision between monster and bullet happened or not to
        make monsters receive damage.
    */ 
    if( Game::instance.collision_manager->checkCollision(
        _main_game_object, "attack_box") || bullet ) {

            m_monster_controler->play_animation("monster_damage");

            /**
                \note Check if a bullet collide with a monster and disable
                bullet image if they collide.
            */
            if( bullet ) { 
                bullet->setState(GameObject::State::disabled);
            }

            has_damage = true;

            if( side == RIGHT ) {

                // _main_game_object->main_positionX -= 10;

            }
            if( side == LEFT ) {

                // _main_game_object->main_positionX += 10;

            }

            assert(Game::instance.timer);

            /// \note Prevents monsters take damage twice with just one bullet
            if( Game::instance.timer->getTicks() > time_damage ) {
                setLifePoints(getLifePoints() - 1);
                time_damage = Game::instance.timer->getTicks() +
                TIME_STEP_ITERATOR;
            }

            ///  \note Check if a monster died and if life < 0 monster disappear
            if( getLifePoints() <= 0 ) {
                _main_game_object->setState(GameObject::State::disabled);
                setLifePoints(3);

                // Game::instance.change_scene("Win Scene");

            }
    }
    else {
            has_damage = false;
    }
}

/**
    This method is responsible for move monster in direction the player in the game
*/
void MonsterAI::move_monster() {

    bool seeing_player = sees_player();

    assert(m_player != NULL);

    /// \note Moves the monster based on his relative position to the player.
    if( seeing_player && !has_damage &&
        m_player->main_positionX > _main_game_object->main_positionX ) {
            m_monster_controler->flipping(true);
            _main_game_object->main_positionX += horizontal_motion_units;
    }
    else if( seeing_player && !has_damage &&
        m_player->main_positionX < _main_game_object->main_positionX ) {
            m_monster_controler->flipping(false);
            _main_game_object->main_positionX -= horizontal_motion_units;
    }
}

/**
    This method is responsible for possibility the monster jump in the game
*/
void MonsterAI::jump_monster() {

    assert(Game::instance.collision_manager != NULL);

    bool on_ground = Game::instance.collision_manager->checkCollision(m_player,
                      "ground");

    /// \note Executes a monster's jump if the player is not on the ground.
    if( sees_player() && on_ground &&
        _main_game_object->main_positionY > m_player->main_positionY ) {
        vertical_position -= JUMP_SIZE; // JUMP_SIZE decreases vertical_position cause vertical_position decreases upwards.
    }
}

/**
    This method is responsible for possibility the monster to see player in the game
    \return return true for prayer see and false see not player
*/
bool MonsterAI::sees_player() {

    int distance_from_monster_to_player = fabs(_main_game_object->main_positionX -
                                               m_player->main_positionX);

    /// \note Checks if the monster is within range of the player.
    if( distance_from_monster_to_player  <= PLAYER_DISTANCE - PLAYER_DISTANCE_ITERATOR ) {
        return true;
    }
    else {
        return false;
    }
}

/**
    This method is responsible to check if monster is on the floor
*/
bool MonsterAI::has_ground() {

    assert(Game::instance.collision_manager != NULL);

    ground_obj = Game::instance.collision_manager->checkCollision(
                 _main_game_object, "ground");

    /**
        \note Places the monster in the right position if it is in contact
        with the ground object.
    */
    if( ground_obj && vertical_position >= 0 ) {
        /// \note if monster aren't in vertical position 0 but are in a floor
        if( vertical_position > 0 ) {
            _main_game_object->main_positionY = ground_obj->main_positionY -
            _main_game_object->main_height;
        }

        return true;
    }

    return false;
}

int MonsterAI::getLifePoints() {
    return life_points;
}

void MonsterAI::setLifePoints(int lifePoints) {
    life_points = lifePoints;
}

MonsterAI::~MonsterAI() {}
