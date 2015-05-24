#pragma once
#include "stdafx.h"
#include "CityGraph.h"

class TspProblem {
private:
	CityGraph *cities;
	CityGraph *result;
public:
	TspProblem();
	~TspProblem();
	void setCityGraph(CityGraph*);
	void setStartCity(int);
	CityGraph* getCitiesMap();
	CityGraph* getWay();

	void doFullCheckAlgoritm();
	void doGreedyAlgoritm();
	void doDynamicProgrammingAlgoritm();

	void loadCityGraph();
	void generateCityGraph(int, int);
};