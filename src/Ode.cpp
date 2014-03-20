#include "Ode.hpp"

namespace aos
{

std::vector< double > * euler(
    Integratable * I,
    std::vector< double > * x, Uint32 dt, Uint32 t) 
{ 
    std::cout << "aos::euler" << std::endl;
    return I->system(t, x);
    
    //double dt_sec = ((double) dt) / 1000.0;

    //std::vector< double > * dxdt = (*f)(x, dt);
    //for(std::vector< double >::iterator it = dxdt->begin(); it != dxdt->end(); ++it) 
    //{
    //    *it = (*it) * dt_sec;
    //}
    //    
    //std::vector< double > * x_new = new std::vector< double >(x.size());
    //for(std::vector< int >::size_type i = 0; i != x.size(); i++) 
    //{ 
    //    (*x_new)[i] = x[i] + (*dxdt)[i];
    //}

    //return new std::vector< double >();//x_new;
}

Integrator::Integrator(){}

std::vector< double > * Integrator::integrate(
    Integratable * I, 
    std::vector< double > * x, Uint32 dt, Uint32 t)
{
    std::cout << "Integrator::integrate" << std::endl;
    return this->integrator(I, x, dt, t);
}

} // END namespace aos
