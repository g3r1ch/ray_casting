#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "Obj.h"
#include "sphere.h"
#include "light.h"

using namespace std;

class Scene {
private:
	vector<Obj*> objects;
	vector<Light*> lights;
	vector<vector<float>> framebuffer;
	vector<float> cameraPosition;
	vector<float> cameraDirection;
	float viewportSize = 1.;
	int weight;
	int height;
	std::ofstream ofs;
	vector<float> getPixelPosition(int x, int y);
public:
	Scene(int aWeight, int aHeight,vector<float> aCameraPosition, string filename = "./out.ppm");
	void render();
	vector<float> castRay(vector<float> orig, vector<float> dir, float min, float max);
	void printToFile();
	void newSphere(float aRadius, vector<float> aCenter, vector<float> aColor);
	void newLight(Light::LightType type, float aIntensity, vector<float> aPositionOrDirect = { 0,0,0 });
	void moveCamera(vector<float> offset);
	float calcLight(vector<float> point, vector<float> normal, int ki);
	bool isShadow(vector<float> point, vector<float> lightPosition, int ki);
	//vector<vector<float>> closestIntersection(vector<float> orig, vector<float> dir, float min, float max);
	~Scene();
};
#endif // !SCENE_H
