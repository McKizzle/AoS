#include "Object.hpp"

using namespace aos;
Object::Object()
{
    velocity.push_back(0.0);
    velocity.push_back(0.0);
    acceleration.push_back(0.0);
    acceleration.push_back(0.0);
    jerk.push_back(0.0);
    jerk.push_back(0.0);

    std::cout << "Object Constructed" << std::endl;
}

Object::~Object()
{
    std::cout << "Object Destructed" << std::endl; 
}

void Object::render(Uint32 dt_ms, Uint32 time) 
{
    glBegin(GL_LINES);  
        glColor3f(1.0f, 1.0f, 1.0f);
        for(std::vector< unsigned int>::iterator it = this->edges.begin(); it != edges.end(); ++it)
        {
            //std::cout << *it << std::endl; 
            //std::cout << "(" << vertices[*it][0] << ", " << vertices[*it][1] << ")" << std::endl;
            glVertex2f((GLfloat)vertices[*it][0], (GLfloat)vertices[*it][1]);

        }
    glEnd();
}

void Object::update(Uint32 dt_ms, Uint32 time) 
{
    std::cout << "Updated Object" << std::endl;
}



