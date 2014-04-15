#include <cstdio>


void	permutation(int** perm, int* trans, int i, int n, int N) {

	printf("%i %i %i\n", i, n, N);

	int* temp = *perm;
	
	if(i == N) {

	} else {
		//for(int p = 0; p < n; ++p) {
		int j = 0;
		bool cont = false;
		while(j < N) {
			printf("j = %i\n",j);
			
			cont = false;
			for(int k = 0; k < i; k++) {
				if(j == temp[k]) {
					j++;
					cont = true;
					break;
				}
			}
			if(cont) continue;

			printf("j = %i\n",j);

			for(int p = 0; p < n; p++) {
				printf("p = %i\n",p);
				
				(*perm)[i] = j;
				(*trans)++;
				
				temp = *perm;
				
				perm++;
				trans++;
			}
			
			j++;
		}
		//}
	}
}

int main() {
	
	int** perm = new int*[6];
	for(int i = 0; i < 6; i++) {
		perm[i] = new int[3];
	}
	
	
	int trans[] = {0,0,0,0,0,0};
	
	permutation(perm, trans, 0, 2, 3);

	permutation(perm,   trans, 1, 1, 3);
	permutation(perm+2, trans, 1, 1, 3);
	permutation(perm+4, trans, 1, 1, 3);

	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 3; j++) {
			printf("%i ",perm[i][j]);
		}
		printf("\n");
	}
}



