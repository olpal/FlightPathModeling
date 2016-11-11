/*
 * link.h
 *
 *  Created on: Jul 24, 2016
 *      Author: aolpin
 */

#ifndef LINK_H
#define LINK_H

//The link class is used to store and manipulate all information relating to a link between two nodes
class Link
{
	public:
		int _sourcex, _sourcey, _sourcez, _destinationx, _destinationy, _destinationz;
		double _distance, _fuelcost, _threatcost;

		Link(int sourcex, int sourcey, int sourcez, int destinationx, int destinationy, int destinationz);
		//Sets the source cell coordinates
		void setsource (int x, int y, int z);
		//Sets the destination cell coordinates
		void setdestination (int x, int y, int z);
		//Calculates the distance between the source cell and destination cell
		void calculatedistance(int* xdistance, int* ydistance, int* zdistance);
		//Calculates the fuel cost of the link
		double calculatefuelcost(double* climb, double* cruise, double* decent, double* rateofclimb, double* rateofdecent, double* airspeed);
		//Add loiter fuel cost
		void addloitertime(double* loiter, double time);
		//Add threat cost
		void addthreatcost(double* minfuel, double* maxfuel, double threatprobability);
};


#endif /* LINK_H_ */
