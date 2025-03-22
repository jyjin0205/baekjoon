#include <iostream>

// N개의 시험장, i번 시험장에 응시자 수는 Ai명
// 감독은 총감독관, 부감독관이 있음. 총감독관은 감시 가능 응시자 수가 B명, 부감독관은 C명
// 한 시험장에 총감독관은 더도 말고 덜도 말고 1명만, 부감독관은 여러 명

using namespace std;

int main(void)
{
	int numberRoom;
	int* numberStudent;
	int maxMain, maxSub;
	long long int numSupervisor = 0;
		
	cin >> numberRoom;
	numberStudent = new int[numberRoom];
	for (int i = 0; i < numberRoom; i++)
	{
		cin >> numberStudent[i];
	}
	cin >> maxMain >> maxSub;
	
	for (int i = 0; i < numberRoom; i++)
	{
		numSupervisor++;
		numberStudent[i] -= maxMain;

		long long int numSub = numberStudent[i] / maxSub;
	
		if (numberStudent[i] % maxSub != 0)
			numSub++;

		if (numberStudent[i] > 0)
			numSupervisor += numSub;
	}

	cout << numSupervisor;
}
