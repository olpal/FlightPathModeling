/*
 * link.cpp
 *
 *  Created on: Jul 24, 2016
 *      Author: aolpin
 */

#include "link.h"
#include <cmath>
#include <cstdlib>

	Link::Link(int sourcex, int sourcey, int sourcez, int destinationx, int destinationy, int destinationz)
	{
		_sourcex = sourcex;
		_sourcey = sourcey;
		_sourcez = sourcez;
		_destinationx = destinationx;
		_destinationy = destinationy;
		_destinationz = destinationz;
		_fuelcost = 0;
		_threatcost = 0;
		_distance = 0;
	}

	void Link::setsource (int x, int y, int z)
	{
		_sourcex = x;
		_sourcey = y;
		_sourcez = z;
	}

	void Link::setdestination (int x, int y, int z)
	{
		_destinationx = x;
		_destinationy = y;
		_destinationz = z;
	}

	void Link::calculatedistance(int* xdistancein, int* ydistancein, int* zdistancein)
	{
		int xdistance = *xdistancein;
		int ydistance = *ydistancein;
		int zdistance = *zdistancein;
		//If the destination cell is forward only on the x plane,
		//moves only along the Y or Z plains are not allowed so only x is accounted for
		if(_sourcey == _destinationy && _sourcez == _destinationz && _sourcex != _destinationx)
		{
			_distance = abs(_destinationx - _sourcex) * xdistance;
		}
		//If this is a move on the X and Z plain, left or right in the next stage
		else if(_sourcey == _destinationy && _sourcez != _destinationz && _sourcex != _destinationx)
		{
			double sidec = pow(abs(_destinationz - _sourcez) * zdistance,2) + pow(abs(_destinationx-_sourcex) * xdistance,2);
			_distance = sqrt(sidec);
		}
		//If this is a move on the X and Y plain, up or down in the next stage
		else if(_sourcey != _destinationy && _sourcez == _destinationz && _sourcex != _destinationx)
		{
			double sidec = pow(abs(_destinationy - _sourcey) * ydistance,2) + pow(abs(_destinationx-_sourcex) * xdistance,2);
			_distance = sqrt(sidec);
		}
		//If this is a move on all 3 plains, up to the left or right down to the left or right
		else if(_sourcey != _destinationy && _sourcez != _destinationz && _sourcex != _destinationx)
		{
			double sidea = sqrt(pow((abs(_destinationy - _sourcey) * ydistance),2) + pow((abs(_destinationx-_sourcex) * xdistance),2));
			double sideb = abs(_destinationz - _sourcez) * zdistance;
			_distance = sqrt(pow(sidea,2) + pow(sideb,2));
		}
	}

	double Link::calculatefuelcost(double* climb, double* cruise, double* decent, double* rateofclimb, double* rateofdecent, double* airspeed)
	{
		if(_sourcey == _destinationy)
		{
			_fuelcost = (_distance / *airspeed) * *cruise;
		}
		else if(_sourcey < _destinationy)
		{
			_fuelcost = (_distance / *rateofclimb) * *climb;
		}
		else if(_sourcey > _destinationy)
		{
			_fuelcost = (_distance / *rateofdecent) * *decent;
		}
		return _fuelcost;

	}

	void Link::addloitertime(double* loiter, double time)
	{
		_fuelcost += (*loiter * time);

	}

	void Link::addthreatcost(double* minfuel, double* maxfuel, double threatprobability)
	{
		_threatcost = (*maxfuel - *minfuel) * threatprobability;
	}



