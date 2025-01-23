#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

// Definindo códigos de cores ANSI para saída formatada
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

// Função para verificar uma porta e identificar o serviço básico
void check_port(const char *ip, int port) {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    int bytes_received;

    // Cria o socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror(RED "Erro ao criar o socket" RESET);
        return;
    }

    // Configura o endereço do servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    // Tenta se conectar ao servidor
    int result = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (result == 0) {
        printf(GREEN "\nPorta %d aberta\n" RESET, port);

        // Tenta identificar o serviço enviando uma requisição simples
        send(sockfd, "HEAD / HTTP/1.1\r\n\r\n", strlen("HEAD / HTTP/1.1\r\n\r\n"), 0);
        bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            printf(YELLOW "Serviço identificado: " RESET);
            if (strstr(buffer, "HTTP/1.1")) {
                printf(BLUE "HTTP\n" RESET);
            } else if (strstr(buffer, "SSH")) {
                printf(BLUE "SSH\n" RESET);
            } else if (strstr(buffer, "MySQL")) {
                printf(BLUE "MySQL\n" RESET);
            } else {
                printf(RED "Não identificado\n" RESET);
            }
        } else {
            printf(RED "Nenhuma resposta do serviço\n" RESET);
        }

        // Verificação básica de vulnerabilidades (exemplo simplificado)
        if (port == 22) {
            printf(YELLOW "Atenção: " RESET "SSH (port 22) pode estar sujeito a ataques de força bruta.\n");
        } else if (port == 80) {
            printf(YELLOW "Atenção: " RESET "HTTP (port 80) pode estar sujeito a ataques de injeção SQL.\n");
        }

    } else {
        printf(RED "\nPorta %d fechada\n" RESET, port);
    }

    // Fecha o socket
    close(sockfd);
}

int main() {
    const char *ip = "170.82.174.30";
    int ports[] = {22, 80, 443, 8080, 3306}; // Lista simplificada de portas para verificar

    printf(BOLD GREEN "Iniciando port scan em %s...\n\n" RESET, ip);
    printf("===============================\n");

    for (int i = 0; i < sizeof(ports) / sizeof(ports[0]); i++) {
        check_port(ip, ports[i]);
        printf("===============================\n");
    }

    printf(BOLD GREEN "Port scan concluído.\n" RESET);

    return 0;
}
