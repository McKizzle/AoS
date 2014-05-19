#ifdef __APPLE__
#include <GLUT/glut.h>
#elif __linux__
#include <GL/glut.h>
#endif

#include <iostream>
#include <sstream>

#ifndef SCORE_HPP
#define SCORE_HPP

#include "System.hpp"
#include "Camera.hpp"

namespace aos
{
    class Score: public System
    {
        public:
            double x = 0.0, y = 0.0;
            double score = 0.0;
            double scale = 0.025;
            std::string display_text = "Score:  ";
            Camera *camera = nullptr; ///< Used to render the object position relative to the camera. 
            bool is_visible = true;
             
            /// Initializes a scorebox at a fixed in the universe. 
            //Score(double x, double y);
            /// Initializes a scorebox at a fixed positoin RELATIVE to the camera. 
            Score(double x, double y);
            ~Score();
             
            void incrementScore(double value); 
            void setScore(double value);
            void resetScore();

            /// This object will only render itself. 
            // TODO: Implement render method. 
            void render(Uint32 dt_ms, Uint32 time); ///< Inherited from Renderable 
    };
}

#endif
