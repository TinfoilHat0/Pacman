/*
 * Node.h
 *
 *  Created on: Feb 27, 2014
 *      Author: mustafa
 */

#ifndef NODE_H_
#define NODE_H_
#include <libplayerc++/playerc++.h>
class Node {
	int x;
	int y;
	int g;
	int h;
	int f;
	bool occupied;
	Node *parent;

public:
	Node();
	Node(int x, int y);
	Node(int x, int y, bool occupied);
	virtual ~Node();
	Node getNode( std::vector<Node> nodeList);
	int getDistance(Node target, char type);
	void getWalkableAdjacentNodes(std::vector<Node> nodeList, std::vector<Node> &adjacentNodes);
	bool equal(Node node);

	Node* getParent() const {
		return parent;
	}

	void setParent(Node* parent) {
		this->parent = parent;
	}

	int getF() const {
		return f;
	}

	void setF() {
		this->f = this->g + this->h;
	}

	int getG() const {
		return g;
	}

	void setG(int g) {
		this->g = g;
	}

	int getH() const {
		return h;
	}

	void setH(int h) {
		this->h = h;
	}


	bool isOccupied() const {
		return occupied;
	}

	void setOccupied(bool occupied) {
		this->occupied = occupied;
	}

	int getX() const {
		return x;
	}

	void setX(int x) {
		this->x = x;
	}

	int getY() const {
		return y;
	}

	void setY(int y) {
		this->y = y;
	}
};

#endif /* NODE_H_ */
