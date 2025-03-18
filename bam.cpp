#include <iostream>
#include <map>
#include <queue>

using namespace std;

enum direction {
	LEFT, RIGHT, UP, DOWN
}; // 뱀의 머리의 방향
struct point {
	int x;
	int y;
};

void printBam(int boardSize, queue<point> snake, bool** appletrackingBoard)
{
	char** board;
	board = new char* [boardSize];
	for (int i = 0; i < boardSize; i++)
	{
		board[i] = new char[boardSize];
		for (int j = 0; j < boardSize; j++)
		{
			if (appletrackingBoard[i][j])
				board[i][j] = 'A';
			else
				board[i][j] = '*';
		}
	}

	while (!snake.empty()) {
		point p = snake.front();
		board[p.x][p.y] = 'O';
		snake.pop();
	}

	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << "------------------------------------" << endl;
}

direction turnBam(direction currentdirection, char c)
{
	switch (currentdirection) {
	case LEFT:
		if (c == 'L') return DOWN;
		else if (c == 'D') return UP;
		break;
	case RIGHT:
		if (c == 'L') return UP;
		else if (c == 'D') return DOWN;
		break;
	case UP:
		if (c == 'L') return LEFT;
		else if (c == 'D') return RIGHT;
		break;
	case DOWN:
		if (c == 'L') return RIGHT;
		else if (c == 'D') return LEFT;
		break;
	}
}

int main(void)
{
	int boardSize, numApple;
	cin >> boardSize >> numApple;

	bool** appleTrackingBoard = new bool* [boardSize];
	for (int i = 0; i < boardSize;i++)
	{
		appleTrackingBoard[i] = new bool[boardSize];
		for (int j = 0; j < boardSize; j++)
			appleTrackingBoard[i][j] = false;
	}

	for (int i = 0; i < numApple; i++)
	{
		int x, y;
		cin >> x >> y;
		appleTrackingBoard[x-1][y-1] = true;
	}

	int L;
	map<int, char> turns;
	cin >> L;
	for (int i = 0; i < L; i++)
	{
		int a;
		char c;
		cin >> a >> c;
		turns[a] = c;
	}

	int time = 0;
	queue<point> snake;
	direction currentDirection = RIGHT;
	point startPoint;
	startPoint.x = 0;
	startPoint.y = 0;
	snake.push(startPoint);

	/*(x,y)
	* ----------------------
	* (0,0) (0,1)             (0,N-1)
	* (1,0) (1,1)            (1,N-1)
	* 
	* 
	* 
	* (N-2,0)            (N-2,N-1)
	* (N-1,0)            (N-1,N-1)
	*/

	// 종료조건 테스트
	while (1)
	{
		//cout << time << endl;
		//printBam(boardSize, snake, appleTrackingBoard);

		time++;
		// turns - <시간, char (L이면 왼쪽, D면 오른쪽)>
		// apples - 모든 사과들의 x와 y좌표가 저장되어 있음
		// snake - queue : fifo 구조, snake.front()는 꼬리, snake.rear() 머리
		// 이동

		point nextPoint;
		point currentHead = snake.back();
		nextPoint.x = currentHead.x;
		nextPoint.y = currentHead.y;

		switch (currentDirection) {
		case UP:
			nextPoint.x--;
			break;
		case DOWN:
			nextPoint.x++;
			break;
		case LEFT:
			nextPoint.y--;
			break;
		case RIGHT:
			nextPoint.y++;
			break;
		}
		// nextPoint가 벗어날 경우, 사과 테스트가 안됨.
		if (nextPoint.x < 0 || nextPoint.y < 0 || nextPoint.x >= boardSize || nextPoint.y >= boardSize)
			break;

		// 종료조건 테스트
		// 벗어나는 거는 이미 테스트 완료
		// 만나는 지만 테스트하면 됨
		queue<point> copySnake = snake;
		bool isCrashed = false;
		while (!copySnake.empty())
		{
			point p = copySnake.front();
			if (nextPoint.x == p.x && nextPoint.y == p.y)
				isCrashed = true;
			copySnake.pop();
		}

		if (isCrashed)
			break;
		else
			snake.push(nextPoint);

		// 사과 여부 테스트
		if (appleTrackingBoard[nextPoint.x][nextPoint.y] == false)
			snake.pop();
		else
		{
			appleTrackingBoard[nextPoint.x][nextPoint.y] = false;
		}

		
		// 방향 전환은 끝난 뒤에라 하였으므로 방향 전환
		if (turns.find(time) != turns.end()) {
			currentDirection = turnBam(currentDirection, turns[time]);
		}
	}
	cout << time;
}
