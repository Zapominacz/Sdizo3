#pragma once
#include "stdafx.h"
#include "BagItem.h"

void BagItem::print() {
	using namespace std;
	cout << value << weight << valueDensity << endl;
}