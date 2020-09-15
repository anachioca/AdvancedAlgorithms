#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

/*
Como o sultão quer o máximo de moedas diferentes possíveis, começamos pela moeda de menor valor. 
A moeda coins[n+1] só será utilizada se o valor dela for maior que a soma de todas as moedas anteriores, pois, por exemplo, 
se utilizarmos uma moeda de 10 centavos ao invés de duas, de 6 e 4 centavos, estaremos obtendo menos moedas diferentes.
*/

int main(){
    int T; //number of test cases
    scanf("%d", &T);

    while (T != 0){

        int n; //number of different coins
        scanf("%d", &n);
        vector <int> coins;
        int coin;
        int differentCoins = 1; //a moeda de menor valor sempre será usada
        int sum = 0;

        for (int i = 0; i < n; i++){
            scanf("%d", &coin);
            coins.push_back(coin);
        }

        for (int j = 0; j < n-1; j++){
            if (coins[j]+sum < coins[j+1]){
                differentCoins++;
                sum+=coins[j];
            }
        }

        printf("%d\n", differentCoins);

        T--;
    }

}

