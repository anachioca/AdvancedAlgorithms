#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
#include <math.h>
using namespace std;

vector <unsigned int> NOTsieve(unsigned int N){

    vector <unsigned int> factors;
    unsigned int c, i;
    double src;

    c = N;
    while ((c%2) == 0){
        factors.push_back(2);
        // cout << "2" << endl;
        c = c / 2;
    }

    i = 3;
    src = sqrt(c);
    while (i <= src){
        if ((c%i) == 0){
            factors.push_back(i);
            // cout << i << " " << endl;
            c = c/i;
            src = sqrt(c);
        } else i+= 2;
    }

    if (c > 1) factors.push_back(c);
    return factors;
} 

vector <unsigned int> factors(unsigned int N, vector <unsigned int> primes){

    vector <unsigned int> solution;
    for (unsigned int i = 0; i < (unsigned int)primes.size(); i++){
        solution.push_back(0);
    }

    unsigned int aux = N;
    for (unsigned int j = 0; j < (unsigned int)primes.size() && primes[j] <= N && aux != 1 ; j++){
        if (aux%primes[j] == 0){
            // cout << "adding " << primes[j] << endl;
            solution[j]++;
            aux = aux/primes[j];
            j--;
        } 
    }

    return solution;
}

unsigned int get_powers(unsigned int n, unsigned int p){
    unsigned int res = 0;
    for (unsigned int power = p ; power <= n ; power *= p)
        res += n/power;
    return res;
}

int main() {
    vector <unsigned int> primes;
    vector <unsigned int> powersm;
    unsigned int n, m;

    while (scanf("%u %u", &n, &m) == 2) {
        int flag = 0;

        if (m == 0) {
            printf("%u does not divide %u!\n", m, n);
            flag = 1;
        }

        if (m <= n && flag == 0) {
            printf("%u divides %u!\n", m, n);
            flag = 1;
        }

        if (flag == 0){
            unsigned int aux = 0;
            primes = NOTsieve(m);
            powersm = factors(m, primes);

            // cout << "Primes: "; 
            // for (unsigned int j = 0; j < primes.size(); j++) 
            //     cout << primes[j] << " ";
            // cout << "\n";
            
            // cout << "Powers of M: "; 
            // for (unsigned int j = 0; j < powersm.size(); j++) 
            //     cout << powersm[j] << " ";
            // cout << "\n";

            for (unsigned int i = 0; i < (unsigned int)primes.size(); i++){
                if (powersm[i] != 0){
                    //printf("get_powers(%d, %d) = %d\n", n, primes[i], get_powers(n, i + 2));
                    if (powersm[i] > get_powers(n, primes[i])) aux = 1;
                }
            }

            if (aux == 0) printf("%u divides %u!\n", m, n);
            else printf("%u does not divide %u!\n", m, n);
        }

        primes.clear();
        powersm.clear();
    }

    return 0;
}