#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <iostream>
#include <conio.h>
#include <random>
#include <Windows.h>

using namespace std;

enum Keys { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27, BackSpace = 8, Q = 113 };

struct Coords {
	int x;
	int y;
	int status;
	Coords();
	Coords(int,int,int);
};

/*
	Value status for field:
		0 - empty untouched cell;
		1 - Hitted deck;
		2 - empty touched cell;
		3 - Deck;
		4 - empty cell near ship;
*/

class Game {
protected:
	bool _end;
public:
	Game();
};

class Field : public Game {
protected:
	Coords _friendlyShipField[10][10];
	Coords _enemyShipField[10][10];
public:
	Field();
	void drawFields();
	bool checkFields(char);
	void setFieldManually();
	void setFieldRandomly();
};

class Ship : public Field {
protected:
	int _index;
	bool _isHorisontal;
	int _deck;
public:
	Ship();
	Ship(int, int);
	bool isHorisont();
};

void gotoxy(int, int);

#endif 
