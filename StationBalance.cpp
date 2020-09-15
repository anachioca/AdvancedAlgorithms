#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

/* 
Utiliza-se um algoritmo guloso. Considerando C câmaras e S espécimes.
Caso S<2*C, completa-se o vetor de massas de espécimes com 0 até atingir 2*C espécimes. O vetor é ordenado, 
de modo que encontrar os maiores e menores valores se torne mais fácil,
e em seguida são colocados o menor e o maior elementos disponíveis no vetor em cada câmara.
*/

int main(){

    int C, S; //number of chambers and specimens (max 10)
    int aux;
    double imbalance;
    int currentCase = 1;
    vector <int> mass;

    //reading until end of file
    while (scanf("%d", &C) != EOF ){
        scanf("%d", &S);
        int AM = 0; //average mass
        for (int i = 0; i < S; i++){
            scanf("%d", &aux);
            mass.push_back(aux);
            AM += aux;
        }

        //filling vector with specimens of mass 0
        if (S < 2*C){
            int dif = 2*C-S;
            for (int j = 0; j < dif; j++){
                mass.push_back(0);
            }
        }

        AM = AM/C; //divide by number of chambers (obtaining average mass)
        sort(mass.begin(), mass.end()); //sorting vector

        // cout << "Vetor: "; 
        // for (auto it = mass.begin(); it != mass.end(); it++) 
        //     cout << *it << " "; 
        // cout << "\n";

        printf("Set #%d\n", currentCase);
        for (int i = 0; i < C; i++){
            printf(" %d:", i);
            if (mass[i] != 0) printf(" %d", mass[i]); //chooses the smallest value that hasn't been allocated yet
            if (mass[2*C-i-1] != 0) printf(" %d", mass[2*C-i-1]); //chooses the largest value that hasn't been allocated yet
            printf("\n");
            imbalance += abs((mass[i] + mass[2*C-i-1])-AM);
        }
        printf("IMBALANCE = %.5lf\n\n", imbalance);

        //cleaning variables for next set:
        currentCase++;
        mass.clear();
        imbalance = 0;
    }

    return 0;
}