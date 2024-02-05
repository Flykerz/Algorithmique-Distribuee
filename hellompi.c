//Écrivez un programme C, utilisant MPI tel que chaque processus ache son identiant
//(sans oublier le retour chariot). Appelez votre source hellompi.c. Pour compiler, utilisez la
//        commande :
//mpicc -Wall hellompi.c -o hellompi
//Pour exécuter votre programme distribué avec n processus, utilisez la commande :
//mpirun -np n ./hellompi
//        Compilez et lancez votre programme avec 4 processus.

//mpicc -Wall hellompi.c -o hellompi
//mpirun -np 4 ./hellompi

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv); // Initialisation de MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtention de l'identifiant du processus
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtention du nombre total de processus

    printf("Hello from process %d of %d\n", rank, size);

    MPI_Finalize(); // Finalisation de MPI

    return 0;
}
