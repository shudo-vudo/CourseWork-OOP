#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <iostream>
#include <conio.h>
#include <random>

using namespace std;

enum Keys { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27, BackSpace = 8, Q = 113 };

class Field {
protected:
	int _shipField[10][10] = { 0 };
public:
	void drawField();
	bool checkField();
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
};

class Game : public Field, public Ship {
protected:
	bool _end;
public:
	Game();
};


#endif 
