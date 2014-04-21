#include "Ode.hpp"

namespace aos
{

std::vector< double > * euler(
    Integratable * I,
    std::vector< double > * x, Uint32 dt, Uint32 t) 
{  
    double dt_sec = ((double) dt) / 1000.0;

    std::vector< double >* dxdt = I->system(t, x);
    for(std::vector< double >::iterator it = dxdt->begin(); it != dxdt->end(); ++it) 
    {
        *it = (*it) * dt_sec;
    }
        
    std::vector< double > * x_new = new std::vector< double >(x->size(), 0.0);
    for(std::vector< int >::size_type i = 0; i != x->size(); i++) 
    { 
        (*x_new)[i] = (*x)[i] + (*dxdt)[i];
    } 
    delete dxdt;
    return x_new;
}

std::vector< double > * euler_richardson( Integratable* I,
    std::vector< double > * x, Uint32 dt, Uint32 t)
{    
    //def euler_richardson(f, x, dt, t):
    //    return x + f(x + f(x, t) * dt / 2.0, t + dt / 2.0) * dt

    double dt_sec = ((double) dt) / 1000.0;
    
    /// First Calculate: x_1o2 = x + f(x, t) * dt / 2.0
    std::vector< double >* dxdt_0 = I->system(t, x); 
    for(std::vector< double >::iterator it = dxdt_0->begin(); it != dxdt_0->end(); ++it) 
    {
        *it = (*it) * dt_sec / 2.0;
    }
    std::vector< double > * x_new0 = new std::vector< double >(x->size(), 0.0);
    for(std::vector< int >::size_type i = 0; i != x->size(); i++) 
    { 
        (*x_new0)[i] = (*x)[i] + (*dxdt_0)[i];
    } 

    /// Second Calculate
    Uint32 t_new = (Uint32)((double) t + dt_sec / 2.0);
    std::vector< double >* dxdt = I->system(t_new, x_new0);
    for(std::vector< double >::iterator it = dxdt->begin(); it != dxdt->end(); ++it) 
    {
        *it = (*it) * dt_sec;
    }
        
    std::vector< double > * x_new = new std::vector< double >(x->size(), 0.0);
    for(std::vector< int >::size_type i = 0; i != x->size(); i++) 
    { 
        (*x_new)[i] = (*x)[i] + (*dxdt)[i];
    } 
    delete dxdt_0;
    delete dxdt;
    delete x_new0;

    return x_new;
}

Integrator::Integrator(){}

std::vector< double > * Integrator::integrate(
    Integratable * I, 
    std::vector< double > * x, Uint32 dt, Uint32 t)
{
    return this->integrator(I, x, dt, t);
}

} // END namespace aos
