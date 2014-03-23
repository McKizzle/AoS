#include "Object.hpp"

namespace aos
{

Object::Object(): state(9, 0.0) 
{
    intgr = new Integrator();
    std::cout << "Object::Object" << std::endl;
}

Object::~Object()
{
    delete intgr;
    std::cout << "Object::~Object" << std::endl; 
}

void Object::render(Uint32 dt_ms, Uint32 time) 
{
    glPushMatrix();
    glTranslatef(state[XIND], state[YIND], 0.0);
    glRotatef(state[HIND], 0, 0, 1);
    glBegin(GL_LINES);  
        glColor3f(1.0f, 1.0f, 1.0f);
        for(std::vector< unsigned int>::iterator it = this->edges.begin(); it != edges.end(); ++it)
        {
            glVertex2f((GLfloat)vertices[*it][0], (GLfloat)vertices[*it][1]);
        }
    glEnd();
    glPopMatrix();
}

void Object::update(Uint32 dt_ms, Uint32 time) {}
void Object::send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time){}
std::vector< double > * Object::system(Uint32 t, std::vector< double > * x)
{
    return new std::vector< double >();
}

} // END namespace aos

