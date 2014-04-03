#include "utils.hpp"

namespace aos
{

void dvect_dump(const std::ostream &os, const std::vector< double > &todump)
{
    std::cout << "(";
    for(std::vector< double >::const_iterator cit = todump.begin(); cit != todump.end() - 1; ++cit)
    {
        std::cout << *cit << ", "; 
    }
    std::vector< double >::const_iterator cit = todump.end() - 1;
    std::cout << *cit << ")" << std::endl;
}

Object * circle(double radius, unsigned int sectors, double x, double y)
{
    Object *circ = new Object();

    circ->state[circ->XIND] = x;
    circ->state[circ->YIND] = y;

    //construct the verticies
    for(unsigned int i = 0; i < sectors; i++)
    {
        double theta = (double) i * 2.0 * M_PI / (double) sectors; 
        circ->add_vertex(radius * std::cos(theta), radius * std::sin(theta));
    }
    //construct the edges
    for(unsigned int idx1 = 0; idx1 < sectors; idx1++)
    {
        unsigned int idx2 = (idx1 + 1) % sectors;
        circ->add_edge(idx1, idx2);
    }

    return circ; 
}

std::vector< Object *> * seed_for_asteroids(unsigned int seed, unsigned int count, 
        double verts_max, double verts_min,
        double max_radius, double max_heading_vel)
{
    std::vector<Object *> * asteroids = new std::vector<Object *>();
    std::srand(seed);

    for(unsigned int i = 0; i < count; i++)
    {   
        Object * asteroid = new Object();
        asteroid->state[asteroid->XIND] = 2 * max_radius * i;
        // Generate a random number of verticies between 5 and 10
        unsigned int verts = (verts_max - verts_min) * ((double) std::rand() / (double) RAND_MAX) + verts_min;

        double heading_vel = (double) std::rand() / (double) RAND_MAX * max_heading_vel;
        asteroid->state[asteroid->VHIND] = heading_vel;


        std::cout << "verts: " << verts << std::endl;
        
        //  Now generate the points. 
        double theta_step_size = 2 * M_PI / (double) verts;
        std::vector< std::vector<double> > vertices;
        double ave_x = 0.0;
        double ave_y = 0.0;
        for(unsigned int j = 0; j < verts; j++)
        { 
            double r = ((double) std::rand() / (double) RAND_MAX) * max_radius;
            double theta = theta_step_size * j;
             
            double x = r * std::cos(theta);
            double y = r * std::sin(theta);
            ave_x += x;
            ave_y += y;
            std::vector< double > vertex = {x, y};
            vertices.push_back(vertex);

            //asteroid->add_vertex(r * std::cos(theta), r * std::sin(theta));
            asteroid->add_edge(j, (j + 1) % verts);
        }
        ave_x /= (double) verts;
        ave_y /= (double) verts;
        std::cout << "Ave X: " << ave_x << ", Ave Y: " << ave_y << std::endl;
        for(std::vector< std::vector< double > >::iterator it = vertices.begin(); it != vertices.end(); ++it)
        {
            asteroid->add_vertex((*it)[0] - ave_x, (*it)[1] - ave_y);
        }
        asteroids->push_back(asteroid);
    }

    return asteroids;
}

} //END namespace aos
