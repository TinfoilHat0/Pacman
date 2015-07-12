/*An early version of pacman framework for Player/Stage sim.
 *
 * Bugs: Glitchy movement occurs when robots move at high speed.
 * this happens due to the conflict between simProxy and model update.
 * A possible solution would be switching their hierarchy. (SOLVED, 26.03.2014)
 *
 * Initializing ghosts: Add them to .cfg and .world files. Then initialize
 * them with the same manner as PacMan's since they share proxies.
 *
 * To do: Add a sample AI agent for both PacMan and Ghosts.(COMPLETED, 8.04.2014)
 *
 * Notes: To get best visual output, make robots' sizes equal with grids
 * and set their center of origin in middle.
 *
 *
 */

#pragma GCC diagnostic ignored "-Wwrite-strings"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "../MapDetails/Map.h"
#include "../AI/Pacman.h"
#include "../AI/Ghost.h"
using namespace PlayerCc;
using namespace std;

//initialize player clients for robots
PlayerClient robot("localhost", 6665);
PlayerClient ghostRed("localhost", 6666);
PlayerClient ghostBlue("localhost", 6667);
PlayerClient ghostPink("localhost", 6668);
PlayerClient ghostOrange("localhost", 6669);

//function prototypes
void printData(Pacman pacman, const vector<Model> &pillList,
		const vector<Model> &powerpillList, const vector<Ghost> &ghostList,
		const vector<Node> &path);
void createPillList(SimulationProxy &sim, vector<Model> &pillList,
		vector<Model> &powerpillList, vector<Node> nodeList,
		vector<Model> &targetList);
void updatePillList(SimulationProxy &sim, vector<Model> &pillList,
		vector<Model> &powerpillList, vector<Node> nodeList);
void updateGame(PlayerCc::SimulationProxy &sim, vector<Ghost> &ghostList,
		vector<Model> &pillList, vector<Model> &powerpillList, Pacman &pacman);
void createNodeList(vector<Node> &nodeList);

int main(int argc, char *argv[]) {
	//Setup proxies
	Position2dProxy pos(&robot, 0);
	Position2dProxy posRed(&ghostRed, 0);
	Position2dProxy posBlue(&ghostBlue, 0);
	Position2dProxy posPink(&ghostPink, 0);
	Position2dProxy posOrange(&ghostOrange, 0);
	SimulationProxy sim(&robot, 0);

	//initialize proxies
	pos.SetMotorEnable(1);
	pos.RequestGeom();
	posRed.SetMotorEnable(1);
	posRed.RequestGeom();
	posBlue.SetMotorEnable(1);
	posBlue.RequestGeom();
	posPink.SetMotorEnable(1);
	posPink.RequestGeom();
	posOrange.SetMotorEnable(1);
	posOrange.RequestGeom();

	//initialize robots&models
	vector<Model> pillList;
	vector<Model> powerpillList;
	vector<Model> targetList;
	vector<Node> nodeList;
	vector<Ghost> ghostList;
	createNodeList(nodeList);
	createPillList(sim, pillList, powerpillList, nodeList, targetList);
	Pacman pacman("pacman", sim, nodeList);
	Ghost redGhost("ghostRed", sim, nodeList);
	Ghost blueGhost("ghostBlue", sim, nodeList);
	Ghost pinkGhost("ghostPink", sim, nodeList);
	Ghost orangeGhost("ghostOrange", sim, nodeList);
	ghostList.push_back(redGhost);
	ghostList.push_back(blueGhost);
	ghostList.push_back(pinkGhost);
	ghostList.push_back(orangeGhost);
	Map map;

	//simulation loop
	while (true) {
		robot.Read();
		ghostRed.Read();
		ghostPink.Read();
		ghostOrange.Read();

		//Game logic begins
		vector<Node> path;
		vector<Node> redPath = map.findPath(ghostList[0].getCurrentNode(),
				pacman.getCurrentNode(), nodeList);
		vector<Node> bluePath;
		vector<Node> pinkPath;
		vector<Node> orangePath;
		path.push_back(
				pacman.simpleAI(map, nodeList, ghostList, pillList,
						powerpillList, targetList));
		bluePath.push_back(
						ghostList[1].simpleAI(map, nodeList, pacman, powerpillList));
		pinkPath.push_back(
				ghostList[2].simpleAI(map, nodeList, pacman, powerpillList));
		orangePath.push_back(
				ghostList[3].simpleAI(map, nodeList, pacman, powerpillList));

		pacman.executePath(sim, path, pos);
		ghostList[0].executePath(sim, redPath, posRed);
		ghostList[1].executePath(sim, bluePath, posBlue);
		ghostList[2].executePath(sim, pinkPath, posPink);
		ghostList[3].executePath(sim, orangePath, posOrange);

		pacman.setSpeed(0.45, pos);
		redGhost.setSpeed(0.45, posRed);
		blueGhost.setSpeed(0.45, posBlue);
		pinkGhost.setSpeed(0.45, posPink);
		orangeGhost.setSpeed(0.45, posOrange);
		//Game logic ends

		//update models for sim engine
		updateGame(sim, ghostList, pillList, powerpillList, pacman);
		pacman.update(sim, nodeList);
		for (int i = 0; i < ghostList.size(); i++)
			ghostList[i].update(sim, nodeList);
		updatePillList(sim, pillList, powerpillList, nodeList);

		printData(pacman, pillList, powerpillList, ghostList, path);
		//sleep(0.35);
	}
	return 0;
}

void printData(Pacman pacman, const vector<Model> &pillList,
		const vector<Model> &powerpillList, const vector<Ghost> &ghostList,
		const vector<Node> &path) {

	/*for (int i = 0; i < ghostList.size(); i++) {
		cout << "Ghost State: " << ghostList[i].getState() << endl;
	}*/
	cout << "Pacman State: " << pacman.getState() << endl;
	cout << "SCORE: " << pacman.getScore() << " LIVES: " << pacman.getLives()
			<< endl;
	/*cout << "X: " << pacman.getCurrentNode().getX() << " Y: " <<
	 pacman.getCurrentNode().getY() << endl;*/

	/*cout << "X: " << robot.getX() << " Y: " << robot.getY() << endl;
	 cout << "iX: " << robot.getCurrentNode().getX() << " iY: "
	 << robot.getCurrentNode().getY() << " isOccupied?: " << robot.getCurrentNode().isOccupied()
	 << endl;
	 /*for ( unsigned int i = 0; i < pillList.size(); i++)
	 cout <<"Name: " << pillList[i].getName() << pillList[i].getCurrentNode().getX() << " " << pillList[i].getCurrentNode().getY() <<
	 "Alive? " << pillList[i].isAlive() << endl;

	 for ( unsigned int i = 0; i < powerpillList.size(); i++)
	 cout <<"Name: " << powerpillList[i].getName() << " X: "<< powerpillList[i].getCurrentNode().getX()
	 << " Y: " << powerpillList[i].getCurrentNode().getY() <<
	 "Alive? " << powerpillList[i].isAlive() << endl;*/

	/*for ( int i = 0; i < path.size(); i++){
	 cout << "HERE! X: " << path[i].getX() << " Y: " << path[i].getY() << endl;
	 }*/
}
void createNodeList(vector<Node> &nodeList) {
	ifstream fin;
	fin.open("map.txt");
	for (int i = 10; i >= -9; i--) { //top left index:(-9,10)-bottom right index:(10, -9)
		for (int j = -9; j <= 10; j++) {
			char toRead;
			bool occupied;
			fin >> toRead;
			if (toRead == '1') {
				occupied = true;
			} else {
				occupied = false;
			}
			Node node(j, i, occupied);
			nodeList.push_back(node);
		}
	}
	fin.close();
}
void createPillList(SimulationProxy &sim, vector<Model> &pillList,
		vector<Model> &powerpillList, vector<Node> nodeList,
		vector<Model> &targetList) {
	//reads pill's names from a .txt file and creates models of them
	ifstream fin;
	fin.open("pillNames.txt");
	while (true) {
		string temp;
		char* name = new char[temp.size() + 1];
		fin >> temp;
		for (unsigned int i = 0; i < temp.size(); i++)
			name[i] = temp[i];
		name[temp.size()] = '\0';
		Model pill(name, sim, nodeList);
		if (temp.size() > 9) //pill names has length of 5, powerpill names has more that.
			powerpillList.push_back(pill);
		else
			pillList.push_back(pill);
		targetList.push_back(pill);
		if (fin.eof()) {
			break;
			delete[] name;
		}
	}

	fin.close();
}
void updatePillList(SimulationProxy &sim, vector<Model> &pillList,
		vector<Model> &powerpillList, vector<Node> nodeList) {
	for (unsigned int i = 0; i < pillList.size(); i++) {
		pillList[i].update(sim, nodeList);
	}

	for (unsigned int i = 0; i < powerpillList.size(); i++) {
		powerpillList[i].update(sim, nodeList);
	}

}
void updateGame(PlayerCc::SimulationProxy &sim, vector<Ghost> &ghostList,
		vector<Model> &pillList, vector<Model> &powerpillList, Pacman &pacman) {

	for (int i = 0; i < pillList.size(); i++) {
		if (pillList[i].isAlive() == false)
			sim.SetPose2d(pillList[i].getName(), -10, -10, 0);
	}
	for (int i = 0; i < powerpillList.size(); i++) {
		if (powerpillList[i].isAlive() == false)
			sim.SetPose2d(powerpillList[i].getName(), -10, -10, 0);
	}

	for (int i = 0; i < ghostList.size(); i++) {
		if (ghostList[i].isAlive() == false) {
			ghostList[i].setEdible(false);
			ghostList[i].setAlive(true);
			sim.SetPose2d(ghostList[i].getName(), -0.5, -2.5, 0);
		}
	}
	if (pacman.isAlive() == false) {
		pacman.setLives(pacman.getLives() - 1);
		sim.SetPose2d(pacman.getName(), -0.5, -2.5, 0);
		sim.SetPose2d(ghostList[0].getName(), -0.5, 1.5, 0);
		sim.SetPose2d(ghostList[1].getName(), 9.5, 9.5, 0);
		sim.SetPose2d(ghostList[2].getName(), -9.5, 9.5, 0);
		sim.SetPose2d(ghostList[3].getName(), -0.5, 9.5, 0);
		pacman.setAlive(true);

	}

}
