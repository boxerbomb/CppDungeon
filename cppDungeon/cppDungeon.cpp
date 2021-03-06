// cppDungeon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h";
#include "time.h";
#include <iostream>;
#include <string>;
#include "graphics.h";
using std::cout;
using std::string;
using std::cin;
using std::getline;


const int mapWidth=50;
const int mapHeight=25;
//Create grid object used for different enviroments
struct grid {
	int map[mapWidth][mapHeight];
};

grid cave;
void draw() {
	//clear screen, windows only
	system("CLS");
	string temp = "";
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			//Change this line for other feilds
			int mat = cave.map[x][y];
			if (mat == 0) {
				temp = temp + " ";
			}
			if (mat == 1) {
				temp = temp + "R";
			}
			if (mat == 2) {
				temp = temp + "X";
			}
		}
		cout << temp+"   "+text[y];
		cout << "\n";
		temp = "";
	}
}
int isSolid(int temp) {
	int value;
	if (temp == 1) {
		value = 1;
	}
	else {
		value = 0;
	}
	return value;
}

void genDungeon() {
	//0=nothing
	//1=Rock
	//2=wall
	srand(time(NULL)); //Randomize seed initialization
	int count = 0;
	for (int y = 0; y < mapHeight; y++) {
		for (int x=0; x < mapWidth; x++) {
			cave.map[x][y] = rand() % 2;
			if (x == mapWidth-1 || y == mapHeight-1 || x==0||y==0) {
				cave.map[x][y] = 2;
			}
		}
	}
	for (int y = 1; y < mapHeight-1; y++) {
		for (int x = 1; x < mapWidth-1; x++) {
			count = isSolid(cave.map[y + 1][x - 1]) + isSolid(cave.map[y + 1][x]) + isSolid(cave.map[y + 1][x + 1]) + isSolid(cave.map[y][x - 1]) + isSolid(cave.map[y][x + 1]) + isSolid(cave.map[y - 1][x - 1]) + isSolid(cave.map[y - 1][x]) + isSolid(cave.map[y - 1][x + 1]);
			if (count <= 3) {
				cave.map[x][y] = 0;
			}
			else if(count==3 && rand()%3==2){
				cave.map[x][y] = 1;
			}
		}
	}
	draw();
}

string input() {
	string text;
	getline(cin, text);
	return text;
}
void loop() {
	while (1==1){
		genDungeon();
		string raw=input();
		string temp = "";
		string command = "";
		string arg1 = "";
		string arg2 = "";
		int count = 0;
		for (unsigned int i = 0; i<raw.length()+1; i++) {
			char c = raw[i];
			if (c == ' ' || c == ',' || i==raw.length()) {
				switch (count) {
				case 0:command = temp;
				case 1:arg1 = temp;
				case 2:arg2 = temp;
				}
				temp = "";
				count = count + 1;
			}
			else {
				temp = temp + c;
			}
		}
		cout << "command:" + command + " arg1:" + arg1 + " arg2:" + arg2 + "\n";
		cout << "looping...\n";
	}
}

int main()
{
	loop();
    return 0;
}

