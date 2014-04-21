#include <SDL2/SDL.h>
#include <vector>

#ifndef ODE_HPP
#define ODE_HPP

namespace aos 
{
    
    /// \Class Integratable Ode.hpp
    /// \brief Integratable objects. 
    ///
    /// Objects that need to be passed into an integrator must abide to the Integratable 
    /// interface. 
    class Integratable {
        public:
            virtual std::vector< double > * system(Uint32 t, std::vector< double > * x) = 0;
    };
    
    /// The classic euler integrator. 
    /// f(x, t) * dt + x
    ///
    /// \param [in] An integrable object. 
    /// \param [in] The state of the object. 
    /// \param [in] The timestep.
    /// \param [in] The time. 
    /// 
    /// \return The updated state of the object as a vector pointer. 
    std::vector< double > * euler( Integratable* I,
        std::vector< double > * x, Uint32 dt, Uint32 t
    );

    /// The Euler-Richardson Integrator. An improvement over euler's classic 
    /// integrator. 
    /// x + f(x + f(x, t) * dt / 2.0, t + dt / 2.0) * dt
    ///
    /// \param [in] An integrable object. 
    /// \param [in] The state of the object. 
    /// \param [in] The timestep.
    /// \param [in] The time. 
    /// 
    /// \return The updated state of the object as a vector pointer. 
    std::vector< double > * euler_richardson( Integratable* I,
        std::vector< double > * x, Uint32 dt, Uint32 t
    );
    
    /// \Class Integrator Ode.hpp
    /// \brief manage integration functions. 
    ///
    /// Allow control of which integration functions to use. 
    class Integrator {
        public:
            Integrator();

            /// Integrates an object. 
            ///
            /// \param [in] The integratable object. 
            /// \param [in] The state of the integratble object. 
            /// \param [in] The timestep. 
            /// \param [in] The time.
            ///
            /// \param The new state as a vector. 
            std::vector< double > * integrate( Integratable* I,
                std::vector< double > * x, Uint32 dt, Uint32 t
            );

            std::vector< double > * (*integrator)( Integratable* I,
                std::vector< double > * x, Uint32 dt, Uint32 t) = euler_richardson; ///< Store a integrator function. 
    };

}


#endif
