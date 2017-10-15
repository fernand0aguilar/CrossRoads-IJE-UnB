/**
  \file gameobject.hpp
  this file contains headers of gameobject's member functions and states
*/

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <unordered_map>
#include <utility>
#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>

#include "sdl2core.hpp"
#include "components/component.hpp"

namespace engine {

    /// Class for managing the gameObject
    /**
    \class GameObject
    This class has member functions which control the state of the game object
    */

    class GameObject {

    public:
        enum class Layer {
            background,
            layer1,
            layer2,
            layer3
        };

        enum class State {
            enabled,
            disabled,
            invalid
        };

        /*
            Overloading the constructor, in case a gameobject without parameters is
            created, it will be treated with invalid.
        */

        GameObject(): GameObject( "", false, "", State::invalid ){}

        // Constructor

        GameObject( std::string name, bool collision = false,
                    std::string m_type = "", State state = State::enabled )
        : main_positionX( 0 ), main_positionY( 0 ), main_width( 0 ),
          main_height( 0 ), main_rotation( 0 ), m_collision( collision ),
        type( m_type ), m_layer( Layer::layer2 ), main_state( state ),
        main_name( name ){}

        virtual ~GameObject(){};

        /*
            Init on each component on a map of components, then for each element in
            a list of components.
        */

        virtual bool init();

        // Shutdown on each component

        virtual bool shutdown();

        /*
            Search, does a type cast and draw on screen a component, if its state
            is enabled.
        */

        virtual bool draw();

        void update();

        // Add the component on the end of a list of its type.

        void add_component( Component &component );

        void setState( State state );

        bool checkCollision( GameObject* object );

        // Function that looks for a component from its id.

        Component* get_component( std::string name );

        /*
            template<typename T> T *get_component() {
                return dynamic_cast<T *>( main_components[ std::type_index( typeid( T ) ) ].front() );
            }

            template<typename T> std::list<Component *> get_components();
        */

        inline std::string name() const {

            return main_name;

        }

        inline State state() const {

            return main_state;

        }

        inline void set_size( int width, int height ) {

            main_width = width;
            main_height = height;

        }

        inline void set_layer( Layer layer ) {

            m_layer = layer;

        }

        int main_positionX = 0;
        int main_positionY = 0;
        int main_width = 0;
        int main_height = 0;
        int main_rotation = 0;

        bool m_collision = false;

        std::string type = "";

        Layer m_layer;

      private:
          State main_state;
          std::string main_name;

        /*
            Unordered map that will store all components of the game object.
            The key will be defined by the type of the component, and the value
            will be a list of components of that type (Sprites, audios, etc.)
        */

          std::unordered_map <std::type_index, std::list<Component *> > main_components;
      };

}

#endif  // __GAMEOBJECT_H__
