#include <iostream>
#include <algorithm>
#include <cmath>
#include "gridmodel.h"
#include "link.h"
#include "path.h"
#include <map>
#include <ctime>
#include <fstream>

using namespace std;

//The grid cost model
Gridmodel* model;

map<int,map<int, vector<Link*> > > dynamicpathmap;
map<int,map<int, vector<Link*> > > binarypathmap;

//grid cost model variables
double _fcm;
double _tcm;
int _xdistance;
int _ydistance;
int _zdistance;
int _xcells;
int _ycells;
int _zcells;
int _startx;
int _starty;
int _startz;
int _endx;
int _endy;
int _endz;

//Craft variables
//Maximum fuel capacity in gallons
double _maxfuel;
//Fuel consumption in gal/hr
double _fuelconsumptionclimb;
double _fuelconsumptioncruise;
double _fuelconsumptionloiter;
double _fuelconsumptiondecent;
//meters per hour to climb/decent
double _rateofclimb;
double _rateofdecent;
//Airspeed of the craft in meters/h
double _airspeed;

//This method initializes the model variables
void IntializeVariables(){
	_maxfuel = 49.0;
	_fuelconsumptionclimb = 4.4;
	_fuelconsumptioncruise = 4.2;
	_fuelconsumptionloiter = 3.5;
	_fuelconsumptiondecent = 4.0;
	_rateofclimb = 18288;
	_rateofdecent = 98156;
	_airspeed = 196312;
	_xdistance = 20000;
	_ydistance = 1524;
	_zdistance = 20000;
	_xcells = 10;
	_ycells = 4;
	_zcells = 10;
	_startx = 0;
	_starty = 0;
	_startz = 4;
	_endx = 9;
	_endy = 3;
	_endz = 6;
	_fcm = 0.8;
	_tcm = 0.2;
}

//This method sets adds a list of forbidden cells
void setforbiddencells(){
	model->addforbidden(1,0,0);
	model->addforbidden(1,0,1);
	model->addforbidden(1,0,2);
	model->addforbidden(2,0,0);
	model->addforbidden(2,0,1);
	model->addforbidden(2,0,2);
	model->addforbidden(3,0,0);
	model->addforbidden(3,0,1);
	model->addforbidden(3,0,2);
	model->addforbidden(2,1,0);
	model->addforbidden(2,1,1);
	model->addforbidden(2,1,2);
	model->addforbidden(1,1,1);
	model->addforbidden(3,1,1);
	model->addforbidden(2,2,1);

	model->addforbidden(2,0,7);
	model->addforbidden(3,0,6);
	model->addforbidden(3,0,7);
	model->addforbidden(3,0,8);
	model->addforbidden(3,1,7);
	model->addforbidden(4,0,7);

	model->addforbidden(4,0,4);
	model->addforbidden(5,0,3);
	model->addforbidden(5,0,4);
	model->addforbidden(5,0,5);
	model->addforbidden(6,0,2);
	model->addforbidden(6,0,3);
	model->addforbidden(6,0,4);
	model->addforbidden(6,0,5);
	model->addforbidden(6,0,6);
	model->addforbidden(7,0,3);
	model->addforbidden(7,0,4);
	model->addforbidden(7,0,5);
	model->addforbidden(8,0,4);
	model->addforbidden(5,1,4);
	model->addforbidden(6,1,3);
	model->addforbidden(6,1,4);
	model->addforbidden(6,1,5);
	model->addforbidden(7,1,3);
	model->addforbidden(7,1,4);
	model->addforbidden(7,1,5);
	model->addforbidden(8,1,4);
	model->addforbidden(6,2,4);
	model->addforbidden(7,2,3);
	model->addforbidden(7,2,4);
	model->addforbidden(7,2,5);
	model->addforbidden(8,2,4);
	model->addforbidden(7,3,4);

}

//This method adds threats to the appropriate cells
void addthreatcosts(){
	model->addthreatcost(0,0,8,0.7);
	model->addthreatcost(1,0,7,0.75);
	model->addthreatcost(1,0,3,0.78);
	model->addthreatcost(3,0,5,0.73);
	model->addthreatcost(4,0,3,0.8);
	model->addthreatcost(6,0,8,0.81);
	model->addthreatcost(6,0,1,0.82);
	model->addthreatcost(7,0,0,0.85);
	model->addthreatcost(9,0,3,0.89);
	model->addthreatcost(2,0,4,0.71);
	model->addthreatcost(6,1,6,0.81);

	model->addthreatcost(8,1,6,0.75);
	model->addthreatcost(8,1,5,0.75);

	model->addthreatcost(8,1,7,0.72);
	model->addthreatcost(7,1,2,0.74);
	model->addthreatcost(3,1,2,0.71);
	model->addthreatcost(4,1,9,0.73);
	model->addthreatcost(3,2,7,0.78);
	model->addthreatcost(4,2,6,0.79);
	model->addthreatcost(5,2,6,0.76);
	model->addthreatcost(7,2,6,0.75);
	model->addthreatcost(1,2,3,0.73);
	model->addthreatcost(3,2,4,0.71);

	model->addthreatcost(2,2,4,0.73);
	model->addthreatcost(1,2,7,0.71);
	model->addthreatcost(6,3,7,0.72);
	model->addthreatcost(6,3,0,0.72);
	model->addthreatcost(6,3,8,0.74);
	model->addthreatcost(2,3,4,0.76);
	model->addthreatcost(4,3,6,0.77);
	model->addthreatcost(5,3,6,0.78);
	model->addthreatcost(7,3,6,0.79);
	model->addthreatcost(8,3,6,0.71);

	model->addthreatcost(7,3,5,0.79);
	model->addthreatcost(6,3,5,0.71);

	model->addthreatcost(2,1,4,0.79);
	model->addthreatcost(3,1,5,0.71);
	model->addthreatcost(3,1,3,0.79);
	model->addthreatcost(4,1,6,0.71);
	model->addthreatcost(4,1,2,0.79);
	model->addthreatcost(5,1,7,0.71);


}

//This method calculates total cost according to the objective function
//fuelcost = the fuelcost of a link
//threatcost = the threat cost of a link
double calculatecost(double fuelcost, double threatcost){
	return (_fcm * fuelcost) + (_tcm * threatcost);
}

//This method constructs the grid model
void constructgridmodel(){
	model = new Gridmodel(_xcells, _ycells, _zcells, &_xdistance, &_ydistance, &_zdistance);
	model->setsingleposition(_startx, _starty, _startz);
	model->setsingleposition(_endx, _endy, _endz);
	setforbiddencells();
	model->buildlinkpaths();
	model->calculatefuelcosts(&_fuelconsumptionclimb, &_fuelconsumptioncruise, &_fuelconsumptiondecent, &_rateofclimb, &_rateofdecent, &_airspeed);
	addthreatcosts();
}

//This method solves the model using dynamic programming
//The method returns a map data structure that is as follows:
//key = stage 1,2...n value = map (key = unique cell id, value = vector of lowest cost links )
void solvedynamic(){
	map<int,double> cellcosts;
	dynamicpathmap.clear();

    //Process the last record
    std::vector<Link*> finalcosts = model->getgridvalue(_endx, _endy, _endz);
    for(std::vector<Link*>::iterator it = finalcosts.begin(); it != finalcosts.end(); it++)
    {
    	Link* link = (*it);
    	int cellid = model->get3dposition(link->_sourcex, link->_sourcey, link->_sourcez);
    	cellcosts[cellid] = calculatecost(link->_fuelcost, link->_threatcost);
    	dynamicpathmap[_xcells-1][cellid].push_back(link);
    }

    //Process the remaining stages
	for(int x=_xcells-2; x>0; x--)
	{
		for(int y=0;y<_ycells;y++)
		{
			for(int z=0;z<_zcells;z++)
			{
				//Only continue if the current cell has a cost value, indicating it has a path to the end
				int cellid = model->get3dposition(x, y, z);
				double currentcellcost = cellcosts[cellid];
				if(currentcellcost > 0)
				{
					std::vector<Link*> links = model->getgridvalue(x, y, z);
					for(std::vector<Link*>::iterator itc = links.begin(); itc != links.end(); itc++)
					{
						Link* link = (*itc);
						int sourcecellid = model->get3dposition(link->_sourcex, link->_sourcey, link->_sourcez);
						//Get the cost of the source cell + the cost of the current cell
						double newcellcost =  calculatecost(link->_fuelcost, link->_threatcost) + currentcellcost;
						//Get the current cost of the source cell
						double currentsourcecellcost = cellcosts[sourcecellid];
						//If the cost is 0 or the new cost is less than the current cost
						if(currentsourcecellcost == 0 || currentsourcecellcost > newcellcost)
						{
							cellcosts[sourcecellid] = newcellcost;
							dynamicpathmap[x][sourcecellid].clear();
							dynamicpathmap[x][sourcecellid].push_back(link);
						}
						//If the new cost is the same as the current cost add the equivalent path
						else if (currentsourcecellcost == newcellcost)
						{
							dynamicpathmap[x][sourcecellid].push_back(link);
						}
					}
				}
			}
		}
	}
}

void solvebinary(){
	binarypathmap.clear();
    //Process the remaining stages
	for(int x=1; x< _xcells; x++)
	{
		for(int y=0;y<_ycells;y++)
		{
			for(int z=0;z<_zcells;z++)
			{
				std::vector<Link*> links = model->getgridvalue(x, y, z);
				for(std::vector<Link*>::iterator itc = links.begin(); itc != links.end(); itc++)
				{
					Link* link = (*itc);
					int sourcecellid = model->get3dposition(link->_sourcex, link->_sourcey, link->_sourcez);
					binarypathmap[x][sourcecellid].push_back(link);
				}
			}
		}
	}
}

//This method calculates a paths
//cellpaths = a map where key = integer representing stage
//value = map (key = integer unique cell id, value = vector of links associated with this cell)
vector<Path*> calculatepath(map<int,map<int, vector<Link*> > > cellpaths){
	vector<Path*> solutions;

	//Get the first vector list from the first stage, there should only be one since there is always only one starting position
	vector<Link*> currentstage = cellpaths[1][model->get3dposition(_startx, _starty, _startz)];
	for(std::vector<Link*>::iterator itc = currentstage.begin(); itc != currentstage.end(); itc++)
	{
		vector<Link*> solution (1, (*itc));
		Path* path = new Path(solution);
		solutions.push_back(path);
	}

	//Process all subsequent elements
	for(int i = 2; i<_xcells; i++){
		//get the map for the current stage
		map<int, vector<Link*> > currentstage = cellpaths[i];
		vector<Path*> toiterate = solutions;
		solutions.clear();
		for(std::vector<Path*>::iterator itc = toiterate.begin(); itc != toiterate.end(); itc++)
		{
			//Get the next path and cost objects
			Path* path = (*itc);
			Link* lastlink = path->getlastlink();

			//Iterate through all the equal cost outgoing links adding a path for each path permutation
			vector<Link*> outgoingpaths = currentstage[model->get3dposition(lastlink->_destinationx,lastlink->_destinationy,lastlink->_destinationz)];
			for(std::vector<Link*>::iterator it = outgoingpaths.begin(); it != outgoingpaths.end(); it++){
				vector<Link*> currentpath = path->_links;
				Link* currentcost = (*it);
				currentpath.push_back(currentcost);
				solutions.push_back(new Path(currentpath));
			}

		}
	}
	return solutions;
}

//This method checks if a solution violates the constraints
//path = a solution to check for validity
//returns a boolean indicating if the solution violates constraints
bool violateconstraints(Path* path){
	if(path->_pathfuelcost > _maxfuel){
		return true;
	}
	return false;
}

//This method calculates the costs associated with a solution
//solutions = a list of Paths pointers to process
//returns a list of processed paths that have had their costs calculated and constraints checked
vector<Path*> calculateobjectivefunction(vector<Path*> solutions){
	vector<Path*> finalpaths;
	double currentcost = 0;

	//Calculate costs of every path
	for(std::vector<Path*>::iterator itc = solutions.begin(); itc != solutions.end(); itc++)
	{
		Path* path = (*itc);
		//Don't proceed of a constraint is violated
		if(violateconstraints(path)){continue;}
		path->calculatecosts();
		double pathcost = calculatecost(path->_pathfuelcost, path->_paththreatcost);
		path->_pathcost = pathcost;
		if(pathcost < currentcost || currentcost == 0){
			finalpaths.clear();
			finalpaths.push_back(path);
			currentcost = pathcost;
		}
		else if (pathcost == currentcost){
			finalpaths.push_back(path);
		}
	}

	return finalpaths;
}

//This method writes the final solutions to a file
//solutions = a list of path pointers representing solutions to output
//outfile =  open file stream
void outputsolution(vector<Path*> solutions, std::ofstream& outfile){
	for(std::vector<Path*>::iterator itc = solutions.begin(); itc != solutions.end(); itc++)
	{
		Path* path = (*itc);
		//Print the start position
		outfile << _startx << "," << _starty << "," << _startz << "\n";
		//Print all the destination
		for(std::vector<Link*>::iterator itc = path->_links.begin(); itc != path->_links.end(); itc++)
		{
			Link* link = (*itc);
			outfile << link->_destinationx << "," << link->_destinationy << "," << link->_destinationz << "\n";
		}
		outfile << "----\n\n" << "Objective function = " << path->_pathcost << "\nfuel cost = " << (path->_pathfuelcost * _fcm) << "\nthreat cost = " << (path->_paththreatcost * _tcm) << "\n";

	}
}


//Main execution method
int main() {
	IntializeVariables();
	constructgridmodel();

	solvedynamic();
	vector<Path*> dynamicpaths = calculatepath(dynamicpathmap);
	vector<Path*> finaldynamicpaths = calculateobjectivefunction(dynamicpaths);

	ofstream outfile;
	outfile.open ("./modelrun.log");
	outputsolution(finaldynamicpaths, outfile);
	outfile.close();

	return 0;

}
