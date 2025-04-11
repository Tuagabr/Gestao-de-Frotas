//
// Created by Gabriel Bueno de Oliveira on 10/04/2025.
//

#ifndef BASICGESTAOFROTAS_H
#define BASICGESTAOFROTAS_H

#define MAX_STRING 11
#define MAX_VEICULOS 100
#define MIN_ANOFAB 1980 //data mínima para o ano de fabricação
#define MAX_ANOFAB 2025 //data máxima para o ano de fabricação

struct veiculo {
    char placa[MAX_STRING];
    char tipo[MAX_STRING]; //tipo de veículo. "Carro", "Moto" ou "Caminhão".
    int anoFab; //data de fabricação. Deve ser entre 1980 e 2025.
    float quilometragem;
};

void get_str_option(char* frase, char* opt);
//frase é a frase que será impressa na tela para pedir input ao usuário.
//opt é a string onde será guardada a opção inserida pelo usuário.

struct veiculo* cria_frota();
//Cria um vetor de tamanho 100 e o retorna.

struct veiculo* destroi_frota(struct veiculo* veiculo);
//Recebe um vetor para veículos, libera o seu espaço e retorna NULL.

int checa_placa(char placa[]);
//Checa se a placa está no formato "ABC-1234" e retorna 1 caso sim e 0 caso contrário.

void cadastra_veiculo(struct veiculo frota[], int *totalVeiculo);
//Mostra opções de cadastro de veículo, como a placa, o tipo, a data de fabricação e a quilometragem.
//Recebe um vetor para veículos e exibe uma mensagem de erro em caso de falha.

void consulta_veiculo(struct veiculo frota[], int totalVeiculo, char placa[]);
//Recebe um vetor para veículos e uma string que será buscada pelo vetor.
//Busca e exibe informações sobre um veículo pela sua placa, também exibe uma mensagem de falha
//quando a placa não é encontrada.

void gera_relatorio(struct veiculo frota[], int totalVeiculo);
//Calcula e exibe relatórios de frota.

void atualiza_quilometragem(struct veiculo frota[], int totalVeiculo, char placa[], float quilometragem);
//Busca pela placa no vetor da frota e atualiza sua quilometragem com o valor de float quilometragem.
//Exibe mensagem de falha caso a placa não seja encontrada.

int exibe_menu();
//Exibe o menu principal e retorna um int de 1 a 5 como opção selecionada.

int busca_placa(struct veiculo frota[], int totalVeiculo, char placa[]);
//Busca a placa[] na frota e retorna o índice de onde foi achado.
//Se não achar, retorna -1.

#endif //BASICGESTAOFROTAS_H
