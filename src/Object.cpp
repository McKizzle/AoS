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

inline void Object::render(Uint32 dt_ms, Uint32 time) 
{
    if(this->is_visible)
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
    double r = std::sqrt(x * x + y * y);
    this->bs_r = (r > this->bs_r) ? r : this->bs_r;

    std::vector< double > p = {x, y};
    this->vertices.push_back(p);
}

void Object::add_edge(unsigned int v1, unsigned int v2)
{
    this->edges.push_back(v1);
    this->edges.push_back(v2);
}

std::vector< double > Object::vertex_average()
{
    std::vector< double > center = {0.0, 0.0};
    
    double count = 0;
    for(std::vector< std::vector< double > >::iterator it = this->vertices.begin(); it != this->vertices.end(); ++it)
    {
        count++;
        center[0] += (*it)[0];
        center[1] += (*it)[1];
    }
    center[0] /= count;
    center[1] /= count;

    return center;
}

void Object::balance()
{
    std::vector< double > center = this->vertex_average();

    for(std::vector< std::vector< double > >::iterator it = this->vertices.begin(); it != this->vertices.end(); ++it)
    {
        (*it)[0] -= center[0];
        (*it)[1] -= center[1];
    }
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

inline void Object::swap_state(std::vector< double> * new_state) 
{
    std::lock_guard< std::mutex > lock(swap_state_lock);
    state.swap((*new_state));
}

inline std::vector< double > * Object::copy_state()
{
    std::lock_guard< std::mutex > lock(swap_state_lock);
    return new std::vector< double >(this->state);
}

inline void Object::get_rotation_matrix(double theta, gmtl::Matrix22d & R)
{
    R[0][0] =  std::cos(theta);
    R[0][1] = -std::sin(theta);
    R[1][0] =  std::sin(theta); 
    R[1][1] =  std::cos(theta);
}

inline bool Object::check_collision(std::vector< double > point)
{
    // Iterate through each triangle the the object and determine if the point is in the triangle. 
    std::vector< double > p0 = {0, 0};
    std::vector< double > t = {this->state[Object::XIND], this->state[Object::YIND]};

    gmtl::Vec2d A, T, P; 
    P.set(&point[0]);
    T.set(&t[0]);
    A.set(&p0[0]);

    A = A + T; // Translate the origin (no need to rotate)
    gmtl::Matrix22d R; // Rotation and translation matrix. 
    this->get_rotation_matrix(DEG2RAD(this->state[Object::HIND]), R);
    
    for(std::vector< unsigned int >::iterator it = this->edges.begin(); it != this->edges.end(); it += 2) 
    {
        gmtl::Vec2d v1; v1.set(&(this->vertices[*(it + 1)][0]));
        gmtl::Vec2d v2; v2.set(&(this->vertices[*it][0]));

        // Next rotate the points about the origin. 
        gmtl::Vec2d B, C;
        B = R * v1;
        C = R * v2;
        
        B = (B + T);
        C = (C + T);

        double u = 0, v = 0; 
        if(this->point_in_triangle(P, A, B, C, u, v))
        {  
            std::cout << "------------------------" << std::endl;
            std::cout << "i: " << *it << std::endl;
            std::cout << "i + 1: " << *(it + 1) << std::endl;
            std::cout << "(u, v): " << u << ", " << v << std::endl;
            std::cout << "A: " << A[0] << ", " << A[1] << std::endl;
            std::cout << "b: " << v1[0] << ", " << v1[1] << std::endl;
            std::cout << "B: " << B[0] << ", " << B[1] << std::endl;
            std::cout << "c: " << v2[0] << ", " << v2[1] << std::endl;
            std::cout << "C: " << C[0] << ", " << C[1] << std::endl;
            std::cout << "P: " << P[0] << ", " << P[1] << std::endl;
            std::cout << "T: " << T[0] << ", " << T[1] << std::endl;
            std::cout << "R: " << R << std::endl;
            std::cout << "theta:\n " << DEG2RAD(this->state[Object::HIND]) << std::endl;
            std::cout << "------------------------" << std::endl;
            return true && this->is_collidable;
        }
    }
    
    return false; // For now nothing can collide. 
}

inline void Object::get_vertices( std::vector< gmtl::Vec2d > & verts )
{ 
    std::vector< double > t = {this->state[Object::XIND], this->state[Object::YIND]};
    gmtl::Vec2d T;
    T.set(&t[0]);

    gmtl::Matrix22d R; // Rotation and translation matrix. 
    this->get_rotation_matrix(DEG2RAD(this->state[Object::HIND]), R);

    for(std::vector< std::vector< double > >::iterator it = this->vertices.begin(); it != this->vertices.end(); ++it)
    {
        gmtl::Vec2d v; v.set(&(*it)[0]); 

        gmtl::Vec2d V;
        V = R * v;
        V = V + T;
        verts.push_back(V);
    }
}

inline double Object::get_bounding_radius() 
{
    return this->bs_r;
}

inline void Object::get_center_coords( gmtl::Vec2d & cords ) 
{
    cords.set(&(this->state[Object::XIND]));
}

inline void Object::set_collision(Collidable * collider)
{
    // TODO: Act on the collision. 
    this->collider = collider; 


}

} // END namespace aos

