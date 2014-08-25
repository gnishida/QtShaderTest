#pragma once

#include <QVector3D>
#include <vector>
#include "Vertex.h"

class OBJLoader
{
protected:
	OBJLoader() {}

public:
	static void load(const char* filename, std::vector<Vertex>& vertices);
};

