#include "fighterplane.h"
#include <iostream>
namespace avdance {

void FighterPlane::setWeapons(int w) {
	weapons = w;
}

int FighterPlane::getWeapons() {
	return weapons;
}

}	// namespace avdance
