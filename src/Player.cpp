#include "Player.hpp"

using namespace aos;

Player::Player() 
{ 
    
}

Player::~Player() 
{
    
}

void Player::update(Uint32 dt, Uint32 time)
{

}

void Player::render(Uint32 dt, Uint32 time)
{

}


void Player::send_event(SDL_Event event, Uint32 dt, Uint32 time)
{
    
}

Player * default_player()
{ 
    std::vector< double > p1;// = new std::vector< double >();
    p1.push_back(1.0);
    p1.push_back(0.0);
    std::vector< double > p2;// = new std::vector< double >(); 
    double theta = 2.0 * M_PI / 3.0;
    p2.push_back(std::cos(theta));
    p2.push_back(std::sin(theta));
    std::vector< double > p3;// = new std::vector< double >();
    p3.push_back(-1.0/3.0);
    p3.push_back(0.0); 
    std::vector< double > p4;// = new std::vector< double >();
    theta = 8.0 * M_PI / 3.0;
    p4.push_back(std::cos(theta));
    p4.push_back(std::sin(theta));
    
    std::vector< std::vector< double > > * vertices = new std::vector< std::vector< double > >();
    
    vertices->push_back(p1);
    vertices->push_back(p2);
    vertices->push_back(p3);
    vertices->push_back(p4); 

    std::vector< unsigned int > edges;
    edges.push_back(0);
    edges.push_back(1);
    edges.push_back(1);
    edges.push_back(2);
    edges.push_back(2);
    edges.push_back(3);
    edges.push_back(3);
    edges.push_back(4);

    Player *plyr = new Player();

    plyr->edges = std::move(edges);
    plyr->vertices = std::move(vertices);

    return plyr;
}


