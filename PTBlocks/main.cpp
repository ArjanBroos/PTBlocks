#include <iostream>
#include "application.h"
#include "sphere.h"
#include "geometry.h"
#include "camera.h"
#include "filter.h"
#include "scene.h"
#include "primitive.h"

int main() {
	// Set up application
	const unsigned width = 800;
	const unsigned height = 600;
	Application app(width, height, "PTBlocks");

	// Create three sphere primitives
	Sphere* sphereShape1 = new Sphere(Point(0.f, 0.f, 0.f), 1.f);
	Material sphereMat1(Color(0.f, 0.f, 1.f));
	Primitive spherePrim1(sphereShape1, sphereMat1);
	Sphere* sphereShape2 = new Sphere(Point(2.f, 0.f, 5.f), 3.f);
	Material sphereMat2(Color(0.f, 1.f, 0.f));
	Primitive spherePrim2(sphereShape2, sphereMat2);
	Sphere* sphereShape3 = new Sphere(Point(-3.f, 2.f, 0.f), 0.5f);
	Material sphereMat3(Color(1.f, 0.f, 0.f));
	Primitive spherePrim3(sphereShape3, sphereMat3);

	// Set up the scene with the sphere primitives
	Scene scene;
	scene.AddPrimitive(spherePrim1);
	scene.AddPrimitive(spherePrim2);
	scene.AddPrimitive(spherePrim3);

	// Set up the camera
	Camera camera(Point(0.f, 0.f, -10.f), Vector(0.f, 0.f, 1.f), Vector(0.f, 1.f, 0.f), width, height, 60.f);

	// Cast rays
	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width; x++) {
			Ray ray = camera.GetRay(x, y);
			float t;
			Primitive* prim = nullptr;
			if (scene.Intersect(ray, t, &prim))
				camera.GetFilm()->AddColor(prim->GetMaterial().c, x, y);
		}
	}

	// Convert film into data usable by SFML
	Filter filter(*camera.GetFilm());

	// Handle events and draw
	while (app.IsRunning()) {
		app.HandleEvents();
		app.Draw(filter.GetPixels(), width, height);
	}

	// Clean up
	delete sphereShape1;
	delete sphereShape2;
	delete sphereShape3;
}