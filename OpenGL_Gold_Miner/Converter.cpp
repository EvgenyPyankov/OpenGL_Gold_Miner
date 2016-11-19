#include "Converter.h"
#include "Constants.h"

using namespace Constants;

float Converter::getX(double x) {
	return 2*(x-0.5);
}

float Converter::getY(double y) {
	return 2*(0.5-y);
}

float Converter::getZ(double z)
{
	return 2*(z - 0.5);
}

float Converter::getLength(double l) {
	return 2*l;
}
