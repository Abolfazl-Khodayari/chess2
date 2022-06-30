#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ifstream inputFile;
    inputFile.open("input.text");
    if (!inputFile){
        cout << "we fucked up :(" << endl;
    }
    string x;
    for (int i = 0; i < 8; i++){
       for (int j = 0; j < 8; ++j){
            inputFile >> x;
            cout << x <<" ";
       }
       cout << endl;
    }
   
    inputFile.close();
    cout << "end" << endl;






    return 0;
}