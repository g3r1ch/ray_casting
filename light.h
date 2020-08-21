#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <vector>

using namespace std;

class Light {
public:
	enum LightType { AMBIENT, POINT, DIRECTIONAL };//1: ambient; 2: a)point; b)directional;
	Light(Light::LightType type, float aIntensity, vector<float> aPositionOrDirect = { 0,0,0 });
	vector<float> positionOrDirect;
	float intensity;
	LightType typeOfLight;
};

#endif // !LIGHT_H
