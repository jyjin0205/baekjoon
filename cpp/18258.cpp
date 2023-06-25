//큐2

#include <iostream>

using namespace std;

int main(){

    int i = 0; int j = 0;
    int instNum = 0;
    string instName = "";
    int pushNum = 0;
    int stackSize = 0;

    cin >> instNum;
    int* stack;
    stack = new int[instNum];

    for(i=0; i<instNum; i++){
        cin >> instName;
        if(instName == "push"){
            cin >> pushNum;
            stack[stackSize] = pushNum;
            stackSize++;
        }
        else if(instName == "pop"){
            if(!stackSize){
                cout << "-1" << endl;
            }
            else{
                cout << stack[stackSize-1]<< endl;
                stack[stackSize-1] = 0;
                stackSize--;
            }
        }
        else if(instName == "size"){
            cout << stackSize<< endl;
        }
        else if(instName == "empty"){
            cout << !(stackSize && 1)<< endl;
        }
        else if(instName == "top"){
            if(!stackSize){
                cout << "-1"<< endl;
            }
            else{
                cout << stack[stackSize-1]<< endl;
            }
        }
    }

    delete stack;
    return 0;
}