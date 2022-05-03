#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <iostream>
#include <conio.h>
#include <random>

using namespace std;

class Field {
protected:
	int _shipField[10][10];
public:
	Field();
	void drawField();
};

class Ship : public Field {
protected:
	int _type;
	int count;
public:
	virtual void setShip() = 0;
};

class Game : public Field, public Ship {
protected:
	bool _end;
public:
	Game();
};


#endif 
