#pragma once
#include "Piece.h"
class Corner :
    public Piece
{
public:
    Corner();
    Corner(Colour xaxis_, Colour yaxis_, Colour zaxis_);
};