#include "Game.h"

Coord::Coord() {
	x = 99;
	y = 99;
}

Coord::Coord(int tx, int ty) {
	x = tx;
	y = ty;
}

Game::Game() : Field() {
	for (int i = 0; i < 2; i++) {
		_tempAICells[i].x = 99;
		_tempAICells[i].y = 99;
	}
	_end = false;
	_AIwork = false;
}

bool Game::isEnd() {
	return _end;
}

bool Game::isEnemyDeadShip(int, int)
{
	return false;
}

bool Game::isEnemyDeadShip(int, int, int)
{
	return false;
}

void Game::markDeadShip() {
	int x = 0;
	int y = 0;
	for (int i = 0; i < _tempDeadShip.capacity(); i++) {
		x = _tempDeadShip[i].x;
		y = _tempDeadShip[i].y;
		for (int j = 0; j < 3; j++) {
			if (this->getStatus(x - 1 + i, y - 1) != 1)
				_friendlyShipField[x - 1 + i][y - 1].status = 2;
		}
		for (int j = 0; j < 3; j++) {
			if (this->getStatus(x - 1 + i, y + 1) != 1)
				_friendlyShipField[x - 1 + i][y + 1].status = 2;
		}
		if (this->getStatus(x - 1, y) != 1) {
			_friendlyShipField[x - 1][y].status = 2;
		}
		if (this->getStatus(x + 1, y) != 1) {
			_friendlyShipField[x + 1][y].status = 2;
		}
	}
	_tempDeadShip.clear();
	_tempDeadShip.resize(0);
}


bool Game::shoot(char type) {
	int x = 0;
	int y = 0;
	Point projectile;
	projectile.tempfield[0][0] = 1;
	if (type == 'f') {
		while (true) {
			this->showEnemyField();
			projectile.showPoint(x, y);
			gotoxy(0, 15);
			cout << x;
			switch (_getch()) {
			case Keys::Up: {
				if (y != 0) {
					projectile.tempfield[x][y] = 0;
					y--;
					projectile.tempfield[x][y] = 1;
				}
				break;
			}
			case Keys::Down: {
				if (y != 9) {
					projectile.tempfield[x][y] = 0;
					y++;
					projectile.tempfield[x][y] = 1;
				}
				break;
			}
			case Keys::Right: {
				if (x != 9) {
					projectile.tempfield[x][y] = 0;
					x++;
					projectile.tempfield[x][y] = 1;
				}
				break;
			}
			case Keys::Left: {
				if (x != 0) {
					projectile.tempfield[x][y] = 0;
					x--;
					projectile.tempfield[x][y] = 1;
				}
				break;
			}
			case Keys::Enter: {
				if (this->_enemyShipField[x][y].status == 0 || this->_enemyShipField[x][y].status == 4) { // miss
					this->_enemyShipField[x][y].status = 2;
					this->showEnemyField();
					return false;
				}
				else if (this->_enemyShipField[x][y].status == 5) { // got it
					this->_enemyShipField[x][y].status = 1;
					this->showEnemyField();
					return true;
				}
				break;
			}
			}
		}
	}
	else if (type == 'e') {
		while (true) {
			if (_AIwork == false) {
				x = rand() % 10;
				y = rand() % 10;
				if (this->_friendlyShipField[x][y].status == 2 || this->_friendlyShipField[x][y].status == 1)
					continue;
				else if (this->_friendlyShipField[x][y].status == 4 || this->_friendlyShipField[x][y].status == 0) {
					this->_friendlyShipField[x][y].status = 2;
					this->showtempFields(3);
					return false;
				}
				else if (this->_friendlyShipField[x][y].status == 3) {
					this->_friendlyShipField[x][y].status = 1;
					_AIwork = true;
					if (isDeadShip(x, y) == true) {
						_AIwork = false;
						this->markDeadShip();
					}
					else {
						_tempDeadShip.clear();
						_tempDeadShip.resize(0);
						AIChooseDirection(x, y);
					}
					this->showtempFields(3);
					return true;
				}
			}
			else if (_AIwork == true) {
				x = _tempAICells[1].x;
				y = _tempAICells[1].y;
				if (this->_friendlyShipField[x][y].status == 2 || this->_friendlyShipField[x][y].status == 1) {
					for (int i = 0; i < 4; i++)
						if (this->_wasDirection[i] == 2)
							this->_wasDirection[i] = 1;
					AIChooseDirection(_tempAICells[0].x, _tempAICells[0].y);
					continue;
				}
				else if (this->_friendlyShipField[x][y].status == 4 || this->_friendlyShipField[x][y].status == 0) {
					this->_friendlyShipField[x][y].status = 2;
					this->showtempFields(3);
					for (int i = 0; i < 4; i++)
						if (this->_wasDirection[i] == 2)
							this->_wasDirection[i] = 1;
					AIChooseDirection(_tempAICells[0].x, _tempAICells[0].y);
					return false;
				}
				else if (this->_friendlyShipField[x][y].status == 3) {
					this->_friendlyShipField[x][y].status = 1;
					if (isDeadShip(_tempAICells[0].x, _tempAICells[0].y) == true) {
						_AIwork = false;
						this->markDeadShip();
					}
					else {
						_tempDeadShip.clear();
						_tempDeadShip.resize(0);
						int cont = 5;
						for (int i = 0; i < 4; i++)
							if (this->_wasDirection[i] == 2) {
								cont = i;
								break;
							}
						switch (cont) {
						case Direction::U: {
							if (y != 0) {
								this->_tempAICells[1].x = x;
								this->_tempAICells[1].y = y - 1;
							}
							else {
								_wasDirection[Direction::D] = 2;
								_wasDirection[Direction::U] = 1;
								this->_tempAICells[1].x = this->_tempAICells[0].x;
								this->_tempAICells[1].y = this->_tempAICells[0].y + 1;
							}
							break;
						}
						case Direction::D: {
							if (y != 9) {
								this->_tempAICells[1].x = x;
								this->_tempAICells[1].y = y + 1;
							}
							else {
								_wasDirection[Direction::D] = 1;
								_wasDirection[Direction::U] = 2;
								this->_tempAICells[1].x = this->_tempAICells[0].x;
								this->_tempAICells[1].y = this->_tempAICells[0].y - 1;
							}
							break;
						}
						case Direction::L: {
							if (x != 0) {
								this->_tempAICells[1].x = x - 1;
								this->_tempAICells[1].y = y;
							}
							else {
								_wasDirection[Direction::L] = 1;
								_wasDirection[Direction::R] = 2;
								this->_tempAICells[1].x = this->_tempAICells[0].x + 1;
								this->_tempAICells[1].y = y;
							}
							break;
						}
						case Direction::R: {
							if (x != 9) {
								this->_tempAICells[1].x = x + 1;
								this->_tempAICells[1].y = y;
							}
							else {
								_wasDirection[Direction::L] = 2;
								_wasDirection[Direction::R] = 1;
								this->_tempAICells[1].x = this->_tempAICells[0].x - 1;
								this->_tempAICells[1].y = y;
							}
							break;
						}
						}
					}
					this->showtempFields(3);
					return true;
				}
			}
		}
	}
}

void Game::AIChooseDirection(int x, int y) {
	this->_tempAICells[0].x = x;
	this->_tempAICells[0].y = y;
	bool choosen = false;
	while (choosen != true) {
		int random = rand() % 4;
		switch (random) {
		case Direction::U: {
			if (y != 0) {
				if (this->_wasDirection[Direction::U] == 0) {
					this->_tempAICells[1].x = x;
					this->_tempAICells[1].y = y - 1;
					choosen = true;
					this->_wasDirection[Direction::U] = 2;
				}
			}
			break;
		}
		case Direction::D: {
			if (y != 9) {
				if (this->_wasDirection[Direction::D] == 0) {
					this->_tempAICells[1].x = x;
					this->_tempAICells[1].y = y + 1;
					choosen = true;
					this->_wasDirection[Direction::D] = 2;
				}
			}
			break;
		}
		case Direction::L: {
			if (x != 0) {
				if (this->_wasDirection[Direction::L] == 0) {
					this->_tempAICells[1].x = x - 1;
					this->_tempAICells[1].y = y;
					choosen = true;
					this->_wasDirection[Direction::L] = 2;
				}
			}
			break;
		}
		case Direction::R: {
			if (x != 9) {
				if (this->_wasDirection[Direction::R] == 0) {
					this->_tempAICells[1].x = x + 1;
					this->_tempAICells[1].y = y;
					choosen = true;
					this->_wasDirection[Direction::R] = 2;
				}
			}
			break;
		}
		}
	}
}

bool Game::isDeadShip(int x, int y) {
	Coord temp = Coord(x, y);
	_tempDeadShip.clear();
	_tempDeadShip.push_back(temp);
	int good = 0;
	if ((this->getStatus(abs(x + 1),y) == 0 || this->getStatus(abs(x + 1), y) == 2)
		&& (this->getStatus(x, abs(y + 1)) == 0 || this->getStatus(x, abs(y + 1)) == 2)
		&& (this->getStatus(abs(x - 1), y) == 0 || this->getStatus(abs(x - 1), y) == 2)
		&& (this->getStatus(x, abs(y - 1)) == 0 || this->getStatus(x, abs(y - 1)) == 2)) {
		return true;
	}
	if (x != 0)
		if (this->getStatus(x - 1, y) == 1) {
			if (this->isDeadShip(x - 1, y, Direction::L) == true)
				good = 1;
		}
		else if (this->getStatus(x + 1, y) == 3 && x != 9) {
			return false;
		}
	if (x != 9)
		if (this->getStatus(x + 1, y) == 1) {
			if (this->isDeadShip(x + 1, y, Direction::R) == true)
				good = 1;
		}
		else if (this->getStatus(x - 1, y) == 3 && x != 0) {
			return false;
		}
	if (y != 0)
		if (this->getStatus(x, y - 1) == 1) {
			if (this->isDeadShip(x, y - 1, Direction::U) == true)
				good = 1;
		}
		else if (this->getStatus(x, y + 1) == 3 && y!= 9) {
			return false;
		}
	if (y != 9)
		if (this->getStatus(x, y + 1) == 1) {
			if (this->isDeadShip(x, y + 1, Direction::D) == true)
				good = 1;
		}
		else if (this->getStatus(x, y - 1) == 3 && y != 0) {
			return false;
		}
	if (good == 1)
		return true;
	else
		return false;
}

bool Game::isDeadShip(int x, int y, int direction) {
	Coord temp = Coord(x, y);
	_tempDeadShip.push_back(temp);
	switch (direction) {
	case Direction::L: {
		if (x != 0) {
			if (_friendlyShipField[x - 1][y].status == 0 || _friendlyShipField[x - 1][y].status == 2)
				return true;
			else if (_friendlyShipField[x - 1][y].status == 3)
				return false;
			else if (_friendlyShipField[x - 1][y].status == 1)
				if (this->isDeadShip(x - 1, y, Direction::L) == true)
					return true;
		}
		else
			return true;
		break;
	}
	case Direction::R: {
		if (x != 9) {
			if (_friendlyShipField[x + 1][y].status == 0 || _friendlyShipField[x + 1][y].status == 2)
				return true;
			else if (_friendlyShipField[x + 1][y].status == 3)
				return false;
			else if (this->_friendlyShipField[x + 1][y].status == 1)
				if (this->isDeadShip(x + 1, y, Direction::R) == true)
					return true;
		}
		else
			return true;
		break;
	}
	case Direction::U: {
		if (y != 0) {
			if (_friendlyShipField[x][y - 1].status == 0 || _friendlyShipField[x][y - 1].status == 2)
				return true;
			else if (_friendlyShipField[x][y - 1].status == 3)
				return false;
			else if (this->_friendlyShipField[x][y - 1].status == 1)
				if (this->isDeadShip(x, y - 1, Direction::U) == true)
					return true;
		}
		else
			return true;
		break;
	}
	case Direction::D: {
		if (y != 9) {
			if (_friendlyShipField[x][y + 1].status == 0 || _friendlyShipField[x][y + 1].status == 2)
				return true;
			else if (_friendlyShipField[x][y + 1].status == 3)
				return false;
			else if (this->_friendlyShipField[x][y + 1].status == 1)
				if (this->isDeadShip(x, y + 1, Direction::D) == true)
					return true;
		}
		else 
			return true;
		break;
	}
	}
}


void Point::showPoint(int x, int y) {
	gotoxy(x + 16, y + 1);
	cout << "*";
	gotoxy(0, 15);
}
