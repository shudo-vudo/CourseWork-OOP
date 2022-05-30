#include "Game.h"

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

Field::Field() {
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

void Field::setShipFieldCellStatus(char type, int x, int y, int stat) {
	if (type == 'f')
		this->_friendlyShipField[x][y].status = stat;
	else if (type == 'e')
		this->_enemyShipField[x][y].status = stat;
}

int Field::getStatus(int x, int y) {
	return this->_friendlyShipField[x][y].status;
}

void Field::drawFields() {
	system("cls");
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
				else if (_enemyShipField[i][j - 16].status == 3) {
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

void Field::showtempFields(int choose) {
	cout.flush();
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			if (choose == 1) {
				if (getStatus(i, j) == 3) {
					gotoxy(j + 1, i + 1);
					cout << "D";
				}
				if (getStatus(i, j) == 6) {
					gotoxy(j + 1, i + 1);
					cout << " ";
				}
				if (getStatus(i, j) == 0) {
					gotoxy(j + 1, i + 1);
					cout << " ";
				}
			}
			else if (choose == 0) {
				if (getStatus(i, j) == 1) {
					gotoxy(j + 1, i + 1);
					cout << char(219);
				}
				else if (getStatus(i, j) == 2) {
					gotoxy(j + 1, i + 1);
					cout << "X";
				}
			}
			else if (choose == 3) {
				if (getStatus(i, j) == 3) {
					gotoxy(j + 1, i + 1);
					cout << char(219);
				}
				else if (getStatus(i,j) == 0) {
					gotoxy(j + 1, i + 1);
					cout << " ";
				}
				else if (getStatus(i, j) == 2) {
					gotoxy(j + 1, i + 1);
					cout << "O";
				}
				else if (getStatus(i, j) == 1) {
					gotoxy(j + 1, i + 1);
					cout << "X";
				}
			}
		}
	gotoxy(0, 12);
}

void Field::showEnemyField() {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			if (_enemyShipField[i][j].status == 1) {
				gotoxy(i + 16, j + 1);
				cout << "X";
			}
			else if (_enemyShipField[i][j].status == 2) {
				gotoxy(i + 16, j + 1);
				cout << "O";
			}
			else {
				gotoxy(i + 16, j + 1);
				cout << " ";
			}
		}
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

void Field::clearFields(char type) {
	if (type == 'f')
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				this->_friendlyShipField[i][j].status = 0;
	else if (type == 'e')
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				this->_enemyShipField[i][j].status = 0;
}

bool Field::checkRandom(char type) {
	int count = 0;
	if (type == 'f') {
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++) {
				if (this->_friendlyShipField[i][j].status == 3)
					count += 1;
			}
	}
	else {
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++) {
				if (this->_enemyShipField[i][j].status == 3)
					count += 1;
			}
	}
	if (count != 20)
		return false;
	else
		return true;
}

void Field::setFieldManually() {
	int deck = 4;
	int count = 0;
	this->drawFields();
	while (count < 10) {
		if (count == 10)
			break;
		int x = 0;
		int y = 0;
		bool set = false;
		bool QIsPressed = false;
		Ship ship(deck, false);
		for (int i = 0; i < deck; i++) {
			if (this->_friendlyShipField[0][i].status == 3 || this->_friendlyShipField[0][i].status == 6)
				ship._friendlyShipField[0][i].status = 2;
			else
				ship._friendlyShipField[0][i].status = 1;
		}
		this->showtempFields(1);
		ship.showtempFields(0);
		cout << endl << "For moving ship, press 'Q'.               ";
		while (set != true) {
			switch (_getch()) {
				// good
				case Keys::Q: {
					if (ship.isHorisont() == true) {
						if (y + deck - 1 < 10) {
							int i = 1;
							while (i!=deck) {
								ship.setShipFieldCellStatus('f', x + i, y, 0);
								if (this->_friendlyShipField[x][y + i].status == 3 || this->_friendlyShipField[x][y + i].status == 6)
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
								if (this->_friendlyShipField[x + i][y].status == 3 || this->_friendlyShipField[x + i][y].status == 6)
									ship.setShipFieldCellStatus('f', x + i, y, 2);
								else 
									ship.setShipFieldCellStatus('f', x + i, y, 1);
								i++;
							}
							ship.swap();
						}
					}
					this->showtempFields(1);
					ship.showtempFields(0);
					if (QIsPressed == false) {
						QIsPressed = true;
						this->drawFields();
						this->showtempFields(1);
						ship.showtempFields(0);
						cout << endl << "For place ship press 'Enter'.              ";
					}
					break;
				}
				// completed
				case Keys::Left: if (QIsPressed == true) {
						if (y > 0 && y < 10 && ship.isHorisont() == true) {
							for (int i = 0; i < deck; i++) {
								if (this->_friendlyShipField[x + i][y - 1].status == 3 || this->_friendlyShipField[x + i][y - 1].status == 6)
									ship.setShipFieldCellStatus('f', x + i, y - 1, 2);
								else
									ship.setShipFieldCellStatus('f', x + i, y - 1, 1);
								ship.setShipFieldCellStatus('f', x + i, y, 0);
							}
							y -= 1;
						}
						else if (y > 0 && y < 10 && ship.isHorisont() == false) {
							if (this->_friendlyShipField[x][y - 1].status == 3 || this->_friendlyShipField[x][y - 1].status == 6)
								ship.setShipFieldCellStatus('f', x, y - 1, 2);
							else
								ship.setShipFieldCellStatus('f', x, y - 1, 1);
							ship.setShipFieldCellStatus('f', x, y + deck - 1, 0);
							y -= 1;
						}
						this->showtempFields(1);
						ship.showtempFields(0);
						break;
					};
				// completed
				case Keys::Right: if (QIsPressed == true) {
						if (y < 9 && y >= 0 && ship.isHorisont() == true) {
							for (int i = 0; i < deck; i++) {
								if (this->_friendlyShipField[x + i][y + 1].status == 3 || this->_friendlyShipField[x + i][y + 1].status == 6)
									ship.setShipFieldCellStatus('f', x + i, y + 1, 2);
								else
									ship.setShipFieldCellStatus('f', x + i, y + 1, 1);
								ship.setShipFieldCellStatus('f', x + i, y, 0);
							}
							y += 1;
						}
						else if (y < 10 - deck && y >= 0 && ship.isHorisont() == false) {
							if (this->_friendlyShipField[x][y + deck].status == 3 || this->_friendlyShipField[x][y + deck].status == 6)
								ship.setShipFieldCellStatus('f', x, y + deck, 2);
							else
								ship.setShipFieldCellStatus('f', x, y + deck, 1);
							ship.setShipFieldCellStatus('f', x, y, 0);
							y += 1;
						}
						this->showtempFields(1);
						ship.showtempFields(0);
						break;
					};
				// completed
				case Keys::Down: if (QIsPressed == true) {
						if (x < 10 - deck && x >= 0 && ship.isHorisont() == true) {
							if (this->_friendlyShipField[x + deck][y].status == 3 || this->_friendlyShipField[x + deck][y].status == 6)
								ship.setShipFieldCellStatus('f', x + deck, y, 2);
							else
								ship.setShipFieldCellStatus('f', x + deck, y, 1);
							ship.setShipFieldCellStatus('f', x, y, 0);
							x += 1;
						}
						else if (x < 9 && x >= 0 && ship.isHorisont() == false) {
							for (int i = 0; i < deck; i++) {
								if (this->_friendlyShipField[x + 1][y + i].status == 3 || this->_friendlyShipField[x + 1][y + i].status == 6)
									ship.setShipFieldCellStatus('f', x + 1, y + i, 2);
								else
									ship.setShipFieldCellStatus('f', x + 1, y + i, 1);
								ship.setShipFieldCellStatus('f', x, y + i, 0);
							}
							x += 1;
						}
						this->showtempFields(1);
						ship.showtempFields(0);
						break;
					};
				// completed
				case Keys::Up: if (QIsPressed == true) {
						if (x > 0 && x < 10 && ship.isHorisont() == true) {
							if (this->_friendlyShipField[x - 1][y].status == 3 || this->_friendlyShipField[x - 1][y].status == 6)
								ship.setShipFieldCellStatus('f', x - 1, y, 2);
							else
								ship.setShipFieldCellStatus('f', x - 1, y, 1);
							ship.setShipFieldCellStatus('f', x + deck - 1, y, 0);
							x -= 1;
						}
						else if (x > 0 && x < 10 && ship.isHorisont() == false) {
							for (int i = 0; i < deck; i++) {
								if (this->_friendlyShipField[x - 1][y + i].status == 3 || this->_friendlyShipField[x - 1][y + i].status == 6)
									ship.setShipFieldCellStatus('f', x - 1, y + i, 2);
								else
									ship.setShipFieldCellStatus('f', x - 1, y + i, 1);
								ship.setShipFieldCellStatus('f', x, y + i, 0);
							}
							x -= 1;
						}
						this->showtempFields(1);
						ship.showtempFields(0);
						break;
					};
				//  completed
				case Keys::Enter: if (QIsPressed == true) {
						if (ship.checkFields('f') == true) {
							ship.clearFields('f');
							if (ship.isHorisont() == true) {
								for (int i = 0; i < deck; i++)
									this->_friendlyShipField[x + i][y].status = 3;
								if (x != 0) {
									this->_friendlyShipField[x - 1][y].status = 6;
									if (y != 0)
										this->_friendlyShipField[x - 1][y - 1].status = 6;
									if (y != 9)
										this->_friendlyShipField[x - 1][y + 1].status = 6;
								}
								if (x + deck < 9) {
									this->_friendlyShipField[x + deck][y].status = 6;
									if (y != 0)
										this->_friendlyShipField[x + deck][y - 1].status = 6;
									if (y != 9)
										this->_friendlyShipField[x + deck][y + 1].status = 6;
								}
								if (y != 0)
									for (int i = 0; i < deck; i++) {
										this->_friendlyShipField[x + i][y - 1].status = 6;
									}
								if (y != 9)
									for (int i = 0; i < deck; i++) {
										this->_friendlyShipField[x + i][y + 1].status = 6;
									}
							}
							else if (ship.isHorisont() == false) {
								for (int i = 0; i < deck; i++)
									this->_friendlyShipField[x][y + i].status = 3;
								if (x != 0)
									for (int i = 0; i < deck; i++) {
										this->_friendlyShipField[x - 1][y + i].status = 6;
									}
								if (x != 9)
									for (int i = 0; i < deck; i++) {
										this->_friendlyShipField[x + 1][y + i].status = 6;
									}
								if (y != 0) {
									this->_friendlyShipField[x][y - 1].status = 6;
									if (x != 0)
										this->_friendlyShipField[x - 1][y - 1].status = 6;
									if (x != 9)
										this->_friendlyShipField[x + 1][y - 1].status = 6;
								}
								if (y + deck < 9) {
									this->_friendlyShipField[x][y + deck].status = 6;
									if (x != 0)
										this->_friendlyShipField[x - 1][y + deck].status = 6;
									if (x != 9)
										this->_friendlyShipField[x + 1][y + deck].status = 6;
								}
							}
							set = true;
							if (count == 0)
								deck--;
							else if (count == 2)
								deck--;
							else if (count == 5)
								deck--;
							else if (count == 9)
								deck--;
							count++;
							this->showtempFields(1);
							ship.showtempFields(0);
							cout << endl << "        Placed!                ";
							sleep_for(milliseconds(500));
						}
						break;
					};
			}
		}
	}
}

void Field::setFieldRandomly(char type) {
	int deck = 4;
	int count = 0;
	this->drawFields();
	if (type == 'f') {
		do {
			deck = 4;
			count = 0;
			this->clearFields(type);
			while (count < 10) {
				bool set = false;
				Ship ship(deck, true);
				while (set != true) {
					ship.clearFields(type);
					ship.swap();
					int x;
					int y;
					if (ship.isHorisont() == true) {
						x = rand() % (11 - deck);
						y = rand() % 10;
						for (int i = 0; i < deck; i++) {
							if (this->_friendlyShipField[x + i][y].status == 3 || this->_friendlyShipField[x + i][y].status == 6) {
								ship.setShipFieldCellStatus(type, x + i, y, 2);
							}
							else {
								ship.setShipFieldCellStatus(type, x + i, y, 1);
							}
						}
					}
					else {
						x = rand() % 10;
						y = rand() % (11 - deck);
						for (int i = 0; i < deck; i++) {
							if (this->_friendlyShipField[x][y + i].status == 3 || this->_friendlyShipField[x][y + i].status == 6) {
								ship.setShipFieldCellStatus(type, x, y + i, 2);
							}
							else {
								ship.setShipFieldCellStatus(type, x, y + i, 1);
							}
						}
					}
					if (ship.checkFields(type) == true) {
						ship.clearFields(type);
						if (ship.isHorisont() == true) {
							for (int i = 0; i < deck; i++)
								this->_friendlyShipField[x + i][y].status = 3;
							if (x != 0) {
								this->_friendlyShipField[x - 1][y].status = 6;
								if (y != 0)
									this->_friendlyShipField[x - 1][y - 1].status = 6;
								if (y != 9)
									this->_friendlyShipField[x - 1][y + 1].status = 6;
							}
							if (x + deck < 9) {
								this->_friendlyShipField[x + deck][y].status = 6;
								if (y != 0)
									this->_friendlyShipField[x + deck][y - 1].status = 6;
								if (y != 9)
									this->_friendlyShipField[x + deck][y + 1].status = 6;
							}
							if (y != 0)
								for (int i = 0; i < deck; i++) {
									this->_friendlyShipField[x + i][y - 1].status = 6;
								}
							if (y != 9)
								for (int i = 0; i < deck; i++) {
									this->_friendlyShipField[x + i][y + 1].status = 6;
								}
						}
						else if (ship.isHorisont() == false) {
							for (int i = 0; i < deck; i++)
								this->_friendlyShipField[x][y + i].status = 3;
							if (x != 0)
								for (int i = 0; i < deck; i++) {
									this->_friendlyShipField[x - 1][y + i].status = 6;
								}
							if (x != 9)
								for (int i = 0; i < deck; i++) {
									this->_friendlyShipField[x + 1][y + i].status = 6;
								}
							if (y != 0) {
								this->_friendlyShipField[x][y - 1].status = 6;
								if (x != 0)
									this->_friendlyShipField[x - 1][y - 1].status = 6;
								if (x != 9)
									this->_friendlyShipField[x + 1][y - 1].status = 6;
							}
							if (y + deck < 9) {
								this->_friendlyShipField[x][y + deck].status = 6;
								if (x != 0)
									this->_friendlyShipField[x - 1][y + deck].status = 6;
								if (x != 9)
									this->_friendlyShipField[x + 1][y + deck].status = 6;
							}
						}
						set = true;
						if (count == 0)
							deck--;
						else if (count == 2)
							deck--;
						else if (count == 5)
							deck--;
						else if (count == 9)
							deck--;
						count++;
					}
				}
				this->showtempFields(1);
			}
		} while (this->checkRandom(type) == false);
	}
	else if (type == 'e') {
	do {
		deck = 4;
		count = 0;
		this->clearFields(type);
		while (count < 10) {
			bool set = false;
			Ship ship(deck, true);
			while (set != true) {
				ship.clearFields(type);
				ship.swap();
				int x;
				int y;
				if (ship.isHorisont() == true) {
					x = rand() % (11 - deck);
					y = rand() % 10;
					for (int i = 0; i < deck; i++) {
						if (this->_enemyShipField[x + i][y].status == 3 || this->_enemyShipField[x + i][y].status == 6) {
							ship.setShipFieldCellStatus(type, x + i, y, 2);
						}
						else {
							ship.setShipFieldCellStatus(type, x + i, y, 1);
						}
					}
				}
				else {
					x = rand() % 10;
					y = rand() % (11 - deck);
					for (int i = 0; i < deck; i++) {
						if (this->_enemyShipField[x][y + i].status == 3 || this->_enemyShipField[x][y + i].status == 6) {
							ship.setShipFieldCellStatus(type, x, y + i, 2);
						}
						else {
							ship.setShipFieldCellStatus(type, x, y + i, 1);
						}
					}
				}
				if (ship.checkFields(type) == true) {
					ship.clearFields(type);
					if (ship.isHorisont() == true) {
						for (int i = 0; i < deck; i++)
							this->_enemyShipField[x + i][y].status = 3;
						if (x != 0) {
							this->_enemyShipField[x - 1][y].status = 6;
							if (y != 0)
								this->_enemyShipField[x - 1][y - 1].status = 6;
							if (y != 9)
								this->_enemyShipField[x - 1][y + 1].status = 6;
						}
						if (x + deck < 9) {
							this->_enemyShipField[x + deck][y].status = 6;
							if (y != 0)
								this->_enemyShipField[x + deck][y - 1].status = 6;
							if (y != 9)
								this->_enemyShipField[x + deck][y + 1].status = 6;
						}
						if (y != 0)
							for (int i = 0; i < deck; i++) {
								this->_enemyShipField[x + i][y - 1].status = 6;
							}
						if (y != 9)
							for (int i = 0; i < deck; i++) {
								this->_enemyShipField[x + i][y + 1].status = 6;
							}
					}
					else if (ship.isHorisont() == false) {
						for (int i = 0; i < deck; i++)
							this->_enemyShipField[x][y + i].status = 3;
						if (x != 0)
							for (int i = 0; i < deck; i++) {
								this->_enemyShipField[x - 1][y + i].status = 6;
							}
						if (x != 9)
							for (int i = 0; i < deck; i++) {
								this->_enemyShipField[x + 1][y + i].status = 6;
							}
						if (y != 0) {
							this->_enemyShipField[x][y - 1].status = 6;
							if (x != 0)
								this->_enemyShipField[x - 1][y - 1].status = 6;
							if (x != 9)
								this->_enemyShipField[x + 1][y - 1].status = 6;
						}
						if (y + deck < 9) {
							this->_enemyShipField[x][y + deck].status = 6;
							if (x != 0)
								this->_enemyShipField[x - 1][y + deck].status = 6;
							if (x != 9)
								this->_enemyShipField[x + 1][y + deck].status = 6;
						}
					}
					set = true;
					if (count == 0)
						deck--;
					else if (count == 2)
						deck--;
					else if (count == 5)
						deck--;
					else if (count == 9)
						deck--;
					count++;
				}
			}
		}
	} while (this->checkRandom(type) == false);
}
}

void Field::setFieldsForGame() {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			if (this->_enemyShipField[i][j].status == 3)
				this->_enemyShipField[i][j].status = 5;
			if (this->_enemyShipField[i][j].status == 6)
				this->_enemyShipField[i][j].status = 4;
			if (this->_friendlyShipField[i][j].status == 6)
				this->_friendlyShipField[i][j].status = 0;
		}
}

Ship::Ship() : Field() {
	_isHorisontal = true;
	_deck = 0;
}

Ship::Ship(int deck, bool random) {
	if (random == true)
		_isHorisontal = rand() % 2;
	else
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

//function for drawing at console
void gotoxy(int xpos, int ypos)
{
	COORD scrn;

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos; scrn.Y = ypos;

	SetConsoleCursorPosition(hOuput, scrn);
}
