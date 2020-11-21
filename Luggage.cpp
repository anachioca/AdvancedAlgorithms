#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

vector <int> luggage;

int allocateLuggage(int total){
    int N = luggage.size() + 1;
    int halfTotal = total/2;

    int dp[N][halfTotal+1]; // memorizing table (dynamic programming)

    // base case 1: you can have weight = 0 with 0 bags 
    for (int i = 0; i < N; i++)
        dp[i][0] = 0;

    // base case 2: you can't have weight != 0 if you have more than one bag
    for (int i = 1; i < halfTotal + 1; i++)
        dp[0][i] = 0;

    for (int i = 1; i < N; i++){
        int weight = luggage[i-1]; // weight of ith item

        for (int j = 1; j < halfTotal + 1; j++){
			if(j<weight) // the item can't be included
				dp[i][j] = dp[i-1][j];
			else // the item can be included
				dp[i][j] = max(dp[i-1][j], weight + dp[i-1][j-weight]); 
        }

    }

    return dp[N-1][halfTotal] == halfTotal ? 1 : 0;
}


int main(){
    int N, aux;
    cin >> N;
    getchar();

    for (int i = 0; i < N; i++){
        int total = 0;
        string line;
        getline(cin, line);
        istringstream input_stream(line);

        while (input_stream >> aux) {
            luggage.push_back(aux);
            total += aux;
        }

        if (total%2 != 0) {
            cout << "NO\n";
        } 

        else {
            if (allocateLuggage(total)) 
                cout << "YES\n";
            else 
                cout << "NO\n";
        }

        // cout << "\nInput : "; 
        // for (auto ir = luggage.crbegin(); ir != luggage.crend(); ++ir) 
        //     cout << *ir << " "; 

        luggage.clear();
    }

    return 0;
}