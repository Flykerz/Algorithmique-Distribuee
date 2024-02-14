//mpicc -Wall Exercice1.c -o Exercice1
//mpirun -np 4 ./Exercice1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <tclDecls.h>

int main(int argc, char** argv) {

    MPI_Init(NULL, NULL);

    int nb_processus;

    MPI_Comm_size(MPI_COMM_WORLD, &nb_processus);

    int identifiant;
    const int M = 100;
    int origine_id = status.MPI.SOURCE;
    int balise = status.MPI_TAG;

    MPI_Comm_rank(MPI_COMM_WORLD, &identifiant);

    int filsD = (2 * identifiant + 1) ;
    int filsG = (2 * identifiant - 1) ;

    if (identifiant == 0) filsG = nb_processus - 1;

    int mesnombres[2];
    int nombresfils[2];

    if (identifiant == 0) {
        srand(time(NULL) + identifiant);

        int k1 = (rand() / (float)RAND_MAX) * (M+1);
        int k2 = (rand() / (float)RAND_MAX) * (M+1);

        if (k1 < k2) {mesnombres[0] = k1; mesnombres[1] = k2;}
        else {mesnombres[0] = k2; mesnombres[1] = k1;}
    }
    else {
        MPI_Recv(&nombresfils, 2, MPI_INT, filsG, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processus %d recoit le nombre min %d et max %d du processus %d\n", identifiant, nombresfils[0], nombresfils[1], filsG);
        if (nombresfils[0] < mesnombres[0]) mesnombres[0] = nombresfils[0];
        if (nombresfils[1] > mesnombres[1]) mesnombres[1] = nombresfils[1];
        MPI_Send(&mesnombres, 2, MPI_INT, filsD, 0, MPI_COMM_WORLD);
        printf("Processus %d envoie le nombre min %d et max %d au processus %d\n", identifiant, mesnombres[0], mesnombres[1], filsD);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}