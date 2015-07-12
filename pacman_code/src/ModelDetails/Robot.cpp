/*
 * Robot.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: mustafa
 */

#include "Robot.h"
using namespace PlayerCc;
using namespace std;

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}
void Robot::executePath(SimulationProxy& sim, std::vector<Node> path, PlayerCc::Position2dProxy &pos) {

	const double eastYaw = 0;
	const double northYaw = 1.5718;
	const double westYaw = 3.14159;
	const double southYaw = -1.5718;

	bool yawChanged = false;
	for (int i = 0; i < path.size(); i++) {
		//next node is on NORTH
		if (this->getCurrentNode().getX() == path[i].getX()
				&& this->getCurrentNode().getY() + 1 == path[i].getY()) {
			if (this->getYaw() != northYaw) {
				this->setYaw(northYaw);
				yawChanged = true;

			}
		}
		//next node is on SOUTH
		else if (this->getCurrentNode().getX() == path[i].getX()
				&& this->getCurrentNode().getY() - 1 == path[i].getY()) {
			if (this->getYaw() != southYaw) {
				this->setYaw(southYaw);
				yawChanged = true;

			}
		}
		//next node is on EAST
		else if (this->getCurrentNode().getX() + 1 == path[i].getX()
				&& this->getCurrentNode().getY() == path[i].getY()) {
			if (this->getYaw() != eastYaw) {
				this->setYaw(eastYaw);
				yawChanged = true;

			}
		}
		//next node is on WEST
		else if (this->getCurrentNode().getX() - 1 == path[i].getX()
				&& this->getCurrentNode().getY() == path[i].getY()) {
			if (this->getYaw() != westYaw) {
				this->setYaw(westYaw);
				yawChanged = true;

			}
		}

	}

	/* SetPose function can't keep up with speed of robots and therefore, applying
	 * it constantly causes glitchy movement. In order to solve this, it is only appliedd
	 * when there is a change in yaw value.
	 */
	if (yawChanged) {
		this->setSpeed(0, pos);
		sim.SetPose2d(name, this->x, this->y ,
				this->yaw);
		if (this->yaw == northYaw || this->yaw == southYaw)
			sim.SetPose2d(name, ceil(this->x)-0.5, this->y ,
							this->yaw);
		else if (this->yaw == westYaw || this->yaw == eastYaw)
			sim.SetPose2d(name, this->x, ceil(this->y)-0.5 ,
							this->yaw);
	}

}

void Robot::setSpeed(double speed, Position2dProxy &pos) {
	pos.SetSpeed(speed, 0);
}

