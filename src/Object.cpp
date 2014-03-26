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
    glTranslatef(state[XIND] - camera->x(), state[YIND] - camera->y(), 0.0);
    glRotatef(state[HIND], 0, 0, 1);
    glBegin(GL_LINES);  
        glColor3f(color[0], color[1], color[2]);
        for(std::vector< unsigned int>::iterator it = this->edges.begin(); it != edges.end(); ++it)
        {
            glVertex2f((GLfloat)vertices[*it][0], (GLfloat)vertices[*it][1]);
        }
    glEnd();
    glPopMatrix();
}

void Object::update(Uint32 dt_ms, Uint32 time)
{
    std::vector< double > * new_state = intgr->integrate(this, &state, dt_ms, time);
    state.swap(*new_state);
    delete new_state;
}

std::vector< double > * Object::system(Uint32 t, std::vector< double > * x)
{
    std::vector< double > * dxdt = new std::vector< double >(x->size(), 0.0);

    (*dxdt)[XIND]  = (*x)[VXIND];
    (*dxdt)[YIND]  = (*x)[VYIND];
    (*dxdt)[VXIND] = (*x)[AXIND];
    (*dxdt)[VYIND] = (*x)[AYIND];
    (*dxdt)[AXIND] = 0.0;  
    (*dxdt)[AYIND] = 0.0;  
    (*dxdt)[HIND]  = (*x)[VHIND];
    (*dxdt)[VHIND] = 0.0; 
    (*dxdt)[AHIND] = 0.0; 
 
    return dxdt;
}

void Object::send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time){}

void Object::add_vertex(double x, double y)
{
    double r = std::sqrt(std::pow(x, 2.0) + std::pow(x, 2.0));
    bs_r = (r > bs_r) ? r : bs_r;

    std::vector< double > p = {x, y};
    vertices.push_back(p);
}

void Object::add_edge(unsigned int v1, unsigned int v2)
{
    edges.push_back(v1);
    edges.push_back(v2);
}

} // END namespace aos

