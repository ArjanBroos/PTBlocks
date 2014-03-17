#ifndef OBJECT_H
#define OBJECT_H

#include <string>

enum objectType{LIGHT, PRIMITIVE};

class Object
{
public:
	Object() : name("undefined"), size(-1) {};
	Object(const std::string name, int size) : name(name), size(size) {};
	int size;
	std::string name;
	int type;
};

#endif