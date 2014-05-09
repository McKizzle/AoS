#include "Systems.hpp"

#include <iostream>

namespace aos 
{

Systems::Systems(){ } 

Systems::~Systems(){ } 

inline unsigned int Systems::push_back(System * subsystem)
{
    this->children.push_back(subsystem);
    return subsystem->sys_id;
}

inline System * Systems::pop_back()
{
    
    if(this->children.empty())
    {
        return nullptr;
    }
    else 
    { 
        System * sys = this->children.back();
        this->children.pop_back();
        return sys;
    }
    
}

inline System * Systems::erase(unsigned int id)
{
    // TODO: Build test cases for recursive erasing. 
    System *sys = nullptr;
    for(std::vector<System *>::iterator it = this->children.begin(); it != this->children.end(); ++it)
    {
        sys = (*it)->erase(id);
    }

    //Find the system. When found delete it.
    std::vector< System * >::iterator it = this->children.begin();
    for(unsigned int i = 0; i < this->children.size(); i++)
    {
        if(this->children[i]->sys_id == id)
        { 
            sys = this->children[i];
            this->children.erase(this->children.begin() + i);
        }
    }
    return sys;
}

//virtual Systems * clone()
//{
//    Systems * clone = new Systems();
//    clone.children(this->children);
//    return clone;
//}

inline void Systems::render(Uint32 dt_ms, Uint32 time) 
{
    for(std::vector<System *>::iterator it = this->children.begin(); it != this->children.end(); ++it)
    {
        (*it)->render(dt_ms, time);
    }
}

inline void Systems::update(Uint32 dt_ms, Uint32 time) 
{  
    for(std::vector<System *>::iterator it = this->children.begin(); it != this->children.end(); ++it)
    {
        (*it)->update(dt_ms, time);
    }
}

inline void Systems::send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time)
{
    for(std::vector<System *>::iterator it = this->children.begin(); it != this->children.end(); ++it)
    {
        (*it)->send_event(keyboardStates, dt, time);
    }
}
}
