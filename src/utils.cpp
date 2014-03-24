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

Object * grid(double width, double height, double step_size) 
{
    double x_max = width / 2.0;
    double x_min = -width / 2.0;
    double y_max = width / 2.0;
    double y_min = -width / 2.0;

    Object *ref_grid = new Object();

    
    // Create vertical lines from x_min to x_max
    //std::cout << " Iterating Vertical Lines Now " << std::endl;
    unsigned int index = 0;
    for(int i = x_min; i <= x_max; i += step_size)
    {
        double x1 = i;
        double y1 = y_min;
        double x2 = i;
        double y2 = y_max;

        std::vector< double > p1 = {x1, y1};
        std::vector< double > p2 = {x2, y2};

        ref_grid->vertices.push_back(p1);
        ref_grid->vertices.push_back(p2);
        ref_grid->edges.push_back(index);
        ref_grid->edges.push_back(index + 1);
        index += 2;

        //std::cout << "(" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ")" << std::endl;
    }

    // Create vertical lines from y_min to y_max
    //std::cout << " Iterating Horizontal Lines Now " << std::endl;
    for(int i = y_min; i <= y_max; i += step_size)
    { 
        double x1 = x_min;
        double y1 = i;
        double x2 = x_max;
        double y2 = i;

        std::vector< double > p1 = {x1, y1};
        std::vector< double > p2 = {x2, y2};

        ref_grid->vertices.push_back(p1);
        ref_grid->vertices.push_back(p2);
        ref_grid->edges.push_back(index);
        ref_grid->edges.push_back(index + 1);
        index += 2;

        //std::cout << "(" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ")" << std::endl;
    }
    
    float color_max = 255.0;
    ref_grid->color[0] = 64.0 / color_max;
    ref_grid->color[1] = 64.0 / color_max;
    ref_grid->color[2] = 64.0 / color_max;

    
    return ref_grid;
}

} //END namespace aos
