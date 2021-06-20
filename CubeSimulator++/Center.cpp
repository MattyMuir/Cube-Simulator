#include "Center.h"

Center::Center()
{
	pieceType = PieceType::CENTER;

	xaxis = Colour();
	yaxis = Colour();
	zaxis = Colour();
}

Center::Center(Colour xaxis_, Colour yaxis_, Colour zaxis_)
{
	pieceType = PieceType::CENTER;

	xaxis = xaxis_;
	yaxis = yaxis_;
	zaxis = zaxis_;
}