#pragma once
#include <vector>
#include <string>
#include <iterator>
#include <sstream>

#include "TurnObject.h"

class Sequence
{
public:
	std::vector<TurnObject> turns;

	Sequence();
	Sequence(std::string notation);
	std::string ToString();

	static Sequence RandomSequence(int len);
};