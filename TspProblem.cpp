#pragma once
#include "TspProblem.h"
#include <random>

TspProblem::TspProblem() {
	currentBest = NULL;
	citiesMap = NULL;
	resultMap = NULL;
	currentBestLength = 0;
}

TspProblem::~TspProblem() {
	if (currentBest != NULL) {
		delete[] currentBest;
	}
	if (citiesMap != NULL) {
		delete[] citiesMap;
	}
	if (resultMap != NULL) {
		delete[] resultMap;
	}
}

void TspProblem::doFullCheckAlgoritm() {
	int cities = citiesMap->getVertexCount();
	if (cities > 256) {
		std::cerr << "Algorytm obsluguje do 256 miast" << std::endl;
	}
	unsigned char* citiesOrder = new unsigned char[cities];
	currentBest = new unsigned char[cities];
	//Pierwsza permutacja
	for (unsigned i = 0; i < cities; i++) {
		citiesOrder[i] = i;
	}
	permuteCities(citiesOrder, 0, cities);
	if (resultMap != NULL) {
		delete resultMap;
	}
	unsigned v1 = currentBest[cities - 1];
	unsigned v2 = currentBest[0];
	resultMap->insertEdge(v1, v2, citiesMap->searchEdge(v1, v2));
	resultMap = new CityGraph(cities);
	for (unsigned i = 1; i < cities; i++) {
		v1 = currentBest[i - 1];
		v2 = currentBest[i];
		resultMap->insertEdge(v1, v2, citiesMap->searchEdge(v1, v2));
	}
	delete[] citiesOrder;
	delete[] currentBest;
	currentBest = NULL;
}

void TspProblem::swapCities(unsigned char& one, unsigned char& two) {
	unsigned char tmp = one;
	one = two;
	two = tmp;
}

void TspProblem::permuteCities(unsigned char *citiesArray, unsigned i, unsigned length) {
	if (length == i){
		checkIsBetterPermutation(citiesArray, length);
	} else {
		for (unsigned j = i; j < length; j++) {
			swapCities(citiesArray[i], citiesArray[j]);
			permuteCities(citiesArray, i + 1, length);
			swapCities(citiesArray[i], citiesArray[j]);
		}
	}
}

void TspProblem::checkIsBetterPermutation(unsigned char *citiesArray, unsigned length) {
	unsigned totalLength = 0;
	int weight = citiesMap->searchEdge((unsigned)citiesArray[length - 1], (unsigned)citiesArray[0]);
	if (weight >= 0) {
		totalLength += weight;
	} else {
		return; //nie ma po��czenia, nie ma co szuka�
	}
	for (unsigned i = 1; i < length; i++) {
		weight = citiesMap->searchEdge((unsigned)citiesArray[i - 1], (unsigned) citiesArray[i]);
		if (weight >= 0) {
			totalLength += weight;
		} else {
			return; //nie ma po��czenia, nie ma co szuka�
		}
	}
	if (totalLength > currentBestLength) {
		currentBestLength = totalLength;
		memcpy(currentBest, citiesArray, length * sizeof(unsigned char));
	}
}

void TspProblem::loadCityGraph() {
	using namespace std;
	char patch[64];
	cout << "sciezka: ";
	cin >> patch;
	fstream file(patch, ios_base::in);
	unsigned liczbaMiast;
	file >> liczbaMiast;
	if (citiesMap != NULL) {
		delete citiesMap;
	}
	citiesMap = new CityGraph(liczbaMiast);
	int waga;
	for (unsigned v1 = 0; v1 < liczbaMiast; v1++) {
		for (unsigned v2 = 0; v2 < liczbaMiast; v2++) {
			file >> waga;
			if (waga > 0) {
				citiesMap->insertEdge(v1, v2, waga);
			}
		}
	}
	file.close();
}

void TspProblem::generateCityGraph(const unsigned vertexCount,
		float density, const unsigned weightTo) {
	using namespace std;

	citiesMap->clear(vertexCount);
	int edgesToGenerate = (int)((density * vertexCount * (vertexCount - 1)) / 2);
	if (isDiGraph) {
		edgesToGenerate *= 2;
	}
	int spanningEdge = vertexCount - 1;
	std::random_device rand_dev;
	std::uniform_int_distribution<int> weightDistr(weightFrom, weightTo);
	std::mt19937 generator(rand_dev());
	for (int i = 0; i < liczba; i++) {
		itemsList[i] = BagItem(weightDistr(generator), valueDistr(generator));
	}
}