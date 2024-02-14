//mpicc -Wall Exercice6.c -o Exercice6
//mpirun -np 3 ./Exercice6

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, n;
    int value_to_send, received_value;

    MPI_Init(&argc, &argv); // Initialisation de MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtention de l'identifiant du processus
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtention du nombre total de processus

    if (size < 2) {
        fprintf(stderr, "Le programme doit être exécuté avec au moins deux processus.\n");
        MPI_Abort(MPI_COMM_WORLD, 1); // Arrêt de tous les processus MPI
    }

    if (rank == 0) {
        n = 3; // Modifier cette valeur selon le nombre de processus

        value_to_send = 100;

        printf("Processus 0 envoie la valeur %d à Processus 1\n", value_to_send);
        MPI_Send(&value_to_send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(&received_value, 1, MPI_INT, n - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processus 0 reçoit la valeur %d de Processus %d\n", received_value, n - 1);

    } else {
        n = size;

        MPI_Recv(&received_value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processus %d reçoit la valeur %d de Processus %d\n", rank, received_value, rank - 1);

        // Suppose que chaque processus renvoie simplement la valeur reçue
        MPI_Send(&received_value, 1, MPI_INT, (rank + 1) % n, 1, MPI_COMM_WORLD);
        printf("Processus %d renvoie la valeur %d à Processus %d\n", rank, received_value, (rank + 1) % n);
    }

    MPI_Finalize(); // Finalisation de MPI

    return 0;
}
