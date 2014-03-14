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
    position.push_back(0.0);
    position.push_back(0.0);

    std::cout << "Object Constructed" << std::endl;
}

Object::~Object()
{
    std::cout << "Object Destructed" << std::endl; 
}

void Object::render(Uint32 dt_ms, Uint32 time) 
{
    glPushMatrix();
    glTranslatef(position[0], position[1], 0.0);
    glRotatef(heading, 0, 0, 1);
    glBegin(GL_LINES);  
        glColor3f(1.0f, 1.0f, 1.0f);
        for(std::vector< unsigned int>::iterator it = this->edges.begin(); it != edges.end(); ++it)
        {
            //std::cout << *it << std::endl; 
            //std::cout << "(" << vertices[*it][0] << ", " << vertices[*it][1] << ")" << std::endl;
            glVertex2f((GLfloat)vertices[*it][0], (GLfloat)vertices[*it][1]);

        }
    glEnd();
    glPopMatrix();
}

void Object::update(Uint32 dt_ms, Uint32 time) 
{
    //std::cout << "Updated Object" << std::endl;
    position[0] += velocity[0];
    position[1] += velocity[1];
}



