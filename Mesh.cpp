#include "include/Mesh.h"
#include <cstdlib>
#include <cstdio>

Mesh::Mesh()
{
    //ctor
}

void Mesh::mergeInto(Mesh *other)
{
    for (std::vector<VerletEdge*>::iterator i = other->edges.begin();
                i != other->edges.end(); ++i)
    {
        edges.push_back((*i));
    }
    for (std::vector<Verlet*>::iterator i = other->verlets.begin();
                i != other->verlets.end(); ++i)
    {
        verlets.push_back((*i));
    }
}

void Mesh::sim()
{
    //printf("about to restitute %d edges\n", edges.size());
    for (std::vector<VerletEdge*>::iterator i = edges.begin();
                i != edges.end(); ++i)
    {
        (*i)->restitute();
    }
    //printf("about to move\n");
    for (std::vector<Verlet*>::iterator i = verlets.begin();
            i != verlets.end(); ++i)
    {
        (*i)->move();
    }
}

void Mesh::wipe()
{
    // the /actual/ clean-all-contents method
    for (std::vector<VerletEdge*>::iterator i = edges.begin();
                i != edges.end(); ++i)
    {
        if (NULL != *i)
        {
            delete *i;
            *i = NULL;
        }
    }
    for (std::vector<Verlet*>::iterator i = verlets.begin();
                i != verlets.end(); ++i)
    {
        if (NULL != *i)
        {
            delete *i;
            *i = NULL;
        }
    }
}

Mesh::~Mesh()
{
    //dtor
    // Verlets and Edges are stored by reference --
}
