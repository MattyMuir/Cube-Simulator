#pragma once
#include <string>

#include "Colour.h"

enum class PieceType { CENTER, EDGE, CORNER };

class Piece
{
public:
	PieceType pieceType;
	Colour xaxis, yaxis, zaxis;

	void Blank();
};