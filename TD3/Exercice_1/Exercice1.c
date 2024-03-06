#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int n, id;
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    srand(time(NULL));

    // Ensure at least 2 neighbors and d < n for all processes
    int d = n / 2 + rand() % (n - n / 2);
    if (d < 2) {
        d = 2;
    } else if (d >= n) {
        d = n - 1;
    }

    int neighbors[d];
    for (int i = 0; i < d; i++) {
        neighbors[i] = -1; // Initialize for clarity
    }

    int available[n - 1];
    int choosen = 0; // Track valid selections
    for (int i = 0, j = 0; i < n; i++) {
        if (i != id) {
            available[j++] = i;
        }
    }

    for (int i = 0; i < d; i++) {
        int idx = rand() % (n - 1 - choosen);  // Use available elements
        int val = available[idx];

        // Efficiently check for duplicates
        bool valid = true;
        for (int j = 0; j < i; j++) {
            if (neighbors[j] == val) {
                valid = false;
                break; // Early exit if duplicate found
            }
        }

        if (valid) {
            neighbors[i] = val;
            choosen++; // Only increment on successful selection
            available[idx] = available[n - 1 - choosen]; // Fill vacated slot
        } else {
            i--; // Decrement to try again for a unique neighbor
        }
    }

    printf("Processus %d : Voisins = ", id);
    for (int i = 0; i < d; i++) {
        printf("%d ", neighbors[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}