#include <iostream>
#include "scene.h"

//no comment//

using namespace std;

//without optimization(fullHD) - 5sec

//!!!ONLY FOR STATIC IMAGE GENERATION!!!

Obj* o(){
	
}

int main()
{
	Scene scen(1920, 1080, { 0,0,0 });
	//scen.newSphere(0.5, { 0, -7, 4 }, { 255, 0, 0 });
	scen.newSphere(1, { 0, 2.5, 4 }, { 0, 0, 255 });
	scen.newSphere(1, { 0, 0, 4 }, { 0, 255, 0 });
	scen.newSphere(5000, { 0, -5001, 0 }, { 255, 255, 0 });
	//scen.newSphere(0.3, { 0,1,2 }, { 0, 255, 255 });
	scen.newLight(Light::AMBIENT,0.2);
	scen.newLight(Light::DIRECTIONAL, 0.5, { 0,100,0 });
	scen.newLight(Light::POINT, 0.2, { 0,5,4 });
	//scen.newLight(Light::POINT, 0.6, { 0,1,0 });
	scen.moveCamera({ 0,0,-0.5 });
	scen.render();
	scen.printToFile();
	return 0;
}