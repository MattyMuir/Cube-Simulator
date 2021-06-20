#pragma once
#include "Piece.h"
class Center :
    public Piece
{
public:
    Center();
    Center(Colour xaxis_, Colour yaxis_, Colour zaxis_);
};