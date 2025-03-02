#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

//고려해야 할 사항
// 1. 이동해서 똑같다면 그 전에서 이미 고려한 경우이므로 큐에 넣지 않음

short height;

enum direction {
	UP, DOWN, RIGHT, LEFT
};

class boardStatus {
private:
	short** board;
	bool isMoved;
	short maximum;
	short count;
public:
	boardStatus(short _height) {
		board = new short* [_height];
		isMoved = false;
		maximum = -1;
		count = 0;
	}

	boardStatus(const boardStatus& other) {
		board = new short* [height];
		for (int i = 0; i < height; i++)
		{
			board[i] = new short[height];
			for (int j = 0; j < height; j++)
			{
				board[i][j] = other.board[i][j];
			}
		}
		isMoved = false;
		maximum = other.maximum;
		count = other.count;
	}

	~boardStatus() {
		for (int i = 0; i < height; i++)
		{
			delete[] board[i];
		}
		delete[] board;
	}

	void inputBoard(short _height) {
		for (int i = 0; i < _height; i++)
		{
			board[i] = new short[_height];
			for (int j = 0; j < _height; j++)
			{
				short input;
				cin >> input;
				if (input == 0)
					board[i][j] = -1;
				else board[i][j] = log2(input);

				if (board[i][j] > maximum)
					maximum = board[i][j];
			}
		}
	}

	bool getisMoved() {
		return isMoved;
	}

	short getCount() {
		return count;
	}

	short getMaximum() {
		return maximum;
	}

	void printBoard() {
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < height; j++)
			{
				if (board[i][j] == -1)
					cout << 0 << " ";
				else 
					cout << pow(2,board[i][j]) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	
	void moveBoard(direction d)
	{
		count++;

		switch (d) {
		case(UP) :
			handleMoveUp();
			break;
		case(DOWN) :
			handleMoveDown();
			break;
		case(RIGHT):
			handleMoveRight();
			break;
		case(LEFT):
			handleMoveLeft();
			break;
		}
		
	}

	
	void handlemoveDownAgain()
	{
		for (int w = 0; w < height; w++)
		{
			if (board[0][w] == -1) // all zero
				continue;
			if (board[height - 1][w] != -1) // all nonzero
				continue;

			if (isMoved == false) isMoved = true;

			int maxNonZeroHeight = 0;
			for (; maxNonZeroHeight < height-1; maxNonZeroHeight++)
				if (board[maxNonZeroHeight+1][w] == -1) break;
			
			int movingDistance = height - 1 - maxNonZeroHeight;
			for (int h = maxNonZeroHeight; h >= 0; h--)
				board[h + movingDistance][w] = board[h][w], board[h][w] = -1;
		}
	}

	void handlemoveRightAgain()
	{
		for (int w = 0; w < height; w++)
		{
			if (board[w][0] == -1) // all zero
				continue;
			if (board[w][height-1] != -1) // all nonzero
				continue;

			if (isMoved == false) isMoved = true;

			int maxNonZeroHeight = 0;
			for (; maxNonZeroHeight < height - 1; maxNonZeroHeight++)
				if (board[w][maxNonZeroHeight + 1] == -1) break;

			int movingDistance = height - 1 - maxNonZeroHeight;
			for (int h = maxNonZeroHeight; h >= 0; h--)
				board[w][h + movingDistance] = board[w][h], board[w][h] = -1;
		}
	}

	void moveBoardRemoveZero(bool isVertical)
	{
		for (int w = 0; w < height; w++)
		{
			bool isMovable = true;
			while (isMovable)
			{
				isMovable = false;
				for (int h = 0; h < height - 1; h++)
				{
					if (isVertical)
					{
						if (board[h][w] == -1 && board[h + 1][w] != -1)
						{
							board[h][w] = board[h + 1][w];
							board[h + 1][w] = -1;
							isMovable = true;
							isMoved = true;
						}
					}
					else
					{
						if (board[w][h] == -1 && board[w][h + 1] != -1)
						{
							board[w][h] = board[w][h + 1];
							board[w][h + 1] = -1;
							isMovable = true;
							isMoved = true;
						}
					}
				}
			}
		}

	}

	void handleMoveRight()
	{
		moveBoardRemoveZero(false);

		for (int w = 0; w < height; w++)
		{
			for (int h = height-1; h > 0; h--)
			{
				if (board[w][h] == board[w][h-1] && board[w][h] != -1)
				{
					board[w][h]++, board[w][h -1] = -1;
					isMoved = true;
					if (board[w][h] > maximum) maximum = board[w][h];
				}
			}
		}

		moveBoardRemoveZero(false);

		handlemoveRightAgain();
	}

	void handleMoveLeft()
	{
		moveBoardRemoveZero(false);

		for (int w = 0; w < height; w++)
		{
			for (int h = 0; h < height - 1; h++)
			{
				if (board[w][h] == board[w][h + 1] && board[w][h] != -1)
				{
					board[w][h]++, board[w][h + 1] = -1;
					isMoved = true;
					if (board[w][h] > maximum) maximum = board[w][h];
				}
			}
		}

		moveBoardRemoveZero(false);
	}

	void handleMoveUp()
	{
		moveBoardRemoveZero(true);

		for (int w = 0; w < height; w++)
		{
			for (int h = 0; h < height - 1; h++)
			{
				if (board[h][w] == board[h + 1][w] && board[h][w] != -1)
				{
					board[h][w]++, board[h + 1][w] = -1;
					isMoved = true;
					if (board[h][w] > maximum) maximum = board[h][w];
				}
			}
		}

		moveBoardRemoveZero(true);
	}

	void handleMoveDown()
	{
		moveBoardRemoveZero(true);

		for (int w = 0; w < height; w++)
		{
			for (int h = height-1; h > 0; h--)
			{
				if (board[h][w] == board[h-1][w] && board[h][w] != -1)
				{
					board[h][w]++, board[h-1][w] = -1;
					isMoved = true;
					if (board[h][w] > maximum) maximum = board[h][w];
				}
			}
		}

		moveBoardRemoveZero(true);

		handlemoveDownAgain();
	}

};

int main(void) {
	cin >> height;
	boardStatus initialBoard(height);
	initialBoard.inputBoard(height);
	
	queue<boardStatus> q;
	q.push(initialBoard);

	short ans = -1;

	while (!q.empty())
	{
		boardStatus currentBoard = q.front();
		q.pop();

		if (currentBoard.getCount() > 5)
			break;

		if (currentBoard.getMaximum() > ans)
		{
			ans = currentBoard.getMaximum();
		}

		boardStatus movedBoard[4] = { currentBoard, currentBoard, currentBoard, currentBoard };
		movedBoard[0].moveBoard(UP);
		movedBoard[1].moveBoard(DOWN);
		movedBoard[2].moveBoard(LEFT);
		movedBoard[3].moveBoard(RIGHT);

		for (int i = 0; i < 4; i++) {
			//movedBoard[i].printBoard();
			q.push(movedBoard[i]);

			/*if (movedBoard[i].getisMoved() == true)
				q.push(movedBoard[i]);
			else
				cout << "ismoved false" << endl;
				*/
		}
	}
	if (ans == -1)
		cout << 0 << endl;
	else 
		cout << pow(2, ans) << endl;
}
