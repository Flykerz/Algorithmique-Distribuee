#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void tri_fusion(int T[], int d, int f);
void fusion(int T[], int d, int m, int f);

int main(int argc, char* argv[]) {
    int n, i;
    double debut, fin;
    clock_t t1, t2;

    // Taille du tableau
    n = atoi(argv[1]);

    // Allocation du tableau
    int* T = (int*)malloc(n * sizeof(int));

    // Remplissage du tableau
    for (i = 0; i < n / 2; i++) {
        T[2 * i] = n - i;
        T[2 * i + 1] = n / 2 - i;
    }

    // Début du chronomètre
    t1 = clock();
    debut = time(NULL);

    // Tri fusion
    tri_fusion(T, 0, n - 1);

    // Fin du chronomètre
    t2 = clock();
    fin = time(NULL);

    // Affichage du temps d'exécution
    printf("Temps d'exécution (clock() ): %f secondes\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
    printf("Temps d'exécution (time() ): %f secondes\n", fin - debut);
    printf("Tableau")

    // Libération du tableau
    free(T);

    return 0;
}

void tri_fusion(int T[], int d, int f) {
    if (d < f) {
        int m = (d + f) / 2;
        tri_fusion(T, d, m);
        tri_fusion(T, m + 1, f);
        fusion(T, d, m, f);
    }
}

void fusion(int T[], int d, int m, int f) {
    int* G = (int*)malloc((m - d + 1) * sizeof(int));
    int* D = (int*)malloc((f - m - 1) * sizeof(int));

    int i, j, k;

    // Copie des sous-tableaux dans G et D
    for (i = d; i <= m; i++) {
        G[i - d] = T[i];
    }
    for (i = m + 1; i <= f; i++) {
        D[i - m - 1] = T[i];
    }

    // Fusion de G et D dans T
    i = 0;
    j = 0;
    k = d;
    while (i <= m - d && j <= f - m - 1) {
        if (G[i] < D[j]) {
            T[k] = G[i];
            i++;
        } else {
            T[k] = D[j];
            j++;
        }
        k++;
    }

    // Copie des éléments restants de G et D
    while (i <= m - d) {
        T[k] = G[i];
        k++;
        i++;
    }
    while (j <= f - m - 1) {
        T[k] = D[j];
        k++;
        j++;
    }

    free(G);
    free(D);
}
