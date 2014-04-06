#include <vector>

#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "System.hpp"

namespace aos
{
    class CompositeSystem: public System
    {
        public:
            vector<System *> children; ///< The children of the system.  

            CompositeSystem();
            virtual ~CompositeSystem();
            virtual unsigned int push_back(System * subsystem); ///< Adds a subsystem. Return assigned ID. 
            virtual void pop_back(); ///< Removes a subsystem. 
    };
}

#endif
