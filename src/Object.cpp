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

    // Initialize the initial state.
    state.push_back(0.0); // x
    state.push_back(0.0); // y
    state.push_back(0.0); // v_x
    state.push_back(0.0); // v_y
    state.push_back(0.0); // j_x
    state.push_back(0.0); // j_y
    state.push_back(0.0); // heading
    state.push_back(0.0); // ang. vel.
    state.push_back(0.0); // ang. jerk

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



