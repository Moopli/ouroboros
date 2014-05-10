#ifndef VERLETBUILDER_H_INCLUDED
#define VERLETBUILDER_H_INCLUDED


Mesh* mkLattice(int x, int y, int z, int linesize, double softness);
Mesh* mkTube(int x, int y, int linesize, double softness);

#endif // VERLETBUILDER_H_INCLUDED
