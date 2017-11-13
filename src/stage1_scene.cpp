/**
    \file stage1_scene.cpp
    This file define methods content of the Stage1Scene class
*/

#include "stage1_scene.hpp"
#include "assert.h"

/**
    Initializes and keeps the scene of the first stage
*/
const int MAXIMUM_SCREEN_WIDTH = 800;
const int BULLET_POSITION_ITERATOR = 20;
const int TIME_STEP_ITERATOR = 500;
const int BACKGROUND_IMAGE_MAXIMUM = 2190;

// Number defined in a standard format during all code
const int SUCCESS = 1;

// This method is reponsable to log attempts of changing Stage1Scene attributes.
void valid_stage1_scene_animations(int validation_code, std::string method_name) {

    if (validation_code == SUCCESS) {
        Log::instance.info("Stage1 Scene attributes changed in method: ." 
        + method_name);
    }
}

void Stage1Scene::setTimeStep(unsigned int timeStep) {
    timestep = timeStep;
}

unsigned int Stage1Scene::getTimeStep() {
    return timestep;
}

/**
    Initializes the scene of the first stage and assigns behavior in his
    execution
*/
void Stage1Scene::game_logic() {


    /**
        Instances the game objects that make up the stage
    */
    background = &get_game_object("backgroundForest");
    bullet1 = &get_game_object("bullet");
    player = &get_game_object("player");
    player_controller = (dynamic_cast<Player*>(
                         player->get_component("player_logic")));
    ground_stage1 = &get_game_object("ground");
    background_image = (dynamic_cast<ImageComponent*>(
        background->get_component("backgroundForest")));
    go_arrow = &get_game_object("go_arrow");
    portal = &get_game_object("portal");
    fire_ball = &get_game_object("fireball");

    Log::instance.info("Instanced game objects of stage.");

    /**
        Instances the monster game objects that make up the stage
    */
    monster1 = &get_game_object("monster1");
    monster2 = &get_game_object("monster2");
    monster3 = &get_game_object("monster3");
    monster4 = &get_game_object("monster4");

    Log::instance.info("Instanced monsters of stage.");

    assert(ground_stage1 != NULL);

    /**
        Sets screen values to the initial stage
    */
    ground_stage1->main_positionY = 552;
    ground_stage1->main_positionX = 0;
    ground_stage1->main_width = 800;
    ground_stage1->main_height = 200;

    Log::instance.info("Setted screen values.");

    assert(background_image != NULL);
    assert(fire_ball != NULL);

    /**
        Checks if the position of the background image on the x-axis
        has come to an end.
    */
    if( background_image->image_measures->x > BACKGROUND_IMAGE_MAXIMUM ) {

        // This line disable the background image camera.
        background_image->enable_camera = false;

        valid_stage1_scene_animations(SUCCESS, "Stage1Scene::game_logic");
    }
    else {
        fire_ball->setState(GameObject::State::disabled);
    }

    assert(portal != NULL);
    assert(go_arrow != NULL);

    /**
        Disables background_image camera and go_arrow elements when the if conditionals
        occur.
    */
    if( ( portal->state() == GameObject::State::enabled &&
        portal->main_positionX + portal->main_width < MAXIMUM_SCREEN_WIDTH ) ||
        background_image->image_measures->x > BACKGROUND_IMAGE_MAXIMUM ||
        is_inside(monster1) ||
        is_inside(monster2) ||
        is_inside(monster3) ||
        is_inside(monster4) ) {
        
        // This line disable the background image camera. 
        background_image->enable_camera = false;
        go_arrow->setState(GameObject::State::disabled);

        valid_stage1_scene_animations(SUCCESS, "Stage1Scene::game_logic");        
    }
    else {

        // This line enable the background image camera.
        background_image->enable_camera = true;
        go_arrow->setState(GameObject::State::enabled);
    }

    bullet();

}

/**
    Is responsible for starting the bullet attack
*/
void Stage1Scene::bulletAttack() {

    if( bullet1->state() == GameObject::State::disabled ) {

        bullet_direction_1 = player_controller->get_direction_boby_side();
        
        // This line assigns horizontal position to bullet.
        bullet1->main_positionX = player->main_positionX +
                                  player->main_width;

        // This line assigns vertical position to bullet.
        bullet1->main_positionY = player->main_positionY;

        valid_stage1_scene_animations(SUCCESS, "Stage1Scene::bulletAttack");
    }
    else {
        // Do nothing
    }

    setTimeStep(Game::instance.timer->getTicks() + TIME_STEP_ITERATOR);
    bullet1->setState(GameObject::State::enabled);
}

/**
    Moves the bullet in the direction selected
*/
void Stage1Scene::increaseBulletPosition() {
    if( bullet1->state() == GameObject::State::enabled ) {
        if( bullet_direction_1 ) {

            // This line increases the bullet position
            bullet1->main_positionX += BULLET_POSITION_ITERATOR;
        }
        else {

            // This line decrements the bullet position
            bullet1->main_positionX -= BULLET_POSITION_ITERATOR;
        }

        valid_stage1_scene_animations(SUCCESS, "Stage1Scene::increaseBulletPosition");
    }
    else {
        Log::instance.info("bullet1 is disable.");
    }

}

/**
    Disable bullet attack
*/
void Stage1Scene::disableBullet() {
    if( bullet1->main_positionX > MAXIMUM_SCREEN_WIDTH || bullet1->main_positionX < 0 ) {
        bullet1->setState(GameObject::State::disabled);

        valid_stage1_scene_animations(SUCCESS, "Stage1Scene::disableBullet");
    }
    else {
        // Do nothing
    }
}

/**
    Detects and define the position of the player's bullet(ranged attack)
    on the scene
*/
void Stage1Scene::bullet() {

    assert(player_controller != NULL);

    /**
        Check is player attack is valid in time step.
    */
    if( player_controller->get_is_attacking_ranged() &&
        getTimeStep() < Game::instance.timer->getTicks() ) {

        bulletAttack();

        valid_stage1_scene_animations(SUCCESS, "Stage1Scene::bullet");
    }
    else {
        // Do nothing
    }

    /**
        \note this line goes into a function that is responsible for increase the vertical position of the bullet
    */
    increaseBulletPosition();

    /**
        \note this line goes into a function that is responsible for changing the state of the bullet to 'disabled'
    */
    disableBullet();

}

/**
    Check if a object is inside the scene
    \param object
    \parblock
        Is a input parameter that represents an object of the game(!=NULL)
    \endparblock
    \return true is inside
    \return false isn't inside
*/
bool Stage1Scene::is_inside( GameObject* object ) {

    assert(object != NULL);

    /**
        \note in the condition of this line the object is tested beyond the limits of the screen
    */
    if( object->state() == GameObject::State::enabled &&
      ( object->main_positionX > 0 || object->main_positionX +
                                      object->main_width < MAXIMUM_SCREEN_WIDTH ) ) {

        return true;

    }
    else {
        return false;
    }
}

Stage1Scene::~Stage1Scene(){

}
