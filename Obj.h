#ifndef OBJ_H
#define OBJ_H

#include <iostream>
#include <vector>

using namespace std;

class Obj {
public:
	virtual vector<float> intersectRay(vector<float> orig, vector<float> dir) const = 0;
	virtual vector<float> getColor() const = 0;
	virtual vector<float> getCenter() const = 0;
	float dot(vector<float> a, vector<float> b) const {
		if (a.size() < 3) {
			return 0;
		}
		else if (b.size() < 3) {
			return 0;
		}

		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	}
	vector<float> mVec(vector<float> a, vector<float> b) const {
		return { a[0] - b[0],a[1] - b[1],a[2] - b[2] };
	}
};

#endif // !OBJ_H

