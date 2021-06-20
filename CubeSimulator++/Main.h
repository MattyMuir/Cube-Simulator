#pragma once
#include <wx\wx.h>

#include "Canvas.h"

class Main : public wxFrame
{
public:
	Main();
	~Main();

protected:
	Canvas* mCanvas;

	wxDECLARE_EVENT_TABLE();
};