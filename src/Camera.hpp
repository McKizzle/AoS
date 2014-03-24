#include "includes.hpp"

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Object.hpp"
namespace aos
{
    class Camera {
        public:
            Object *ref_object; ///< The object of reference to keep track of.

            Camera(Object *ref_object);
            ~Camera();

            double x();
            double y();
    };
}

#endif
