#include <iostream>
#include <unistd.h>   // Para fork() e sleep()
#include <sys/types.h> // Para tipos de processo (pid_t)
#include <sys/wait.h>  // Para a função wait()

void vida_do_pai() {
    pid_t pid_filho1 = -1, pid_filho2 = -1, pid_neto1 = -1, pid_neto2 = -1;  // Inicializa os PIDs dos filhos e netos
    int idade_filho1 = 0, idade_filho2 = 0, idade_neto1 = 0, idade_neto2 = 0;   // Idades dos filhos e netos

    // A variável `ano` é o ano global compartilhado entre o pai e os filhos
    for (int ano = 1; ano <= 60; ++ano) {
        // Imprime a vida do pai
        std::cout << "Ano " << ano << ": O pai tem " << ano << " anos e está vivendo." << std::endl;

        if (ano == 14 && pid_filho1 == -1) {
            // O pai tem o Filho 1 aos 14 anos
            pid_filho1 = fork();  // Cria o Filho 1

            if (pid_filho1 < 0) {
                std::cerr << "Erro ao criar o Filho 1!" << std::endl;
                return;
            }

            if (pid_filho1 == 0) {
                // Processo do Filho 1
                idade_filho1 = 0; // O Filho 1 começa a vida com 0 anos
                for (int i = ano; i <= 60 && idade_filho1 <= 30; ++i) {
                    std::cout << "Ano " << i << ": O Filho 1 tem " << idade_filho1 << " anos e está vivendo." << std::endl;

                    // Filho 1 tem Neto 1 aos 12 anos de idade (ano 26 do Pai)
                    if (idade_filho1 == 12 && pid_neto1 == -1) {
                        pid_neto1 = fork();  // Cria o Neto 1

                        if (pid_neto1 < 0) {
                            std::cerr << "Erro ao criar o Neto 1!" << std::endl;
                            return;
                        }

                        if (pid_neto1 == 0) {
                            // Processo do Neto 1
                            idade_neto1 = 0; // O Neto 1 começa a vida com 0 anos
                            for (int j = i; j <= 60 && idade_neto1 <= 12; ++j) {
                                std::cout << "Ano " << j << ": O Neto 1 tem " << idade_neto1 << " anos e está vivendo." << std::endl;
                                idade_neto1++; // A idade do Neto 1 aumenta a cada ano
                                sleep(1);  // Simula 1 ano com 1 segundo
                            }
                            std::cout << "O Neto 1 morreu aos 12 anos." << std::endl;
                            return;  // O Neto 1 termina aqui
                        }
                    }

                    idade_filho1++; // A idade do Filho 1 aumenta a cada ano
                    sleep(1);  // Simula 1 ano com 1 segundo
                }
                std::cout << "O Filho 1 morreu aos 30 anos." << std::endl;
                return;  // O Filho 1 termina aqui
            }
        }

        if (ano == 16 && pid_filho2 == -1) {
            // O pai tem o Filho 2 aos 16 anos
            pid_filho2 = fork();  // Cria o Filho 2

            if (pid_filho2 < 0) {
                std::cerr << "Erro ao criar o Filho 2!" << std::endl;
                return;
            }

            if (pid_filho2 == 0) {
                // Processo do Filho 2
                idade_filho2 = 0; // O Filho 2 começa a vida com 0 anos
                for (int i = ano; i <= 60 && idade_filho2 <= 30; ++i) {
                    std::cout << "Ano " << i << ": O Filho 2 tem " << idade_filho2 << " anos e está vivendo." << std::endl;

                    // Neto 2 nasce quando o Pai tem exatamente 30 anos
                    if (i == 30 && pid_neto2 == -1) {
                        pid_neto2 = fork();  // Cria o Neto 2

                        if (pid_neto2 < 0) {
                            std::cerr << "Erro ao criar o Neto 2!" << std::endl;
                            return;
                        }

                        if (pid_neto2 == 0) {
                            // Processo do Neto 2
                            idade_neto2 = 0; // O Neto 2 começa a vida com 0 anos
                            for (int j = i; j <= 60 && idade_neto2 <= 18; ++j) {
                                std::cout << "Ano " << j << ": O Neto 2 tem " << idade_neto2 << " anos e está vivendo." << std::endl;
                                idade_neto2++; // A idade do Neto 2 aumenta a cada ano
                                sleep(1);  // Simula 1 ano com 1 segundo
                            }
                            std::cout << "O Neto 2 morreu aos 18 anos." << std::endl;
                            return;  // O Neto 2 termina aqui
                        }
                    }

                    idade_filho2++; // A idade do Filho 2 aumenta a cada ano
                    sleep(1);  // Simula 1 ano com 1 segundo
                }
                std::cout << "O Filho 2 morreu aos 30 anos." << std::endl;
                return;  // O Filho 2 termina aqui
            }
        }

        // O pai também envelhece, e todos compartilham o mesmo ano
        sleep(1);  // Simula 1 ano com 1 segundo
    }
    std::cout << "Ao final do Ano 60: O pai morreu." << std::endl;
}

int main() {
    pid_t pid = fork();  // Cria um novo processo (o processo pai)

    if (pid < 0) {
        std::cerr << "Erro ao criar o processo!" << std::endl;
        return 1; // Se houve erro no fork
    }

    if (pid == 0) {
        // Processo filho (simula a vida do pai)
        vida_do_pai();  // Passa a função de vida do pai para o processo filho
    } else {
        // Processo pai (aguarda os filhos terminarem)
        wait(NULL);  // Espera o processo pai terminar
    }

    return 0;
}
