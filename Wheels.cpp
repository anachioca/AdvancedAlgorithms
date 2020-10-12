#include <stdio.h>
#include <queue>
#include <cstring>

using namespace std;

struct state{
	int digit[4];
	int depth; //g
    int f; //depth + heuristica
};

struct compareF{
    bool operator()(state const& s1, state const& s2){
        return s2.f < s1.f;
    }
};

int moves [8][4]= { {-1, 0, 0, 0 },
					 { 1, 0, 0, 0 },
					 { 0,-1, 0, 0 },
					 { 0, 1, 0, 0 },
					 { 0, 0,-1, 0 }, 
					 { 0, 0, 1, 0 },
					 { 0, 0, 0,-1 },
					 { 0, 0, 0, 1 } };


void next_states(state s, state next[8]){
	int i,j;

	for(i=0; i<8; i++){
		next[i] = s;
		next[i].depth = s.depth+1;
		for(j=0; j<4; j++){
			next[i].digit[j] += moves[i][j];
			if (next[i].digit[j]<0)
				next[i].digit[j] = 9;
			if (next[i].digit[j]>9)
				next[i].digit[j] = 0;
		}
	}
}

int equal(state s, state e){
	int i;
	for (i=0; i<4; i++)
		if (s.digit[i] != e.digit[i])
			return 0;

	return 1;
}

// Heurística:
int h(state current, state final){
    int count = 0;
    for (int i = 0; i < 4; i++){
        int minimo = min (current.digit[i], final.digit[i]);
        int maximo = max (current.digit[i], final.digit[i]);
        count += min ((maximo-minimo), (minimo+10-maximo));
    }
    return count;
}

int bfs(state current, state final, int visited[10][10][10][10]){
	state next[8];
	int i;
	priority_queue<state, vector<state>, compareF> pq;

	// o estado inicial pode ser invalido !!!!
	if (!visited[current.digit[0]][current.digit[1]][current.digit[2]][current.digit[3]]){
		visited[current.digit[0]][current.digit[1]][current.digit[2]][current.digit[3]] = 1;
		pq.push(current);

		while(!pq.empty()) {
			current = pq.top();
			pq.pop();
			// chegou no estado final.. basta terminar (este nao eh nivel minino!!!) e mostrar o nivel que saiu da arvore...!
			if (equal(current, final)){
				return current.depth;
            }
			// nao eh igual.. entao, calcula todos os proximos estados e continua a busca em largura.....
			next_states(current, next);
			for (i=0; i<8; i++)
				if (!visited[next[i].digit[0]][next[i].digit[1]][next[i].digit[2]][next[i].digit[3]]){
					visited[next[i].digit[0]][next[i].digit[1]][next[i].digit[2]][next[i].digit[3]] = 1;
                    next[i].f = next[i].depth + h(next[i], final);
					pq.push(next[i]);
				}
		}
	}

	return -1;
}


int main(){
	int nr_testes, test, forbidden, i;
	int visited[10][10][10][10];
	state initial, final, aux;

	scanf("%d", &nr_testes);
	for (test=0; test<nr_testes; test++){
		scanf("%d %d %d %d", &initial.digit[0], &initial.digit[1], &initial.digit[2], &initial.digit[3]);
		scanf("%d %d %d %d", &final.digit[0], &final.digit[1], &final.digit[2], &final.digit[3]);
		scanf("%d", &forbidden);


		memset(visited, 0, sizeof visited);

		// for(i=0; i<10; i++)
		// 	for(j=0; j<10; j++)
		// 		for(k=0; k<10; k++)
		// 			for(l=0; l<10; l++)
		// 				visited[i][j][k][l] = 0;

		for(i=0; i<forbidden; i++) {
			scanf("%d %d %d %d", &aux.digit[0], &aux.digit[1], &aux.digit[2], &aux.digit[3]);
			visited[aux.digit[0]][aux.digit[1]][aux.digit[2]][aux.digit[3]] = 1;
		}

        // state current;
        // //6508
        // current.digit[0] = 6;
        // current.digit[1] = 4;
        // current.digit[2] = 9;
        // current.digit[3] = 7;
		// initial.depth=0;
        // printf("%d", h(current, final));
        
		printf("%d\n", bfs(initial, final, visited));
	}
	return 0;

}