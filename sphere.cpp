#include "sphere.h"

Sphere::Sphere(float aRadius, vector<float> aCenter, vector<float> aColor) : radius(aRadius), center(aCenter), color(aColor) {}

//float Sphere::dot(vector<float> a, vector<float> b) {
//	if (a.size() < 3) {
//		return 0;
//	}
//	else if (b.size() < 3) {
//		return 0;
//	}
//
//	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
//}

vector<float> Sphere::intersectRay(vector<float> orig, vector<float> dir) const {
	vector<float> OC = mVec(orig,center);

	float a = dot(dir, dir);
	float b = 2 * dot(OC, dir);
	float c = dot(OC, OC) - radius * radius;

	float d = b * b - 4 * a * c;
	if (d < 0)
		return{ INFINITY,INFINITY };

	float k1 = (-b + sqrt(d)) / (2 * a);
	float k2 = (-b - sqrt(d)) / (2 * a);

	return { k1,k2 };
}

vector<float> Sphere::getCenter() const {
	return center;
}

//vector<float> Sphere::mVec(vector<float> a, vector<float> b) {
//	return { a[0] - b[0],a[1] - b[1],a[2] - b[2] };
//}
vector<float> Sphere::getColor() const {
	return color;
}