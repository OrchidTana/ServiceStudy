/**
 * server class
 * @author helloworld
 * @date 2022-05-26
 * @copyleft GPL 2.0
 */
#include <iostream>
#include <unistd.h>
#include "server.h"
namespace avdance {

Server::Server() {
	std::cout << "construct..." << std::endl;
}

Server::~Server() {
	std::cout << "destruct..." << std::endl;
}

void Server::run() {
	while(1) {
		std::cout <<"running..." << std::endl;
		::usleep(2000000);	// sleep two second
	}
}

}	// namespace avdance
