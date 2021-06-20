#include "Corner.h"

Corner::Corner()
{
	pieceType = PieceType::CORNER;

	xaxis = Colour();
	yaxis = Colour();
	zaxis = Colour();
}

Corner::Corner(Colour xaxis_, Colour yaxis_, Colour zaxis_)
{
	pieceType = PieceType::CORNER;

	xaxis = xaxis_;
	yaxis = yaxis_;
	zaxis = zaxis_;
}