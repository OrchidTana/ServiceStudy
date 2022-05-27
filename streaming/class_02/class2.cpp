/**
 * this program is constructing for testing class and using it 
 *
 * @author	helloworld
 * @date	2022-05-26
 * @copyleft	GPL 2.0
 */

#include <iostream>
#include "human.h"

int main(int argc, char* argv[]) {
	avdane::Human* human = new avdane::Human();
	human->setAge(18);
	human->setSex(1);
	
	std::cout << "human: " << human->getAge() << ", " << human->getSex() << std::endl;

	//delete human;

	return 0;
}
