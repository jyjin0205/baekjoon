#include<iostream>
#include<stack>

// 틀려서 나중에 풀기로 함 ㅗ 모양을 고려 못했음

// bfs 문제
// 시작점을 정하고, 상하좌우로 깊이 5의 bfs
// 모든 시작점마다 하면 됨
using namespace std;

short** paper;
int height, width;

struct point {
	short leftindex;
	short topindex;
};

struct stackElement {
	point p;
	short numVisitedElement;
	int sum;
};

// (0,1)이면, left에서는 0번째, top에서는 1번째

int dfs(point p) {
	
	int ans = 0;

	stack<stackElement> s;
	bool** visited;
	visited = new bool* [height];
	for (int i = 0; i < height; i++)
	{
		visited[i] = new bool[width];
		for (int j = 0; j < width; j++)
		{
			visited[i][j] = false;
		}
	}

	stackElement sElem;
	sElem.p = p;
	sElem.numVisitedElement = 1;
	sElem.sum = paper[p.topindex][p.leftindex];
	s.push(sElem);
	visited[p.topindex][p.leftindex] = true;
	
	while (!s.empty())
	{
		stackElement currentElem = s.top();
		s.pop();
		if (currentElem.numVisitedElement == 4)
		{
			if (currentElem.sum > ans)
				ans = currentElem.sum;
			continue;
		}
		
		// 아직 끝까지 안 봤을 경우는 상하좌우 점을 확인		
		bool isTopAvailable = true;
		bool isBottomAvailable = true;
		bool isLeftAvailable = true;
		bool isRightAvailable = true;

		point currentPoint = currentElem.p;
		// 점이 유효한 점인지 확인
		if (currentPoint.leftindex == 0)
			isLeftAvailable = false;
		if (currentPoint.leftindex == width - 1)
			isRightAvailable = false;
		if (currentPoint.topindex == 0)
			isTopAvailable = false;
		if (currentPoint.topindex == height - 1)
			isBottomAvailable = false;


		stackElement nextElem = currentElem;
		nextElem.numVisitedElement++;
		stackElement topElem = nextElem;
		stackElement bottomElem = nextElem;
		stackElement leftElem = nextElem;
		stackElement rightElem = nextElem;

		topElem.p.topindex--;
		bottomElem.p.topindex++;
		leftElem.p.leftindex--;
		rightElem.p.leftindex++;

		if (isTopAvailable && !visited[topElem.p.topindex][topElem.p.leftindex])
		{
			topElem.sum += paper[topElem.p.topindex][topElem.p.leftindex];
			s.push(topElem);
			visited[topElem.p.topindex][topElem.p.leftindex] = true;
		}

		if (isBottomAvailable && !visited[bottomElem.p.topindex][bottomElem.p.leftindex])
		{
			bottomElem.sum+= paper[bottomElem.p.topindex][bottomElem.p.leftindex];
			s.push(bottomElem);
			visited[bottomElem.p.topindex][bottomElem.p.leftindex] = true;
		}

		if (isLeftAvailable && !visited[leftElem.p.topindex][leftElem.p.leftindex])
		{
			leftElem.sum += paper[leftElem.p.topindex][leftElem.p.leftindex];
			s.push(leftElem);
			visited[leftElem.p.topindex][leftElem.p.leftindex] = true;
		}

		if (isRightAvailable && !visited[rightElem.p.topindex][rightElem.p.leftindex])
		{
			rightElem.sum += paper[rightElem.p.topindex][rightElem.p.leftindex];
			s.push(rightElem);
			visited[rightElem.p.topindex][rightElem.p.leftindex] = true;
		}
	}
	
	return ans;
}

int main(void)
{
	int ans = -1;

	cin >> height >> width;
	paper = new short* [height];
	for (int i = 0; i < height; i++)
	{
		paper[i] = new short[width];
		for (int j = 0; j < width; j++)
		{
			cin >> paper[i][j];
		}
	}

	for (int countLeftIndex = 0; countLeftIndex < width; countLeftIndex++)
	{
		for (int countTopIndex = 0; countTopIndex < height; countTopIndex++)
		{
			point p;
			p.leftindex = countLeftIndex;
			p.topindex = countTopIndex;
			int temp = dfs(p);
			if (temp > ans)
				ans = temp;
		}
	}

	cout << ans;
	
}
