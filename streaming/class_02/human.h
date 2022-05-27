#pragma once

#include <iostream>

namespace avdane {

class Human {
	public:
		Human() {
			std::cout << "construct human..." << std::endl;
			age = 0;
			sex = 0;
		};

		~Human(){
			std::cout << "destruct human..." << std::endl;
		}

	public:
		void setAge(int age);
		int getAge();

		void setSex(int sex);
		int getSex();
	private:
		int age;
		int sex;	// 0:male  1:female
};

}	// namespace
