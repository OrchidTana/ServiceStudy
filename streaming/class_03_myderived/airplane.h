#pragma once

#include <iostream>

namespace avdance {

class AirPlane {
	public:
		AirPlane() {
			wings = 2;
			wheels = 3;
			engines = 2;
		}
		~AirPlane() {}

	public:
		void setWings(int w);
		int getWings();

		void setWheels(int w);
		int getWheels();
		
		void setEngines(int e);
		int getEngines();

	private:
		int wings;
		int wheels;
		int engines;
	
	public:
		void fly();
};

}
