#include <iostream>
#include <vector>
using namespace std;

#define MAX 999999



int minCoins(int value, vector <int> coins, int numCoins){
    vector <int> solutions;
    solutions.push_back(0); 

    for (int i = 1; i < value+1; i++){
        solutions.push_back(MAX);
    }

    for (int i = 1; i <= value; i++){
        for (int j = 0; j < numCoins; j++){
            if (coins[j] <= i){
                if (solutions[i] >= solutions[i - coins[j]] + 1)
                    solutions[i] = solutions[i - coins[j]] + 1;
            }
        }
    }

    if (solutions[value] == MAX) solutions[value] = -1;
    return solutions[value];

}

int main() {
    int N, value, numCoins, aux;
    vector <int> coins;
    scanf("%d", &N);

    while (N) {
        scanf("%d", &value);
        scanf("%d", &numCoins);
        for (int i = 0; i < numCoins; i++){
            scanf("%d", &aux);
            coins.push_back(aux);
        }

        int solution = minCoins(value, coins, numCoins);
        if (solution == -1) printf("sem solucao");
        else printf("%d\n", solution);
        coins.clear();
        N--;
    }

    return 0;
}
