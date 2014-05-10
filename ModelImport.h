#ifndef MODELIMPORT_H_
#define MODELIMPORT_H_
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "include/Mesh.h"

struct triple
{
    double x, y, z;
};

Mesh* ImportObj(std::string pFile);
#endif // MODELIMPORT_H_
