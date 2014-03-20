#include "includes.hpp"

#include <SDL2/SDL.h>
//#include <functional>

#ifndef ODE_HPP
#define ODE_HPP

namespace aos 
{ 
    class Integratable {
        public:
            virtual std::vector< double > * system(Uint32 t, std::vector< double > * x) = 0;
    };

    std::vector< double > * euler( Integratable* I,
        std::vector< double > * x, Uint32 dt, Uint32 t
    );

    class Integrator {
        public:
            Integrator();
            std::vector< double > * (*integrator)( Integratable* I,
                std::vector< double > * x, Uint32 dt, Uint32 t) = euler;  ///< Stores a pointer to the default ODE integrator function (defaults to euler)   
             
            std::vector< double > * integrate( Integratable* I,
                std::vector< double > * x, Uint32 dt, Uint32 t
            );
    };

}


#endif
