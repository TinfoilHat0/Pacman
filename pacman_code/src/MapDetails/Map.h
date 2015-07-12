/*
 * Map.h
 *
 *  Created on: Feb 27, 2014
 *      Author: mustafa
 */

#ifndef MAP_H_
#define MAP_H_
#include "Node.h"
#include "../ModelDetails/Model.h"
#include <ctime>
#include <cstdlib>


class Map {
public:
	Map();
	virtual ~Map();


	std::vector<Node> findPath(const Node &start,const Node &end, std::vector<Node> nodeList);
	Node getNextMoveTowardsTarget(const Node &start, const Node &end, const std::vector<Node> &nodeList);
	Node getNextMoveAwayFromTarget(Node start, Node end, const std::vector<Node> &nodeList);
	Node getRandomMove(Node start, const std::vector<Node> &nodeList);


};

#endif /* MAP_H_ */
