#include "Edge.h"

Edge::Edge()
{
	pieceType = PieceType::EDGE;

	xaxis = Colour();
	yaxis = Colour();
	zaxis = Colour();
}

Edge::Edge(Colour xaxis_, Colour yaxis_, Colour zaxis_)
{
	pieceType = PieceType::EDGE;

	xaxis = xaxis_;
	yaxis = yaxis_;
	zaxis = zaxis_;
}