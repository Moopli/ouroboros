#include "include/Verlet.h"
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
// #include <cmath>

#define CLICK_RANGE 400

inline unsigned int hypot2(int dx, int dy) {
    return dx * dx + dy * dy;
}

Verlet::Verlet(double x, double y, double z)
{
    //ctor
    m_x = m_xp = x;
    m_y = m_yp = y;
    m_z = m_zp = z;
    held = false;
    m_mass = 100;
    m_xa = m_ya = m_za = 0;
}

void Verlet::move()
{
    time_t timenow = time(NULL);
    if (!held)
    {
        m_x = 2 * m_x - m_xp + m_xa * (timenow - m_t) * (timenow - m_t) / m_mass;
        m_y = 2 * m_y - m_yp + m_ya * (timenow - m_t) * (timenow - m_t) / m_mass;
        m_z = 2 * m_z - m_zp + m_za * (timenow - m_t) * (timenow - m_t) / m_mass;
    }
    m_xp = m_x;
    m_yp = m_y;
    m_zp = m_z;
    m_t = timenow;
}

void Verlet::grab(unsigned int x, unsigned int y)
{   
    if (hypot2(x - m_x, y - m_y) < CLICK_RANGE)
    {
        held = true;
        m_x = x;
        m_y = y;
    }
}

void Verlet::release() {
    held = false;
}

void Verlet::drag(unsigned int x, unsigned int y) {
    // printf("woo!\n");
    if (held) {
        m_x = x; m_y = y;
    }
}

Verlet::~Verlet() {
}

