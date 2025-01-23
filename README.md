# PortScan: Escaneador de Portas em C

Este projeto é um escaneador de portas simples, desenvolvido em linguagem C, que verifica portas abertas em um IP alvo. Ele também tenta identificar serviços básicos e realizar uma análise simples de vulnerabilidades com base nas portas abertas.

## 📋 Funcionalidades

- **Verificação de portas:** Escaneia um conjunto de portas específicas para determinar quais estão abertas.
- **Identificação de serviços:** Tenta identificar serviços básicos (como HTTP, SSH, MySQL) com base nas respostas recebidas.
- **Análise de vulnerabilidades:** Realiza uma análise básica e sugere possíveis vulnerabilidades comuns associadas às portas abertas.

## 🛠️ Tecnologias Utilizadas

O projeto utiliza as seguintes bibliotecas padrão da linguagem C:

- `stdio.h` e `stdlib.h`: Para entrada e saída de dados.
- `string.h`: Para manipulação de strings.
- `unistd.h`: Para funções de sistema, como manipulação de sockets.
- `arpa/inet.h` e `netinet/in.h`: Para comunicação em rede (IPv4).
- `sys/socket.h`: Para criação e gerenciamento de sockets.
- `errno.h`: Para tratamento de erros.

![image](https://github.com/user-attachments/assets/11301186-d20c-4731-806c-50f49f11df40)

## 🚀 Como Usar

### Pré-requisitos
- Um compilador C, como `gcc`.
- Sistema operacional compatível com as bibliotecas de rede utilizadas (Linux ou Windows com suporte a sockets POSIX).

### Compilação
Para compilar o programa, execute o comando abaixo no terminal:
```bash
gcc -o portscan portscan.c


