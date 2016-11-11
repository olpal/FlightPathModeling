/*
 * gridmodel.h
 *
 *  Created on: Jul 24, 2016
 *      Author: aolpin
 */

#ifndef GRIDMODEL_H_
#define GRIDMODEL_H_

#include <algorithm>
#include <cmath>
#include <vector>
#include "link.h"

class Gridmodel
{
	public:
		//Size of the grid to construct in cells
		int _xcells;
		int _ycells;
		int _zcells;

		//Distance in meters
		int* _xdistance;
		int* _ydistance;
		int* _zdistance;

		//The max and min fuelcosts for the entire model
		double _maxfuelcost;
		double _minfuelcost;

		std::vector<Link*> defaultcost;
		//A vector of pointers to forbidden cells
		std::vector<int> forbiddencells;
		//A three dimensional vector where each value is a vector itself
		std::vector<std::vector<Link*> > landgrid;

		//This method adds a cell to the forbidden cells list
		//x = the x position of the cell
		//y = the y position of the cell
		//z = the z position of the cell
		void addforbidden(int x, int y, int z);

		//This method adds a new link if it is within the boundries of the grid
		//sourcex = the x position of the source cell
		//sourcey = the y position of the source cell
		//sourcez = the z position of the source cell
		//offsetx = the offset to add to determine the x position of the next cell
		//offsety = the offset to add to determine the y position of the next cell
		//offsetz = the offset to add to determine the z position of the next cell
		void addlink(int sourcex, int sourcey, int sourcez, int offsetx, int offsety, int offsetz);

		//This method will get the pointer value at a specified location
		//x = the x position of the cell
		//y = the y position of the cell
		//z = the z position of the cell
		//value = a pointer to a link to add the cost to
		void addlinkcost(int x, int y, int z, Link* value);

		//This method adds threat cost to all cost objects associated with a cell
		//x = the x position of the cell to add threat cost to
		//y = the y position of the cell to add threat cost to
		//z = the z position of the cell to add threat cost to
		void addthreatcost(int x, int y, int z, double threatprobability);

		//This method builds all link paths betwen all relevant cells
		void buildlinkpaths();

		//This method calculates the costs associated with all links between cells
		//climb = the fuel/gallons per hour when climbing
		//cruise = the fuel/gallons per hour when climbing
		//decent = the fuel/gallons per hour when climbing
		//rateofclimb = the speed in which climbing happens in meters per hour
		//rateofdecent = the speed in meters per hour the craft can decent
		//airspeed = the crusining speed in meters per hour
		void calculatefuelcosts(double* climb, double* cruise, double* decent, double* rateofclimb, double* rateofdecent, double* airspeed);

		//This method will return a one dimensional value based on a three dimensional coordinate
		//x = the x position of the cell
		//y = the y position of the cell
		//z = the z position of the cell
		//returns = a one dimensional coordinate
		int get3dposition(int x, int y, int z);

		//This method will return the vector from a certain position in the array
		//x = the x position of the cell
		//y = the y position of the cell
		//z = the z position of the cell
		//returns a vector of links associated with that cell where destination
		//should equal that cell and source will equal the orginating cell
		std::vector<Link*> getgridvalue(int x, int y, int z);

		//The constructor for the grid class
		//int = number of x cells
		//int = number of y cells
		//int = number of z cells
		//int = distance of an x cell
		//int = distance of an y cell
		//int = distance of an z cell
		Gridmodel(int, int, int, int*, int*, int*);

		//This method checks if a cell is forbidden
		//x = the x position of the cell
		//y = the y position of the cell
		//z = the z position of the cell
		//returns boolean indicating if the cells is forbidden
		bool isforbidden(int x, int y, int z);

		//This method sets a single point in a Z,Y based panel as valid and the rest as forbidden
		//x = the x position of the valid cell
		//y = the y position of the valid cell
		//z = the z position of the valid cell
		void setsingleposition(int x, int y, int z);

};


#endif /* GRIDMODEL_H_ */
