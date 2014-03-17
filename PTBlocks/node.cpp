#include "node.h"
#include "point.h"
#include "primitive.h"
#include "light.h"
#include "object.h"
#include <iostream>
#include <cmath>

Node::Node(Point bounda, Point boundb) : nObjects(0), object(nullptr), id(nextId++)
{
	parent = nullptr;
	if(bounda < boundb) {
		bounds[0] = bounda;
		bounds[1] = boundb;
	} else {
		bounds[0] = boundb;
		bounds[1] = bounda;
	}
	for( int i = 0; i < 8; i++) 
		nodes[i] = nullptr;
}

Node::Node(Point bounda, Point boundb, Node* parent) : nObjects(0), object(nullptr), id(nextId++)
{
	this->parent = parent;
	if(bounda < boundb) {
		bounds[0] = bounda;
		bounds[1] = boundb;
	} else {
		bounds[0] = boundb;
		bounds[1] = bounda;
	}
	for( int i = 0; i < 8; i++) 
		nodes[i] = nullptr;
}

int Node::nextId = 0;

int Node::insert(const Object* object, const Point &loc)
{
	//Is loc in this bounding box?
	if(loc < bounds[0] || loc > bounds[1])
		return 0;
	//If smallest node, try to insert it
	if( (fabsf(bounds[1].x - bounds[0].x - 1) < 1e-5f) && (fabsf(bounds[1].y - bounds[0].y - 1) < 1e-5f) && (fabsf(bounds[1].z - bounds[0].z - 1) < 1e-5f) ) {
		if(this->object) {
			return -1;
		}
		this->object = object;
		Node* nextNode = this;
		while(nextNode->parent != nullptr) {
			nextNode->nObjects++;
			nextNode = nextNode->parent;
		}
		nextNode->nObjects++;
		return 1;
	}
	//Find correct subNode and insert object
	int midx = (bounds[0].x+bounds[1].x)/2.0;
	int midy = (bounds[0].y+bounds[1].y)/2.0;
	int midz = (bounds[0].z+bounds[1].z)/2.0;
	bool east = loc.x >= midx;
	bool north = loc.y >= midy;
	bool top = loc.z >= midz;
	if(east && north && top) {
		if(nodes[NET] == nullptr)
			nodes[NET] = new Node(Point(midx, midy, midz), Point(bounds[1].x, bounds[1].y, bounds[1].z), this);
		nodes[NET]->insert(object, loc);
	}
	if(!east && north && top) {
		if(nodes[NWT] == nullptr)
			nodes[NWT] = new Node(Point(bounds[0].x, midy, midz), Point(midx, bounds[1].y, bounds[1].z), this);
		nodes[NWT]->insert(object, loc);
	}
	if(east && !north && top) {
		if(nodes[SET] == nullptr)
			nodes[SET] = new Node(Point(midx, bounds[0].y, midz), Point(bounds[1].x, midy, bounds[1].z), this);
		nodes[SET]->insert(object, loc);
	}
	if(!east && !north && top) {
		if(nodes[SWT] == nullptr)
			nodes[SWT] = new Node(Point(bounds[0].x, bounds[0].y, midz), Point(midx, midy, bounds[1].z), this);
		nodes[SWT]->insert(object, loc);
	}
	if(east && north && !top) {
		if(nodes[NEB] == nullptr)
			nodes[NEB] = new Node(Point(midx, midy, bounds[0].z), Point(bounds[1].x, bounds[1].y, midz), this);
		nodes[NEB]->insert(object, loc);
	}
	if(!east && north && !top) {
		if(nodes[NWB] == nullptr)
			nodes[NWB] = new Node(Point(bounds[0].x, midy, bounds[0].z), Point(midx, bounds[1].y, midz), this);
		nodes[NWB]->insert(object, loc);
	}
	if(east && !north && !top) {
		if(nodes[SEB] == nullptr)
			nodes[SEB] = new Node(Point(midx, bounds[0].y, bounds[0].z), Point(bounds[1].x, midy, midz), this);
		nodes[SEB]->insert(object, loc);
	}
	if(!east && !north && !top) {
		if(nodes[SWB] == nullptr)
			nodes[SWB] = new Node(Point(bounds[0].x, bounds[0].y, bounds[0].z), Point(midx, midy, midz), this);
		nodes[SWB]->insert(object, loc);
	}

	//Somehow not a correct subNode is found
	return 1;
}