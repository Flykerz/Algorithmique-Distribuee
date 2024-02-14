//mpicc -Wall Exercice4.c -o Exercice4
//mpirun -np 2 ./Exercice4

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, value_to_send, received_value;

    MPI_Init(&argc, &argv); // Initialisation de MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtention de l'identifiant du processus
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtention du nombre total de processus

    if (size != 2) {
        fprintf(stderr, "Le programme doit être exécuté avec exactement deux processus.\n");
        MPI_Abort(MPI_COMM_WORLD, 1); // Arrêt de tous les processus MPI
    }

    if (rank == 0) {
        value_to_send = 100;

        printf("Processus 0 envoie la valeur %d à Processus 1\n", value_to_send);
        MPI_Send(&value_to_send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(&received_value, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processus 0 reçoit la valeur %d de Processus 1\n", received_value);

    } else if (rank == 1) {
        MPI_Recv(&received_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processus 1 reçoit la valeur %d de Processus 0\n", received_value);

        // Suppose que chaque processus renvoie simplement la valeur reçue
        MPI_Send(&received_value, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        printf("Processus 1 renvoie la valeur %d à Processus 0\n", received_value);
    }

    MPI_Finalize(); // Finalisation de MPI

    return 0;
}
