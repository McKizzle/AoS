#ifndef GRID_HPP
#define GRID_HPP

#include "Object.hpp"

namespace aos
{
    class Grid: public Object
    {
        public:
            Grid(double width, double height);
            ~Grid();

            Camera * obj_camera; ///< The Object the grid will 'follow'

            virtual void render(Uint32 dt_ms, Uint32 time); ///< Inherited from Renderable
            virtual void update(Uint32 dt_ms, Uint32 time); ///< Inherited from Updatable
            
            double width = 500;
            double height = 500;
                
            std::vector< float > & major_color = color; /// Simply use the color for the major gridlines. 
            std::vector< float > minor_color = {1.0, 1.0, 1.0, 1.0}; ///< The color of the object. 

            double horizontal_major_spacing = 10;
            double horizontal_minor_spacing = 5;
            double vertical_major_spacing = 10;
            double vertical_minor_spacing = 5;
            
    };
}

#endif

