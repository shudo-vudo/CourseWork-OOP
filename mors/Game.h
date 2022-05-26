#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <conio.h>
#include <random>
#include <Windows.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace this_thread;
using namespace chrono;

enum Keys { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27, BackSpace = 8, Q = 113 };

struct Coords {
	int x;
	int y;
	int status;
	Coords();
	Coords(int,int,int);
	int getStatus();
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
public:
	Field();
	void setShipFieldCellStatus(char,int,int,int);
	void drawFields();
	void showtempFields(int);
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
protected:
	bool _end;
public:
	Game();
	void shoot(char, int, int);
	void markDeadShip();
};

#endif 
