#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <vector>
#include "Obj.h"

using namespace std;

class Sphere : public Obj{
private:
	float radius;
	vector<float> center;
	vector<float> color;
	/*float dot(vector<float> a, vector<float> b);
	vector<float> mVec(vector<float> a, vector<float> b);*/
public:
	Sphere(float aRadius, vector<float> aCenter, vector<float> aColor);
	virtual vector<float> intersectRay(vector<float> orig, vector<float> dir) const;
	virtual vector<float> getColor() const;
	virtual vector<float> getCenter() const;
};
#endif // !SPHERE_H
