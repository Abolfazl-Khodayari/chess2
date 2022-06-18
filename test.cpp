#include <vector>
#include <iostream>
using namespace std;

int main(){
    vector<vector<int>>a (8, vector<int>(8,0));
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; ++j){
            cout << a[i][j] <<" ";
        }
        cout << endl;
    }








    return 0;
}