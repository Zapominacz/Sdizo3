#pragma once
#include "stdafx.h"
#include "GraphRepresentationInterface.h"
/** implementacja grafu jako macierz incydencji*/
class CityGraph {
public:
	unsigned getVertexCount(void) { return vertexCount; }
	unsigned getEdgeCount(void) { return edgeCount; }

	void printListGraph(void);
	void loadFromFile(void);
	void printMatrixGraph(void);
	Edge* getAllEdges(void);
	void generateGraph(const unsigned int, float, const int, const int);

	CityGraph(unsigned int);
	~CityGraph();
	bool insertEdge(unsigned int, unsigned int, int);
	void clear(unsigned);
	void createMatrix(void);
	void deleteMatrix(void);
	Edge* getAllEdges(void);
	bool deleteEdge(unsigned, unsigned);
	unsigned vertexDegree(unsigned);
	int searchEdge(unsigned, unsigned);
	EdgeStack* getAdjFor(unsigned);
	EdgeList* getSimpleAdjFor(unsigned);
	bool exist(unsigned, unsigned);
private:
	unsigned int vertexCount;
	unsigned int edgeCount;
	int** matrix;
};