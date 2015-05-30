#pragma once
#include "stdafx.h"
#include "CityGraph.h"

/*Klasa rozwi�zauj�ca problem komiwoja�era*/
class TspProblem {
private:
	CityGraph *citiesMap;
	CityGraph *resultMap;
	void swapCities(unsigned char&, unsigned char&);

	void permuteCities(unsigned char*, unsigned, unsigned);
	void checkIsBetterPermutation(unsigned char*, unsigned);
	//pomocnicze pola dla permutacji
	unsigned char* currentBest;
	unsigned currentBestLength;
public:
	TspProblem();
	~TspProblem();
	CityGraph* getCitiesMap() { return citiesMap; }
	CityGraph* getWay() { return resultMap; }

	void doFullCheckAlgoritm();
	void doGreedyAlgoritm();
	void do2optAlgorithm();

	void loadCityGraph();
	void generateCityGraph(const unsigned, const unsigned);
};