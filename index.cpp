#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/wait.h>

std::vector<std::string> noms;

void afegirNom(const std::string& nom) {
    noms.push_back(nom);
}

void mostrarNomAleatori() {
    if (!noms.empty()) {
        int index = rand() % noms.size();
        std::cout << "Nom escollit aleatòriament: " << noms[index] << std::endl;
    }
}

int main() {
    srand(time(0));
    int N;
    std::cout << "Introdueix el nombre de processos: ";
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        pid_t pid = fork();
        if (pid == 0) { // Procés fill
            std::string nom;
            std::cout << "Introdueix un nom per al procés " << i + 1 << ": ";
            std::cin >> nom;
            afegirNom(nom);
            mostrarNomAleatori();
            exit(0);
        }
        else if (pid > 0) { // Procés pare
            wait(NULL); // Espera que el procés fill acabi
        }
        else {
            std::cerr << "Error en crear el procés" << std::endl;
            return 1;
        }
    }

    return 0;
}
