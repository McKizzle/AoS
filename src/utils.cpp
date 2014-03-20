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

} //END namespace aos
