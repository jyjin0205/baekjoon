//스택

#include <iostream>


using namespace std;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int i = 0; int j = 0;
    int instNum = 0;
    string instName = "";
    int pushNum = 0;
    int queueSize = 0;
    int first = 0;

    cin >> instNum;
    int* queue;
    queue = new int[instNum];

    for(i=0; i<instNum; i++){

        cin >> instName;
        if(instName.compare("push") == 0){
            cin >> pushNum;
            queue[first+queueSize] = pushNum;
            queueSize++;
        }
        else if(instName.compare("pop")== 0){
            if(!queueSize){
                cout << "-1" << '\n';
            }
            else{
                cout << queue[first] << '\n';
                first = first + 1;
                queueSize--;
            }
        }
        else if(instName.compare("size")== 0){
            cout << queueSize << '\n';
        }
        else if(instName.compare("empty")== 0){
            cout << !(queueSize && 1)<< '\n';
        }
        else if(instName.compare("front")== 0){
            if(!queueSize){
                cout << "-1"<< '\n';
            }
            else{
                cout << queue[first] << '\n';
            }
        }
        else if(instName.compare("back")== 0){
            if(!queueSize){
                cout << "-1"<< '\n';
            }
            else{
                cout << queue[first+queueSize-1]<< '\n';
            }
        }
    }

    return 0;
}