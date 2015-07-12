/*
 * Ghost.h
 *
 *  Created on: Mar 29, 2014
 *      Author: mustafa
 */

#ifndef GHOST_H_
#define GHOST_H_
#include "../ModelDetails/Robot.h"
#include "../MapDetails/Map.h"
#include <string>
class Ghost:public Robot {
	bool edible;
	std::string state;
	int edibleCounter;

public:
	Ghost(char* name, PlayerCc::SimulationProxy &sim, std::vector<Node> nodeList)
			:Robot(name, sim, nodeList){this->edible = false; this->edibleCounter = 0;  }
	virtual ~Ghost();

	void update(PlayerCc::SimulationProxy &sim, std::vector<Node> nodeList);
	Node simpleAI(Map map, const std::vector<Node> &nodeList, Robot &pacman,
				 std::vector<Model> &pillList);
	void eatTarget(Robot &pacman);

	int getEdibleCounter() const {
		return edibleCounter;
	}

	void setEdibleCounter(int edibleCounter) {
		this->edibleCounter = edibleCounter;
	}


	std::string getState() const {
		return state;
	}

	void setState(std::string state) {
		this->state = state;
	}

	void setEdible(bool edible) {
		this->edible = edible;
	}

	bool isEdible() const {
		return this->edible;
	}
};


#endif /* GHOST_H_ */
