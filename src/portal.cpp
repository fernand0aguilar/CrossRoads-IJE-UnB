/**
    \file portal.cpp
    This file implements the portal class
*/
#include <portal.hpp>

Portal::~Portal(){}

/**
    This method initiates the portal in the game scene
    \return return a true value that make the portal active
*/

bool Portal::init() {

    /*
        _main_game_object->main_positionX = 00;
        _main_game_object->main_positionY = 00;
    */

    monster_number_iterator = 0;
    time_between_monsters = 0;
    monsters_out_of_portal = 0;

    return true;

}

/**
    This method is responsible for updating portal positions in the game for
    monsters to appear
*/

void Portal::update() {

    if( time_between_monsters < Game::instance.timer->getTicks() &&
        m_monsters[monster_number_iterator]->state() == GameObject::State::disabled &&
        _main_game_object->main_positionX > 0 &&
        _main_game_object->main_positionX + _main_game_object->main_width < 800
      ) {

        m_monsters[monster_number_iterator]->main_positionX = _main_game_object->main_positionX;
        m_monsters[monster_number_iterator]->main_positionY = _main_game_object->main_positionY;
        m_monsters[monster_number_iterator]->setState(GameObject::State::enabled);

        monsters_out_of_portal++;

        time_between_monsters = Game::instance.timer->getTicks() + 3000;
    }

    monster_number_iterator = (monster_number_iterator + 1) % m_monsters.size();

    if( monster_number_iterator <= 5 && m_background->image_measures->x == 0 ) {
        m_portal_pos->m_horizontal_starting_position = 650;
    }

    if( monster_number_iterator < 10 && monster_number_iterator > 5 ) {
        m_portal_pos->m_horizontal_starting_position = 1200;
    }

    if( monster_number_iterator < 20 && monster_number_iterator > 10 ) {
        m_portal_pos->m_horizontal_starting_position = 1600;
    }

    if( monsters_out_of_portal > 20 ) {
        _main_game_object->setState(GameObject::State::disabled);
    }

}

//so chamar na main

/**
    This method is responsible for add a monster no game through the portal
    @param monster specifies the monster that enters the game
*/
void Portal::add_monster( GameObject* monster ){

    monster->setState( GameObject::State::disabled );
    m_monsters.push_back( monster );

}
