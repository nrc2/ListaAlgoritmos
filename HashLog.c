#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pair {
	int T;
	int C;
} Pair;

typedef struct HashTable {
	int numPair;
	Pair value;
} HashTable;

int hashFunction(int T, int M);
void swap(Pair *a, Pair *b);
void quickSort(HashTable *arr, int initialP, int lastP);
int partition(HashTable *arr, int left, int right);
void binarySearch (HashTable *arr, int posA, int posB, int T);

int main() {
	int M, T, elements = 0;
	long long int C;
	float Lmax;
	char opr[4];

	scanf("%d %f", &M, &Lmax);
	HashTable **hashTable = (HashTable **) malloc(M * sizeof(HashTable *));
	for(int i = 0; i < M; i++) {
		hashTable[i] = (HashTable *) malloc(sizeof(HashTable));
		hashTable[i]->numPair = 0;
	}
	
	while(strcmp(opr, "END") != 0) {
		scanf("%s", opr);
		if(strcmp(opr, "NEW") == 0) {
			scanf("%d %lld", &T, &C);
			Pair newPair;
			newPair.T = T;
			newPair.C = C;
			
			if(((float)elements/M) > Lmax) {
				HashTable **auxHashTable = hashTable;
				int auxM = M;
				
				M = (2 * M) + 1;
				hashTable = (HashTable **) malloc(M * sizeof(HashTable *));
				for(int i = 0; i < M; i++) {
					hashTable[i] = (HashTable *) malloc(sizeof(HashTable));
					hashTable[i]->numPair = 0;
				}
				
				for(int i = 0; i < auxM; i++) {
					for(int j = 0; j < auxHashTable[i]->numPair; j++) {
						int h = hashFunction(auxHashTable[i][j].value.T, M);
						hashTable[h]->numPair++;
						hashTable[h] = (HashTable *) realloc(hashTable[h], hashTable[h]->numPair * sizeof(HashTable));
						hashTable[h][(hashTable[h]->numPair - 1)].value = auxHashTable[i][j].value;
					}
				}
				for(int i = 0; i < M; i++) {
					if(hashTable[i]->numPair > 1){
					quickSort(hashTable[i], 0, (hashTable[i]->numPair - 1));
					}
				}
			}
			int h = hashFunction(T, M);
			hashTable[h]->numPair++;
			hashTable[h] = (HashTable *) realloc(hashTable[h], hashTable[h]->numPair * sizeof(HashTable));
			hashTable[h][(hashTable[h]->numPair - 1)].value = newPair;
			elements++;
			printf("%d %d\n", h, hashTable[h]->numPair);
		}
		else if(strcmp(opr, "QRY") == 0) {
			scanf("%d", &T);
			int h = hashFunction(T, M);
			binarySearch (hashTable[h], 0, hashTable[h]->numPair, T);
		}
	}
	
	return 0;
}

int hashFunction(int T, int M) {
	return T % M;	
}

void swap(Pair *a, Pair *b) {
	Pair temp = *a;
	*a = *b;
	*b = temp;
}

void quickSort(HashTable *arr, int initialP, int lastP) {
	if(initialP < lastP) {
		int p = partition(arr, initialP, lastP);
		quickSort(arr, initialP, p - 1);
		quickSort(arr, p + 1, lastP);
	}
}

int partition(HashTable *arr, int left, int right) {
	int pivo = arr[left].value.T;
	int i = left;
	int j = right + 1;

	do {
		do {
			i++;
		} while((i < right) && (arr[i].value.T < pivo));
		do {
			j--;
		} while(arr[j].value.T > pivo);
		swap(&arr[i].value, &arr[j].value);
	} while(i < j);
	
	swap(&arr[i].value, &arr[j].value);
	swap(&arr[left].value, &arr[j].value);
	
	return j;
}

void binarySearch (HashTable *arr, int posA, int posB, int T){
	while(posA<=posB){
		int meio = (posA + posB)/2;
		if(arr[meio].value.T < T){
			posA = meio + 1;
		}
		else if(arr[meio].value.T > T){
			posB = meio - 1;
		}
		else{
			printf("%lld %d\n", arr[meio].value.C, meio);
			return ;
		}
	}
	printf("-1 -1\n");
}