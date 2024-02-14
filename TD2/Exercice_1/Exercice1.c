//mpicc -Wall Exercice1.c -o Exercice1
//mpirun -np 4 ./Exercice1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char** argv) {

    MPI_Init(NULL, NULL);

    int nb_processus;

    MPI_Comm_size(MPI_COMM_WORLD, &nb_processus);

    int identifiant;

    MPI_Comm_rank(MPI_COMM_WORLD, &identifiant);

    int filsD = (2 * identifiant + 2) ;
    int filsG = (2 * identifiant + 1) ;

    int mesnombres[2];
    int nombresfils[2];

    if (identifiant == 0) {
        srand(time(NULL) + identifiant);

        int k1 = rand()%1001;
        int k2 = rand()%1001;

        if (k1 < k2) {mesnombres[0] = k1; mesnombres[1] = k2;}
        else {mesnombres[0] = k2; mesnombres[1] = k1;}

        if (filsG < nb_processus) MPI_Send(&mesnombres, 2, MPI_INT, filsG, 0, MPI_COMM_WORLD);

        if (filsD < nb_processus) MPI_Send(&mesnombres, 2, MPI_INT, filsD, 0, MPI_COMM_WORLD);

    }
    else {
        MPI_Recv(&nombresfils, 2, MPI_INT, ((identifiant - 1)/2)%nb_processus , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (filsG < nb_processus) MPI_Send(&mesnombres, 2, MPI_INT, filsG, 0, MPI_COMM_WORLD);
        if (filsD < nb_processus) MPI_Send(&mesnombres, 2, MPI_INT, filsD, 0, MPI_COMM_WORLD);
        printf("Processus %d Fils Droit %d, Fils Gauche %d du processus %d\n", identifiant, nombresfils[0], nombresfils[1], filsG);

    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}