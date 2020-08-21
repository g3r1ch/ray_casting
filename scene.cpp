#include "scene.h"

Scene::Scene(int aWeight, int aHeight, vector<float> aCameraPosition, string filename) : weight(aWeight), height(aHeight), cameraPosition(aCameraPosition) {
	cameraDirection = { cameraPosition[0],cameraPosition[1],cameraPosition[2] + 1 };
	ofs.open(filename);
	ofs << "P6\n" << weight << " " << height << "\n255\n";
	framebuffer.resize(weight * height);
}

void Scene::render(){
	float i = 0.5;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < weight; x++) {
			vector<float> d = getPixelPosition(x, y);
			d = { d[0] - i,d[1] - i,d[2] };
			framebuffer[(height - y) * weight - (weight - x)] = castRay(cameraPosition, d, 1, INFINITY);
		}
	}
}

vector<float> Scene::getPixelPosition(int x, int y) {
	return{ x * viewportSize / weight, y * viewportSize / height, cameraDirection[2] };
}

vector<float> Scene::castRay(vector<float> orig, vector<float> dir, float min, float max) {
	float closest = INFINITY;
	//bool flag = 0;
	vector<float> center;
	vector<float> color = { 255,255,255 };
	int ki = -1;
	int ii = 0;
	for (auto& i : objects) {
		vector<float> k = i->intersectRay(orig, dir);
		if (k[0] > min && k[0] < max && k[0] < closest) {
			closest = k[0];
			ki = ii;
			color = i->getColor();
			center = i->getCenter();
		}else if (k[1] > min && k[1] < max && k[1] < closest) {
			closest = k[1];
			ki = ii;
			color = i->getColor();
			center = i->getCenter();
		}
		ii++;
	}
	//closest -= 1;
	if (ki != -1) {
		vector<float> point = { orig[0] + closest * dir[0], orig[1] + closest * dir[1], orig[2] + closest * dir[2] };
		vector<float> normal = { point[0] - center[0], point[1] - center[1], point[2] - center[2] };
		float NSqrt = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
		normal = { normal[0] / NSqrt, normal[1] / NSqrt, normal[2] / NSqrt };
		float calcd = calcLight(point, normal, ki);
		return { color[0] * calcd, color[1] * calcd, color[2] * calcd };
	}
	else {
		return color;
	}
}

void Scene::printToFile() {
	for (size_t i = 0; i < height * weight; i++) {
		//for (int j = 2; j >= 0; j--) {normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]
		ofs << (char)(framebuffer[i][1]);
		ofs << (char)(framebuffer[i][2]);
		ofs << (char)(framebuffer[i][0]);
		//}
	}
}

void Scene::newSphere(float aRadius, vector<float> aCenter, vector<float> aColor) {
	objects.emplace_back(new Sphere(aRadius, aCenter, aColor));
}

void Scene::moveCamera(vector<float> offset) {
	cameraPosition = { cameraPosition[0] + offset[0],cameraPosition[1] + offset[1],cameraPosition[2] + offset[2] };
	cameraDirection = { cameraPosition[0] ,cameraPosition[1] ,cameraPosition[2] + 1 };
}

float Scene::calcLight(vector<float> point, vector<float> normal, int ki) {
	float k = 0.;
	for (auto& i : lights) {
		if (i->typeOfLight == Light::AMBIENT) {
			k += i->intensity;
		}
		else {
			vector<float> l;
			bool some;
			if (i->typeOfLight == Light::POINT) {
				l = { i->positionOrDirect[0] - point[0],i->positionOrDirect[1] - point[1],i->positionOrDirect[2] - point[2] };
				some = isShadow(point, i->positionOrDirect, ki);
			}
			else {
				l = i->positionOrDirect;
				some = isShadow(point, { point[0] + i->positionOrDirect[0],point[1] + i->positionOrDirect[1],point[2] + i->positionOrDirect[2] }, ki);
			}
			if (!some) {
				float dotOfNL = normal[0] * l[0] + normal[1] * l[1] + normal[2] * l[2];
				if (dotOfNL > 0)
					k += (i->intensity * dotOfNL) / (sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]) * sqrt(l[0] * l[0] + l[1] * l[1] + l[2] * l[2]));
			}
		}
		
	}
	if (k > 1) {
		return 1.;
	}
	return k;
}

void Scene::newLight(Light::LightType type, float aIntensity, vector<float> aPositionOrDirect) {
	lights.emplace_back(new Light(type, aIntensity, aPositionOrDirect));
}

bool Scene::isShadow(vector<float> point, vector<float> lightPosition, int ki) {
	bool d = 0;
	int ii = 0;
	for (auto& i : objects) {
		if (ii == ki)
			continue;
		vector<float> intersections = i->intersectRay(point, lightPosition);
		if (!(intersections[0] == INFINITY && intersections[0] == INFINITY)) {
			d = 1;
			break;
		}
		ii++;
	}
	return d;
}

Scene::~Scene() {
	ofs.close();
}