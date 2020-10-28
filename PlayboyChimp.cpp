#include <iostream>
#include <vector>
using namespace std;

int findFirstTaller(vector <int> ladyChimps, int lunchusHeight, int N, int i){
    for (int j = i; j < N; j++){
        if (ladyChimps[j] > lunchusHeight) {
            return ladyChimps[j];
        }
    }
    return 0;
}

void findChimps(vector <int> ladyChimps, int lunchusHeight, int N){

    int LS = ladyChimps[0]; 
    int FT; //last shorter, first taller

    // if the first chimp of ladyChimps is taller than Lunchu, she is the only possible match.
    if (LS > lunchusHeight){
        printf("X %d\n", LS);
        return;
    }

    // if the first chimp of ladyChimps is the same height as Lunchu, she can't be a match.
    // so we look for the next taller chimp.
    if (LS == lunchusHeight){
        if (N > 1) FT = findFirstTaller(ladyChimps, lunchusHeight, N, 1);
        if (FT) printf("X %d\n", ladyChimps[1]);
        else printf("X X\n");
        return;
    }

    // looking for the first taller and last shorter lady chimps.
    for (int i = 1; i < N; i++){

        if (ladyChimps[i] >= lunchusHeight){

            // if the current lady chimp is the same height as Lunchu, and there are more lady chimps
            // in the list, we look for the first taller lady chimp
            if (ladyChimps[i] == lunchusHeight && N >= i+1){
                FT = findFirstTaller(ladyChimps, lunchusHeight, N, i);
                if (FT != 0) printf("%d %d\n", LS, FT);
                else printf("%d X\n", LS);
                return;
            }
            
            // if the current lady chimp is the same height as Lunchu, and there are 
            // no more lady chimps in the list
            else if (ladyChimps[i] == lunchusHeight && N < i+1){
                printf("%d X\n", LS);
                return;
            }

            // if the current lady chimp is taller than Lunchu, we have found
            // the first taller chimp!
            else {
                printf("%d %d\n", LS, ladyChimps[i]);
                return;
            }
        }

        LS = ladyChimps[i];
    }

    // if all lady chimps are shorter than Lunchu...
    printf("%d X\n", LS);
}

int main(){
    int N, Q, aux;
    vector <int> ladyChimps;
    vector <int> queries;

    scanf("%d", &N);
    for (int i = 0; i < N; i++){
        scanf("%d", &aux);
        ladyChimps.push_back(aux);
    }

    scanf("%d", &Q);
    for (int i = 0; i < Q; i++){
        scanf("%d", &aux);
        queries.push_back(aux);
    }

    while (queries.empty() == false){
        int lunchusHeight = queries.front(); // current Lunchus Height is the first element of queries
        findChimps(ladyChimps, lunchusHeight, N);
        queries.erase(queries.begin()); //removes the first element
    }
}