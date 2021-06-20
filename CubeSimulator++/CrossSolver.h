#pragma once
#include <iostream>
#include <algorithm>


#include "Cube.h"
#include "pmod.h"

class Node
{
public:
	Cube cubeState;
	int gCost, hCost;
	TurnObject turn;
	std::shared_ptr<Node> parent;

	Node()
	{
		gCost = 10000;
		hCost = 10000;
		cubeState = Cube(3, false);
		turn = TurnObject();
		parent = nullptr;
	}
	int FCost() { return hCost + gCost; }
};

class CrossSolver
{
public:
	CrossSolver();

	int HCost(Cube& c);
	Sequence operator()(Cube& solveTarget);
private:
	std::unique_ptr<std::vector<TurnObject>> allTurns;
	std::vector<std::shared_ptr<Node>> activeNodes;

	int RingColourOffset(Colour c1, Colour c2);
	void AppendAdjacentNodes(std::vector<std::shared_ptr<Node>>& nodes, std::shared_ptr<Node> fromNode);
	void InitializeTurnList();
};