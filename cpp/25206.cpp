//너의 평점은

#include <iostream>

using namespace std;

int main(){

    string subjectName = "";
    float tempScale= 0.00000;
    string tempAlp = "";
    float avgScore= 0.00000;
    int PNUM = 0;
    float totalScale = 0.0;

    int i;
    for(i = 0; i<20; i++){

        cin >> subjectName >> tempScale >> tempAlp;

        totalScale = totalScale + tempScale;

        if(tempAlp == "A+"){
            avgScore = avgScore + 4.5 * tempScale ;
        }
        else if(tempAlp == "A0"){
            avgScore = avgScore + 4.0 * tempScale;
        }
        else if(tempAlp == "B+"){
            avgScore = avgScore + 3.5 * tempScale;
        }
        else if(tempAlp == "B0"){
            avgScore = avgScore + 3.0 * tempScale;
        }
        else if(tempAlp == "C+"){
            avgScore = avgScore + 2.5 * tempScale;
        }
        else if(tempAlp == "C0"){
            avgScore = avgScore + 2.0 * tempScale;
        }
        else if(tempAlp == "D+"){
            avgScore = avgScore + 1.5 * tempScale;
        }
        else if(tempAlp == "D0"){
            avgScore = avgScore + 1.0 * tempScale;
        }
        else if(tempAlp == "P"){
            totalScale = totalScale - tempScale;
        }
        else {
            avgScore = avgScore;
        }
    }

    if(PNUM == 20){
        avgScore = 0.00000;
    }
    else {
        avgScore = avgScore / totalScale;
    }

    cout << avgScore;

    return 0;
}

