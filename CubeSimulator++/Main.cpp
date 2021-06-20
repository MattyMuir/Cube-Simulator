#include "Main.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
	// Events
wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "Cube Simulator", wxPoint(30, 30), wxSize(600, 600))
{
	mCanvas = new Canvas(this);
}

Main::~Main()
{

}