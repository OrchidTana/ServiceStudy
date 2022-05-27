#pragma once

#include <iostream>
#include "airplane.h"

namespace avdance {

class FighterPlane: public AirPlane {
	public:
		FighterPlane() {
			weapons = 1;
		}
		~FighterPlane() {

		}

	public:
		void setWeapons(int w);
		int getWeapons();


	private:
		int weapons;

};


}	// namespace avdance
