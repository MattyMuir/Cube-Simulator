#include "Colour.h"

Colour::Colour()
{
	colour = ColourEnum::BLANK;
}

Colour::Colour(ColourEnum colour_)
{
	colour = colour_;
}

Colour Colour::Opposite()
{
	switch (colour)
	{
	case ColourEnum::WHITE:
		return Colour(ColourEnum::YELLOW);
	case ColourEnum::YELLOW:
		return Colour(ColourEnum::WHITE);
	case ColourEnum::RED:
		return Colour(ColourEnum::ORANGE);
	case ColourEnum::ORANGE:
		return Colour(ColourEnum::RED);
	case ColourEnum::GREEN:
		return Colour(ColourEnum::BLUE);
	case ColourEnum::BLUE:
		return Colour(ColourEnum::GREEN);
	}
}
