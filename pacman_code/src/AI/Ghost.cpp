/*
 * Ghost.cpp
 *
 *  Created on: Mar 29, 2014
 *      Author: mustafa
 */

#include "Ghost.h"
#include <iostream>
using namespace std;
bool closeToPowerPill(Robot pacman, const std::vector<Model> powerpillList);

/* This ghost controller does the following:
 * 1. If edible or Ms Pac-Man is close to power pill, run away from Ms Pac-Man
 * 2. If non-edible, attack Ms Pac-Man with certain probability, else choose random direction
 */
Node Ghost::simpleAI(Map map, const std::vector<Node> &nodeList, Robot &pacman,
		std::vector<Model> &powerpillList) {

	Node nextNode;
	if (this->edible || closeToPowerPill(pacman, powerpillList)) {
		nextNode = map.getNextMoveAwayFromTarget(this->getCurrentNode(), pacman.getCurrentNode(), nodeList);
		this->setState("Evading");
	}

	else {
		this->setState("Chasing");
		//With %90 probability chase Pacman, else take a random move
		int roll = rand() % 10 + 1;
		if (roll == 10)
			nextNode = map.getRandomMove(this->currentNode, nodeList);
		else
		nextNode = map.getNextMoveTowardsTarget(this->currentNode, pacman.getCurrentNode(), nodeList);

	}
	this->eatTarget(pacman);
	return nextNode;

}
void Ghost::update(PlayerCc::SimulationProxy &sim, std::vector<Node> nodeList) {
	Model::update(sim, nodeList);
	if (this->edible)
		this->edibleCounter++;
	if (this->edibleCounter >= 40) {
		this->edible = false;
		this->edibleCounter = 0;
	}

}
void Ghost::eatTarget(Robot &pacman) {
	if (this->currentNode.equal(pacman.getCurrentNode())){
		pacman.setAlive(false);
	}
}

bool closeToPowerPill(Robot pacman, const std::vector<Model> powerpillList) {
	int minDistance = 3;
	for (int i = 0; i < powerpillList.size(); i++) {
		if (powerpillList[i].isAlive()&& pacman.getCurrentNode()
				.getDistance( powerpillList[i].getCurrentNode(), 'e') < minDistance){
			return true;
			std::cout << pacman.getCurrentNode()
						.getDistance( powerpillList[i].getCurrentNode(), 'e') << std::endl;
		}
	}

	return false;
}
Ghost::~Ghost() {
	// TODO Auto-generated destructor stub
}

