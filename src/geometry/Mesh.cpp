#include "Mesh.h"

Mesh::Mesh() : polychain(), vertexchain() {}

Mesh::~Mesh()
{
    delete vertexchain;
    delete polychain;
}