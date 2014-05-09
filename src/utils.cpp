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

Object * circle(double radius, unsigned int sectors, double x, double y)
{
    Object *circ = new Object();

    circ->state[circ->XIND] = x;
    circ->state[circ->YIND] = y;

    //construct the verticies
    for(unsigned int i = 0; i < sectors; i++)
    {
        double theta = (double) i * 2.0 * M_PI / (double) sectors; 
        circ->add_vertex(radius * std::cos(theta), radius * std::sin(theta));
    }
    //construct the edges
    for(unsigned int idx1 = 0; idx1 < sectors; idx1++)
    {
        unsigned int idx2 = (idx1 + 1) % sectors;
        circ->add_edge(idx1, idx2);
    }

    circ->calculate_mass();
    return circ; 
}

std::vector< Object *> * seed_for_asteroids(unsigned int seed, unsigned int count, 
        double verts_max, double verts_min,
        double min_radius, double max_radius, double max_heading_vel)
{
    std::vector<Object *> * asteroids = new std::vector<Object *>();
    std::srand(std::time(NULL));

    for(unsigned int i = 0; i < count; i++)
    {   
        Object * asteroid = new Object();
        asteroid->state[asteroid->XIND] = 2 * max_radius * i;
        // Generate a random number of verticies between 5 and 10
        unsigned int verts = (verts_max - verts_min) * ((double) std::rand() / (double) RAND_MAX) + verts_min;

        double heading_vel = (double) std::rand() / (double) RAND_MAX * max_heading_vel;
        asteroid->state[asteroid->VHIND] = heading_vel;


        //std::cout << "verts: " << verts << std::endl;
        
        //  Now generate the points. 
        double theta_step_size = 2 * M_PI / (double) verts;
        std::vector< std::vector<double> > vertices;
        double ave_x = 0.0;
        double ave_y = 0.0;
        for(unsigned int j = 0; j < verts; j++)
        { 
            double r = (max_radius - min_radius ) * ((double) std::rand() / (double) RAND_MAX) + min_radius;
            double theta = theta_step_size * j;
             
            double x = r * std::cos(theta);
            double y = r * std::sin(theta);
            ave_x += x;
            ave_y += y;
            std::vector< double > vertex = {x, y};
            vertices.push_back(vertex);

            //asteroid->add_vertex(r * std::cos(theta), r * std::sin(theta));
            asteroid->add_edge(j, (j + 1) % verts);
        }
        ave_x /= (double) verts;
        ave_y /= (double) verts;
        //std::cout << "Ave X: " << ave_x << ", Ave Y: " << ave_y << std::endl;
        for(std::vector< std::vector< double > >::iterator it = vertices.begin(); it != vertices.end(); ++it)
        {
            asteroid->add_vertex((*it)[0] - ave_x, (*it)[1] - ave_y);
        }
        asteroid->calculate_mass();
        asteroids->push_back(asteroid);
    }

    return asteroids;
}

Systems * single_asteroid()
{


    Systems * universe = new Systems();

    Score * score = new Score(30, 30);
    
    Player * plyr = Player::default_player(); // player ship 
    Camera *cmra = new Camera(plyr); // focus the camera on the player
    plyr->camera = cmra;
    plyr->score = score;
    
    // Create 10 projectiles. 
    std::vector< Projectile *> *ammo = new std::vector< Projectile *>();
    for(int i = 0; i < 10; i++)
    {
        ammo->push_back((new Projectile()));
    }
    Weapon * laser = new Weapon(plyr, ammo); 
    laser->muzzle_velocity = 100;
    plyr->weapon = laser;

    Grid * grd = new Grid(200.0, 200.0); // Grid to follow the player's ship
    grd->horizontal_minor_spacing = 10;
    grd->vertical_minor_spacing = 10;
    grd->horizontal_major_spacing = 20;
    grd->vertical_major_spacing = 20;
    grd->camera = cmra;
    grd->obj_camera = cmra;

    Object * asteroid = circle(5, 4, 11.0, 0); //(*asteroids)[0]; 
    asteroid->state[Object::XIND] = 10.0;
    asteroid->camera = cmra;
 
    Systems *render = new Systems(); // Renders all of the objects.
    render->push_back(grd);
    render->push_back(plyr);
    render->push_back(asteroid);
    for(auto &prjtl: *ammo)
    {
        render->push_back(prjtl);
    }
    render->push_back(score);
    
    Systems *update = new Systems(); // Renders all of the objects.
    update->push_back(plyr);
    update->push_back(asteroid);
    for(auto &prjtl: *ammo)
    {
        update->push_back(prjtl);
    }

    Collision *cllsn = new Collision(plyr);
    cllsn->push_back(asteroid);
    for(auto &prjtl: *ammo)
    {
        cllsn->add_collider((Collidable *) prjtl);
    }

    universe->push_back(update);
    universe->push_back(render);
    universe->push_back(cllsn);
    
    return universe;
}

Systems * two_planets()
{
    Systems *gameverse = new Systems();

    Score * score = new Score(30, 30);

    Player * plyr = Player::default_player(); // player ship
    plyr->state[Object::XIND] = 120; 
    plyr->score = score;

    // TODO: Needing to create a player and then adding that player to the
    //      camera is confusing. Fix this later. 
    Camera *cmra = new Camera(plyr); // focus the camera on the player

    plyr->camera = cmra; // Set the camera for the player

    // Create 10 projectiles. 
    std::vector< Projectile *> *ammo = new std::vector< Projectile *>();
    for(int i = 0; i < 10; i++)
    {
        ammo->push_back((new Projectile()));
    }
    Weapon * laser = new Weapon(plyr, ammo); 
    laser->muzzle_velocity = 100.0;
    plyr->weapon = laser;
    
    Grid * grd = new Grid(200.0, 200.0); // Grid to follow the player's ship
    grd->horizontal_minor_spacing = 10;
    grd->vertical_minor_spacing = 10;
    grd->horizontal_major_spacing = 20;
    grd->vertical_major_spacing = 20;
    grd->camera = cmra;
    grd->obj_camera = cmra;
     
    // Create a bunch of random asteroids
    std::vector< Object *> *asteroids = seed_for_asteroids(12345, 200, 5, 10, 1.0, 10.0, 20.0); //FIXME: Get rid of vector pointer. 
    for(std::vector< Object *>::iterator it = asteroids->begin(); it != asteroids->end(); ++it)
    {
        (*it)->camera = cmra;
    }
     
    // Create a planet with gravity and add satellites to it (including the player.)
    Systems *gravity_systems = new Systems();
    Object * plnt1 = new Planet(300, 360, 0.0, 0.0);
    Object * plnt2 = new Planet(40, 360, 0.0, 0.0);
    plnt1->camera = cmra;
    plnt2->camera = cmra;
    GravityWell *planet_gravity = new GravityWell(plnt1);
    GravityWell *moon_gravity = new GravityWell(plnt2);

    planet_gravity->push_back_orbit(plnt2, 400, 0);
    planet_gravity->push_back_orbit(plyr, 310, 0);
    moon_gravity->push_back(plyr);
    for(auto &prjtl: *ammo)
    {
        planet_gravity->push_back(prjtl);
        moon_gravity->push_back(prjtl);
    }

    for(std::vector< Object *>::iterator it = asteroids->begin(); it != asteroids->end(); ++it)
    {
        planet_gravity->push_back_orbit(*it, 375, 45);
    }
    gravity_systems->push_back(planet_gravity);
    gravity_systems->push_back(moon_gravity);

    Systems *render = new Systems(); // Renders all of the objects.
    render->push_back(grd);
    for(std::vector< Object *>::iterator it = asteroids->begin(); it != asteroids->end(); ++it)
    {
        render->push_back(*it);
    }
    render->push_back(plnt1);
    render->push_back(plnt2);
    render->push_back(plyr);
    for(auto &prjtl: *ammo)
    {
        render->push_back(prjtl);
    }
    render->push_back(score);
    
    // Push items to the update system that calculates objects position. 
    Systems *update = new Systems(); // Updates all of the objects. 
    update->push_back(plnt2);
    update->push_back(plyr);
    for(std::vector< Object *>::iterator it = asteroids->begin(); it != asteroids->end(); ++it)
    {
        update->push_back(*it);
    }

    // Setup the collision detection system. 
    Collision *cllsn = new Collision(plyr);
    cllsn->push_back(plnt1);
    cllsn->push_back(plnt2);
    for(auto &prjtl: *ammo)
    {
        cllsn->add_collider((Collidable *) prjtl);
    }
    for(std::vector< Object *>::iterator it = asteroids->begin(); it != asteroids->end(); ++it)
    {
        cllsn->push_back(*it);
    }


    gameverse->push_back(gravity_systems); 
    gameverse->push_back(update);
    gameverse->push_back(cllsn);
    gameverse->push_back(render);

    delete asteroids;

    return gameverse;
}

} //END namespace aos
