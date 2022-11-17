#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

bool gameOver;
const int height = 20;
const int width = 40;

int x, y, frX, frY;
int score = 0;
string user;
string path = "Score.txt";

int tlX[100], tlY[100], ntl;

enum eDirection { STOP = 0, UP, DOWN, LEFT, RIGHT };
eDirection dir;




void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	srand(time(0));
	frX = rand() % width;
	frY = rand() % height;
}
void Draw() {

	system("CLS");
	
	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				cout << "#";
			}
			else if (i == y && j == x) {
				cout << "O";
			}
			else if (i == frY && j == frX) {
				cout << "F";
			}
			else {
				bool print = false;

				for (int k = 0; k < ntl; k++) {
					if (i == tlY[k] && j == tlX[k]) {
						cout << "o";
						print = true;
					}
				}
				if (!print) {
					cout << " ";
				}	
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;
	cout << endl;
	cout << "SCORE: " << score << endl;
}
void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		default:
			break;
		}
	}
}
void Logic() {

	int prevX = tlX[0];
	int prevY = tlY[0];
	tlX[0] = x;
	tlY[0] = y;
	int prev2X, prev2Y;

	for (int i = 1; i < ntl; i++) {
		prev2X = tlX[i];
		prev2Y = tlY[i];
		tlX[i] = prevX;
		tlY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}

	if (x < 0 || x > width || y < 0 || y > height) {
		gameOver = true;
	}

	for (int i = 0; i < ntl; i++) {
		if (x == tlX[i] && y == tlY[i]) {
			gameOver = true;
		}
	}


	if (x == frX && y == frY) {
		score += 10;
		frX = rand() % width;
		frY = rand() % height;
		ntl++;
	}
}

int main() {
	cout << "Enter your nickname: ";
	cin >> user;
    
	fstream fs;
	fs.open(path, fstream::in | fstream::out | fstream::app);
	fs << user << " - " << score << "\n";


	if (user != "russian") {
		Setup();
		while (!gameOver) {
			Draw();
			Input();
			Logic();
			Sleep(40);
		}
	}
		

	return 0;
}