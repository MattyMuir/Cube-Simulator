#pragma once
#include <wx\wx.h>
#include <wx\dcclient.h>
#include <wx\dcmemory.h>
#include <wx\dcbuffer.h>

#include <thread>

#include "Cube.h"
#include "CrossSolver.h"

class Canvas : wxPanel
{
public:
	Canvas(wxWindow* parent_);
	~Canvas();
protected:
	int w, h;

	void OnDraw(wxDC& dc);
	void OnPaint(wxPaintEvent& evt);
	void Resized(wxSizeEvent& evt);
	void Idle(wxIdleEvent& evt);

	void MouseDown(wxMouseEvent& evt);

	wxWindow* parent;
	Cube cube;
	CrossSolver solver;
	wxString debugStr;

	wxDECLARE_EVENT_TABLE();
};