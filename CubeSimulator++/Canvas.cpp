#include "Canvas.h"

wxBEGIN_EVENT_TABLE(Canvas, wxPanel)
	EVT_PAINT(Canvas::OnPaint)
	EVT_SIZE(Canvas::Resized)
	EVT_LEFT_DOWN(Canvas::MouseDown)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow* parent_) : wxPanel(parent_, wxID_ANY)
{
	parent = parent_;
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	cube = Cube(3, true);
	debugStr = "";
	srand(time(0));

	cube.ApplySequence("F R' D2 F D2 L F' B L' B' D'");

	Sequence solution = solver(cube);
	debugStr = wxString(solution.ToString());
}

Canvas::~Canvas()
{

}

void Canvas::OnDraw(wxDC& dc)
{
	dc.Clear();
	// Drawing here
	float tileWidth = std::min((float)(w - 15) / (4 * cube.order), (float)(h - 30) / (3 * cube.order));
	float faceWidth = tileWidth * cube.order;
	std::vector<Face> faceOrder{ Face::UP, Face::LEFT, Face::FRONT, Face::RIGHT, Face::BACK, Face::DOWN };
	std::vector<std::pair<float, float>> Offsets{ { faceWidth + 5, faceWidth }, { 0, 2 * faceWidth + 5 },
		{ faceWidth + 5, 2 * faceWidth + 5 }, { 2 * faceWidth + 10, 2 * faceWidth + 5 }, { 3 * faceWidth + 15, 2 * faceWidth + 5 }, { faceWidth + 5, 3 * faceWidth + 10 }, };

	wxPen pen = dc.GetPen();
	pen.SetColour(0, 0, 0);
	pen.SetWidth(2);
	dc.SetPen(pen);

	for (int f = 0; f < 6; f++)
	{
		for (int x = 0; x < cube.order; x++)
		{
			for (int y = 0; y < cube.order; y++)
			{
				wxBrush brush = dc.GetBrush();
				Colour tileCol = cube.GetTileColour(faceOrder[f], x, y);
				switch (tileCol.colour)
				{
				case ColourEnum::WHITE:
					brush.SetColour(255, 255, 255);
					break;
				case ColourEnum::YELLOW:
					brush.SetColour(255, 255, 0);
					break;
				case ColourEnum::RED:
					brush.SetColour(255, 0, 0);
					break;
				case ColourEnum::ORANGE:
					brush.SetColour(255, 128, 0);
					break;
				case ColourEnum::GREEN:
					brush.SetColour(0, 255, 0);
					break;
				case ColourEnum::BLUE:
					brush.SetColour(0, 0, 255);
					break;
				}
				dc.SetBrush(brush);

				dc.DrawRectangle(Offsets[f].first + x * tileWidth, Offsets[f].second - y * tileWidth - tileWidth, tileWidth, tileWidth);
			}
		}
	}
	dc.DrawText(debugStr, 100, faceWidth * 3 + 15);
}

void Canvas::OnPaint(wxPaintEvent& evt)
{
	wxBufferedPaintDC dc(this);
	this->GetSize(&w, &h);
	this->PrepareDC(dc);
	this->OnDraw(dc);
}

void Canvas::Resized(wxSizeEvent& evt)
{
	this->GetSize(&w, &h);
	this->Refresh();
	evt.Skip();
}

void dostuff()
{

}

void Canvas::MouseDown(wxMouseEvent& evt)
{
	debugStr = "Searching...";
	this->Refresh();
	this->Update();

	int searched = 0;
	bool found = false;
	Sequence scramble, crossSolution;
	while (!found)
	{
		cube.Reset();
		scramble = Sequence::RandomSequence(25);
		cube.ApplySequence(scramble);

		crossSolution = solver(cube);
		cube.ApplySequence(crossSolution);

		Piece& p1 = *cube.pieces[Cube::Index(3, 0, 0, 2)];
		Piece& p2 = *cube.pieces[Cube::Index(3, 0, 0, 1)];
		if (p1.xaxis.colour == ColourEnum::GREEN && p1.yaxis.colour == ColourEnum::ORANGE && p1.zaxis.colour == ColourEnum::WHITE)
		{
			if (p2.xaxis.colour == ColourEnum::GREEN && p2.yaxis.colour == ColourEnum::ORANGE)
			{
				found = true;
			}
		}
		searched++;
	}
	debugStr = wxString(scramble.ToString()) + "\n" + wxString(crossSolution.ToString()) + "\n" + wxString::Format(wxT("%i"), searched);

	this->Refresh();
	this->Update();
	parent->Destroy();
}