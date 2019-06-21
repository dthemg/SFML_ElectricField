#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using std::vector;

struct eField
{
	float eX = 0;
	float eY = 0;
};

struct charge
{
	float x; 
	float y;
	float q;
};


class Field
{
public:
	Field(float epsilon);
	float chargePotential(float x, float y);
	eField electricField(float x, float y);
	void addCharge(float x, float y, float q);
	eField electricFieldDerivative(float x, float y);
	float conv2loc(float coordV);

private:
	vector<charge> chargeLocations;
	float k;
};

