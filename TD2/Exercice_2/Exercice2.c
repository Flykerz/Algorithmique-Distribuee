//mpicc -Wall Exercice2.c -o Exercice2
//mpirun -np 4 ./Exercice2

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    double start_time, end_time;

    MPI_Init(&argc, &argv); // Initialisation de MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtention de l'identifiant du processus
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtention du nombre total de processus

    start_time = MPI_Wtime(); // Mesure du temps au début de l'exécution

    printf("Hello from process %d of %d\n", rank, size);

    // Exemple d'envoi et de réception de messages entre les processus
    if (rank == 0) {
        int data = 42;
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        int received_data;
        MPI_Recv(&received_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data: %d\n", received_data);
    }

    end_time = MPI_Wtime(); // Mesure du temps juste avant MPI_Finalize
    printf("Time elapsed for process %d: %f seconds\n", rank, end_time - start_time);

    MPI_Finalize(); // Finalisation de MPI

    return 0;
}
