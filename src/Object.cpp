#include "Object.hpp"
#include "includes.hpp"

namespace aos {
    int Object::render() 
    {
        std::cout << "Rendered Object" << std::endl;
        return 0;
    }

    int Object::update(int dt_ms) 
    {
        std::cout << "Updated Object" << std::endl;
        return 0;
    }
}

