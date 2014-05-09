#include "AsteroidsOnSteroids.hpp"

namespace aos
{

AsteroidsOnSteroids::AsteroidsOnSteroids(
        Player * player, std::vector< System * > * systems, 
        Planet * planet, Planet * moon) 
{ 
    std::cout << "Generating AoS Game" << std::endl;
    this->universe = new Systems();
    this->gravity_systems = new Systems();
    this->collision_systems = new Systems();
    
    // Initialize components for the player. 
    Score * score = new Score(30, 30); 
    Camera *cmra = new Camera(player);
    player->camera = cmra;
    player->score = score;
    // Create a weapon for the player
    Weapon * laser = new Weapon(player); 
    player->weapon = laser;

    // Initialize the grid.
    Grid * grd = new Grid(200.0, 200.0);
    grd->horizontal_minor_spacing = 10;
    grd->vertical_minor_spacing = 10;
    grd->horizontal_major_spacing = 20;
    grd->vertical_major_spacing = 20;
    grd->camera = cmra; // this is the game camera location. 
    grd->obj_camera = cmra; // set this to another camera if you wish to have a grid follow another object. 
    
    Object * asteroid = circle(5, 4, 11.0, 0);
    asteroid->state[Object::XIND] = 10.0;
    asteroid->camera = cmra;

    Systems *render = new Systems(); // Renders all of the objects.
    render->push_back(grd);
    render->push_back(player);
    render->push_back(asteroid);
    render->push_back(score);
    
    Systems * update = new Systems(); // Renders all of the objects.
    update->push_back(player);
    update->push_back(asteroid);

    Collision * cllsn = new Collision(player);
    cllsn->push_back(asteroid);
    this->clone_template = cllsn;

    this->universe->push_back(update);
    this->universe->push_back(render);
    this->universe->push_back(cllsn);

    this->render_systems = render;
    this->update_systems = update;
    
    // keep track of all of this so that we do not have mem leaks. 
    this->system_tracker.push_back(laser);
    this->system_tracker.push_back(player);
    this->system_tracker.push_back(grd);
    this->system_tracker.push_back(asteroid);
    this->system_tracker.push_back(render);
    this->system_tracker.push_back(update);
    this->system_tracker.push_back(cllsn);

    for(auto &sys : this->system_tracker)
    {
        sys->systems_manager = this;
    }
}

AsteroidsOnSteroids::~AsteroidsOnSteroids()
{
    delete this->universe;

    while(!system_tracker.empty())
    {
        System * sys = this->system_tracker.back();
        this->system_tracker.pop_back();
        delete sys;
    }
}

unsigned int AsteroidsOnSteroids::push_back(System * subsystem)
{
    // Assumes that a projectile is being pushed back. 
    // Build a new collision system for the projectile that was pushed back. 
    Collision *projectile_collision = clone_template->clone();
    projectile_collision->collider = (Collidable *)subsystem; 
    this->collision_systems->push_back(projectile_collision);
    this->system_tracker.push_back(projectile_collision);
    this->render_systems->push_back(subsystem);
    this->update_systems->push_back(subsystem);
    
    return ((System *)projectile_collision)->sys_id;
}

void AsteroidsOnSteroids::projectile_collision(System * projectile)
{
    // Locate the projectile system 
    unsigned int to_delete = 0;
    for(std::vector<System *>::iterator it = this->collision_systems->children.begin();
            it != this->collision_systems->children.end(); ++it)
    {
        Collision * cs = (Collision *)(*it);
        System * clldr = (System *)(cs->collider);
        if(clldr->sys_id == projectile->sys_id)
        {
            to_delete = ((System *)cs)->sys_id;
            break;
        }
    }
    // delelete the associated Collision system. 
    System *sys = this->universe->erase(to_delete);
    // Remove the projectile from the universe. 
    this->universe->erase(projectile->sys_id);
   
    // Remove the projectile from the tracked objects before delting it. 
    unsigned int id = projectile->sys_id;
    for(unsigned int i = 0; i < this->system_tracker.size(); i++)
    { 
        System * sys2chk = this->system_tracker[i]; // derefrence the vector pointer. 
        if(sys2chk->sys_id == id)
        { 
            this->system_tracker.erase(this->system_tracker.begin() + i);
        }
    }

    delete projectile;
}

void AsteroidsOnSteroids::render(Uint32 dt_ms, Uint32 time)
{
    this->universe->render(dt_ms, time);
}

void AsteroidsOnSteroids::update(Uint32 dt_ms, Uint32 time)
{
    this->universe->update(dt_ms, time);
}

void AsteroidsOnSteroids::send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time) 
{
    this->universe->send_event(keyboardStates, dt, time);
}

}
