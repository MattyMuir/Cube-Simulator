#pragma once
#include <string>

#include "Axis.h"
#include "pmod.h"

class TurnObject
{
public:
	Axis axis;
	int layer;
	int num;

	TurnObject();
	TurnObject(Axis axis_, int layer_, int num_);
	TurnObject(std::string notation);
	std::string ToString();

	static TurnObject RandomTurn();
};