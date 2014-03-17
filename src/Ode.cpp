#include "Ode.hpp"

using namespace aos;

std::vector< double > * euler(std::vector< double > * (*f)(std::vector< double >, Uint32),
                                    std::vector< double > & x, Uint32 dt, Uint32 t) 
{ 
    double dt_sec = ((double) dt) / 1000.0;

    std::vector< double > * dxdt = (*f)(x, dt);
    for(std::vector< double >::iterator it = dxdt->begin(); it != dxdt->end(); ++it) 
    {
        *it = (*it) * dt_sec;
    }
        
    std::vector< double > * x_new = new std::vector< double >(x.size());
    for(std::vector< int >::size_type i = 0; i != x.size(); i++) 
    { 
        (*x_new)[i] = x[i] + (*dxdt)[i];
    }

    return x_new;
}

std::vector< double > * Integrator::integrate(std::vector< double > * (*f)(std::vector< double >, Uint32),
                                    std::vector< double > & x, Uint32 dt, Uint32 t)
{
    return new std::vector< double >();//this->integrator(f, x, dt, t);
}


