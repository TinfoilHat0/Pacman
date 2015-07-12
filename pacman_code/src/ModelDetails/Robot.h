/*
 * Robot.h
 *
 *  Created on: Feb 27, 2014
 *      Author: mustafa
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include "../MapDetails/Node.h"
#include "Model.h"
#include <libplayerc++/playerc++.h>

class Robot : public Model{
	int cameFrom;

public:
	Robot(char* name, PlayerCc::SimulationProxy &sim, std::vector<Node> nodeList)
	 :Model(name, sim, nodeList){ this->cameFrom = -1; }
	virtual ~Robot();
	void executePath(PlayerCc::SimulationProxy &sim, std::vector<Node> path,
			 PlayerCc::Position2dProxy &pos);
	void setSpeed(double speed, PlayerCc::Position2dProxy &pos);
	void fixError();

	int getCameFrom() const {
		return cameFrom;
	}

	void setCameFrom(int cameFrom) {
		this->cameFrom = cameFrom;
	}





};

#endif /* ROBOT_H_ */
