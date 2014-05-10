#ifndef VERLET_H
#define VERLET_H
#include "SDL/SDL.h"

class Verlet
{
    public:
        double m_xa, m_x;
        double m_ya, m_y;
        double m_za, m_z;
        bool held;
        Verlet(double x, double y, double z);
        virtual ~Verlet();
        //unsigned int Getm_x() { return m_x; }
        //void Setm_x(unsigned int val) { m_x = val; }
        //unsigned int Getm_y() { return m_y; }
        //void Setm_y(unsigned int val) { m_y = val; }
        unsigned int GetMass() { return m_mass; }
        void SetMass(unsigned int val) { m_mass = val; }
        void move();
        void eatEvent(SDL_Event e);
    protected:
    private:
        double m_xp, m_yp, m_zp;
        unsigned int m_mass;
        unsigned long int m_t;
};

#endif // VERLET_H
