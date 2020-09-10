#include <iostream>
#include <vector>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;

// checks if the woman prefers the current man over her husband.
// returns 1 if true
int preference(int woman, int man, int ** prefs, vector <int> current, int n){
    int positionMan;
    int positionHusband;
    for (int i = 0; i < n; i++){
        if (prefs[woman-1][i] == man) positionMan = i;
        if (prefs[woman-1][i] == current[woman-1]) positionHusband = i;
    }

    if (positionHusband > positionMan){
        return 1;
    }
    else return 0;
}

void stableMatching(){

    int n; // number of men and women
    scanf("%d", &n);

    // allocating memory and initializing values:

    int ** womensPrefs = (int**)malloc(n*sizeof(int*));
    int ** mensPrefs = (int**)malloc(n*sizeof(int*));
    stack <int> singleMen; 
    vector <int> husbands; // represents who each man is married to
    vector <int> wives; // represents who each woman is married to
    vector <int> numberOfProposals; // number of women each man has proposed to

    for (int i = 0; i < n; i++){
        womensPrefs[i] = (int*)malloc(n*sizeof(int));
        mensPrefs[i] = (int*)malloc(n*sizeof(int));
        husbands.push_back(0);
        wives.push_back(0);
        numberOfProposals.push_back(0);
    }

    for (int i = n; i > 0; i--){
        singleMen.push(i);
    }

    // getting input:

    int trash;

    for (int i = 0; i < n; i++){
        scanf("%d", &trash);
        for (int j = 0; j < n; j++){
            scanf("%d", &womensPrefs[i][j]);
        }
    }

    for (int i = 0; i < n; i++){
        scanf("%d", &trash);
        for (int j = 0; j < n; j++){
            scanf("%d", &mensPrefs[i][j]);
        }
    }
    
    // Matching pairs:

    int currentWoman;
    int currentMan = singleMen.top();

    while (!singleMen.empty() && numberOfProposals.at(currentMan-1)!=n){

        // first woman in the man's preference list he hasn't proposed to yet
        currentWoman = mensPrefs[currentMan-1][numberOfProposals.at(currentMan-1)];

        // if the woman in single, she accepts the proposal
        if (wives.at(currentWoman-1) == 0){
            wives[currentWoman-1] = currentMan;
            husbands[currentMan-1] = currentWoman;
        }
        // if she is married, she will only accept the proposal if she preffers the current man over her husband
        else {
            if ( preference(currentWoman, currentMan, womensPrefs, wives, n)){
                wives[currentWoman-1] = currentMan;
                husbands[currentMan-1] = currentWoman;

            }
            else { // the woman did not accept the proposal, the man is single again;
                singleMen.push(currentMan);
            }
        }

        //for debugging purposes:

        // cout << "\n\nCurrent Woman: ";
        // cout << currentWoman;

        // cout << "\nCurrent Man:";
        // cout << currentMan;

        // cout << "\nsingleMen: ";
        // showstack(singleMen);

        // cout << "hubands: ";
        // for (auto i = husbands.begin(); i != husbands.end(); ++i) 
        //     cout << *i << " "; 

        // cout << "\nwives: ";
        // for (auto i = wives.begin(); i != wives.end(); ++i) 
        //     cout << *i << " "; 

        numberOfProposals[currentMan-1]++;
        singleMen.pop();

        if (!singleMen.empty()){
            currentMan = singleMen.top();
        }

    }

    // prints the couples
    int j = 1;
    for (auto i = husbands.begin(); i != husbands.end(); ++i) {
        cout << j << " " << *i;
        j++;
        cout << "\n"; 
    }   

    for (int i = 0; i < n; i++){
        free(womensPrefs[i]);
        free(mensPrefs[i]);
    }
    free(womensPrefs);
    free(mensPrefs); 
}

int main(){
    int numberOfCases;
    scanf("%d", &numberOfCases);

    for (int i = 0; i < numberOfCases; i++){
        stableMatching();
    }
  
    return 0;
}

