#pragma once
#include <vector>
#include <memory>
#include <string>

#include "AllPieces.h"
#include "Colour.h"
#include "Vec3.h"
#include "Axis.h"
#include "TurnObject.h"
#include "Sequence.h"

enum class Face { UP, DOWN, RIGHT, LEFT, FRONT, BACK };

class Cube
{
public:
	std::vector<std::shared_ptr<Piece>> pieces;
	int order;

	Cube();
	Cube(int order_, bool coloured);
	int Index(int x, int y, int z);
	static int Index(int order, int x, int y, int z);
	int Index(Vec3& pos);
	Colour GetTileColour(Face face, int x, int y);
	void Turn(Axis axis, int layer);
	void AntiTurn(Axis axis, int layer);
	void DoubleTurn(Axis axis, int layer);

	void ApplyTurn(TurnObject& t);
	void ApplySequence(Sequence& seq);
	void ApplyTurn(std::string tStr);
	void ApplySequence(std::string sStr);

	void Reset();
	void CopyColours(Cube& targetCube);
};