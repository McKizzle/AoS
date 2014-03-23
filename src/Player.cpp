#include "Player.hpp"

using namespace aos;

Player::Player() 
{ 
    std::cout << "Player::Player" << std::endl; 
}

Player::~Player() 
{ 
    std::cout << "Player::~Player" << std::endl; 
}

void Player::update(Uint32 dt_ms, Uint32 time) 
{
    std::vector< double > * new_state = intgr->integrate(this, &state, dt_ms, time);
    state.swap((*new_state));

    // Nudge the ship heading velocity if it is close to zero and the heading thrusters are slowing it down. 
    short sign_vheading = (state[VHIND] < 0.0) ? 1 : -1; 
    state[VHIND] = (!heading_key_pressed && (sign_vheading != prev_sign_vheading)) ? 0.0 : state[VHIND];
    heading_key_pressed = false;
    thruster_key_pressed= false;
    
    // Change current state values
    state[AXIND] = 0.0;
    state[AYIND] = 0.0;
    state[AHIND] = 0.0;

    delete new_state;
}

std::vector< double > * Player::system(Uint32 t, std::vector< double > * x)
{
    //std::cout << "Player::system" << std::endl; 
    std::vector< double > * dxdt = new std::vector< double >(x->size(), 0.0);
    
    // Calculate the heading acceleration. 
    short sign_vheading = ((*x)[VHIND] < 0.0) ? 1 : -1; 
    double abs_vheading = std::abs((*x)[VHIND]);
    double d2xdt2_heading = (abs_vheading > max_heading_velocity) ? sign_vheading * heading_thrusters_impulse : (*x)[AHIND];
    if(!heading_key_pressed && (abs_vheading > 0)) 
    { 
        d2xdt2_heading += sign_vheading * heading_thrusters_impulse;
    } 
    prev_sign_vheading = sign_vheading;


    (*dxdt)[XIND]  = (*x)[VXIND];
    (*dxdt)[YIND]  = (*x)[VYIND];
    (*dxdt)[VXIND] = (*x)[AXIND];
    (*dxdt)[VYIND] = (*x)[AYIND];
    (*dxdt)[AXIND] = 0.0;  
    (*dxdt)[AYIND] = 0.0;  
    (*dxdt)[HIND]  = (*x)[VHIND];
    (*dxdt)[VHIND] = d2xdt2_heading; 
    (*dxdt)[AHIND] = 0.0; 
 
    return dxdt;
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
    //std::cout << "------------" << std::endl;
    //double dt_ms = dt / 1000.0;

    // Velocity
    //double curr_vel = std::sqrt(std::pow(state[VXIND], 2.0) + std::pow(state[VYIND], 2.0));
    //std::cout << "Current Velocity: " << curr_vel << std::endl;
 
    //delete new_state;

    // Acceleration
    double theta = 2.0 * M_PI * state[HIND] / 360.0;
    double a_x = std::cos(theta) * thrusters_impulse;
    double a_y = std::sin(theta) * thrusters_impulse; 
     
    std::vector< double > tmp_state(state);
    if(keyboardStates[SDL_SCANCODE_A])
    {
        heading_key_pressed = true;
        tmp_state[AHIND] = heading_thrusters_impulse;
    }
    if(keyboardStates[SDL_SCANCODE_W])
    {
        tmp_state[AXIND] = a_x;
        tmp_state[AYIND] = a_y;
        thruster_key_pressed = true;
    }
    if(keyboardStates[SDL_SCANCODE_D])
    { 
        heading_key_pressed = true;
        tmp_state[AHIND] = -heading_thrusters_impulse;
    }
    if(keyboardStates[SDL_SCANCODE_S])
    { 
        tmp_state[AXIND] = -a_x;
        tmp_state[AYIND] = -a_y;
        thruster_key_pressed = true;
    }
    if(keyboardStates[SDL_SCANCODE_SPACE]) 
    { 
        std::cout << "Fire" << std::endl;
    }
    std::vector< double > * next_state = intgr->integrate(this, &tmp_state, dt, time);
   
    //std::cout << "Current State\n";
    //dvect_dump(std::cout, state); 
    //std::cout << "Tmp State\n";
    //dvect_dump(std::cout, tmp_state); 

    // Next velocity
    //double new_vel = std::sqrt(std::pow((*next_state)[VXIND], 2.0) + std::pow((*next_state)[VYIND], 2.0));
    //std::cout << "New Velocity: " << new_vel << std::endl;

    state[AHIND] = tmp_state[AHIND];
    state[AXIND] = tmp_state[AXIND];//(new_vel < max_velocity) ? tmp_state[AXIND] : 0.0;
    state[AYIND] = tmp_state[AYIND];//(new_vel < max_velocity) ? tmp_state[AYIND] : 0.0;

    delete next_state;
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
    //plyr->angular_vel = M_PI / 5.0;
    //plyr->heading_jerk = 1.0;

    return plyr;
}


