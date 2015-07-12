/*
 * Model.cpp
 *
 *  Created on: Feb 28, 2014
 *      Author: mustafa
 */

#include "Model.h"
using namespace PlayerCc;
using namespace std;

Model::Model()
{
}

Model::Model(char* name, SimulationProxy &sim, vector<Node> nodeList) {
	this->name = name;
	sim.GetPose2d(this->name, this->x, this->y, this->yaw);
	this->alive = true;
	Node node(ceil(x), ceil(y));
	this->currentNode = node.getNode(nodeList);

}
void Model::update(SimulationProxy &sim, vector<Node> nodeList) {
	sim.GetPose2d(name, this->x , this->y , this->yaw);
	Node node(ceil(x), ceil(y));
	this->setCurrentNode(node.getNode(nodeList));

}
Model::~Model() {
	// TODO Auto-generated destructor stub
}

