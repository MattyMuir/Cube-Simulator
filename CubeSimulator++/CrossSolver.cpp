#include "CrossSolver.h"

CrossSolver::CrossSolver()
{
    InitializeTurnList();
}

int CrossSolver::HCost(Cube& c)
{
    int hCost = 0;
    char parityByte = 0;
    for (int z = 0; z < 3; z++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 3; x++)
            {
                int index = Cube::Index(3, x, y, z);
                std::shared_ptr<Piece> piecePtr = c.pieces[index];
                if (piecePtr->pieceType == PieceType::EDGE)
                {
                    if (piecePtr->xaxis.colour == ColourEnum::WHITE
                        || piecePtr->yaxis.colour == ColourEnum::WHITE
                        || piecePtr->zaxis.colour == ColourEnum::WHITE)
                    {
                        if ((z == 0 || z == 2) && piecePtr->zaxis.colour != ColourEnum::WHITE)
                        {
                            // Piece is parity-less
                            hCost += 2;
                        }
                        else
                        {
                            if (z != 2) { hCost += 1; }
                            // Determine piece parity
                            if (piecePtr->xaxis.colour == ColourEnum::WHITE)
                            {
                                if (y == 0)
                                {
                                    // Orange center
                                    parityByte = parityByte | RingColourOffset(piecePtr->yaxis, ColourEnum::ORANGE);
                                }
                                else
                                {
                                    // Red center
                                    parityByte = parityByte | RingColourOffset(piecePtr->yaxis, ColourEnum::RED);
                                }
                            }
                            if (piecePtr->yaxis.colour == ColourEnum::WHITE)
                            {
                                if (x == 0)
                                {
                                    // Green center
                                    parityByte = parityByte | RingColourOffset(piecePtr->xaxis, ColourEnum::GREEN);
                                }
                                else
                                {
                                    // Blue center
                                    parityByte = parityByte | RingColourOffset(piecePtr->xaxis, ColourEnum::BLUE);
                                }
                            }
                            if (piecePtr->zaxis.colour == ColourEnum::WHITE)
                            {
                                if (x == 0)
                                {
                                    // Green center
                                    parityByte = parityByte | RingColourOffset(piecePtr->xaxis, ColourEnum::GREEN);
                                }
                                else if (x == 2)
                                {
                                    // Blue center
                                    parityByte = parityByte | RingColourOffset(piecePtr->xaxis, ColourEnum::BLUE);
                                }
                                if (y == 0)
                                {
                                    // Orange center
                                    parityByte = parityByte | RingColourOffset(piecePtr->yaxis, ColourEnum::ORANGE);
                                }
                                else if (y == 2)
                                {
                                    // Red center
                                    parityByte = parityByte | RingColourOffset(piecePtr->yaxis, ColourEnum::RED);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    char parityCases[16] = { 1, 0, 1, 2, 1, 2, 3, 4, 1, 2, 3, 4, 3, 4, 5, 6 };
    return hCost + parityCases[parityByte];
}

Sequence CrossSolver::operator()(Cube& solveTarget)
{
    activeNodes.clear();
    std::shared_ptr<Node> start = std::make_shared<Node>();
    start->cubeState = solveTarget;
    start->gCost = 0;
    start->hCost = HCost(solveTarget);

    std::shared_ptr<Node> current;
    current = start;
    bool running = (current->hCost != 0);
    while (running)
    {
        AppendAdjacentNodes(activeNodes, current);
        std::sort(activeNodes.begin(), activeNodes.end(), [](std::shared_ptr<Node>& n1, std::shared_ptr<Node>& n2) { return n1->FCost() < n2->FCost(); });

        current = activeNodes[0];

        if (current->hCost == 0) { running = false; }

        activeNodes.erase(activeNodes.begin());
    }

    std::vector<TurnObject> turnsBackward;
    bool hasParent = current->parent != nullptr;
    turnsBackward.push_back(current->turn);
    while (hasParent)
    {
        current = current->parent;
        turnsBackward.push_back(current->turn);
        hasParent = (current->parent != nullptr);
    }

    Sequence s = Sequence();
    for (int i = 0; i < turnsBackward.size(); i++)
    {
        s.turns.push_back(turnsBackward[turnsBackward.size() - 1 - i]);
    }

    return s;
}

int CrossSolver::RingColourOffset(Colour c1, Colour c2)
{
    int offsets[4] = { 1, 2, 4, 8 };
    return offsets[pmod(static_cast<int>(c1.colour) - static_cast<int>(c2.colour),4)];
}

void CrossSolver::AppendAdjacentNodes(std::vector<std::shared_ptr<Node>>& nodes, std::shared_ptr<Node> fromNode)
{
    nodes.reserve(nodes.size() + 18);

    int originalSize = nodes.size();
    for (int i = 0; i < 18; i++)
    {
        nodes.push_back(std::make_shared<Node>());
    }
    for (int t = 0; t < 18; t++)
    {
        Node& currentNode = *(nodes[originalSize + t]);

        currentNode.parent = fromNode;
        currentNode.cubeState.CopyColours(fromNode->cubeState);
        currentNode.cubeState.ApplyTurn((*allTurns)[t]);
        currentNode.turn = (*allTurns)[t];

        currentNode.gCost = fromNode->gCost + 1;
        currentNode.hCost = HCost(currentNode.cubeState);
    }
}

void CrossSolver::InitializeTurnList()
{
    allTurns = std::make_unique<std::vector<TurnObject>>();
    (*allTurns).reserve(18);
    int index = 0;
    for (int axis = 0; axis < 3; axis++)
    {
        for (int layer = 0; layer < 3; layer += 2)
        {
            for (int num = 1; num < 4; num++)
            {
                (*allTurns).emplace_back(static_cast<Axis>(axis), layer, num);
            }
        }
    }
}