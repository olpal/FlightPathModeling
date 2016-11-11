/*
 * path.h
 *
 *  Created on: Jul 25, 2016
 *      Author: aolpin
 */

#include <vector>
#include "link.h"
#ifndef PATH_H_
#define PATH_H_

class Path{

	public:
		std::vector<Link*> _links;
		double _pathfuelcost;
		double _paththreatcost;
		double _pathcost;

		//Constructor for the path class
		Path(std::vector<Link*> links);
		//This method returns the total number of links in the path
		int gettotallinks();
		//This method returns the last link in the path
		Link* getlastlink();
		//This method calculates teh costs associated with the path
		void calculatecosts();
};



#endif /* PATH_H_ */
