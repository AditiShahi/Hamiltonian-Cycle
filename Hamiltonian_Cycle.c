#include <stdio.h>
#define MAX 10

int n;                    
int G[MAX][MAX];          
int x[MAX];            
char vertexNames[MAX];   
int cycleCount = 0;          

void NextVertex(int k) {
    do {
        x[k] = (x[k] + 1) % (n + 1);  
        if (x[k] == 0)
            return;

        if (G[x[k - 1]][x[k]] != 0) { 
            int j;
            for (j = 1; j < k; j++) {
                if (x[j] == x[k]) 
                    break;
            }

            if (j == k) { 
                if (k < n || (k == n && G[x[n]][x[1]] != 0))
                    return; 
            }
        }
    } while (1);
}

void Hamiltonian(int k) {
    do {
        NextVertex(k);
        if (x[k] == 0)
            return;

        if (k == n) {
            cycleCount++;
            printf("\nHamiltonian Cycle %d: ", cycleCount);
            for (int i = 1; i <= n; i++)
                printf("%c -> ", vertexNames[x[i]]);
            printf("%c", vertexNames[x[1]]);
        } else {
            Hamiltonian(k + 1);
        }
    } while (1);
}

int main() {
    printf("Enter number of areas (vertices): ");
    scanf("%d", &n);

    printf("Enter the names of areas :\n");
    for (int i = 1; i <= n; i++)
        scanf(" %c", &vertexNames[i]);

    printf("\nEnter the adjacency matrix (%d x %d):\n", n, n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &G[i][j]);
        }
    }

    printf("\nAdjacency Matrix:\n");
    printf("  ");
    for (int i = 1; i <= n; i++)
        printf("%c ", vertexNames[i]);
    printf("\n");
    for (int i = 1; i <= n; i++) {
        printf("%c ", vertexNames[i]);
        for (int j = 1; j <= n; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }

    for (int i = 1; i <= n; i++)
        x[i] = 0;
    x[1] = 1; 

    Hamiltonian(2);

    if (cycleCount == 0)
        printf("\n\nNo Hamiltonian Cycle exists.\n");

    return 0;
}
