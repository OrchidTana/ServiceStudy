/**
 * this file is testing deriver
 * @author helloworld
 * @date 2022-05-26
 * @copyleft GPL 2.0
 */

#include <iostream>
#include "fighterplane.h"

int main(int argc, char* argv[]) {
	avdance::FighterPlane fp;
	fp.setWings(5);
	fp.setWheels(3);
	fp.setWeapons(10);

	std::cout << "FighterPlane" << fp.getWings() << ", " 
								<< fp.getWheels() << ", "
								<< fp.getWeapons() << std::endl;
	
	return 0;

}
