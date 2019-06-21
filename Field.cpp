#define _USE_MATH_DEFINES

#include "Field.h"
#include <iostream>
#include <math.h>

using namespace std;

// Constructor
Field::Field(float epsilon)
{
	k = 1. / (4.0 * M_PI * epsilon);
}

// Add charge to field
void Field::addCharge(float x, float y, float q)
{
	x = conv2loc(x);
	y = conv2loc(y);
	charge thisCharge;
	thisCharge.x = x;
	thisCharge.y = y;
	thisCharge.q = q;
	chargeLocations.push_back(thisCharge);
}

// Calculate charge potential at a given point
float Field::chargePotential(float x, float y)
{
	x = conv2loc(x);
	y = conv2loc(y);
	unsigned n_ch = chargeLocations.size();
	float p_tot = 0;

	for (int i = 0; i < n_ch; i++)
	{
		charge ch = chargeLocations[i];
		float dist = sqrt(pow(ch.x - x, 2) + pow(ch.y - y, 2));
		float p = k * ch.q/abs(dist);
		p_tot += p;
	}
	return p_tot;
}

// Calculate resulting electric field at a given point
eField Field::electricField(float x, float y)
{
	x = conv2loc(x);
	y = conv2loc(y);
	unsigned n_ch = chargeLocations.size();
	eField eF_tot;

	for (int i = 0; i < n_ch; i++)
	{
		charge ch = chargeLocations[i];
		float dist = sqrt(pow(ch.x - x, 2) + pow(ch.y - y, 2));
		float eFx = k * ch.q * (x - ch.x) / pow(abs(dist), 3);
		float eFy = k * ch.q * (y - ch.y) / pow(abs(dist), 3);
		eF_tot.eX += eFx;
		eF_tot.eY += eFy;
	}
	return eF_tot;
}

eField Field::electricFieldDerivative(float x, float y)
{
	x = conv2loc(x);
	y = conv2loc(y);
	unsigned n_ch = chargeLocations.size();
	eField eF_deriv;

	for (unsigned i = 0; i < n_ch; i++)
	{
		charge ch = chargeLocations[i];
		float D = 1.0/(sqrt(pow(ch.x - x, 2) + pow(ch.y - y, 2)));

		float eF_dx = ch.q * (-3 * (pow(D, 5) * (x - ch.x + y - ch.y) * (x - ch.x)) + pow(D, 3));
		float eF_dy = ch.q * (-3 * (pow(D, 5) * (x - ch.x + y - ch.y) * (y - ch.y)) + pow(D, 3));
		eF_deriv.eX += eF_dx;
		eF_deriv.eY += eF_dy;
	}
	eF_deriv.eX *= k;
	eF_deriv.eY *= k;

	return eF_deriv;
}

float Field::conv2loc(float coordV)
{
	return coordV / 1000.0; // TODO: Set outside
}