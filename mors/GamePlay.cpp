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
	_end = false;
	_AIwork = false;
}

bool Game::isEnd() {
	return _end;
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

			}
		}
	}
}

bool Game::isDeadShip(int x, int y) {
	Coord temp = Coord(x, y);
	_tempDeadShip.push_back(temp);
	if ((this->_friendlyShipField[abs(x + 1)][y].status == 0 || this->_friendlyShipField[abs(x + 1)][y].status == 2) 
		&& (this->_friendlyShipField[x][abs(y + 1)].status == 0 || this->_friendlyShipField[x][abs(y + 1)].status == 2) 
		&& (this->_friendlyShipField[abs(x - 1)][y].status == 0 || this->_friendlyShipField[abs(x - 1)][y].status == 2)
		&& (this->_friendlyShipField[x][abs(y - 1)].status == 0 || this->_friendlyShipField[x][abs(y - 1)].status == 2)) {
		return true;
	}
	if (x != 0)
		if (this->_friendlyShipField[x - 1][y].status == 1)
			if (this->isDeadShip(x - 1, y, Direction::Left) == true)
				return true;
	if (x != 9)
		if (this->_friendlyShipField[x + 1][y].status == 1)
			if (this->isDeadShip(x + 1, y, Direction::Right) == true)
				return true;
	if (y != 0)
		if (this->_friendlyShipField[x][y - 1].status == 1)
			if (this->isDeadShip(x, y - 1, Direction::Up) == true)
				return true;
	if (y != 9)
		if (this->_friendlyShipField[x][y + 1].status == 1)
			if (this->isDeadShip(x, y + 1, Direction::Down) == true)
				return true;
	return false;
}

bool Game::isDeadShip(int x, int y, char direction) {
	Coord temp = Coord(x, y);
	_tempDeadShip.push_back(temp);
	switch (direction) {
	case Direction::Left: {
		if (x != 0) {
			if (_friendlyShipField[x - 1][y].status == 0 || _friendlyShipField[x - 1][y].status == 2)
				return true;
			else if (_friendlyShipField[x - 1][y].status == 3)
				return false;
			else if (_friendlyShipField[x - 1][y].status == 1)
				if (this->isDeadShip(x - 1, y, Direction::Left) == true)
					return true;
		}
		else
			return true;
		break;
	}
	case Direction::Right: {
		if (x != 9) {
			if (_friendlyShipField[x + 1][y].status == 0 || _friendlyShipField[x + 1][y].status == 2)
				return true;
			else if (_friendlyShipField[x + 1][y].status == 3)
				return false;
			else if (this->_friendlyShipField[x + 1][y].status == 1)
				if (this->isDeadShip(x + 1, y, Direction::Right) == true)
					return true;
		}
		else
			return true;
		break;
	}
	case Direction::Up: {
		if (y != 0) {
			if (_friendlyShipField[x][y - 1].status == 0 || _friendlyShipField[x][y - 1].status == 2)
				return true;
			else if (_friendlyShipField[x][y - 1].status == 3)
				return false;
			else if (this->_friendlyShipField[x][y - 1].status == 1)
				if (this->isDeadShip(x, y - 1, Direction::Up) == true)
					return true;
		}
		else
			return true;
		break;
	}
	case Direction::Down: {
		if (y != 9) {
			if (_friendlyShipField[x][y + 1].status == 0 || _friendlyShipField[x][y + 1].status == 2)
				return true;
			else if (_friendlyShipField[x][y + 1].status == 3)
				return false;
			else if (this->_friendlyShipField[x][y + 1].status == 1)
				if (this->isDeadShip(x, y + 1, Direction::Down) == true)
					return true;
		}
		else 
			return true;
		break;
	}
	}
}

void Game::markDeadShip() {

}

void Point::showPoint(int x, int y) {
	gotoxy(x + 16, y + 1);
	cout << "*";
	gotoxy(0, 15);
}
