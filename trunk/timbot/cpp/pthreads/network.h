/*
 * network.h
 *
 *  Created on: Apr 17, 2014
 *      Author: matt
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include "dataHolder.h"

class network {
public:
	dataHolder* data;

	network(dataHolder* data);
	virtual ~network();

	void scanNet();
};

#endif /* NETWORK_H_ */
