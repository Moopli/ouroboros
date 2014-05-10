#include "include/Verlet.h"
#include <ctime>
#include "SDL/SDL.h"
#include <cmath>

#define CLICK_RANGE 20

Verlet::Verlet(double x, double y, double z)
{
    //ctor
    m_x = m_xp = x;
    m_y = m_yp = y;
    m_z = m_zp = z;
    held = false;
    m_mass = 100;
    m_xa = m_ya = 0;
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

void Verlet::eatEvent(SDL_Event e)
{
    if (held && e.type == SDL_MOUSEMOTION)
    {
        m_x = e.button.x;
        m_y = e.button.y;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (hypot(e.button.x - m_x, e.button.y - m_y) < CLICK_RANGE)
        {
            held = true;
            m_x = e.button.x;
            m_y = e.button.y;
        }
    }
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
        held = false;
    }
}

Verlet::~Verlet()
{
    //dtor
}

