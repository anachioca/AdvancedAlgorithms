#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector <int> sieve(int N){

    // prime[i] will be false if i is not a prime, if it is, it will be true. 
    bool prime[N+1]; 
    vector <int> primes;
    memset(prime, true, sizeof(prime)); 
  
    for (int p=2; p <= N; p++) {

        if (prime[p] == true) { 
            primes.push_back(p);
            for (int i=p*p; i <= N; i += p) {
                prime[i] = false; 
            }
        } 
    }  

    return primes;
} 

vector <int> factors(int N, vector <int> primes){
    vector <int> solution;
    for (int i = 0; i < (int)primes.size(); i++){
        solution.push_back(0);
    }

    for (int i = N; i >= 2; i--){
        int aux = i;
        for (int j = 0; j < (int)primes.size() && primes[j] <= i ; j++){
            if (aux%primes[j] == 0){
                // cout << "adding " << primes[j] << endl;
                solution[j]++;
                aux = aux/primes[j];
                j--;
            } 
        }
    }

    return solution;
}

int main (){
    int N;
    cin >> N;
    vector <int> primes;
    vector <int> solution;

    while (N != 0){
        primes = sieve(N);

        // cout << "Primes up to N: "; 
        // for (int j = 0; j < primes.size(); j++) 
        //     cout << primes[j] << " ";
        // cout << "\n";

        solution = factors(N, primes);
        
        printf("%3d! =", N);
        for (int j = 0; j < (int)solution.size(); j++){
            if (j%15 == 0 && j != 0) printf("\n      ");
            printf("%3d", solution[j]);
        }
        cout << endl;

        primes.clear();
        solution.clear();
        cin >> N;
    }

    return 0;
}