#pragma once
#include "Color.h"

using namespace std;

namespace Console {
	Color::Color()
	{
		value = 0;
		representation = "0";
	}
	
	Color::Color(unsigned char v, string rep)
	{
		value = v;
		representation = rep;
	}

	unsigned char Color::getColorValue()
	{
		return value;
	}

	string Color::getColorString()
	{
		return representation;
	}
}
