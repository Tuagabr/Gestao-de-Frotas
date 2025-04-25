//
// Created by Gabriel Bueno de Oliveira on 10/04/2025.
//

#include "BasicGestaoFrotas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct veiculo* cria_frota(){
    struct veiculo* veiculo = malloc(MAX_VEICULOS * sizeof(struct veiculo));

    if (veiculo == NULL) return NULL;
    return veiculo;
}

struct veiculo* destroi_frota(struct veiculo* veiculo){
    if (veiculo == NULL) return NULL;
    free(veiculo);
    return NULL;
}

int checa_placa(char placa[]) {
    int i = 0, errado = 0;

    //código para checar se a placa inserida está no formato "ABC-1234":
    while (!errado && (placa[i] != '\0')) {
        if (i <= NUM_LETRAS) {                                             //para todos os NUM_LETRAS primeiros caracteres, testa se o caracter é uma letra maiúscula
            if ((placa[i] < 'A') || (placa[i] > 'Z')) errado = 1;
        }else if (i == NUM_LETRAS + 1) {                                       //testa se o próximo caracter é um '-'
            if (placa[i] != '-') errado = 1;
        }else {
            if (placa[i] < '0' || placa[i] > '9') errado = 1;     //testa se o resto dos caracteres são números
            if (i > COMPRIM_PLACA) errado = 1;                                //testa se a placa tem o comprimento correto de 8 caracteres, contando com o -
        }

        i++;
    }

    if (errado) return 0;
    return 1;
}

void get_str_option(char* frase, char* opt) {
    printf("%s", frase);
    fgets(opt, MAX_STRING, stdin);
    fflush(stdin);
    opt[strcspn(opt, "\n")] = '\0'; //acha qualquer instância de \n na string placa e a substitui com '\0'.
}

void get_int_option(char* frase, int* opt) {
    printf("%s", frase);
    scanf("%d", opt);
    fflush(stdin);
}

void get_float_option(char* frase, float* opt) {
    printf("%s", frase);
    scanf("%f", opt);
    fflush(stdin);
}

void cadastra_veiculo(struct veiculo frota[], int* totalVeiculo) {
    if (*totalVeiculo == MAX_VEICULOS) {
        printf("Ja foi cadastrado o numero maximo de veiculos\n");
        return;
    }
    if (frota == NULL) {
        printf("Vetor frota inexistente ou nao encontrado\n");
        return;
    }

    char placa[MAX_STRING], tipo[MAX_STRING];
    int anoFab; //ano de fabricação
    float quilometragem;

    do {
        get_str_option("Digite a placa do veiculo (formato ABC-1234): ", placa);
    }while(!checa_placa(placa));
    if (busca_placa(frota, *totalVeiculo, placa) != -1) {
        printf("Placa ja existente\n");
        return;
    }
    do {
        get_str_option("Digite o tipo do veiculo (Carro, Moto, Caminhao): ", tipo);
    }while (strcmp(tipo, "Carro") && strcmp(tipo, "Moto") && strcmp(tipo, "Caminhao"));
    //strcmp() retorna 0 se as duas strings são iguais
    do {
        get_int_option("Digite o ano de fabricacao (1980 a 2025): ", &anoFab);
    }while((anoFab < MIN_ANOFAB) || (anoFab > MAX_ANOFAB));
    get_float_option("Digite a quilometragem atual: ", &quilometragem);

    *totalVeiculo = *totalVeiculo + 1;
    strcpy(frota[*totalVeiculo - 1].placa, placa);
    strcpy(frota[*totalVeiculo - 1].tipo, tipo);
    frota[*totalVeiculo - 1].anoFab = anoFab;
    frota[*totalVeiculo - 1].quilometragem = quilometragem;

    printf("Veiculo cadastrado com sucesso!\n");
}

int busca_placa(struct veiculo frota[], int totalVeiculo, char placa[]) {
    int i = 0, found = 0, resultado = 0;

    while (!found && (i < totalVeiculo)) {
        if (strcmp(placa, frota[i].placa) == 0) {
            found = 1;
            resultado = i;
        }
        i++;
    }

    if (!found) return -1;
    return resultado;
}
//Retorna o índice de frota[] em que a placa foi encontrada se a placa não foi encontrada, retorna -1.
//É utilizada nas funções consulta_veículo e atualiza_quilometragem.

void consulta_veiculo(struct veiculo frota[], int totalVeiculo, char placa[]) {
    if (frota == NULL) {
        printf("Vetor frota inexistente\n");
        return;
    }
    if (totalVeiculo <= 0) {
        printf("Nao ha veiculos no sistema\n");
        return;
    }
    if (placa == NULL) {
        printf("Placa inexistente\n");
        return;
    }

    int i = busca_placa(frota, totalVeiculo, placa);
    if (i >= 0) {
        printf("=== DADOS DO VEICULO ===\n");
        printf("Placa: %s\nTipo: %s\n", frota[i].placa, frota[i].tipo);
        printf("Ano de fabricacao: %d\nQuilometragem: %.2f\n", frota[i].anoFab, frota[i].quilometragem);
    }else {
        printf("Veiculo nao encontrado\n");
    }
}

double media_quilometragem_frota(struct veiculo frota[], int totalVeiculo) {
    double soma = 0;

    for (int i = 0; i < totalVeiculo; i++) {
        soma += frota[i].quilometragem;
    }

    return soma / (totalVeiculo * 1.0);
}
//Função auxiliar à gera_relatorio(). Retorna a média de quilometragem da frota em double.

int veiculo_mais_antigo(struct veiculo frota[], int totalVeiculo) {
    int menorIdade = frota[0].anoFab;
    int resultado = 0;

    for (int i = 0; i < totalVeiculo; i++)
        if (menorIdade > frota[i].anoFab) {
            menorIdade = frota[i].anoFab;
            resultado = i;
        }
    return resultado;
}
//Função auxiliar à gera_relatório(). Retorna o índice de frota[] cujo veículo tem a maior idade.

int veiculo_mais_novo(struct veiculo frota[], int totalVeiculo) {
    int maiorIdade = frota[0].anoFab;
    int resultado = 0;

    for (int i = 0; i < totalVeiculo; i++)
        if (maiorIdade < frota[i].anoFab) {
            maiorIdade = frota[i].anoFab;
            resultado = i;
        }
    return resultado;
}
//Função auxiliar à gera_relatório(). Retorna o índice de frota[] cujo veículo tem a menor idade.

void gera_relatorio(struct veiculo frota[], int totalVeiculo) {
    if (frota == NULL) {
        printf("Vetor frota inexistente\n");
        return;
    }
    if (totalVeiculo <= 0) {
        printf("Nao ha veiculos no sistema\n");
        return;
    }

    int maisNovo = veiculo_mais_novo(frota, totalVeiculo);
    int maisVelho = veiculo_mais_antigo(frota, totalVeiculo);

    printf("=== RELATORIO DA FROTA ===\n");
    printf("Total de veiculos cadastrados: %d\n", totalVeiculo);
    printf("Media de quilometragem: %.2lf\n", media_quilometragem_frota(frota, totalVeiculo));
    printf("Veiculo mais antigo: Placa %s, Ano %d\n", frota[maisVelho].placa, frota[maisVelho].anoFab);
    printf("Veiculo mais novo: Placa %s, Ano %d\n", frota[maisNovo].placa, frota[maisNovo].anoFab);
}

void atualiza_quilometragem(struct veiculo frota[], int totalVeiculo, char placa[], float quilometragem) {
    if (frota == NULL) {
        printf("Vetor frota inexistente\n");
        return;
    }
    if (totalVeiculo <= 0) {
        printf("Nao ha veiculos no sistema\n");
        return;
    }
    if (quilometragem < 0) {
        printf("Quilometragem nao pode ser menor que zero\n");
        return;
    }


    int atualizar = busca_placa(frota, totalVeiculo, placa);

    if (atualizar >= 0) {
        frota[atualizar].quilometragem = quilometragem;
        printf("Quilometragem atualizada com sucesso!\n");
    }else printf("Veiculo nao encontrado\n");
}

int exibe_menu() {
    int opt;

    printf("=== SISTEMA DE GERENCIAMENTO DE FROTA ===\n");
    printf("1. Cadastrar Veiculo\n2. Consultar Veiculo\n3. Gerar Relatorio de Frota\n");
    printf("4. Atualizar Quilometragem\n5. Sair\n");

    do {
        printf("Escolha uma opcao: ");
        scanf("%d", &opt);
        fflush(stdin);
    }while(opt < 1 || opt > 5);

    return opt;
}
