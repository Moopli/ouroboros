#include "include/VerletEdge.h"
#include "include/Verlet.h"
#include <cmath>

VerletEdge::VerletEdge(Verlet* a, Verlet *b, float elasticity, double length)
{
    //ctor
    m_a = a;
    m_b = b;
    m_elasticity = elasticity;
    m_stress = 1;
    m_length = length;
}
void VerletEdge::freeze()
{
    m_length = hypot(m_a->m_x - m_b->m_x, m_a->m_y - m_b->m_y);
}
void VerletEdge::stretch(int i)
{
    m_length = fmax(4, m_length + i);
}
void VerletEdge::restitute()
{
    double xdist = m_a->m_x - m_b->m_x; // how rightward A is of B
    double ydist = m_a->m_y - m_b->m_y; // how bottomward A is of B

    double h = hypot(xdist, ydist);
    double diff;
    if (std::abs(h) < 0.00001)
    {
        diff = 1 << 30;
    }
    else
    {
        diff = (h - m_length) / h;
    }
    m_stress = diff;
    if (!m_a->held)
    {
        m_a->m_x -= xdist * 0.5 * (diff / m_elasticity);
        m_a->m_y -= ydist * 0.5 * (diff / m_elasticity);
    }
    if (!m_b->held)
    {
        m_b->m_y += ydist * 0.5 * (diff / m_elasticity);
        m_b->m_x += xdist * 0.5 * (diff / m_elasticity);
    }
}
VerletEdge::~VerletEdge()
{
    //dtor
}
