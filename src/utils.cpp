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
    for(int i = x_min; i < x_max; i += step_size)
    {
        double x1 = i;
        double y1 = y_min;
        double x2 = i;
        double y2 = y_max;

        std::cout << "(" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ")" << std::endl;
    }

    // Create vertical lines from y_min to y_max
    for(int i = y_min; i < y_max; i += step_size)
    {
        
    }


    
    return new Object();
}

} //END namespace aos
