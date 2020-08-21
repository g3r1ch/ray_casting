#include "light.h"

Light::Light(Light::LightType type, float aIntensity, vector<float> aPositionOrDirect) :typeOfLight(type), intensity(aIntensity), positionOrDirect(aPositionOrDirect) {}