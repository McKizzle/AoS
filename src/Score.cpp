#include "Score.hpp"

#include <cctype>
#include <vector>

namespace aos
{

namespace
{
    /// A minimal monospace "digital scoreboard" stroke font, self-contained
    /// (no font file / library) so it draws with plain GL_LINES the same way
    /// GLUT's stroke font did internally. Only covers the characters the
    /// score display actually uses: digits, "SCORE:" (case-insensitive),
    /// space, and '-'. Unrecognized characters are skipped (blank advance).
    ///
    /// Coordinates are sized (~120 tall) to roughly match
    /// GLUT_STROKE_ROMAN's own unit scale, so Score::scale's existing
    /// default still looks right with no further tuning.
    struct Seg { float x1, y1, x2, y2; };

    const float GLYPH_ADVANCE = 100.0f;

    const float X0 = 0.0f,  X1 = 40.0f, X2 = 80.0f;
    const float Y0 = 0.0f,  Y1 = 60.0f, Y2 = 120.0f;

    // Named 7-segment-style bars, reused across glyphs.
    const Seg SEG_A = {X0, Y2, X2, Y2}; // top
    const Seg SEG_B = {X2, Y2, X2, Y1}; // top-right
    const Seg SEG_C = {X2, Y1, X2, Y0}; // bottom-right
    const Seg SEG_D = {X0, Y0, X2, Y0}; // bottom
    const Seg SEG_E = {X0, Y1, X0, Y0}; // bottom-left
    const Seg SEG_F = {X0, Y2, X0, Y1}; // top-left
    const Seg SEG_G = {X0, Y1, X2, Y1}; // middle
    const Seg SEG_R_LEG = {X1, Y1, X2, Y0}; // diagonal leg, letter R only

    void draw_char(char c)
    {
        std::vector<Seg> segs;
        switch(std::toupper(static_cast<unsigned char>(c)))
        {
            case '0': segs = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F}; break;
            case '1': segs = {SEG_B, SEG_C}; break;
            case '2': segs = {SEG_A, SEG_B, SEG_G, SEG_E, SEG_D}; break;
            case '3': segs = {SEG_A, SEG_B, SEG_G, SEG_C, SEG_D}; break;
            case '4': segs = {SEG_F, SEG_G, SEG_B, SEG_C}; break;
            case '5': segs = {SEG_A, SEG_F, SEG_G, SEG_C, SEG_D}; break;
            case '6': segs = {SEG_A, SEG_F, SEG_G, SEG_E, SEG_C, SEG_D}; break;
            case '7': segs = {SEG_A, SEG_B, SEG_C}; break;
            case '8': segs = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G}; break;
            case '9': segs = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_F, SEG_G}; break;
            case 'S': segs = {SEG_A, SEG_F, SEG_G, SEG_C, SEG_D}; break;
            case 'C': segs = {SEG_A, SEG_F, SEG_E, SEG_D}; break;
            case 'O': segs = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F}; break;
            case 'R': segs = {SEG_A, SEG_F, SEG_E, SEG_G, SEG_B, SEG_R_LEG}; break;
            case 'E': segs = {SEG_A, SEG_F, SEG_E, SEG_G, SEG_D}; break;
            case '-': segs = {SEG_G}; break;
            case ':':
                segs = {
                    {X1 - 6, 35, X1 + 6, 35}, {X1, 29, X1, 41},
                    {X1 - 6, 95, X1 + 6, 95}, {X1, 89, X1, 101}
                };
                break;
            default: break; // space and anything else: blank, still advances
        }

        glBegin(GL_LINES);
        for(std::vector<Seg>::const_iterator it = segs.begin(); it != segs.end(); ++it)
        {
            glVertex2f(it->x1, it->y1);
            glVertex2f(it->x2, it->y2);
        }
        glEnd();
    }
}

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
            draw_char(*it);
            glTranslatef(GLYPH_ADVANCE, 0.0f, 0.0f);
        }
        glColor3f(1.0, 1.0, 1.0);
        glPopMatrix();
    }
}

}
