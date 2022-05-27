#include <iostream>
#include "airplane.h"

namespace avdance {

void AirPlane::setWings(int w) {
	wings = w;
}

int AirPlane::getWings() {
	return wings;
}

void AirPlane::setWheels(int w) {
	wheels = w;
}

int AirPlane::getWheels() {
	return wheels;
}

void AirPlane::setEngines(int e) {
	engines = e;;
}

int AirPlane::getEngines() {
	return engines;
}

}	// namespace avdance
