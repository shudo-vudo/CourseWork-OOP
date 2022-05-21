#include "GameField.h"

// this is square: char(219);

Coords::Coords() {
	this->status = 99;
	this->x = 99;
	this->y = 99;
}

Coords::Coords(int xc, int yc, int stat) {
	this->x = xc;
	this->y = yc;
	this->status = stat;
}

Field::Field() : Game() {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			_friendlyShipField[i][j].x = i;
			_friendlyShipField[i][j].y = j;
			_friendlyShipField[i][j].status = 0;
			_enemyShipField[i][j].x = i;
			_enemyShipField[i][j].y = j;
			_enemyShipField[i][j].status = 0;
		}
}

void Field::drawFields() {
	system("cls");
	/*
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << _friendlyShipField[i][j].status;
		}
		cout << endl;
	}
	*/
	cout << " ";
	for (int i = 0; i < 25; i++) {
		if (i > 9 && i < 15)
			cout << " ";
		else
			cout << "-";
	}
	cout << " " << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 27; j++) {
			if (j == 0 || j == 11 || j == 15 || j == 26)
				cout << "|";
			else if (j < 11) {
				if (_friendlyShipField[i][j - 1].status == 1)
					cout << "X";
				else if (_friendlyShipField[i][j - 1].status == 2)
					cout << "O";
				else if (_friendlyShipField[i][j - 1].status == 3) {
					cout << char(219);
				}
				else
					cout << " ";
			}
			else if (j > 11 && j < 15)
				cout << " ";
			else if (j > 15) {
				if (_enemyShipField[i][j - 16].status == 1)
					cout << "X";
				else if (_enemyShipField[i][j - 16].status == 2)
					cout << "O";
				else if (_enemyShipField[i][j - 16].status > 3 && _enemyShipField[i][j - 16].status < 5) {
					cout << char(219);
				}
				else
					cout << " ";
			}
		}
		cout << endl;
	}
	cout << " ";
	for (int i = 0; i < 25; i++) {
		if (i > 9 && i < 15)
			cout << " ";
		else
			cout << "-";
	}
	cout << " " << endl;
}

bool Field::checkFields(char type) {
	if (type == 'f')
		for (int i = 0; i < 10; i++)
			for (int j = 1; j < 10; j++) {
				if (_friendlyShipField[i][j].status != _friendlyShipField[i][j - 1].status)
					if (_friendlyShipField[i][j].status != 0 && _friendlyShipField[i][j - 1].status != 0)
						return false;
				if (_friendlyShipField[j][i].status != _friendlyShipField[j - 1][i].status)
					if (_friendlyShipField[j][i].status != 0 && _friendlyShipField[j - 1][i].status != 0)
						return false;
			}
	else if (type == 'e')
		for (int i = 0; i < 10; i++)
			for (int j = 1; j < 10; j++) {
				if (_enemyShipField[i][j].status != _enemyShipField[i][j - 1].status)
					if (_enemyShipField[i][j].status != 0 && _enemyShipField[i][j - 1].status != 0)
						return false;
				if (_enemyShipField[j][i].status != _enemyShipField[j - 1][i].status)
					if (_enemyShipField[j][i].status != 0 && _enemyShipField[j - 1][i].status != 0)
						return false;
			}
	return true;
}

void Field::setFieldManually() {
	this->drawFields();
	int deck = 4;
	int index = 1;
	int count = 0;
	int x = 0;
	int y = 0;
	while (true) {
		Ship ship(deck, index);
		y = 0;
		x = 0;
		count += 1;
		while (true) {
			switch (_getch()) {
				case Keys::Up: {

					break;
				};
				case Keys::Down: {
	
					break;
				};
				case Keys::Left: {

					break;
				};
				case Keys::Right: {
	
					break;
				}
				case Keys::Q: {

					break;
				}
			}
		}
	}
}
// попытки до этого сделать перемещение вверх
/*if ((y - 1 >= 0) && (ship.isHorisont() == true)) {
	for (int i = 0; i < deck; i++)
		_friendlyShipField[y + i][x].status = 0;
		y -= 1;
	for (int i = 0; i < deck; i++)
		_friendlyShipField[y + i][x].status = 1;
		if (this->checkFields() == false) {
	for (int i = 0; i < deck; i++)
		_friendlyShipField[y + i][x].status = 0;
	}
}*/

void Field::setFieldRandomly() {

}

Game::Game()
{
	_end = false;
}

Ship::Ship() {
	_index = 99;
	_isHorisontal = true;
	_deck = 0;
}

Ship::Ship(int deck, int index)
{
	_index = index;
	_isHorisontal = true;
	_deck = deck;
}

bool Ship::isHorisont()
{
	return _isHorisontal;
}


//na vsyakii sluchai

//function for drawing at console
void gotoxy(int xpos, int ypos)
{
	COORD scrn;

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos; scrn.Y = ypos;

	SetConsoleCursorPosition(hOuput, scrn);
}
