#include <iostream>
#include <vector>
using namespace std;

int N;
vector <int> array1;
vector <int> array2;
int MEMO[2000][2000]; // menos que foi pedido na especificação, mas o run.codes não aceitou com mais que isso.

int min(int a, int b){
    if (a < b) return a;
    return b;
}

int countPermutations(int i, int j){

    if (i == 0) return j;
    if (j == 0) return i;

    if (MEMO[i-1][j-1] != -1)
        return MEMO[i-1][j-1];

    if (array1[i-1] == array2[j-1])
        return MEMO[i-1][j-1] = countPermutations(i-1, j-1);

    MEMO[i-1][j-1] =  1 + min(countPermutations(i-1, j), // remoção
                              countPermutations(i, j-1)); // inserção 

    return MEMO[i-1][j-1];

}

int main(){
    int T, aux;
    cin >> T;

    for (int k = 0; k < T; k++) {
        cin >> N;

        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                MEMO[i][j] = -1;
            }
        }

        for (int i = 0; i < N; i++){
            cin >> aux;
            array1.push_back(aux);
        }
        for (int i = 0; i < N; i++){
            cin >> aux;
            array2.push_back(aux);
        }

        int solution = countPermutations(N, N);
        cout << "Case " << k+1 << ": " << solution << endl;

        // cout << "Input : "; 
        // for (int j = 0; j < N; j++) 
        //     cout << array1[j] << ", " << array2[j] << endl;

        array1.clear();
        array2.clear();

    }

    return 0;
}