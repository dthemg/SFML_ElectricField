#define _USE_MATH_DEFINES

#include "Field.h"
#include <iostream>
#include <math.h>

using namespace std;

// Constructor
Field::Field(float epsilon)
{
	k = 1. / (4 * M_PI * epsilon);
}

// Add charge to field
void Field::addCharge(float x, float y, float q)
{
	charge thisCharge;
	thisCharge.x = x;
	thisCharge.y = y;
	thisCharge.q = q;
	chargeLocations.push_back(thisCharge);
}

// Calculate charge potential at a given point
float Field::chargePotential(float x, float y)
{
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