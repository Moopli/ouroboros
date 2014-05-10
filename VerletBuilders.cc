#include "include/Verlet.h"
#include "include/VerletEdge.h"
#include "include/Mesh.h"
#include <cstdio>
#include <cassert>

Mesh* mkLattice(int x, int y, int z, int linesize, double softness)
{
    Mesh *mesh = new Mesh;
    Verlet *verls[z][y][x];
    int linesizesqrt2 = (int) (linesize * 1.414213562);

    Verlet *verl;
    for (int k = 0; k < z; k++)
    {
        for (int i = 0; i < y; i++) // i for rows
        {
            for (int j = 0; j < x; j++) // j for columns
            {
                verl = new Verlet(linesize * j, linesize * i, linesize * k);
                verls[k][i][j] = verl;
                mesh->verlets.push_back(verl);

                if (i != 0)
                {
                    mesh->edges.push_back(new VerletEdge(verls[k][i][j], verls[k][i-1][j], softness, linesize));

                    if (j != x - 1)
                    {
                        mesh->edges.push_back(new VerletEdge(verls[k][i][j], verls[k][i-1][j+1], softness, linesizesqrt2));
                    }
                    if (j != 0)
                    {
                        mesh->edges.push_back(new VerletEdge(verls[k][i][j], verls[k][i-1][j-1], softness, linesizesqrt2));
                    }
                }
                if (j != 0)
                {
                    mesh->edges.push_back(new VerletEdge(verls[k][i][j], verls[k][i][j-1], softness, linesizesqrt2));
                }
                if (k != 0)
                {
                    mesh->edges.push_back(new VerletEdge(verls[k][i][j], verls[k-1][i][j], softness, linesizesqrt2));
                }
            }
        }
    }
    //printf("made mesh\n");
    return mesh;
}

Mesh* mkTube(int x, int y, int linesize, double elast)
{
    Verlet *verls[y][x];
    Verlet *verl;
    Mesh *mesh = new Mesh;
    int linesizesqrt2 = (int) (linesize * 1.414213562);
    for (int rowN = 0; rowN < y; rowN++)
    {
        for (int colN = 0; colN < x; colN++)
        {
            verl = new Verlet(x * linesize, y * linesize, 0);
            verls[rowN][colN] = verl;
            mesh->verlets.push_back(verl);

            if (rowN != 0)
            {
                mesh->edges.push_back(new VerletEdge(verls[rowN][colN], verls[rowN - 1][colN], elast, linesize));
            }
            if (colN != 0)
            {
                mesh->edges.push_back(new VerletEdge(verls[rowN][colN], verls[rowN][colN - 1], elast, linesize));
            }
        }
        mesh->edges.push_back(new VerletEdge(verls[rowN][x - 1], verls[rowN][0], elast, linesize));
    }
    printf("%d %d\n", mesh->edges.size(), mesh->verlets.size());
    return mesh;
}

