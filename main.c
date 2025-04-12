#include <stdio.h>
#include <string.h>
#include "BasicGestaoFrotas.h"

int main(void) {
    struct veiculo* frota = NULL;
    char placa[MAX_STRING];
    int opt, totalVeiculo = 0;
    float quilometragem = 0;

    frota = cria_frota();

    do {
        opt = exibe_menu();
        switch (opt) {
            case 1: cadastra_veiculo(frota, &totalVeiculo); break;

            case 2:
                if (totalVeiculo != 0) {
                    get_str_option("Digite a placa do veiculo: ", placa);
                    consulta_veiculo(frota, totalVeiculo, placa);
                }else printf("Nao ha veiculos no sistema\n");
                break;

            case 3: gera_relatorio(frota, totalVeiculo); break;

            case 4:
                if (totalVeiculo !=0) {
                    get_str_option("Digite a placa do veiculo: ", placa);
                    if (busca_placa(frota, totalVeiculo, placa) != -1) {
                        get_float_option("Digite a nova quilometragem: ", &quilometragem);
                        atualiza_quilometragem(frota, totalVeiculo, placa, quilometragem);
                    }else printf("Placa inexistente\n");
                }else printf("Nao ha veiculos no sistema\n");
                break;

            case 5: printf("Fechando o Programa...\n");
        }
    }while (opt != 5);

    destroi_frota(frota);
    return 0;
}
