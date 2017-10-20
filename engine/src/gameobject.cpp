
/**
  \file gameobject.cpp
  This file contains the implementations of the gameobject member functions
*/

#include "gameobject.hpp"
#include "components/image.hpp"
#include "components/animation.hpp"

using namespace engine;


/**
  Starts a new game object instance
  \return true if all components were succefully initialized
  \return false if some component receives a false initialization
*/

bool GameObject::init() {

    // INFO("Init game object " << m_name);

    for( auto id_componentlist: main_components ) {
        for ( auto component: id_componentlist.second ) {
            if( component->init() == true ) {
                // Do nothing
            }
            else {
                return false;
            }
        }


    }

    return true;

}

/**
  Shuts the game object down, shutting down the components
  \return true if the gameObject's components were succefully shutted down
  \return false if some component is enabled but also shutted.
*/

bool GameObject::shutdown() {

    Log::instance.info("Shutdown game object");

    // Iterating the component map, going through each type of component.

    for( auto id_componentList: main_components ) {

        // Iterating a list of components of the type found.

        for( auto component:id_componentList.second ) {
            if( component->state() != Component::State::enabled ||
                component->shutdown() == true ) {
                    // DO nothing
                }
            else {
                return false;
            }
        }

    }

    return true;

}

/**
  Draws the components of the gameObject
  \return true
*/

bool GameObject::draw() {
    draw_image_component();
    draw_animation();

    return true;
}
    // Searching in the map the components of type ImageComponent
void GameObject::draw_image_component() {
    for( auto component:
        main_components[ std::type_index( typeid( ImageComponent ) ) ] ) {

            /*
            If the component found with the enabled state, converts it to a
            component of the image and draws it on the screen.
            */

            if( component->state() == Component::State::enabled )
                ( dynamic_cast<ImageComponent *>( component ) )->draw();
            else {
                // Do nothing
            }

    }
}

void GameObject::draw_animation() {
    for( auto component:
        main_components[ std::type_index( typeid( Animation ) ) ] ) {

            /*
            If the component found with the state enabled, convert it to a
            component of the image and draw on the screen.
            */

            if( component->state() == Component::State::enabled )
                ( dynamic_cast<Animation *>( component ) )->draw();
            else {
                // Do nothing
            }

    }
}

    /*
        for(auto component: main_components[std::type_index(typeid(TextComponent))]){

        If the component found with the state enabled, convert it to a
        component of the image and draw on the screen.

        if(component->state() == Component::State::enabled)
        (dynamic_cast<TextComponent *>(component))->draw();
    }
    */

/**
  Adds a new component for the game object
  \param component the component object that will be added
*/

void GameObject::add_component( Component &component ) {

    Log::instance.info("Adding component: '" +
                       component.component_id +
                       "' to game object: '" +
                       main_name +
                       "'.");

    // Adds the component to the end of the list for the type of it.

    main_components[ std::type_index( typeid( component ) ) ]
                   .push_back( &component );

}

/**
  Updates the current state of the gameObject
*/

void GameObject::update() {

    for( auto id_componentlist: main_components ) {
        for( auto component: id_componentlist.second ) {
	        if( component->state() == Component::State::enabled) {
                component->update();
	        }
            else {
                // Do nothing
            }
        }
    }

}

/**
  Gets a component based on the string name
  \param name the name of the component
  \return returns a pointer to the component
  \return returns NULL if no component was found
*/

Component* GameObject::get_component( std::string name ) {

    for( auto id_componentList: main_components ) {

        // Iterating the list of components of the type found.

        for( auto component:id_componentList.second ) {
            if( component->component_id == name ) {
                return component;
            }
            else {
                // Do nothing
            }
        }
    }

    Log::instance.warning("Component '" +
                          name +
                          "' not found in '" +
                          main_name +
                          "' gameobject.");

    return NULL;

}

/**
  Sets the state of the GameObject
  \param state the state to be setted
*/

void GameObject::setState( State state ) {

    main_state = state;

}

/*
    bool GameObject::collision( GameObject* object ) {

    SDL_Rect obj1;
    SDL_Rect obj2;
    SDL_Rect result;

    obj1.x = main_positionX;
    obj1.y = main_positionY;
    obj1.w = main_width;
    obj1.h = main_height;
    obj2.x = object->main_positionX;
    obj2.y = object->main_positionY;
    obj2.w = object->main_width;
    obj2.h = object->main_height;

    return SDL_IntersectRect( &obj1, &obj2, &result);

    }

    GameObject* GameObject::checkCollision() {

    Game::instance.current_scene->

    }
*/
