cmake_minimum_required(VERSION 3.27)
project(Algorithmique_Distribuee C)

set(CMAKE_C_STANDARD 11)

add_executable(Algorithmique_Distribuee
        "Exercice_0/Exercice0.c"
        "Exercice_1/hellompi.c"
        "Exercice_2/Exercice2.c"
        "Exercice_3/Exercice3.c"
        "Exercice_4/Exercice4.c"
        "Exercice_5/Exercice5.c"
        Exercice_6/Exercice6.c)
