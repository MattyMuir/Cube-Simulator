#include "TurnObject.h"

TurnObject::TurnObject()
{
	axis = Axis::X;
	layer = 0;
	num = 0;
}

TurnObject::TurnObject(Axis axis_, int layer_, int num_)
	: axis(axis_), layer(layer_), num(num_) { }

TurnObject::TurnObject(std::string notation)
{
	std::string faceStr = notation.substr(0, 1);
	std::string turnNum = notation.substr(std::min((size_t)1, notation.length() - 1), 1);

	axis = Axis::X;
	layer = 0;
	num = 0;
	
	if (faceStr == "U")
	{
		axis = Axis::Z;
		layer = 2;
		num = -1;
		if (turnNum == "'") { num = 1; }
		if (turnNum == "2") { num = 2; }
	}
	if (faceStr == "D")
	{
		axis = Axis::Z;
		layer = 0;
		num = 1;
		if (turnNum == "'") { num = -1; }
		if (turnNum == "2") { num = 2; }
	}
	if (faceStr == "R")
	{
		axis = Axis::Y;
		layer = 2;
		num = -1;
		if (turnNum == "'") { num = 1; }
		if (turnNum == "2") { num = 2; }
	}
	if (faceStr == "L")
	{
		axis = Axis::Y;
		layer = 0;
		num = 1;
		if (turnNum == "'") { num = -1; }
		if (turnNum == "2") { num = 2; }
	}
	if (faceStr == "F")
	{
		axis = Axis::X;
		layer = 0;
		num = 1;
		if (turnNum == "'") { num = -1; }
		if (turnNum == "2") { num = 2; }
	}
	if (faceStr == "B")
	{
		axis = Axis::X;
		layer = 2;
		num = -1;
		if (turnNum == "'") { num = 1; }
		if (turnNum == "2") { num = 2; }
	}
}

std::string TurnObject::ToString()
{
	std::string s = "";
	if (num == 0) { return s; }
	switch (axis)
	{
	case Axis::X:
		if (layer == 0)
		{
			s += "F";
			if (pmod(num, 4) == 3) { s += "'"; }
			if (pmod(num, 4) == 2) { s += "2"; }
		}
		else if (layer == 2)
		{
			s += "B";
			if (pmod(num, 4) == 1) { s += "'"; }
			if (pmod(num, 4) == 2) { s += "2"; }
		}
		break;
	case Axis::Y:
		if (layer == 0)
		{
			s += "L";
			if (pmod(num, 4) == 3) { s += "'"; }
			if (pmod(num, 4) == 2) { s += "2"; }
		}
		else if (layer == 2)
		{
			s += "R";
			if (pmod(num, 4) == 1) { s += "'"; }
			if (pmod(num, 4) == 2) { s += "2"; }
		}
		break;
	case Axis::Z:
		if (layer == 0)
		{
			s += "D";
			if (pmod(num, 4) == 3) { s += "'"; }
			if (pmod(num, 4) == 2) { s += "2"; }
		}
		else if (layer == 2)
		{
			s += "U";
			if (pmod(num, 4) == 1) { s += "'"; }
			if (pmod(num, 4) == 2) { s += "2"; }
		}
		break;
	}

	return s;
}

TurnObject TurnObject::RandomTurn()
{
	return TurnObject(static_cast<Axis>(rand() % 3), 2 * (rand() % 2), (rand() % 3) + 1);
}
