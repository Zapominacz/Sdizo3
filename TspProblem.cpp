#pragma once
#include "stdafx.h"
#include "TspProblem.h"
#include <random>
#include "MyList.h"
#include "EdgeList.h"

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
	unsigned cities = citiesMap->getVertexCount();
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
	unsigned v1 = currentBest[cities - 1];
	unsigned v2 = currentBest[0];
	resultMap->clear(cities);
	resultMap->insertEdge(v1, v2, citiesMap->searchEdge(v1, v2));
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
		return; //nie ma po³¹czenia, nie ma co szukaæ
	}
	for (unsigned i = 1; i < length; i++) {
		weight = citiesMap->searchEdge((unsigned)citiesArray[i - 1], (unsigned) citiesArray[i]);
		if (weight >= 0) {
			totalLength += weight;
		} else {
			return; //nie ma po³¹czenia, nie ma co szukaæ
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
	edgesToGenerate *= 2;
	edgesToGenerate -= vertexCount;

	MyList *list = new MyList();
	std::random_device rand_dev;
	std::uniform_int_distribution<int> weightDistr(1, weightTo);
	std::mt19937 generator(rand_dev());
	for (unsigned i = 0; i < vertexCount; i++) {
		list->addAtBeginning(i);
	}
	int hamiltonianEdges = vertexCount;
	std::uniform_int_distribution<int> distr(0, vertexCount - 1);
	int lastVertex = list->removeAt(distr(generator));
	int firstVertex = lastVertex;
	hamiltonianEdges--;
	while(hamiltonianEdges > 0) {
		std::uniform_int_distribution<int> distr(0, hamiltonianEdges - 1);
		int tmp = list->removeAt(distr(generator));
		citiesMap->insertEdge(lastVertex, tmp, weightDistr(generator));
		lastVertex = tmp;
		hamiltonianEdges--;
	}
	citiesMap->insertEdge(lastVertex, firstVertex, weightDistr(generator));

	//Generuje wszystkie mo¿liwe krawêdzie które mogê dodaæ
	delete list;
	EdgeList *el = new EdgeList();
	unsigned jdelim = vertexCount;
	for (unsigned i = 0; i < vertexCount; i++) {
		for (unsigned j = 0; j < jdelim; j++) {
			el->add(new Edge(i, j, weightDistr(generator)));
		}
	}
	//losuje z puli krawêdzi i dodaje a¿ do otrzymania po¿¹danej iloœci
	for (int i = 0; i < edgesToGenerate; i++) {
		std::uniform_int_distribution<int> edgeDistr(0, el->getSize() - 1);
		int pos = edgeDistr(generator);
		Edge* gen = el->pop(pos);
		bool exist = citiesMap->insertEdge(gen->v1, gen->v2, gen->weight);
		if (exist) {
			i--;
		}
		delete gen;
	}
	delete el;
}

void TspProblem::doGreedyAlgoritm() {
	MyList *stack = new MyList();
	unsigned vertexes = citiesMap->getVertexCount();
	bool* visited = new bool[vertexes];
	visited[0] = true;
	stack->addAtBeginning(0);
	unsigned element, dst = 0, last = 0;
	const int INF = 10000;
	int min = INF;

	bool minFlag = false;
	while (stack->getSize() > 0) {
		element = stack->getValueAt(0);
		min = INF;

		for(unsigned i = 0; i < vertexes; i++) {
			int weight = citiesMap->searchEdge(element, i);
			if (weight > 0 && visited[i] == false && min > weight) {
				min = weight;
				dst = i;
				minFlag = true;
			}
		}

		if (minFlag) {
			visited[dst] = true;
			stack->addAtBeginning(dst);
			citiesMap->insertEdge(last, dst, citiesMap->searchEdge(last, dst));
			last = dst;
			minFlag = false;
		} else {
			stack->removeAtBeginning();
		}
	}
	delete stack;
}

void TspProblem::doDynamicProgrammingAlgoritm() {
	unsigned vertexes = citiesMap->getVertexCount();
	doGreedyAlgoritm(); //2 opt startuje ju¿ z pewnej pocz¹tkowej drogi
	CityGraph *alternative = new CityGraph(resultMap);
	int improve = 0; //powtarzamy do ulepszenia
	while (improve < 20) { //prób arbitralnie
		unsigned bestDistance = resultMap->getDistance();
		for (unsigned i = 0; i < vertexes - 1; i++) {
			for (unsigned j = i + 1; j < vertexes; j++) {
				alternative->twoOptSwap(i, j, resultMap);

				unsigned newDistance = alternative->getDistance();

				if (newDistance < bestDistance) {
					improve = 0;
					resultMap->copyFrom(alternative);
				}
			}
		}

		improve++;
	}
	delete alternative;
}