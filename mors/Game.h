#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <conio.h>
#include <random>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <math.h>
#include <vector>

using namespace std;
using namespace this_thread;
using namespace chrono;

enum Keys { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27, BackSpace = 8, Q = 113 };
enum Direction { Up = 'U', Left = 'L', Right = 'R', Down = 'D' };

struct Coords {
	int x;
	int y;
	int status;
	Coords();
	Coords(int,int,int);
	int getStatus();
};

struct Coord {
	int x;
	int y;
	Coord();
	Coord(int, int);
};

/*
	Value status for field:
		0 - empty untouched cell;
		1 - Hitted deck;
		2 - empty touched cell;
		3 - Deck;

		4 - empty cell near ship;
		5 - Hidden deck;
		6 - empty visible cell near ship
*/


class Field {
protected:
	Coords _friendlyShipField[10][10];
	Coords _enemyShipField[10][10];
	Field();
	void setShipFieldCellStatus(char, int, int, int);
public:
	void drawFields();
	void showtempFields(int);
	void showEnemyField();
	bool checkFields(char);
	void clearFields(char);
	bool checkRandom(char);
	void setFieldManually();
	void setFieldRandomly(char);
	void setFieldsForGame();
};

class Ship : public Field {
protected:
	bool _isHorisontal;
	int _deck;
public:
	Ship();
	Ship(int, bool);
	bool isHorisont();
	void swap();
	int getShipDeck();
};
void gotoxy(int, int);

class Game : public Field {
private:
	bool _end;
	vector<Coord> _tempAICells;
	vector<Coord> _tempDeadShip;
	bool _AIwork;
public:
	Game();
	bool isEnd();
	bool shoot(char);
	bool isDeadShip(int, int);
	bool isDeadShip(int, int, char);
	void markDeadShip();
};

struct Point {
	int tempfield[10][10] = { 0 };
	void showPoint(int, int);
};

#endif 
