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
	_isTurned = false;
	_tempDeadShip.resize(0);
	_tempDeadFriendlyShip.resize(0);
	for (int i = 0; i < 4; i++) {
		_wasDirection[i] = 0;
	}
}

char Game::whoIsWinner() {
	int countDeadEnemyDecks = 0;
	int countDeadFriendlyDecks = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			if (this->getStatus(i, j) == 1) {
				countDeadFriendlyDecks++;
			}
			if (this->getEnemyStatus(i, j) == 1) {
				countDeadEnemyDecks++;
			}
		}
	if (countDeadEnemyDecks == 20)
		return 'f';
	else if (countDeadFriendlyDecks == 20)
		return 'e';
	else
		return 'n';
}

bool Game::isEnd() {
	return _end;
}

bool Game::isEnemyDeadShip(int x, int y) {
	bool ended = false;
	_tempDeadFriendlyShip.clear();
	_tempDeadFriendlyShip.shrink_to_fit();
	Coord temp(x, y);
	_tempDeadFriendlyShip.push_back(temp);
	if ((this->getEnemyStatus(x + 1, y) == 0 || this->getEnemyStatus(x + 1, y) == 2 || (x + 1 > 9))
		&& (this->getEnemyStatus(x, y + 1) == 0 || this->getEnemyStatus(x, y + 1) == 2 || (x + 1 > 9))
		&& (this->getEnemyStatus(abs(x - 1), y) == 0 || this->getEnemyStatus(abs(x - 1), y) == 2)
		&& (this->getEnemyStatus(x, abs(y - 1)) == 0 || this->getEnemyStatus(x, abs(y - 1)) == 2)) {
		return true;
	}
	int i = 1;
	while (ended != true) {
		if (x + i < 10) {
			if (this->getEnemyStatus(x + i, y) == 5) {
				return false;
			}
			else if (this->getEnemyStatus(x + i, y) == 1) {
				temp.x = x + i;
				temp.y = y;
				_tempDeadFriendlyShip.push_back(temp);
				i++;
				continue;
			}
			else if (this->getEnemyStatus(x + i, y) == 0 || this->getEnemyStatus(x + i, y) == 2)
				ended = true;
		}
		else
			ended = true;
		i++;
	}
	i = 1;
	ended = false;
	while (ended != true) {
		if (x - i >= 0) {
			if (this->getEnemyStatus(x - i, y) == 5) {
				return false;
			}
			else if (this->getEnemyStatus(x - i, y) == 1) {
				temp.x = x - i;
				temp.y = y;
				_tempDeadFriendlyShip.push_back(temp);
				i++;
				continue;
			}
			else if (this->getEnemyStatus(x - i, y) == 0 || this->getEnemyStatus(x - i, y) == 2)
				ended = true;
		}
		else
			ended = true;
		i++;
	}
	i = 1;
	ended = false;
	while (ended != true) {
		if (y + i < 10) {
			if (this->getEnemyStatus(x, y + i) == 5) {
				return false;
			}
			else if (this->getEnemyStatus(x, y + i) == 1) {
				temp.x = x;
				temp.y = y + i;
				_tempDeadFriendlyShip.push_back(temp);
				i++;
				continue;
			}
			else if (this->getEnemyStatus(x, y + i) == 0 || this->getEnemyStatus(x, y + i) == 2)
				ended = true;
		}
		else
			ended = true;
		i++;
	}
	i = 1;
	ended = false;
	while (ended != true) {
		if (y - i >= 0) {
			if (this->getEnemyStatus(x, y - i) == 5) {
				return false;
			}
			else if (this->getEnemyStatus(x, y - i) == 1) {
				temp.x = x;
				temp.y = y - i;
				_tempDeadFriendlyShip.push_back(temp);
				i++;
				continue;
			}
			else if (this->getEnemyStatus(x, y - i) == 0 || this->getEnemyStatus(x, y - i) == 2)
				ended = true;
		}
		else
			ended = true;
		i++;
	}
	return true;
}

void Game::markFriendlyDeadShip() {
	int x = 0;
	int y = 0;
	_tempDeadShip.shrink_to_fit();
	for (int i = 0; i < _tempDeadShip.capacity(); i++) {
		x = _tempDeadShip[i].x;
		y = _tempDeadShip[i].y;
		for (int j = 0; j < 3; j++) {
			if ((this->getStatus(abs(x - 1 + j), abs(y - 1)) == 2 || this->getStatus(abs(x - 1 + j), abs(y - 1)) == 0) && (x - 1 + j < 10))
				_friendlyShipField[abs(x - 1 + j)][abs(y - 1)].status = 2;
		}
		for (int j = 0; j < 3; j++) {
			if ((this->getStatus(abs(x - 1 + j), y + 1) == 2 || this->getStatus(abs(x - 1 + j), abs(y + 1)) == 0) && (x - 1 + j < 10) && (y + 1 < 10))
				_friendlyShipField[abs(x - 1 + j)][y + 1].status = 2;
		}
		if (this->getStatus(abs(x - 1), y) == 2 || this->getStatus(abs(x - 1), y) == 0) {
			_friendlyShipField[abs(x - 1)][y].status = 2;
		}
		if ((this->getStatus(abs(x + 1), y) == 2 || this->getStatus(abs(x + 1), y) == 0) && (x + 1 < 10)) {
			_friendlyShipField[x + 1][y].status = 2;
		}
	}
	_tempDeadShip.clear();
	_tempDeadShip.shrink_to_fit();
}

void Game::markEnemyDeadShip() {
	int x = 0;
	int y = 0;
	_tempDeadFriendlyShip.shrink_to_fit();
	for (int i = 0; i < _tempDeadFriendlyShip.capacity(); i++) {
		x = _tempDeadFriendlyShip[i].x;
		y = _tempDeadFriendlyShip[i].y;
		for (int j = 0; j < 3; j++) {
			if ((this->getEnemyStatus(abs(x - 1 + j), abs(y - 1)) == 2 || this->getEnemyStatus(abs(x - 1 + j), abs(y - 1)) == 0) && (x - 1 + j < 10))
				_enemyShipField[abs(x - 1 + j)][abs(y - 1)].status = 2;
		}
		for (int j = 0; j < 3; j++) {
			if ((this->getEnemyStatus(abs(x - 1 + j), y + 1) == 2 || this->getEnemyStatus(abs(x - 1 + j), abs(y + 1)) == 0) && (x - 1 + j < 10) && (y + 1 < 10))
				_enemyShipField[abs(x - 1 + j)][y + 1].status = 2;
		}
		if (this->getEnemyStatus(abs(x - 1), y) == 2 || this->getEnemyStatus(abs(x - 1), y) == 0) {
			_enemyShipField[abs(x - 1)][y].status = 2;
		}
		if ((this->getEnemyStatus(abs(x + 1), y) == 2 || this->getEnemyStatus(abs(x + 1), y) == 0) && (x + 1 < 10)) {
			_enemyShipField[x + 1][y].status = 2;
		}
	}
	_tempDeadFriendlyShip.clear();
	_tempDeadFriendlyShip.shrink_to_fit();
}

bool Game::shoot(char type) {
	int x = 0;
	int y = 0;
	bool choosenDirection = false;
	Point projectile;
	projectile.tempfield[0][0] = 1;
	if (type == 'f') {
		while (true) {
			this->showEnemyField();
			projectile.showPoint(x, y);
			gotoxy(0, 15);
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
					if (this->isEnemyDeadShip(x, y) == true) {
						this->markEnemyDeadShip();
						this->showEnemyField();
					}
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
					Coord temp(x, y);
					_tempDeadShip.push_back(temp);
					if (isDeadShip(x, y) == true) {
						_AIwork = false;
						this->markFriendlyDeadShip();
					}
					else {
						this->_tempAICells[0].x = x;
						this->_tempAICells[0].y = y;
						AIChooseDirection(this->_tempAICells[0].x, this->_tempAICells[0].y);
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
					Coord temp(x, y);
					_tempDeadShip.push_back(temp);
					if (isDeadShip(_tempAICells[0].x, _tempAICells[0].y) == true) {
						_AIwork = false;
						this->markFriendlyDeadShip();
						for (int i = 0; i < 4; i++)
							_wasDirection[i] = 0;
					}
					else {
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
	bool choosen = false;
	int random = 0;
	while (choosen != true) {
		random = rand() % 4;
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
	int good = 0;
	_isTurned = false;
	if ((this->getStatus(x + 1, y) == 0 || this->getStatus(x + 1, y) == 2 || (x + 1 > 9))
		&& (this->getStatus(x, y + 1) == 0 || this->getStatus(x, y + 1) == 2 || (x + 1 > 9))
		&& (this->getStatus(abs(x - 1), y) == 0 || this->getStatus(abs(x - 1), y) == 2)
		&& (this->getStatus(x, abs(y - 1)) == 0 || this->getStatus(x, abs(y - 1)) == 2)) {
		return true;
	}
	if (x != 0)
		if (this->getStatus(x - 1, y) == 1) {
			if (this->isDeadShip(x, y, Direction::L) == true)
				good = 1;
		}
		if (this->getStatus(x + 1, y) == 3 && x != 9 && this->isDeadShip(x, y, Direction::R) == false) {
			return false;
		}
	if (x != 9)
		if (this->getStatus(x + 1, y) == 1) {
			if (this->isDeadShip(x, y, Direction::R) == true)
				good = 1;
		}
		if (this->getStatus(x - 1, y) == 3 && x != 0 && this->isDeadShip(x, y, Direction::L) == false) {
			return false;
		}
	if (y != 0)
		if (this->getStatus(x, y - 1) == 1) {
			if (this->isDeadShip(x, y, Direction::U) == true)
				good = 1;
		}
		if (this->getStatus(x, y + 1) == 3 && y!= 9 && this->isDeadShip(x, y, Direction::D) == false) {
			return false;
		}
	if (y != 9)
		if (this->getStatus(x, y + 1) == 1) {
			if (this->isDeadShip(x, y, Direction::D) == true)
				good = 1;
		}
		if (this->getStatus(x, y - 1) == 3 && y != 0 && this->isDeadShip(x, y, Direction::U) == false) {
			return false;
		}
	if (good == 1)
		return true;
	else
		return false;
}

bool Game::isDeadShip(int x, int y, int direction) {
	switch (direction) {
	case Direction::L: {
		if (x != 0) {
			if (_friendlyShipField[x - 1][y].status == 0 || _friendlyShipField[x - 1][y].status == 2) {
				if (x != 9 && _isTurned == false) {
					_isTurned = true;
					if (_friendlyShipField[this->_tempAICells[0].x + 1][this->_tempAICells[0].y].status == 0 || _friendlyShipField[this->_tempAICells[0].x + 1][this->_tempAICells[0].y].status == 2)
						return true;
					if (this->isDeadShip(this->_tempAICells[0].x + 1, this->_tempAICells[0].y, Direction::R) == true)
						return true;
					else
						return false;
				}
				else
					return true;
			}
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
			if (_friendlyShipField[x + 1][y].status == 0 || _friendlyShipField[x + 1][y].status == 2) {
				if (x != 0 && _isTurned == false) {
					_isTurned = true;
					if (_friendlyShipField[this->_tempAICells[0].x - 1][this->_tempAICells[0].y].status == 0 || _friendlyShipField[this->_tempAICells[0].x - 1][this->_tempAICells[0].y].status == 2)
						return true;
					if (this->isDeadShip(this->_tempAICells[0].x - 1, this->_tempAICells[0].y, Direction::L) == true)
						return true;
					else
						return false;
				}
				else
					return true;
			}
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
			if (_friendlyShipField[x][y - 1].status == 0 || _friendlyShipField[x][y - 1].status == 2) {
				if (y != 9 && _isTurned == false) {
					_isTurned = true;
					if (_friendlyShipField[this->_tempAICells[0].x][this->_tempAICells[0].y + 1].status == 0 || _friendlyShipField[this->_tempAICells[0].x][this->_tempAICells[0].y + 1].status == 2)
						return true;
					if (this->isDeadShip(this->_tempAICells[0].x, this->_tempAICells[0].y + 1, Direction::D) == true)
						return true;
					else
						return false;
				}
				else
					return true;
			}
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
			if (_friendlyShipField[x][y + 1].status == 0 || _friendlyShipField[x][y + 1].status == 2) {
				if (y != 0 && _isTurned == false) {
					_isTurned = true;
					if (_friendlyShipField[this->_tempAICells[0].x][this->_tempAICells[0].y - 1].status == 0 || _friendlyShipField[this->_tempAICells[0].x][this->_tempAICells[0].y - 1].status == 2)
						return true;
					if (this->isDeadShip(this->_tempAICells[0].x, this->_tempAICells[0].y - 1, Direction::U) == true)
						return true;
					else
						return false;
				}
				else
					return true;
			}
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

void Game::End() {
	_end = true;
}

void Point::showPoint(int x, int y) {
	gotoxy(x + 16, y + 1);
	cout << "*";
	gotoxy(0, 15);
}