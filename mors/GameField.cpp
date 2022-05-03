#include "GameField.h"

Field::Field()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			_shipField[i][j] = 0;
}

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
					cout << " ";
				else if (_shipField[i][j - 1] == 2)
					cout << "O";
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

Game::Game() : Field()
{
	_end = false;
}
