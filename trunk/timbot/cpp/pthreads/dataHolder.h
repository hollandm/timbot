/*
 * dataHolder.h
 *
 *  Created on: Apr 17, 2014
 *      Author: matt
 */

#ifndef DATAHOLDER_H_
#define DATAHOLDER_H_

class dataHolder {
public:
	dataHolder();
	virtual ~dataHolder();

	int getNetVal() const {
		return netVal;
	}

	void setNetVal(int netVal) {
		this->netVal = netVal;
	}

	int getSensorVal1() const {
		return sensorVal1;
	}

	void setSensorVal1(int sensorVal1) {
		this->sensorVal1 = sensorVal1;
	}

	int getSensorVal2() const {
		return sensorVal2;
	}

	void setSensorVal2(int sensorVal2) {
		this->sensorVal2 = sensorVal2;
	}

private:

	int sensorVal1;
	int sensorVal2;
	int netVal;
};

#endif /* DATAHOLDER_H_ */
