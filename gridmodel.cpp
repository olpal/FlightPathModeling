#include <vector>
#include <algorithm>
#include <cmath>
#include "gridmodel.h"

Gridmodel::Gridmodel(int xcells, int ycells, int zcells, int* xdistance, int* ydistance, int* zdistance)
{
	_xcells = xcells;
	_ycells = ycells;
	_zcells = zcells;
	_xdistance = xdistance;
	_ydistance = ydistance;
	_zdistance = zdistance;
	_minfuelcost = 0;
	_maxfuelcost = 0;
	Gridmodel::landgrid = std::vector<std::vector<Link*> > (_xcells * _ycells * _zcells, Gridmodel::defaultcost);
}

int Gridmodel::get3dposition(int x, int y, int z)
{
	return (y*_xcells) + (z*(_xcells*_ycells)) + x ;
}

void Gridmodel::addforbidden(int x, int y, int z)
{
	forbiddencells.push_back(get3dposition(x,y,z));
}

bool Gridmodel::isforbidden(int x, int y, int z)
{
	if(std::find(Gridmodel::forbiddencells.begin(), Gridmodel::forbiddencells.end(), get3dposition(x,y,z)) == Gridmodel::forbiddencells.end())
	{
		return false;
	}
	else
	{
		return true;
	}

}

void Gridmodel::setsingleposition(int xin, int yin, int zin)
{
	for(int y=0;y<_ycells;y++)
	{
		for(int z=0;z<_zcells;z++)
		{
			if(y != yin || z != zin)
			{
				addforbidden(xin, y, z);
			}
		}
	}
}

std::vector<Link*> Gridmodel::getgridvalue(int x, int y, int z)
{
	return Gridmodel::landgrid[get3dposition(x,y,z)];
}

void Gridmodel::addlinkcost(int x, int y, int z, Link* value)
{
	if(!isforbidden(x,y,z))
	{
		Gridmodel::landgrid[get3dposition(x,y,z)].push_back(value);
	}
}

void Gridmodel::addlink(int sourcex, int sourcey, int sourcez, int offsetx, int offsety, int offsetz)
{
	int newcellx = (sourcex + offsetx);
	int newcelly = (sourcey + offsety);
	int newcellz = (sourcez + offsetz);
	//If any of the new cells fall outside the bounds of operating grid
	if( newcellx < 0 || newcellx >= _xcells || newcelly < 0 || newcelly >= _ycells ||  newcellz < 0 || newcellz >= _zcells)
	{
		return;
	}
	Link* linkcost = new Link(sourcex, sourcey, sourcez, newcellx, newcelly, newcellz);
	linkcost->calculatedistance( _xdistance, _ydistance, _zdistance);
	addlinkcost(newcellx, newcelly, newcellz, linkcost);
}

void Gridmodel::buildlinkpaths(){
	for(int x=0;x<_xcells;x++)
	{
		for(int y=0;y<_ycells;y++)
		{
			for(int z=0;z<_zcells;z++)
			{
				if(!isforbidden(x,y,z))
				{
					//9 possible moves from every cell
					addlink(x, y, z, 1, 0, 0);
					addlink(x, y, z, 1, 1, 0);
					addlink(x, y, z, 1, -1, 0);
					addlink(x, y, z, 1, 0, 1);
					addlink(x, y, z, 1, 1, 1);
					addlink(x, y, z, 1, -1, 1);
					addlink(x, y, z, 1, 0, -1);
					addlink(x, y, z, 1, 1, -1);
					addlink(x, y, z, 1, -1, -1);
				}
			}
		}
	}
}

void Gridmodel::calculatefuelcosts(double* climb, double* cruise, double* decent, double* rateofclimb, double* rateofdecent, double* airspeed){
	for(int x=0;x<_xcells;x++)
	{
		for(int y=0;y<_ycells;y++)
		{
			for(int z=0;z<_zcells;z++)
			{
				std::vector<Link*> links = getgridvalue(x, y, z);
				for(std::vector<Link*>::iterator it = links.begin(); it != links.end(); it++)
				{
					double fuelcost = (*it)->calculatefuelcost(climb, cruise, decent, rateofclimb, rateofdecent, airspeed);
					if(fuelcost > _maxfuelcost){_maxfuelcost = fuelcost;}
					if((_minfuelcost == 0) || (fuelcost < _minfuelcost)){_minfuelcost = fuelcost;}
				}
			}
		}
	}
}

void Gridmodel::addthreatcost(int x, int y, int z, double threatprobability)
{
	std::vector<Link*> links = getgridvalue(x, y, z);
	for(std::vector<Link*>::iterator it = links.begin(); it != links.end(); it++)
	{
		(*it)->addthreatcost(&_minfuelcost, &_maxfuelcost, threatprobability);
	}
}
