#include <iostream>
#include <string>
#include <sstream>
#include "application.h"
#include "sphere.h"
#include "geometry.h"
#include "camera.h"
#include "filter.h"
#include "scene.h"
#include "primitive.h"
#include "arealight.h"
#include "lambertmaterial.h"
#include "mirrormaterial.h"
#include "rng.h"
#include "plane.h"
#include "renderer.h"

std::string GetTitle(unsigned nIterations);
//Test Jesper
int main() {
	RNG	rng;

	// Set up application
	const unsigned width = 1024;
	const unsigned height = 576;
	Application app(width, height, "PTBlocks");

	// Create three sphere primitives
	Sphere sphereShape1(Point(0.f, 0.5f, 0.f), 1.f);
	MirrorMaterial sphereMat1(Color(1.f, 1.f, 1.f), 1.f);
	Primitive spherePrim1(&sphereShape1, &sphereMat1);
	Sphere sphereShape2(Point(2.f, 2.f, 5.f), 3.f);
	LambertMaterial sphereMat2(Color(0.f, 1.f, 0.f), 1.f);
	Primitive spherePrim2(&sphereShape2, &sphereMat2);
	Sphere sphereShape3(Point(4.f, 2.f, -2.f), 0.5f);
	LambertMaterial sphereMat3(Color(1.f, 0.f, 0.f), 1.f);
	Primitive spherePrim3(&sphereShape3, &sphereMat3);
	Sphere sphereShape4(Point(-6.f, 1.f, 3.f), 1.5f);
	LambertMaterial sphereMat4(Color(1.f, 1.f, 1.f), 1.f);
	Primitive spherePrim4(&sphereShape4, &sphereMat4);
	Plane planeShape(Point(0.f, 0.f, 0.f), Vector(0.f, 1.f, 0.f));
	LambertMaterial planeMat(Color(1.f, 1.f, 0.3f), 1.f);
	Primitive planePrim(&planeShape, &planeMat);

	// Create an area light
	Sphere lightShape1(Point(3.f, 2.f, -1.f), 1.f);
	AreaLight light1(&lightShape1);
	Sphere lightShape2(Point(-4.f, 1.f, 6.f), 2.f);
	AreaLight light2(&lightShape2, Color(0.2f, 0.2f, 1.f), 3.f);

	// Set up the scene with the sphere primitives
	Scene scene;
	scene.AddPrimitive(spherePrim1);
	scene.AddPrimitive(spherePrim2);
	scene.AddPrimitive(spherePrim3);
	scene.AddPrimitive(spherePrim4);
	scene.AddPrimitive(planePrim);
	scene.AddLight(&light1);
	scene.AddLight(&light2);

	// Set up the camera
	Camera camera(Point(0.f, 3.f, -10.f), Normalize(Vector(0.f, 0.f, 1.f)), Vector(0.f, 1.f, 0.f), width, height, 60.f);

	// Convert film into data usable by SFML
	Filter filter(*camera.GetFilm());

	Renderer renderer;

	// Handle events and draw
	unsigned nIterations = 0;
	while (app.IsRunning()) {
		app.HandleEvents();

		renderer.ComputeColors(camera, scene, rng);
		nIterations++;

		filter.Refilter(*camera.GetFilm(), nIterations);
		app.Draw(filter.GetPixels(), width, height);

		app.SetTitle(GetTitle(nIterations));
	}
}

std::string GetTitle(unsigned nIterations) {
	std::stringstream ss;
	ss << "PTBlocks - Iterations: " << nIterations;
	return ss.str();
}