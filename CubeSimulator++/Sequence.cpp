#include "Sequence.h"

Sequence::Sequence()
{
	turns = std::vector<TurnObject>();
}

Sequence::Sequence(std::string notation)
{
	std::stringstream ss(notation);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	for (std::string& moveStr : vstrings)
	{
		turns.emplace_back(moveStr);
	}
}

std::string Sequence::ToString()
{
	std::string s = "";
	for (int i = 0; i < turns.size(); i++)
	{
		s += turns[i].ToString();
		if (i < turns.size() - 1)
		{
			s += " ";
		}
	}
	return s;
}

Sequence Sequence::RandomSequence(int len)
{
	Sequence s = Sequence();
	TurnObject t;
	for (int i = 0; i < len; i++)
	{
		bool valid = false;
		while (!valid)
		{
			t = TurnObject::RandomTurn();
			if (i == 0) { valid = true; }
			else
			{
				valid = (s.turns[i - 1].axis != t.axis);
			}
		}
		s.turns.push_back(t);
	}
	return s;
}
