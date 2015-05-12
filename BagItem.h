#pragma once
#include "stdafx.h"

/* Klasa odpowiadajaca za element który mo¿na wsadziæ do plecaka*/
class BagItem {
public:
	unsigned getWeight() { return weight;  }
	unsigned getValue() { return value; }
	float getValueDensity() { return (float) value / (float) weight; }

	BagItem(unsigned weight, unsigned value) {
		this->value = value;
		this->weight = weight;
	}
private:
	unsigned weight;
	unsigned value;
};