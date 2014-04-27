#include "Camera.hpp"

namespace aos 
{

Camera::Camera(Object * ref_object)
{
    this->ref_object = ref_object;
}

Camera::~Camera(){ }

const double Camera::x() const
{
    return ref_object->state[Object::XIND];
}

const double Camera::y() const
{
    return ref_object->state[Object::YIND];
}

}

