#pragma once
#define M(mcol) Colour(ColourEnum::mcol)

enum class ColourEnum { WHITE, YELLOW, GREEN, RED, BLUE, ORANGE, BLANK };

class Colour
{
public:
	ColourEnum colour;

	Colour();
	Colour(ColourEnum colour_);
	Colour Opposite();
};