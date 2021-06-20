#pragma once
#include "Piece.h"
class Edge :
    public Piece
{
public:
    Edge();
    Edge(Colour xaxis_, Colour yaxis_, Colour zaxis_);
};