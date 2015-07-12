/*
 * Model.h
 *
 *  Created on: Feb 28, 2014
 *      Author: mustafa
 */

#ifndef MODEL_H_
#define MODEL_H_
#include "../MapDetails/Node.h"
class Model {
protected:
	char* name;
	double x;
	double y;
	double yaw;
	Node currentNode;
	bool alive;
public:
	Model();
	Model(char* name, PlayerCc::SimulationProxy &sim, std::vector<Node> nodeList);
	virtual ~Model();
	void update(PlayerCc::SimulationProxy &sim, std::vector<Node> nodeList);
	/*void initModelList(PlayerCc::SimulationProxy &sim, std::vector<Model> &pillList);
	void updateModelList(PlayerCc::SimulationProxy &sim, std::vector<Model> &pillList);*/

	double getY() const {
		return y;
	}

	void setY(double y) {
		this->y = y;
	}

	double getYaw() const {
		return yaw;
	}

	void setYaw(double yaw) {
		this->yaw = yaw;
	}

	bool isAlive() const {
		return alive;
	}

	void setAlive(bool alive) {
		this->alive = alive;
	}

	Node getCurrentNode() const {
		return currentNode;
	}

	void setCurrentNode(Node currentNode) {
		this->currentNode = currentNode;
	}

	char* getName() const {
		return name;
	}

	void setName(char* name) {
		this->name = name;
	}

	double getX() const {
		return x;
	}

	void setX(double x) {
		this->x = x;
	}
};

#endif /* MODEL_H_ */
