#include <iostream>

// 주사위를 굴렸을 때, 이동한 칸에 쓰여 있는 수가 0이면, 주사위의 바닥면의 수가 칸에 복사
// 0이 아니면, 칸에 쓰인 수가 주사위의 바닥면으로 복사

using namespace std;


int height, width;

enum direction {
	RIGHT, LEFT, UP, DOWN, ERROR
};

struct Dice {
	short top, bottom, up, down, right, left;

	short x, y;
	
	void printAll() {
		cout << " " << up << " " << endl;
		cout << left << top << right << endl;
		cout << " " << down << " " << endl;
		cout << " " << bottom << " " << endl;
	}

	void printTop() {
		cout << top << endl;
	}

	short getBottom() {
		return bottom;
	}

	void setBottom(short num) {
		bottom = num;
	}

	bool determineRoll(direction d)
	{
		if (d == LEFT && x == 0)
			return false;

		if (d == RIGHT && x == width - 1)
			return false;

		if (d == UP && y == 0)
			return false;

		if (d == DOWN && y == height - 1)
			return false;

		return true;
	}

	void roll(direction d) {
		if (d == LEFT)
		{

			// 왼쪽으로 굴리면, up, down은 유지, top이었던 게 left가 되고, left 였던 게 bottom이 되고 ...
			short beforeleft = left;
			left = top;
			top = right;
			right = bottom;
			bottom = beforeleft;
			x--;

		}
		else if (d == RIGHT)
		{
			// 오른쪽으로 굴리면, top이었던 게 right가 되고, right 였던 게 bottom이 되고 ...
			short beforeright = right;
			right = top;
			top = left;
			left = bottom;
			bottom = beforeright;
			x++;
		}
		else if (d == UP)
		{
			// 위로 굴리면, left, right는 유지, up이었던 게 bottom이 되고, bottom이었던 게 down이 됨
			short beforeup = up;
			up = top;
			top = down;
			down = bottom;
			bottom = beforeup;
			y--;

		}
		else if (d == DOWN)
		{
			// 아래로 굴리면, up 이었던 게 top이 되고, top 이었던 게 down이 됨;
			short beforeup = up;
			up = bottom;
			bottom = down;
			down = top;
			top = beforeup;
			y++;
		}
		else
		{
			cout << "error";
		}
	}
};

void printmap(short**& map)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}


int main(void)
{
	Dice dice;
	dice.top = 0;
	dice.bottom = 0;
	dice.up = 0;
	dice.down = 0;
	dice.right = 0;
	dice.left = 0;

	int numOrder;
	direction* dir;
	short** map;

	cin >> height >> width >> dice.y >> dice.x >> numOrder;
	map = new short* [height];
	for (int i = 0; i < height; i++)
	{
		map[i] = new short[width];
		for (int j = 0; j < width; j++)
		{
			cin >> map[i][j];
		}
	}

	dir = new direction[numOrder];
	for (int i = 0; i < numOrder; i++)
	{
		short a;
		cin >> a;
		switch (a)
		{
		case 1 :
			dir[i] = RIGHT;
			break;
		case 2:
			dir[i] = LEFT;
			break;
		case 3:
			dir[i] = UP;
			break;
		case 4:
			dir[i] = DOWN;
			break;
		default:
			dir[i] = ERROR;
			break;
		}
	}

	for (int i = 0; i < numOrder; i++)
	{
		//dice.printAll();
		//dice.printTop();
		//printmap(map);

		//cout << "current x, y: (" << dice.x << "," << dice.y << ")" << endl;
		
		// 주사위 굴리기
		if (dice.determineRoll(dir[i]) == false)
			continue;
		dice.roll(dir[i]);

		// 지도 업데이트
		if (map[dice.y][dice.x] == 0)
		{
			short num = dice.getBottom();
			map[dice.y][dice.x] = num;
		}
		else {
			short num = map[dice.y][dice.x];
			dice.setBottom(num);
			map[dice.y][dice.x] = 0;
		}

		dice.printTop();
	}
}
