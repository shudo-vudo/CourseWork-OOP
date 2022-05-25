#include "GameField.h"

// this is square: char(219);

Coords::Coords() {
	this->status = 0;
	this->x = 0;
	this->y = 0;
}

Coords::Coords(int xc, int yc, int stat) {
	this->x = xc;
	this->y = yc;
	this->status = stat;
}

int Coords::getStatus() {
	return this->status;
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
				if (_friendlyShipField[i][j].status == 2)
					return false;
			}
	else if (type == 'e')
		for (int i = 0; i < 10; i++)
			for (int j = 1; j < 10; j++) {
				if (_enemyShipField[i][j].status == 2)
					return false;
			}
	return true;
}

//if (_enemyShipField[i][j].status != _enemyShipField[i][j - 1].status)
//	if (_enemyShipField[i][j].status != 0 && _enemyShipField[i][j - 1].status != 0)
//		return false;
//if (_enemyShipField[j][i].status != _enemyShipField[j - 1][i].status)
//	if (_enemyShipField[j][i].status != 0 && _enemyShipField[j - 1][i].status != 0)
//		return false;

void Field::setFieldManually() {
	int deck = 4;
	int count = 1;
	int tmp = 0;
	while (count < 10) {
		int x = 0;
		int y = 0;
		bool set = false;
		Ship ship(deck);
		this->drawFields();
		for (int i = 0; i < deck; i++)
			ship._friendlyShipField[0][i].status = 1;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				cout << ship._friendlyShipField[i][j].status;
			cout << endl;
		}
		cout << ship.isHorisont() << endl;
		cout << endl;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				cout << this->_friendlyShipField[i][j].status;
			cout << endl;
		}
		ship.showFields(this->_friendlyShipField);
		while (set != true) {
			switch (_getch()) {
				// good
				case Keys::Q: {
					if (ship.isHorisont() == true) {
						if (y + deck - 1 < 10) {
							int i = 1;
							while (i!=deck) {
								ship.setShipFieldCellStatus('f', x + i, y, 0);
								if (this->_friendlyShipField[x][y + i].status == 3 || this->_friendlyShipField[x][y + i].status == 4)
									ship.setShipFieldCellStatus('f', x, y + i, 2);
								else
									ship.setShipFieldCellStatus('f', x, y + i, 1);
								i++;
							}
							ship.swap();
						}
					} 
					else if (ship.isHorisont() == false) {
						if (x + deck - 1 < 10) {
							int i = 1;
							while (i != deck) {
								ship.setShipFieldCellStatus('f', x, y + i, 0);
								if (this->_friendlyShipField[x + i][y].status == 3 || this->_friendlyShipField[x][y + i].status == 4)
									ship.setShipFieldCellStatus('f', x + i, y, 2);
								else 
									ship.setShipFieldCellStatus('f', x + i, y, 1);
								i++;
							}
							ship.swap();
						}
					}
					this->drawFields();
					ship.showFields(this->_friendlyShipField);
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++)
							cout << ship._friendlyShipField[i][j].status;
						cout << endl;
					}
					cout << endl;
					cout << ship.isHorisont() << 1;
					cout << endl;
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++)
							cout << this->_friendlyShipField[i][j].status;
						cout << endl;
					}
					break;
				}
				// completed
				case Keys::Left: {
					if (y > 0 && y < 10 && ship.isHorisont() == true) {
						for (int i = 0; i < deck; i++) {
							if (this->_friendlyShipField[x + i][y - 1].status == 3 || this->_friendlyShipField[x + i][y - 1].status == 4)
								ship.setShipFieldCellStatus('f', x + i, y - 1, 2);
							else
								ship.setShipFieldCellStatus('f', x + i, y - 1, 1);
							ship.setShipFieldCellStatus('f', x + i, y, 0);
						}
						y -= 1;
					}
					else if (y > 0 && y < 10 && ship.isHorisont() == false) {
							if (this->_friendlyShipField[x][y - 1].status == 3 || this->_friendlyShipField[x][y - 1].status == 4)
								ship.setShipFieldCellStatus('f', x, y - 1, 2);
							else
								ship.setShipFieldCellStatus('f', x, y - 1, 1);
							ship.setShipFieldCellStatus('f', x, y + deck - 1, 0);
							y -= 1;
					}
					this->drawFields();
					ship.showFields(this->_friendlyShipField);
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++)
							cout << ship._friendlyShipField[i][j].status;
						cout << endl;
					}
					cout << endl << y;
					cout << endl;
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++)
							cout << this->_friendlyShipField[i][j].status;
						cout << endl;
					}
					break;
				};
				// completed
				case Keys::Right: {
					if (y < 9 && y >= 0 && ship.isHorisont() == true) {
						for (int i = 0; i < deck; i++) {
							if (this->_friendlyShipField[x + i][y + 1].status == 3 || this->_friendlyShipField[x + i][y + 1].status == 4)
								ship.setShipFieldCellStatus('f', x + i, y + 1, 2);
							else
								ship.setShipFieldCellStatus('f', x + i, y + 1, 1);
							ship.setShipFieldCellStatus('f', x + i, y, 0);
						}
						y += 1;
					}
					else if (y < 10 - deck && y >= 0 && ship.isHorisont() == false) {
						if (this->_friendlyShipField[x][y + 1].status == 3 || this->_friendlyShipField[x][y + 1].status == 4)
							ship.setShipFieldCellStatus('f', x, y + deck, 2);
						else
							ship.setShipFieldCellStatus('f', x, y + deck, 1);
						ship.setShipFieldCellStatus('f', x, y, 0);
						y += 1;
					}
					this->drawFields();
					ship.showFields(this->_friendlyShipField);
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++)
							cout << ship._friendlyShipField[i][j].status;
						cout << endl;
					}
					cout << endl << y << endl;
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++)
							cout << this->_friendlyShipField[i][j].status;
						cout << endl;
					}
					break;
				};
				// completed
				case Keys::Down: {
					if (x < 10 - deck && x >= 0 && ship.isHorisont() == true) {
						if (this->_friendlyShipField[x + 1][y].status == 3 || this->_friendlyShipField[x + 1][y].status == 4)
							ship.setShipFieldCellStatus('f', x + deck, y, 2);
						else
							ship.setShipFieldCellStatus('f', x + deck, y, 1);
						ship.setShipFieldCellStatus('f', x, y, 0);
						x += 1;
					}
					else if (x < 9 && x >= 0 && ship.isHorisont() == false) {
						for (int i = 0; i < deck; i++) {
							if (this->_friendlyShipField[x + 1][y + i].status == 3 || this->_friendlyShipField[x + 1][y + i].status == 4)
								ship.setShipFieldCellStatus('f', x + 1, y + i, 2);
							else
								ship.setShipFieldCellStatus('f', x + 1, y + i, 1);
							ship.setShipFieldCellStatus('f', x, y + i, 0);
						}
						x += 1;
					}
					this->drawFields();
					ship.showFields(this->_friendlyShipField);
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++)
							cout << ship._friendlyShipField[i][j].status;
						cout << endl;
					}
					cout << endl << y << endl;
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++)
							cout << this->_friendlyShipField[i][j].status;
						cout << endl;
					}
					break;
				};
				// completed
				case Keys::Up: {
					if (x > 0 && x < 10 && ship.isHorisont() == true) {
						if (this->_friendlyShipField[x - 1][y].status == 3 || this->_friendlyShipField[x - 1][y].status == 4)
							ship.setShipFieldCellStatus('f', x - 1, y, 2);
						else
							ship.setShipFieldCellStatus('f', x - 1, y, 1);
						ship.setShipFieldCellStatus('f', x + deck - 1, y, 0);
						x -= 1;
					}
					else if (x > 0 && x < 10 && ship.isHorisont() == false) {
						for (int i = 0; i < deck; i++) {
							if (this->_friendlyShipField[x - 1][y + i].status == 3 || this->_friendlyShipField[x - 1][y + i].status == 4)
								ship.setShipFieldCellStatus('f', x - 1, y + i, 2);
							else
								ship.setShipFieldCellStatus('f', x - 1, y + i, 1);
							ship.setShipFieldCellStatus('f', x, y + i, 0);
						}
						x -= 1;
					}
					this->drawFields();
					ship.showFields(this->_friendlyShipField);
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++)
							cout << ship._friendlyShipField[i][j].status;
						cout << endl;
					}
					cout << endl << y;
					cout << endl;
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++)
							cout << this->_friendlyShipField[i][j].status;
						cout << endl;
					}
					break;
				};
				//  completed
				case Keys::Enter: {
					if (ship.checkFields('f') == true) {
						if (ship.isHorisont() == true) {
							for (int i = 0; i < deck; i++)
								this->_friendlyShipField[x + i][y].status = 3;
							if (x != 0) {
								this->_friendlyShipField[x - 1][y].status = 4;
								if (y != 0)
									this->_friendlyShipField[x - 1][y - 1].status = 4;
								if (y != 9)
									this->_friendlyShipField[x - 1][y + 1].status = 4;
							}
							if (x + deck < 9) {
								this->_friendlyShipField[x + deck][y].status = 4;
								if (y != 0)
									this->_friendlyShipField[x + deck][y - 1].status = 4;
								if (y != 9)
									this->_friendlyShipField[x + deck][y + 1].status = 4;
							}
							if (y != 0)
								for (int i = 0; i < deck; i++) {
									this->_friendlyShipField[x + i][y - 1].status = 4;
								}
							if (y != 9)
								for (int i = 0; i < deck; i++) {
									this->_friendlyShipField[x + i][y + 1].status = 4;
								}
						}
						else if (ship.isHorisont() == false) {
							for (int i = 0; i < deck; i++)
								this->_friendlyShipField[x][y+i].status = 3;
							if (x != 0)
								for (int i = 0; i < deck; i++) {
									this->_friendlyShipField[x - 1][y + i].status = 4;
								}
							if (x != 9)
								for (int i = 0; i < deck; i++) {
									this->_friendlyShipField[x + 1][y + i].status = 4;
								}
							if (y != 0) {
								this->_friendlyShipField[x][y - 1].status = 4;
								if (x != 0)
									this->_friendlyShipField[x - 1][y - 1].status = 4;
								if (x != 9)
									this->_friendlyShipField[x + 1][y - 1].status = 4;
							}
							if (y + deck < 9) {
								this->_friendlyShipField[x][y + deck].status = 4;
								if (x != 0)
									this->_friendlyShipField[x - 1][y + deck].status = 4;
								if (x != 9)
									this->_friendlyShipField[x + 1][y + deck].status = 4;
							}
						}
						set == true;
						if (count == 1 && deck == 4)
							deck--;
						else if (count == 3)
							deck--;
						else if (count == 6)
							deck--;
						else if (count == 10)
							deck--;
						count++;
						this->drawFields();
						ship.showFields(this->_friendlyShipField);
						for (int i = 0; i < 10; i++) {
							for (int j = 0; j < 10; j++)
								cout << ship._friendlyShipField[i][j].status;
							cout << endl;
						}
						cout << endl;
						for (int i = 0; i < 10; i++) {
							for (int j = 0; j < 10; j++)
								cout << this->_friendlyShipField[i][j].status;
							cout << endl;
						}
					}
					break;
				};
			}
		}
	}
}

void Field::setFieldRandomly() {

}

void Field::setShipFieldCellStatus(char type, int x, int y, int stat) {
	if (type == 'f')
		this->_friendlyShipField[x][y].status = stat;
	else if (type == 'e')
		this->_enemyShipField[x][y].status = stat;
}

void Field::showFields(Coords field[10][10]) {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			if (field[i][j].getStatus() == 4) {
				gotoxy(j + 1, i + 1);
				cout << "O";
			}
			if (field[i][j].getStatus() == 3) {
				gotoxy(j + 1, i + 1);
				cout << "D";
			}
			if (_friendlyShipField[i][j].status == 0) {
				gotoxy(j + 1, i + 1);
				cout << " ";
			}
			if (_friendlyShipField[i][j].status == 1) {
				gotoxy(j + 1, i + 1);
				cout << char(219);
			}
			else if (_friendlyShipField[i][j].status == 2) {
				gotoxy(j + 1, i + 1);
				cout << "X";
			}
		}
	gotoxy(0, 12);
}


Game::Game()
{
	_end = false;
}

Ship::Ship() : Field() {
	_isHorisontal = true;
	_deck = 0;
}

Ship::Ship(int deck) {
	_isHorisontal = true;
	_deck = deck;
}

bool Ship::isHorisont() {
	return _isHorisontal;
}

int Ship::getShipDeck() {
	return _deck;
}

void Ship::swap() {
	if (this->isHorisont() == false)
		_isHorisontal = true;
	else
		_isHorisontal = false;
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