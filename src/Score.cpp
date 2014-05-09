#include "Score.hpp"

namespace aos
{ 

Score::Score(double x, double y) 
{
   this->camera = camera; 
   this->x = x;
   this->y = y;
}
Score::~Score() { }

void Score::incrementScore(double value) 
{
    this->score += value;
}

void Score::setScore(double value)
{
    this->score = value;
}

void Score::resetScore()
{
    this->score = 0.0;
}

inline void Score::render(Uint32 dt_ms, Uint32 time) 
{
    if(this->is_visible)
    {   
        double cx = 0.0, cy = 0.0;
        if(!(this->camera == nullptr))
        {
           cx = camera->x();
           cy = camera->y();
        }

        std::stringstream sstrng;
        sstrng << this->display_text << (int)this->score;
        std::string to_display = sstrng.str();

        
        glPushMatrix();
        glTranslatef(this->x - cx, this->y - cy, 0.0);
        glScalef(this->scale, this->scale, this->scale); 
        glColor3f(1.0, 0.0, 0.0);
        for(std::string::iterator it = to_display.begin(); it != to_display.end(); it++)
        {  
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *it);  
        }
        glColor3f(1.0, 1.0, 1.0);
        glPopMatrix();
    }
}

}
