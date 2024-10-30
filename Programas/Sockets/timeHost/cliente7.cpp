#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_MENSAGEM  4096  // Defina o tamanho fixo da mensagem

void gerar_mensagem_aleatoria(char *mensagem, int tamanho) {
    const char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int num_caracteres = sizeof(caracteres) - 1;
    for (int i = 0; i < tamanho; i++) {
        mensagem[i] = caracteres[rand() % num_caracteres];
    }
}

int main() {
    int sockfd;
    int len;
    socklen_t len_recv;
    struct sockaddr_in address;
    char mensagem[TAMANHO_MENSAGEM];

    unsigned short porta = 9734;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // criação do socket

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(porta);

    len = sizeof(address);
    len_recv = sizeof(address);

    gerar_mensagem_aleatoria(mensagem, TAMANHO_MENSAGEM);  // Gera a mensagem aleatória

    printf("O cliente vai enviar a mensagem para o servidor\n");

    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);  // Marca o tempo inicial antes de enviar

    // Envia a mensagem para o servidor
    sendto(sockfd, mensagem, sizeof(mensagem), 0, (struct sockaddr *)&address, len);

    // Recebe a resposta do servidor
    ssize_t bytes_recebidos = recvfrom(sockfd, mensagem, sizeof(mensagem), 0, (struct sockaddr *)&address, &len_recv);

    if (bytes_recebidos < 0) {
        perror("Erro ao receber resposta do servidor");
        close(sockfd);
        exit(1);
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);  // Marca o tempo final após o recebimento

    // Calcula o RTT em segundos com precisão
    double tempo_total = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    printf("Tempo total de envio e recebimento: %.8f segundos\n", tempo_total);
    printf("Mensagem recebida do servidor: %.*s\n", TAMANHO_MENSAGEM, mensagem);

    close(sockfd);
    return 0;
}
