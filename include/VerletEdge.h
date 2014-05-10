#ifndef VERLETEDGE_H
#define VERLETEDGE_H
#include "Verlet.h"

class VerletEdge
{
    public:
        VerletEdge(Verlet* a, Verlet *b, float elasticity, double length);
        virtual ~VerletEdge();
        Verlet *m_a;
        Verlet *m_b;
        void restitute();
        float getStress(){return m_stress;}
        void freeze();
        void stretch(int i);
    protected:
    private:
        double m_length;
        float m_elasticity;
        float m_stress;
};

#endif // VERLETEDGE_H
