/*
 * network.cpp
 *
 *  Created on: Apr 17, 2014
 *      Author: matt
 */

#include "network.h"

network::network(dataHolder* data) {
	this->data = data;
}

network::~network() {
	// TODO Auto-generated destructor stub
}

void network::scanNet() {

	this->data->setNetVal(0);
//	this->data->setNetVal(0);

}

int main (int argc, char *argv[]) {

	dataHolder d = dataHolder();
//	network n = network(&d);

	return 0;
}

