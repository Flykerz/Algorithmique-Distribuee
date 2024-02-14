cmake_minimum_required(VERSION 3.27)
project(Algorithmique_Distribuee C)

set(CMAKE_C_STANDARD 11)

add_executable(Algorithmique_Distribuee
        "TD1/Exercice_0/Exercice0.c"
        "TD1/Exercice_1/hellompi.c"
        "TD1/Exercice_2/Exercice2.c"
        "TD1/Exercice_3/Exercice3.c"
        "TD1/Exercice_4/Exercice4.c"
        "TD1/Exercice_5/Exercice5.c"
        "TD1/Exercice_6/Exercice6.c"
        "TD1/Exercice_7/Exercice7a.c"
        "TD1/Exercice_7/Exercice7b.c"
        "TD1/Exercice_7/Exercice7c.c"

        "TD2/Exercice_1/Exercice1.c"
        "TD2/Exercice_2/Exercice2.c"
        "TD2/Exercice_3/Exercice3.c"
        "TD2/Exercice_4/Exercice4.c"
        "TD2/Exercice_5/Exercice5.c")