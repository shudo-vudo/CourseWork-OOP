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

enum Keys { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Q = 113 };

enum Direction { U = 0, L = 1, R = 2, D = 3 };

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
	int _friendlyShipField[10][10];
	int _enemyShipField[10][10];
	Field();
	void setShipFieldCellStatus(char, int, int, int);
	int getStatus(int, int);
	int getEnemyStatus(int, int);
	bool checkRandom(char);
	bool checkFields(char);
public:
	void drawFields();
	void showtempFields(int);
	void showEnemyField();
	void clearFields(char);
	void setFieldManually();
	void setFieldRandomly(char);
	void setFieldsForGame();
};

class Ship : public Field {
private:
	bool _isHorisontal;
	int _deck;
public:
	bool isHorisont();
	Ship();
	Ship(int, bool);
	void swap();
	int getShipDeck();
};

void gotoxy(int, int);

class Game : public Field {
private:
	bool _end; // ������� ���������� ����� ����
	int _wasDirection[4]; // ������������� ������, ��������������� ��� ����������� ����������� �������� ����������
	Coord _tempAICells[2]; // ������ �������� Coord ��� ������������� ����� ����������
	vector<Coord> _tempDeadShip; // ��������� �������� Coord ��� ����������� ������ �������� �������
	bool _AIwork; // ������� ����������, ���������� �� ������ ������� ����������� �������
public:
	Game();
	char whoIsWinner(); // ����� ����������� ����������
	void AIChooseDirection(int, int); // ����� ��� ������ ����������� �������� ����
	bool isEnd(); // ����� ������, ������, ����������� ���� ��� ���
	bool shoot(char); // ����� ��������
	void markFriendlyDeadShip(); // ����� ������� ����� ������ �������� ������� ������
	void markEnemyDeadShip(); // ����� ������� ����� ������ �������� ������� ����������
	bool isFriendlyDeadShip(int, int); // ����� ����������� ��������� ������� ������
	bool isEnemyDeadShip(int, int); // ����� ����������� ��������� ������� ����������
	void End(); // ����� ��������� ��������� ����
	void Restart(); // ����� ��������� ������ ����
};

struct Point {
	int tempfield[10][10] = { 0 };
	void showPoint(int, int);
};

#endif 