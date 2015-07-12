/*
 * Pacman.h
 *
 *  Created on: Mar 29, 2014
 *      Author: mustafa
 */

#ifndef PACMAN_H_
#define PACMAN_H_
#include "../ModelDetails/Robot.h"
#include "../MapDetails/Map.h"
#include "Ghost.h"
#include <string>
class Pacman:public Robot{
	int score;
	int lives;
	std::string state;
public:
	Pacman(char* name, PlayerCc::SimulationProxy &sim, std::vector<Node> nodeList)
		:Robot(name, sim, nodeList){this->score = 0; this->lives = 3; };
	virtual ~Pacman();


	void eatTarget(std::vector<Model> &pillList,
			std::vector<Model> &powerpillList, std::vector<Ghost> &ghostList);
	Node getNearestPill(const std::vector<Model> &pillList, const std::vector<Model> &powerpillList);
	Node getNearestEdibleGhost(const std::vector<Ghost> &ghostList);
	Node simpleAI(Map map, const std::vector<Node> &nodeList, std::vector<Ghost> &ghostList,
			 std::vector<Model> &pillList, std::vector<Model> &powerpillList,
			 std::vector<Model> &targetList);

	int getLives() const
	{
		return lives;
	}

	void setLives(int lives)
	{
		this->lives = lives;
	}

	std::string getState() const
	{
		return state;
	}

	void setState(std::string state)
	{
		this->state = state;
	}

	int getScore() const
	{
		return score;
	}

	void setScore(int score)
	{
		this->score = score;
	}
};


#endif /* PACMAN_H_ */
