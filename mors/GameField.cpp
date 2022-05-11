#include "GameField.h"

void Field::drawField() {
	cout << " ";
	for (int i = 0; i < 10; i++)
		cout << "_";
	cout << " " << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			if (j == 0 || j == 11)
				cout << "|";
			else {
				if (_shipField[i][j - 1] == 1)
					cout << "X";
				else if (_shipField[i][j - 1] == 2)
					cout << "O";
				else if (_shipField[i][j - 1] > 3 && _shipField[i][j - 1] < 5) {
					char prikol = 2;
					cout << prikol;
				}
				else
					cout << " ";
			}
		}
		cout << endl;
	}
	cout << " ";
	for (int i = 0; i < 10; i++)
		cout << "-";
	cout << " " << endl;
}

bool Field::checkField() {
	for (int i = 0; i < 10; i++)
		for (int j = 1; j < 10; j++) {
			if (_shipField[i][j] != _shipField[i][j - 1])
				if (_shipField[i][j] != 0 && _shipField[i][j - 1] != 0)
					return false;
			if (_shipField[j][i] != _shipField[j - 1][i])
				if (_shipField[j][i] != 0 && _shipField[j - 1][i] != 0)
					return false;
		}
	return true;
}

void Field::setFieldManually() {

}

Game::Game() : Field()
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
