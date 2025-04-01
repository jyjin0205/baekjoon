/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제 
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
 
#include<iostream>
#include<queue>
 
using namespace std;
 
 
struct Customer {
    short index;
    short arrivalTime;
    short visitedCounterFirst;
    short visitedCounterSecond;
 
    Customer() {}
 
    Customer(short i, short t) : index(i), arrivalTime(t), visitedCounterFirst(0), visitedCounterSecond(0) {}
};
 
struct WaitingCounter {
    Customer* c;
    short arrivalCounterSecond;
};
 
// priority queue는 우선순위가 높은 요소가 먼저 나오도록 정렬한다. 
// compare가 true이면 우선순위가 낮다고 판단한다.
struct CompareCustomerTime {
    bool operator()(const Customer* c1, const Customer* c2)
    {
        if (c1->arrivalTime > c2->arrivalTime)
            return true; 
        return false;
    }
};
 
struct CompareCustomerIndex {
    bool operator()(const Customer* c1, const Customer* c2)
    {
        if (c1->index > c2->index) // index가 커질 때, 우선순위가 낮아진다
            return true;
        return false;
    }
};
 
struct CompareWaitingCounterSecond {
    bool operator()(const WaitingCounter& c1, const WaitingCounter& c2){
        if (c1.arrivalCounterSecond > c2.arrivalCounterSecond)
            return true;
        else if (c1.arrivalCounterSecond == c2.arrivalCounterSecond)
        {
            if (c1.c->visitedCounterFirst > c2.c->visitedCounterFirst)
                return true;
            else
                return false;
        }
        else
            return false;
    }
};
 
struct Counter {
    short index;
    short neededTime;
    Customer* currentCustomer;
    short currentCustomerEndTime;
};
 
 
int main(int argc, char** argv)
{
    int test_case;
    int T;
    /*
       아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
       앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
       //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
       freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
       따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
       freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
       단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
    */
    //freopen("input.txt", "r", stdin);
    cin>>T;
    /*
       여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */
    for(test_case = 1; test_case <= T; ++test_case)
    {
 
        /////////////////////////////////////////////////////////////////////////////////////////////
        int numCounterFirst, numCounterSecond, numCustomer;
int importantA, importantB;
cin >> numCounterFirst >> numCounterSecond >> numCustomer >> importantA >> importantB;
 
priority_queue<Customer* , vector<Customer* >, CompareCustomerTime> notArrived;
priority_queue<Customer* , vector<Customer* >, CompareCustomerIndex> WaitingCounterFirst;
priority_queue<WaitingCounter, vector<WaitingCounter>, CompareWaitingCounterSecond> WaitingCounterSecond;
 
 
Customer* Customers = new Customer[numCustomer];
Counter* CounterFirst = new Counter[numCounterFirst];
Counter* CounterSecond = new Counter[numCounterSecond];
 
for (int j = 0; j < numCounterFirst; j++)
{
    int t;
    cin >> t;
    CounterFirst[j].index = j + 1;
    CounterFirst[j].neededTime = t;
    CounterFirst[j].currentCustomer = NULL;
    CounterFirst[j].currentCustomerEndTime = -1;
}
 
for (int j = 0; j < numCounterSecond; j++)
{
    int t;
    cin >> t;
    CounterSecond[j].index = j + 1;
    CounterSecond[j].neededTime = t;
    CounterSecond[j].currentCustomer = NULL;
    CounterSecond[j].currentCustomerEndTime = -1;
}
 
for (int j = 0; j < numCustomer; j++)
{
    int t;
    cin >> t;
    Customers[j].index = j + 1;
    Customers[j].arrivalTime = t;
    notArrived.push(&Customers[j]);
}
 
int outGoingCustomer = 0;
int currentTime = 0;
while (outGoingCustomer < numCustomer) // 무한 루프면 내 코드가 문제가 있는 거
{
    // CounterSecond에서 끝난 고객들을 빼냄
    for (int j = 0; j < numCounterSecond; j++)
    {
        if (CounterSecond[j].currentCustomerEndTime == currentTime && CounterSecond[j].currentCustomer)
        {
            CounterSecond[j].currentCustomerEndTime = -1;
            CounterSecond[j].currentCustomer= NULL;
            outGoingCustomer++;
        }
    }
 
 
    for (int j = 0; j < numCounterFirst; j++)
    {
        if (CounterFirst[j].currentCustomerEndTime == currentTime && CounterFirst[j].currentCustomer)
        {
            CounterFirst[j].currentCustomerEndTime = -1;
            WaitingCounter w;
            w.c = CounterFirst[j].currentCustomer;
            w.arrivalCounterSecond = currentTime;
            WaitingCounterSecond.push(w);
            CounterFirst[j].currentCustomer = NULL;
        }
    }
 
    while (!WaitingCounterSecond.empty())
    {
        int index = -1;
        for (int j = 0; j < numCounterSecond; j++)
        {
            if (CounterSecond[j].currentCustomer == NULL)
            {
                index = j;
                break;
            }
        }
        if (index == -1)
            break;
 
        WaitingCounter w = WaitingCounterSecond.top();
        WaitingCounterSecond.pop();
        CounterSecond[index].currentCustomer = w.c;
        CounterSecond[index].currentCustomerEndTime = currentTime + CounterSecond[index].neededTime;
        w.c->visitedCounterSecond = CounterSecond[index].index;
    }
 
    while (!notArrived.empty())
    {
        Customer* c = notArrived.top();
        if (c->arrivalTime > currentTime)
            break;
        else if (c->arrivalTime < currentTime)
        {
            cout << "Not Detected Customer in NotArrived" << endl;
        }
        else
        {
            WaitingCounterFirst.push(c);
            notArrived.pop();
        }
    }
 
    while (!WaitingCounterFirst.empty())
    {
        int index = -1;
        for (int j = 0; j < numCounterFirst; j++)
        {
            if (CounterFirst[j].currentCustomer == NULL)
            {
                index = j;
                break;
            }
        }
        if (index == -1)
            break;
 
        Customer* c = WaitingCounterFirst.top();
        WaitingCounterFirst.pop();
        CounterFirst[index].currentCustomer = c;
        CounterFirst[index].currentCustomerEndTime = currentTime + CounterFirst[index].neededTime;
        c->visitedCounterFirst = CounterFirst[index].index;
    }
 
    currentTime++;
 
}
int ans = 0;
for (int j = 0; j < numCustomer; j++)
{
    if (Customers[j].visitedCounterFirst == importantA && Customers[j].visitedCounterSecond == importantB)
        ans += Customers[j].index;
}
if (ans == 0)
    cout << "#" << test_case << " -1" << endl;
else
    cout << "#" << test_case << " " << ans << endl;
        /////////////////////////////////////////////////////////////////////////////////////////////
 
 
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
