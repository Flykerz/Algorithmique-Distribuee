#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define MAX 50

int main(int argc, char** argv) {

    MPI_Init(NULL, NULL);

    int nb_processus;
    MPI_Comm_size(MPI_COMM_WORLD, &nb_processus);

    int identifiant;
    MPI_Comm_rank(MPI_COMM_WORLD, &identifiant);

    srand(time(NULL) + identifiant); // Seed différent pour chaque processus

    int d = nb_processus / 2 + rand() % (nb_processus - nb_processus / 2); // Nombre de voisins

    int *voisins = (int*)malloc(d * sizeof(int)); // Tableau des voisins

    // Recevoir les voisins du processus précédent
    if (identifiant > 0) {
        MPI_Recv(voisins, d, MPI_INT, identifiant - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Envoyer les voisins au processus suivant, sauf pour le dernier processus
    if (identifiant < nb_processus - 1) {
        MPI_Send(voisins, d, MPI_INT, identifiant + 1, 0, MPI_COMM_WORLD);
    }

    // Afficher les voisins
    printf("Processus %d : Voisins = ", identifiant);
    for (int i = 0; i < d; i++) {
        printf("%d ", voisins[i]);
    }
    printf("\n");

    // Le processus 0 commence l'inondation
    if (identifiant == 0) {
        int n1 = rand() % (MAX + 1);
        int n2 = rand() % (MAX + 1);
        printf("Processus %d démarre l'inondation avec les données %d et %d\n", identifiant, n1, n2);

        // Envoyer les données aux voisins
        for (int i = 0; i < d; i++) {
            MPI_Send(&n1, 1, MPI_INT, voisins[i], 0, MPI_COMM_WORLD);
            MPI_Send(&n2, 1, MPI_INT, voisins[i], 0, MPI_COMM_WORLD);
        }
    }

        // Recevoir les données et les transmettre aux voisins
    else {
        int n1, n2;
        MPI_Recv(&n1, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&n2, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processus %d reçoit les données %d et %d du processus avec l'ID %d\n", identifiant, n1, n2, MPI_ANY_SOURCE);

        // Envoyer les données aux voisins, sauf à l'expéditeur
        for (int i = 0; i < d; i++) {
            if (voisins[i] != MPI_ANY_SOURCE) {
                MPI_Send(&n1, 1, MPI_INT, voisins[i], 0, MPI_COMM_WORLD);
                MPI_Send(&n2, 1, MPI_INT, voisins[i], 0, MPI_COMM_WORLD);
            }
        }
    }

    free(voisins);
    MPI_Finalize();
    return EXIT_SUCCESS;
}
