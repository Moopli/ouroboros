#ifndef MESH_H
#define MESH_H
#include <vector>
#include "Verlet.h"
#include "VerletEdge.h"

class Mesh
{
    public:
        std::vector<Verlet*> verlets;
        std::vector<VerletEdge*> edges;
        Mesh();
        virtual ~Mesh();
        void wipe();
        void mergeInto(Mesh *other);
        void sim();
    protected:
    private:

};

#endif // MESH_H
