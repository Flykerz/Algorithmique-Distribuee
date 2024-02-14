#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void echange(int *, int *);


int main(int argc, char** argv) {

    MPI_Init(NULL, NULL);

    int nb_processus;

    MPI_Comm_size(MPI_COMM_WORLD, &nb_processus);

    int identifiant;
    const int M = 100;

    MPI_Comm_rank(MPI_COMM_WORLD, &identifiant);

    int voisinD = (identifiant + 1)%nb_processus;
    int voisinG = (identifiant - 1)%nb_processus;

    if (identifiant == 0) voisinG = nb_processus-1;

    srand(time(NULL) + identifiant);

    int k1 = (rand() / (float)RAND_MAX) * (M+1);
    int k2 = (rand() / (float)RAND_MAX) * (M+1);

    int r1,r2;

    if (k1 > k2) echange(&k1,&k2);

    if (identifiant == 0) {
        MPI_Send(&k1, 1, MPI_INT, voisinD, 0, MPI_COMM_WORLD);
        MPI_Send(&k2, 1, MPI_INT, voisinD, 0, MPI_COMM_WORLD);

        printf("Processus %d envoie les nombre min %d et max %d au processus %d\n",identifiant,k1,k2,voisinD);

        MPI_Recv(&r1, 1, MPI_INT, voisinG, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&r2, 1, MPI_INT, voisinG, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (r1 > r2) echange(&r1,&r2);

        printf("Processus %d recoit le nombre min %d et max %d du process %d\n",identifiant,r1,r2,voisinG);
    }
    else {
        MPI_Recv(&r1, 1, MPI_INT, voisinG, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&r2, 1, MPI_INT, voisinG, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (r1 > r2) echange(&r1,&r2);

        printf("Processus %d recoit le nombre min %d et max %d du processus %d\n",identifiant,r1,r2,voisinG);

        if (r1 < k1) k1 = r1;
        if (r2 > k2) k2 = r2;

        MPI_Send(&k1, 1, MPI_INT, voisinD, 0, MPI_COMM_WORLD);
        MPI_Send(&k2, 1, MPI_INT, voisinD, 0, MPI_COMM_WORLD);

        printf("Processus %d envoie le nombre min %d et max %d au processus %d\n",identifiant,k1,k2,voisinD);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}

void echange(int * x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}