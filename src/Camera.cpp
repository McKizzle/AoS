#include "Camera.hpp"

namespace aos 
{

Camera::Camera(Object * ref_object)
{
    this->ref_object = ref_object;
}

Camera::~Camera(){ }

double Camera::x()
{
    return ref_object->state[Object::XIND];
}

double Camera::y()
{
    return ref_object->state[Object::YIND];
}

}

