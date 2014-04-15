#include <cstdio>

int	factorial(int n) {
	if(n < 0) {
		throw;
	}

	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}
void	permutation(int** perm, int* trans, int i, int N) {

	int n = factorial(N-i-1);

	//printf("i=%i n=%i N=%i perm=%p\n", i, n, N, perm);
	
	int** temp = perm;
	
	if(i == N) {
	
	} else {
		//for(int p = 0; p < n; ++p) {
		int j = 0;
		bool cont = false;
		for(int j = 0; j < N; j++) {
			//printf("j = %i\n",j);
			
			cont = false;
			for(int k = 0; k < i; k++) {
				if(j == (*temp)[k]) {
					cont = true;
					//printf("j=%i taken\n",j);
					break;
				}
			}
			
			if(cont) continue;
			
			//printf("j = %i\n",j);
			
			temp = perm;

			if(i+1 < N) {
				//printf("perm = %p\n",perm);
				//permutation(perm, trans, i+1, N);
			}
			
			for(int p = 0; p < n; p++) {
				//printf("p = %i\n",p);
				
				//printf("perm = %p i = %i j = %i\n",perm,i,j);

				(*perm)[i] = j;
				(*trans)++;
				
				//temp = *perm;
				
				perm++;
				trans++;
			}
			
			if(i+1 < N) {
				//printf("perm = %p\n",perm);
				permutation(temp, trans, i+1, N);
			}
			
		}
		//}
	}
}

int main() {
	
	int** perm = new int*[6];
	for(int i = 0; i < 6; i++) {
		perm[i] = new int[3];
		for(int j = 0; j < 3; j++) {
			perm[i][j] = -1;
		}
	}
	
	
	int trans[] = {0,0,0,0,0,0};
	
	permutation(perm, trans, 0, 3);

	//permutation(perm,   trans, 1, 1, 3);
	//permutation(perm+2, trans, 1, 1, 3);
	//permutation(perm+4, trans, 1, 3);
	//permutation(perm+5, trans, 2, 3);
	
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 3; j++) {
			printf("% i ",perm[i][j]);
		}
		printf("\n");
	}
}



