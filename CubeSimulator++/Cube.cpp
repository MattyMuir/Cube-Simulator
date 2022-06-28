#include "Cube.h"
#define edge(expr) (expr == 0 || expr == order - 1)

Cube::Cube(int order_, bool coloured)
{
	order = order_;

	int pieceNum = 6 * order * order - 12 * order + 8;
	pieces.resize(pieceNum);

	int index = 0;
	for (int z = 0; z < order; z++)
	{
		for (int y = 0; y < order; y++)
		{
			for (int x = 0; x < order; x++)
			{
				if (!edge(x) && !edge(y) && !edge(z)) { continue; }

				int numEdges = edge(x) + edge(y) + edge(z);

				switch (numEdges)
				{
				case 1:
					pieces[index] = std::make_shared<Center>();
					break;
				case 2:
					pieces[index] = std::make_shared<Edge>();
					break;
				case 3:
					pieces[index] = std::make_shared<Corner>();
					break;
				}

				if (coloured)
				{
					Piece& pieceRef = *pieces[index];
					if (x == 0) { pieceRef.xaxis = M(GREEN); }
					if (x == order - 1) { pieceRef.xaxis = M(BLUE); }
					if (y == 0) { pieceRef.yaxis = M(ORANGE); }
					if (y == order - 1) { pieceRef.yaxis = M(RED); }
					if (z == 0) { pieceRef.zaxis = M(YELLOW); }
					if (z == order - 1) { pieceRef.zaxis = M(WHITE); }
				}
				index++;
			}
		}
	}
}

Cube::Cube()
{
	order = 0;
	pieces = std::vector<std::shared_ptr<Piece>>();
}

int Cube::Index(Vec3& pos)
{
	return Index(pos.x, pos.y, pos.z);
}

int Cube::Index(int order, int x, int y, int z)
{
	if (z == 0)
	{
		return order * y + x;
	}
	else if (z == order - 1)
	{
		return (5 * order * order - 12 * order + 8) + order * y + x;
	}
	else
	{
		if (y == 0)
		{
			return order * order + (z - 1) * (4 * order - 4) + x;
		}
		else if (y == order - 1)
		{
			return order * order + (z - 1) * (4 * order - 4) + order + 2 * (order - 2) + x;
		}
		else
		{
			if (x == 0)
			{
				return order * order + (z - 1) * (4 * order - 4) + order + (y - 1) * 2;
			}
			else
			{
				return order * order + (z - 1) * (4 * order - 4) + order + (y - 1) * 2 + 1;
			}
		}
	}
}

int Cube::Index(int x, int y, int z)
{
	if (z == 0)
	{
		return order * y + x;
	}
	else if (z == order - 1)
	{
		return (5 * order * order - 12 * order + 8) + order * y + x;
	}
	else
	{
		if (y == 0)
		{
			return order * order + (z - 1) * (4 * order - 4) + x;
		}
		else if (y == order - 1)
		{
			return order * order + (z - 1) * (4 * order - 4) + order + 2 * (order - 2) + x;
		}
		else
		{
			if (x == 0)
			{
				return order * order + (z - 1) * (4 * order - 4) + order + (y - 1) * 2;
			}
			else
			{
				return order * order + (z - 1) * (4 * order - 4) + order + (y - 1) * 2 + 1;
			}
		}
	}
}

Colour Cube::GetTileColour(Face face, int x, int y)
{
	switch (face)
	{
	case Face::UP:
		return (*pieces[Index(y, x, order - 1)]).zaxis;
	case Face::DOWN:
		return (*pieces[Index(order - y - 1, x, 0)]).zaxis;
	case Face::RIGHT:
		return (*pieces[Index(x, order - 1, y)]).yaxis;
	case Face::LEFT:
		return (*pieces[Index(order - x - 1, 0, y)]).yaxis;
	case Face::FRONT:
		return (*pieces[Index(0, x, y)]).xaxis;
	case Face::BACK:
		return (*pieces[Index(order - 1, order - x - 1, y)]).xaxis;
	}
}

void Cube::Turn(Axis axis, int layer)
{
	Cube copy = *this;
	int xpos, ypos, zpos;
	int endx, endy, endz;
	std::shared_ptr<Piece>* newPiecePP;
	std::shared_ptr<Piece>* oldPiecePP;
	Colour oldCol;
	for (int x = 0; x < order; x++)
	{
		for (int y = 0; y < order; y++)
		{
			if (!(layer == 0 || layer == order - 1 || edge(x) || edge(y))) { continue; }

			switch (axis)
			{
			case Axis::X:
				xpos = layer;
				ypos = x;
				zpos = y;

				endx = xpos;
				endy = zpos;
				endz = order - 1 - ypos;

				newPiecePP = &pieces[Index(endx, endy, endz)];
				oldPiecePP = &copy.pieces[Index(xpos, ypos, zpos)];

				*newPiecePP = *oldPiecePP;

				oldCol = (*newPiecePP)->yaxis;
				(*newPiecePP)->yaxis = (*oldPiecePP)->zaxis;
				(*newPiecePP)->zaxis = oldCol;
				break;
			case Axis::Y:
				xpos = x;
				ypos = layer;
				zpos = y;

				endx = order - 1 - zpos;
				endy = ypos;
				endz = xpos;

				newPiecePP = &pieces[Index(endx, endy, endz)];
				oldPiecePP = &copy.pieces[Index(xpos, ypos, zpos)];

				*newPiecePP = *oldPiecePP;

				oldCol = (*newPiecePP)->xaxis;
				(*newPiecePP)->xaxis = (*oldPiecePP)->zaxis;
				(*newPiecePP)->zaxis = oldCol;
				break;
			case Axis::Z:
				xpos = y;
				ypos = x;
				zpos = layer;

				endx = ypos;
				endy = order - 1 - xpos;
				endz = zpos;

				newPiecePP = &pieces[Index(endx, endy, endz)];
				oldPiecePP = &copy.pieces[Index(xpos, ypos, zpos)];

				*newPiecePP = *oldPiecePP;

				oldCol = (*newPiecePP)->xaxis;
				(*newPiecePP)->xaxis = (*oldPiecePP)->yaxis;
				(*newPiecePP)->yaxis = oldCol;
				break;
			}
		}
	}
}

void Cube::AntiTurn(Axis axis, int layer)
{
	Cube copy = *this;
	int xpos, ypos, zpos;
	int endx, endy, endz;
	std::shared_ptr<Piece>* newPiecePP;
	std::shared_ptr<Piece>* oldPiecePP;
	Colour oldCol;
	for (int x = 0; x < order; x++)
	{
		for (int y = 0; y < order; y++)
		{
			if (!(layer == 0 || layer == order - 1 || edge(x) || edge(y))) { continue; }

			switch (axis)
			{
			case Axis::X:
				xpos = layer;
				ypos = x;
				zpos = y;

				endx = xpos;
				endy = order - 1 - zpos;
				endz = ypos;

				newPiecePP = &pieces[Index(endx, endy, endz)];
				oldPiecePP = &copy.pieces[Index(xpos, ypos, zpos)];

				*newPiecePP = *oldPiecePP;

				oldCol = (*newPiecePP)->yaxis;
				(*newPiecePP)->yaxis = (*oldPiecePP)->zaxis;
				(*newPiecePP)->zaxis = oldCol;
				break;
			case Axis::Y:
				xpos = x;
				ypos = layer;
				zpos = y;

				endx = zpos;
				endy = ypos;
				endz = order - 1 - xpos;

				newPiecePP = &pieces[Index(endx, endy, endz)];
				oldPiecePP = &copy.pieces[Index(xpos, ypos, zpos)];

				*newPiecePP = *oldPiecePP;

				oldCol = (*newPiecePP)->xaxis;
				(*newPiecePP)->xaxis = (*oldPiecePP)->zaxis;
				(*newPiecePP)->zaxis = oldCol;
				break;
			case Axis::Z:
				xpos = y;
				ypos = x;
				zpos = layer;

				endx = order - 1 - ypos;
				endy = xpos;
				endz = zpos;

				newPiecePP = &pieces[Index(endx, endy, endz)];
				oldPiecePP = &copy.pieces[Index(xpos, ypos, zpos)];

				*newPiecePP = *oldPiecePP;

				oldCol = (*newPiecePP)->xaxis;
				(*newPiecePP)->xaxis = (*oldPiecePP)->yaxis;
				(*newPiecePP)->yaxis = oldCol;
				break;
			}
		}
	}
}

void Cube::DoubleTurn(Axis axis, int layer)
{
	Cube copy = *this;
	int xpos, ypos, zpos;
	int endx, endy, endz;
	std::shared_ptr<Piece>* newPiecePP;
	std::shared_ptr<Piece>* oldPiecePP;
	Colour oldCol;
	for (int x = 0; x < order; x++)
	{
		for (int y = 0; y < order; y++)
		{
			if (!(layer == 0 || layer == order - 1 || edge(x) || edge(y))) { continue; }

			switch (axis)
			{
			case Axis::X:
				xpos = layer;
				ypos = x;
				zpos = y;

				endx = xpos;
				endy = order - 1 - ypos;
				endz = order - 1 - zpos;

				newPiecePP = &pieces[Index(endx, endy, endz)];
				oldPiecePP = &copy.pieces[Index(xpos, ypos, zpos)];

				*newPiecePP = *oldPiecePP;
				break;
			case Axis::Y:
				xpos = x;
				ypos = layer;
				zpos = y;

				endx = order - 1 - xpos;
				endy = ypos;
				endz = order - 1 - zpos;

				newPiecePP = &pieces[Index(endx, endy, endz)];
				oldPiecePP = &copy.pieces[Index(xpos, ypos, zpos)];

				*newPiecePP = *oldPiecePP;
				break;
			case Axis::Z:
				xpos = y;
				ypos = x;
				zpos = layer;

				endx = order - 1 - xpos;
				endy = order - 1 - ypos;
				endz = zpos;

				newPiecePP = &pieces[Index(endx, endy, endz)];
				oldPiecePP = &copy.pieces[Index(xpos, ypos, zpos)];

				*newPiecePP = *oldPiecePP;
				break;
			}
		}
	}
}

void Cube::ApplyTurn(TurnObject& t)
{
	int mod = fmod(t.num, 4);
	int num = (mod >= 0) ? mod : mod + 4;
	if (num == 1) { this->Turn(t.axis, t.layer); }
	if (num == 2) { this->DoubleTurn(t.axis, t.layer); }
	if (num == 3) { this->AntiTurn(t.axis, t.layer); }
}

void Cube::ApplySequence(Sequence& seq)
{
	for (TurnObject& t : seq.turns)
	{
		this->ApplyTurn(t);
	}
}

void Cube::Reset()
{
	for (int z = 0; z < order; z++)
	{
		for (int y = 0; y < order; y++)
		{
			for (int x = 0; x < order; x++)
			{
				int index = Index(x, y, z);

				Piece& pieceRef = *pieces[index];
				pieceRef.Blank();
				if (x == 0) { pieceRef.xaxis = M(GREEN); }
				if (x == order - 1) { pieceRef.xaxis = M(BLUE); }
				if (y == 0) { pieceRef.yaxis = M(ORANGE); }
				if (y == order - 1) { pieceRef.yaxis = M(RED); }
				if (z == 0) { pieceRef.zaxis = M(YELLOW); }
				if (z == order - 1) { pieceRef.zaxis = M(WHITE); }
			}
		}
	}
}

void Cube::CopyColours(Cube& targetCube)
{
	for (int i = 0; i < pieces.size(); i++)
	{
		pieces[i]->xaxis = targetCube.pieces[i]->xaxis;
		pieces[i]->yaxis = targetCube.pieces[i]->yaxis;
		pieces[i]->zaxis = targetCube.pieces[i]->zaxis;
	}
}

void Cube::ApplyTurn(std::string tStr)
{
	TurnObject t(tStr);
	this->ApplyTurn(t);
}

void Cube::ApplySequence(std::string sStr)
{
	Sequence s(sStr);
	this->ApplySequence(s);
}

bool Cube::IsSolved()
{
	std::vector<Colour> x1, x2, y1, y2, z1, z2;
	for (int z = 0; z < order; z++)
	{
		for (int y = 0; y < order; y++)
		{
			for (int x = 0; x < order; x++)
			{
				int index = Index(x, y, z);
				Piece& pieceRef = *pieces[index];

				if (x == 0) { x1.push_back(pieceRef.xaxis); }
				if (x == order - 1) { x2.push_back(pieceRef.xaxis); }
				if (y == 0) { y1.push_back(pieceRef.yaxis); }
				if (y == order - 1) { y2.push_back(pieceRef.yaxis); }
				if (z == 0) { z1.push_back(pieceRef.zaxis); }
				if (z == order - 1) { z2.push_back(pieceRef.zaxis); }
			}
		}
	}

	bool solved = true;

	Colour col = x1[0];
	for (Colour c : x1) { if (c.colour != col.colour) { solved = false; } }

	col = x2[0];
	for (Colour c : x2) { if (c.colour != col.colour) { solved = false; } }

	col = y1[0];
	for (Colour c : y1) { if (c.colour != col.colour) { solved = false; } }

	col = y2[0];
	for (Colour c : y2) { if (c.colour != col.colour) { solved = false; } }

	col = z1[0];
	for (Colour c : z1) { if (c.colour != col.colour) { solved = false; } }

	col = z2[0];
	for (Colour c : z2) { if (c.colour != col.colour) { solved = false; } }

	return solved;
}