#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stdio.h> 
  
using namespace std;

typedef struct Doll {
    int w;
    int h;
} DOLL;

void swap(DOLL *xp, DOLL *yp) {  
    DOLL temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
  
void selectionSortw(DOLL dolls[], int n) {  
    int i, j, min;  
  
    for (i = 0; i < n-1; i++) {  

        // Find the minimum element in unsorted array  
        min = i;  
        for (j = i+1; j < n; j++)  
        if (dolls[j].w < dolls[min].w)  
            min = j;  
        else if (dolls[j].w == dolls[min].w){  
            if (dolls[j].h > dolls[min].h)
                min = j;  
        }
  
        // Swap the found minimum element with the first element  
        swap(&dolls[min], &dolls[i]);  
    }  
}    

int LIS(DOLL dolls[], int M){
    int MEMO[20000], i, j, max = 0; 
  
    for (i = 0; i < M; i++) 
        MEMO[i] = 1; 
  
    // Compute LIS values 
    for (i = 1; i < M; i++) 
        for (j = 0; j < i; j++) 
            if (dolls[i].h > dolls[j].h && MEMO[i] < MEMO[j] + 1) 
                MEMO[i] = MEMO[j] + 1; 
  
    // Pick maximum of all LIS values
    for (i = 0; i < M; i++) 
        if (max < MEMO[i]) 
            max = MEMO[i];  
  
    return max; 
}

int solve(int M, DOLL dolls[]){

    deque <int> piles;

    for (int i = 0; i < M; i++) {

        /* index of the next smaller doll that is bigger than the height of the current doll
        Our array of dolls is sorted, so the smaller doll that is bigger than the current one 
        is always after the current position */
        int index = lower_bound(piles.begin(), piles.end(), dolls[i].h) - piles.begin();

        /* if index == 0, that means there's nothing inside the deque yet, or
        that none of the dolls inside the deque is shorter than the current one */
        if (index == 0)
            piles.push_front(dolls[i].h);

        /* if index != 0, that means we've found the smaller doll that is bigger than the current one, 
        so we change that doll in the deque to the current one (piling those two dolls up!) */
        else piles[index-1] = dolls[i].h;

        // deque <int> :: iterator it; 
        // for (it = seq.begin(); it != seq.end(); ++it) 
        //     cout << '\t' << *it; 
        // cout << '\n';
    }

    /* In the end, the deque contains the amount of piles we can form with the dolls */
    return piles.size();
}

int main(){
    int N, M;
    cin >> N;

    for (int i = 0; i < N; i++){
        cin >> M;
        DOLL dolls[20000];

        for (int j = 0; j < M; j++){
            scanf("%d %d", &dolls[j].w, &dolls[j].h);
        }

        selectionSortw(dolls, M); 
        int solution = solve(M, dolls);

        cout << solution << endl;

        // cout << "Input : "; 
        // for (int j = 0; j < M; j++) 
        //     cout << dolls[j].w << ", " << dolls[j].h << endl;
    }

    return 0;
}