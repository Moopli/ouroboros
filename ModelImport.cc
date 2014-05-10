#include "assimplib/include/assimp/Importer.hpp"
#include "assimplib/include/assimp/scene.h"             // Output data structure
#include "assimplib/include/assimp/postprocess.h"       // Post processing flags
#include <string>
#include <cstdio>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "ModelImport.h"
#include "include/Mesh.h"
/*
bool ImportTesting( const std::string& pFile)
{
  // Create an instance of the Importer class
  Assimp::Importer importer;
  // And have it read the given file with some example postprocessing
  // Usually - if speed is not the most important aspect for you - you'll
  // propably to request more postprocessing than we do in this example.
  const aiScene* scene = importer.ReadFile( pFile,
        aiProcess_CalcTangentSpace       |
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);

  // If the import failed, report it
  if(!scene)
  {
    printf(importer.GetErrorString());
    return false;
  }
  // Now we can access the file's contents.
  //DoTheSceneProcessing(scene);
  printf("%s\n", scene);

  // We're done. Everything will be cleaned up by the importer destructor
  return true;
}*/


Mesh* ImportObj( std::string pFile)
{
    std::ifstream fin;
    fin.open(pFile.c_str());
    std::vector<triple> points;
    std::string line, garbage;
    triple t;
    do {
        fin >> garbage;
    } while(garbage != "v");
    while (garbage == "v")
    {
        fin >> t.x >> t.y >> t.z >> garbage;
        points.push_back(t);
    }
    std::vector<triple> triangles;
    do {
        fin >> garbage;
    } while(garbage != "f");
    while (garbage == "f")
    {
        fin >> t.x >> t.y >> t.z >> garbage;
        triangles.push_back(t);
    }
    printf("%d is num of triangles\n", triangles.size());
    // all useful data read for now
    //printf("points is %d big\n", points.size());
    Mesh *mesh = new Mesh;
    for (int i = 0; i < points.size(); i++)
    {
        mesh->verlets.push_back(new Verlet(((points[i]).x + 6)*60,((points[i]).y + 1)*60,((points[i]).z)*60));
    }
    printf("managed to load %d verlets\n", mesh->verlets.size());
    Verlet *a, *b, *c;
    for (std::vector<triple>::iterator i = triangles.begin();
                i != triangles.end(); ++i)
    {
        //printf("managed to enter loop\n");
        a = (mesh->verlets)[(*i).x-1];
        b = (mesh->verlets)[(*i).y-1];
        c = (mesh->verlets)[(*i).z-1];
        //printf("managed to set pointers\n");
        mesh->edges.push_back(new VerletEdge(a,c,4,hypot(hypot(a->m_x - c->m_x,a->m_y - c->m_y), a->m_z - c->m_z)));
        //printf("yay\n");
        //printf("peek successful\n");
        mesh->edges.push_back(new VerletEdge(c,b,4,hypot(hypot(c->m_x - b->m_x,c->m_y - b->m_y), c->m_z - b->m_z)));
        mesh->edges.push_back(new VerletEdge(a,b,4,hypot(hypot(a->m_x - b->m_x,a->m_y - b->m_y), a->m_z - b->m_z)));
        //printf("yay\n");

    }
    return mesh;
}

