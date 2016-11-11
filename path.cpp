/*
 * path.cpp
 *
 *  Created on: Jul 25, 2016
 *      Author: aolpin
 */

#include "path.h"
#include <vector>

	Path::Path(std::vector<Link*> links){
		_links = links;
		_pathfuelcost=0;
		_paththreatcost=0;
		_pathcost=0;
	}
	int Path::gettotallinks(){
		return _links.size();
	}
	Link* Path::getlastlink(){
		return _links.back();
	}
	void Path::calculatecosts(){
		for(std::vector<Link*>::iterator itc = _links.begin(); itc != _links.end(); itc++)
		{
			Link* link = (*itc);
			_pathfuelcost += link->_fuelcost;
			_paththreatcost += link->_threatcost;
		}
	}


