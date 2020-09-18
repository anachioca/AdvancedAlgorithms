#include <iostream>
#include <vector>
using namespace std;

/*
Because the maximum number of tracks is 20, it is ok to use backtracking.
*/

void backTracking(int numOfTracks, int tapeLenght, vector <int> &tracks, int &finalSum, vector <int> &chosen, int c, int sum, vector <int> currentChosen = vector <int>()){
    
    /* c is the current index of the array.
    if the end of the array has been reached, returns */
    if (c >= numOfTracks) return;

    /* checks if the cth track fits in the tape, if it does, test all possible situation in which that track is 
    in the tape. Then remove the track and check other possibilities (there may be a better one!) */
    if(sum + tracks[c] <= tapeLenght){
        currentChosen.push_back(tracks[c]); // inserts the cth track.

        if (finalSum < sum + tracks[c]){ // checks if the current situation is the best one yet
            finalSum = sum + tracks[c];
            chosen = currentChosen;
        }

        backTracking(numOfTracks, tapeLenght, tracks, finalSum, chosen, c+1, sum + tracks[c], currentChosen);
        currentChosen.pop_back(); // removes the cth track.
    }

    // testing other combinations without the cth track.
    backTracking(numOfTracks, tapeLenght, tracks, finalSum, chosen, c+1, sum, currentChosen);
}

int main(){
    int N, T; //space in tape, number of tracks
    int aux;
    while (scanf("%d", &N) != EOF ){
        scanf("%d", &T);
        int sum = 0; 
        vector <int> tracks;
        vector <int> chosen;

        for (int i = 0; i < T; i++){
            scanf("%d", &aux);
            tracks.push_back(aux);
            sum += aux;
        }

        if (sum <= N){ // all tracks fit in the tape
            for (auto it = tracks.begin(); it != tracks.end(); it++) 
                cout << *it << " ";
            printf("sum:%d\n", sum);
        }

        else if (sum > N){
            sum = 0;
            backTracking(T, N, tracks, sum, chosen, 0, 0);
            for (auto it = chosen.begin(); it != chosen.end(); it++) 
                cout << *it << " ";
            printf("sum:%d\n", sum);
        }
    }

    return 0;
}

