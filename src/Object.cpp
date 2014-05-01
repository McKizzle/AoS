#include <iostream>
#include <cmath>

#include "Object.hpp"

namespace aos
{

Object::Object(): state(9, 0.0) 
{
    intgr = new Integrator();
}

Object::~Object()
{
    delete intgr;
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
    std::vector< double > * old_state = this->copy_state();
    std::vector< double > * new_state = intgr->integrate(this, old_state, dt_ms, time);
    
    (*new_state)[AXIND] = 0.0;
    (*new_state)[AYIND] = 0.0;
    (*new_state)[AHIND] = 0.0;

    this->swap_state(new_state);
    
    delete old_state;
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

void Object::calculate_mass()
{
    double new_mass = 0.0;
    for(std::vector< unsigned int >::iterator it = this->edges.begin() + 1; it != this->edges.end(); ++it) 
    {
        std::vector< double > p1 = this->vertices[*(it - 1)];
        std::vector< double > p2 = this->vertices[*it];
        std::vector< double > p0 = {0, 0};

        std::vector< double > dxdy01 = { p1[0] - p0[0], p1[1] - p0[1] };
        double e01 = std::sqrt( std::pow(dxdy01[0], 2) + std::pow(dxdy01[1], 2) );

        std::vector< double > dxdy12 = { p2[0] - p1[0], p2[1] - p1[1] };
        double e12 = std::sqrt( std::pow(dxdy12[0], 2) + std::pow(dxdy12[1], 2) );

        std::vector< double > dxdy20 = { p2[0] - p0[0], p2[1] - p0[1] };
        double e20 = std::sqrt( std::pow(dxdy20[0], 2) + std::pow(dxdy20[1], 2) );

        double lambda = acos( (std::pow(e12, 2) - std::pow(e01, 2) - std::pow(e20, 2)) / (-2.0 * e01 * e20) );

        double h = std::sqrt( std::pow(e01, 2) + std::pow( e01 * cos(lambda), 2) );
        double b = e12;

        double area = (1.0 / 2.0) * b * h;
        new_mass += area * this->density;
    }
    this->mass = new_mass;
}

unsigned int Object::push_back(System * subsystem)
{
    return 0;
}
void Object::pop_back(){ }

void Object::swap_state(std::vector< double> * new_state) 
{
    std::lock_guard< std::mutex > lock(swap_state_lock);
    state.swap((*new_state));
}

std::vector< double > * Object::copy_state()
{
    std::lock_guard< std::mutex > lock(swap_state_lock);
    return new std::vector< double >(this->state);
}

} // END namespace aos

