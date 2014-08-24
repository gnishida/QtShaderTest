#pragma once

#include <QVector3D>
#include <vector>
#include "Vertex.h"

//using namespace std;

class OBJLoader
{
protected:
	OBJLoader() {}

public:
	static void load(const char* filename, std::vector<Vertex>& vertices);
};

