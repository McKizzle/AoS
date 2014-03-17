#include "Player.hpp"

using namespace aos;

Player::Player() 
{ 
    
}

Player::~Player() 
{
    
}

void Player::update(Uint32 dt_ms, Uint32 time) 
{
    double dt = (double) dt_ms / 1000.0;

    //std::cout << "Updated Object" << std::endl; 
    //position[0] = velocity[0] * cos(M_PI / 180.0 * heading) * dt + position[0];
    //position[1] = velocity[1] * sin(M_PI / 180.0 * heading) * dt + position[1];
    position[0] += dt * velocity[0];
    position[1] += dt *velocity[1];
    
    heading += angular_vel;
    if(angular_vel >= 0)
    {
        angular_vel = (angular_vel <= 0.0) ? 0.0 : angular_vel - heading_jerk;
    } 
    else
    {
        angular_vel = (angular_vel >= 0.0) ? 0.0 : angular_vel + heading_jerk;
    }
}

//void Player::render(Uint32 dt, Uint32 time)
//{ 
//    glColor3f(1.0f, 1.0f, 1.0f);
//    glBegin(GL_QUADS); // Start drawing a quad primitive  
//
//    glVertex3f(-1.0f, -1.0f, 0.0f); // The bottom left corner  
//    glVertex3f(-1.0f, 1.0f, 0.0f); // The top left corner  
//    glVertex3f(1.0f, 1.0f, 0.0f); // The top right corner  
//    glVertex3f(1.0f, -1.0f, 0.0f); // The bottom right corner  
//
//    glEnd();  
//}


void Player::send_event(const Uint8 * keyboardStates, Uint32 dt, Uint32 time) 
{
    double d = 360.0;
    double h = 100.0;
    if(keyboardStates[SDL_SCANCODE_A])
    {
        //std::cout << "Left" << std::endl;
        angular_vel = -d/h;
        //std::cout << "V_x: " << velocity[0] << std::endl;
    }
    if(keyboardStates[SDL_SCANCODE_W])
    {
        //std::cout << "Forward" << std::endl;
        velocity[1] += 0.1;
        //std::cout << "V_y: " << velocity[1] << std::endl;
    }
    if(keyboardStates[SDL_SCANCODE_D])
    { 
        //std::cout << "Right" << std::endl;
        angular_vel = d/h;
        //std::cout << "V_x: " << velocity[0] << std::endl;
    }
    if(keyboardStates[SDL_SCANCODE_S])
    {
        //std::cout << "Backwards" << std::endl;
        velocity[1] -= 0.1;
        //std::cout << "V_y: " << velocity[1] << std::endl;
    }
    if(keyboardStates[SDL_SCANCODE_SPACE]) 
    { 
        std::cout << "Fire" << std::endl;
    }
}


void Player::test_vectors() 
{
    std::cout << "VERTICIES: " << std::endl;
    for(std::vector< std::vector<double> >::iterator it = vertices.begin(); it != vertices.end(); ++it) 
    {
        std::cout << "(";
        for(std::vector<double>::iterator jt = it->begin(); jt != it->end(); ++jt) 
        {
            std::cout << *jt << " ,";
        }
        std::cout << ")" << std::endl;
    }
    std::cout << "EDGES: " << std::endl;
    for(std::vector< unsigned int >::iterator it = edges.begin(); it != edges.end(); it += 2) {
        std::vector< unsigned int >::iterator itn = it + 1;
        std::cout << "(" << *it << ", " << *itn << ")" << std::endl;
    }
    exit(0);
}

Player * Player::default_player()
{ 
    std::vector< double > p0;// = new std::vector< double >();
    p0.push_back(1.0);
    p0.push_back(0.0);
    std::vector< double > p1;// = new std::vector< double >(); 
    double theta = 2.0 * M_PI / 3.0; //one-third of 2pi
    p1.push_back(std::cos(theta));
    p1.push_back(std::sin(theta));
    std::vector< double > p2;// = new std::vector< double >();
    p2.push_back(-1.0/3.0);
    p2.push_back(0.0); 
    std::vector< double > p3;// = new std::vector< double >();
    theta = 4.0 * M_PI / 3.0; // two-thirds of 2pi`
    p3.push_back(std::cos(theta));
    p3.push_back(std::sin(theta));
    
    std::vector< std::vector< double > > vertices;
    
    vertices.push_back(p0);
    vertices.push_back(p1);
    vertices.push_back(p2);
    vertices.push_back(p3); 

    std::vector< unsigned int > edges;
    edges.push_back(0);
    edges.push_back(1);
    edges.push_back(1);
    edges.push_back(2);
    edges.push_back(2);
    edges.push_back(3);
    edges.push_back(3);
    edges.push_back(0);

    Player *plyr = new Player();
    plyr->edges = std::move(edges);
    plyr->vertices = std::move(vertices);
    plyr->angular_vel = M_PI / 5.0;
    plyr->heading_jerk = 1.0;

    return plyr;
}


