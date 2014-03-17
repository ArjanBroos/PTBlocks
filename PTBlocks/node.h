#ifndef OCTREE_H
#define OCTREE_H

#include "point.h"
#include "vector.h"
#include "object.h"
enum subNodes{NEB, NWB, SWB, SEB, NET, NWT, SWT, SET};

class Node {
public:
	int id;
	Node* parent;
	Node(Point boundmin, Point boundmax);
	Node(Point boundmin, Point boundmax, Node* parent);
	Point bounds[2];
	int nObjects;
	Node* nodes[8];
	const Object* object;
	int insert(const Object* object, const Point &loc);
	static int nextId;
};

#endif