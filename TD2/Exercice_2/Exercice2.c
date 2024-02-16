//mpicc -Wall Exercice2.c -o Exercice2
//mpirun -np 4 ./Exercice2

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

    if (identifiant == 0) {
        int n1,n2, *tab;

        srand(time(NULL));

        n1 = rand()%(MAX + 1);
        n2 = rand()%(MAX + 1);

        tab = (int*) malloc (sizeof(int)*2);
        tab[0] = n1;
        tab[1] = n2;

        for (int i=1; i < nb_processus; i++) {
            MPI_Send(tab, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        printf("processeur %d demarre l'innondation avec les données %d et %d\n",identifiant,tab[0],tab[1]);

        free(tab);

    }
    else {
        int *M = (int*) malloc (sizeof(int)*2);
        int origine_id;
        MPI_Status status;

        MPI_Recv(M, 2, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

        origine_id = status.MPI_SOURCE;

        printf("processeur %d recoit les données %d et %d du processus avec id %d\n",identifiant,M[0],M[1], origine_id);

        for (int i=0; i < nb_processus; i++) {
            if (i != origine_id) {
                MPI_Send(M, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }

        free(M);

    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}