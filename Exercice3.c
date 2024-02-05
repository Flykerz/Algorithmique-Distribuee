//Écrivez, compilez et exécutez un programme distribué, fait de deux processus (et qui
//        vérie bien qu'il n'y a que deux processus), tel que chacun des processus envoie son identiant
//        à l'autre processus, et ache le message reçu.

//mpicc -Wall Exercice3.c -o Exercice3
//mpirun -np 4 ./Exercice3

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, received_id;

    MPI_Init(&argc, &argv); // Initialisation de MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtention de l'identifiant du processus
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtention du nombre total de processus

    if (size != 2) {
        fprintf(stderr, "Le programme doit être exécuté avec exactement deux processus.\n");
        MPI_Abort(MPI_COMM_WORLD, 1); // Arrêt de tous les processus MPI
    }

    // Chaque processus envoie son identifiant à l'autre processus
    if (rank == 0) {
        int my_id = 0;
        MPI_Send(&my_id, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&received_id, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if (rank == 1) {
        int my_id = 1;
        MPI_Send(&my_id, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(&received_id, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {printf("Processus n'a pas reçu l'identifiant de l'autre processus.\n");}

    printf("Processus %d a reçu l'identifiant %d de l'autre processus.\n", rank, received_id);

    MPI_Finalize(); // Finalisation de MPI

    return 0;
}
