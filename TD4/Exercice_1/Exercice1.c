#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int i, nc, rank, size, new_rank, new_comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Déclaration de nc
    nc = 2;

    // Vérification du nombre d'entités de calcul
    if (size % nc != 0) {
        printf("Le nombre d'entités de calcul (%d) n'est pas divisible par nc (%d)\n", size, nc);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Création des nouveaux communicateurs
    MPI_Comm_split(MPI_COMM_WORLD, rank % nc, rank, &new_comm);

    // Diffusion de la valeur i%nc dans chaque nouveau communicateur
    MPI_Bcast(&new_rank, 1, MPI_INT, 0, new_comm);

    // Affichage de la valeur reçue
    printf("Entité %d (rang %d dans le nouveau communicateur %d) : valeur reçue = %d\n",
           rank, MPI_Comm_rank(new_comm, &new_rank), new_comm, new_rank);

    MPI_Finalize();
    return 0;
}
