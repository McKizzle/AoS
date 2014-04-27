#include "Grid.hpp"


namespace aos
{
Grid::Grid(double width, double height)
{
    float color_max = 255.0;
    major_color[0] = 64.0 / color_max;
    major_color[1] = 64.0 / color_max;
    major_color[2] = 64.0 / color_max;

    minor_color[0] = 32.0 / color_max;
    minor_color[1] = 32.0 / color_max;
    minor_color[2] = 32.0 / color_max;

    this->width = width;
    this->height = height;
}
Grid::~Grid(){}

void Grid::render(Uint32 dt_ms, Uint32 time)
{ 
    const double x_max = width / 2.0;
    const double x_min = -width / 2.0;
    const double y_max = width / 2.0;
    const double y_min = -width / 2.0;
    const double x = (double) ((int)(obj_camera->x() / vertical_major_spacing)) * vertical_major_spacing;
    const double y = (double) ((int)(obj_camera->y() / horizontal_major_spacing)) * horizontal_major_spacing;

    glPushMatrix();
    glTranslatef(x - camera->x(), y - camera->y(), 0.0);
    glRotatef(state[HIND], 0, 0, 1);
    glBegin(GL_LINES);  
        double x1, y1, x2, y2;

        glColor3f(minor_color[0], minor_color[1], minor_color[2]);
        // Draw the minor x lines
        for(int i = x_min; i <= x_max; i += vertical_minor_spacing)
        {
            x1 = i;
            y1 = y_min;
            x2 = i;
            y2 = y_max;

            glVertex2f((GLfloat) x1, (GLfloat) y1);
            glVertex2f((GLfloat) x2, (GLfloat) y2);
        }
        // Draw the minor y lines
        for(int i = y_min; i <= y_max; i += horizontal_minor_spacing)
        { 
             x1 = x_min;
             y1 = i;
             x2 = x_max;
             y2 = i;

            glVertex2f((GLfloat) x1, (GLfloat) y1);
            glVertex2f((GLfloat) x2, (GLfloat) y2);
        }
        
        glColor3f(color[0], color[1], color[2]);
        // Draw the major x lines 
        for(int i = x_min; i <= x_max; i += vertical_major_spacing)
        {
            x1 = i;
            y1 = y_min;
            x2 = i;
            y2 = y_max;

            glVertex2f((GLfloat) x1, (GLfloat) y1);
            glVertex2f((GLfloat) x2, (GLfloat) y2);
        }
        // Draw the major y lines
        for(int i = y_min; i <= y_max; i += horizontal_major_spacing)
        { 
             x1 = x_min;
             y1 = i;
             x2 = x_max;
             y2 = i;

            glVertex2f((GLfloat) x1, (GLfloat) y1);
            glVertex2f((GLfloat) x2, (GLfloat) y2);
        }
    glEnd();
    glPopMatrix();
}

void Grid::update(Uint32 dt_ms, Uint32 time) {}

}
