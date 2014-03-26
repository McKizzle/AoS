#include "includes.hpp"

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Object.hpp"
namespace aos
{
    /// \Class Camera Camera.hpp
    /// \brief Represents a camera object in the game. 
    ///
    /// The camera object keeps track of a game object. This class
    /// for now has one primary goal. Allow the rendering of objects in 
    /// openGL such the viewport focuses on teh player at all times. 
    class Camera {
        public:
            Object *ref_object; ///< The object of reference to keep track of.

            /// Create a camera and set the object to monitor. 
            /// 
            /// \param [in] the object to monitor. 
            Camera(Object *ref_object);
            ~Camera();

            double x(); ///< Get the x coordinates of the camera. 
            double y(); ///< Get the y coordinates of the camera. 
    };
}

#endif
