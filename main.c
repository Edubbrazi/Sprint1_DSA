// Importação de bibliotecas
#include <stdio.h>
#include <unistd.h>

// Definição das constantes
#define PRECO_BASE_KWH 1.49
#define TAXA_FIXA 5.00
#define LIMITE_PREMIUM 50.0 

// Definição das funções 
typedef struct {
    int id_sessao;
    int tipo_usuario; 
    float energia_entregue;
    float custo_total;
} SessaoRecarga;

void exibir_cabecalho() {
    printf("\n========================================\n");
    printf("     SISTEMA DE RECARGA - SPRINT 1   \n");
    printf("========================================\n");
}

int main() {
    SessaoRecarga sessao;
    int progresso;

    exibir_cabecalho();

   // Validação do ID com Loop 
    do {
        printf("Digite o ID da sessao (positivo): ");
        scanf("%d", &sessao.id_sessao);
        
        // Mensagem de erro caso o valor não seja positivo
        if (sessao.id_sessao <= 0) {
            printf("ID invalido! Por favor, digite um valor maior que zero.\n");
        }
    } while (sessao.id_sessao <= 0);

    // Escolha da categoria do usuário  
   do {
        printf("\nTipo de Usuario:\n1 - Regular\n2 - Premium (Desconto em recargas longas)\nEscolha: ");
        scanf("%d", &sessao.tipo_usuario);

    // Loop caso o usuário não escolha uma opção acima
        if (sessao.tipo_usuario != 1 && sessao.tipo_usuario != 2) {
            printf("Opcao inexistente! Escolha apenas 1 ou 2.\n");
        }
    } while (sessao.tipo_usuario != 1 && sessao.tipo_usuario != 2);

// Coleta de valores da recarga de energia com loop caso  energia<=0
   do {
        printf("Quantidade de energia desejada (kWh): ");
        scanf("%f", &sessao.energia_entregue);
        if (sessao.energia_entregue <= 0) {
            printf("Quantidade invalida! A energia deve ser maior que 0.\n");
        }
    } while (sessao.energia_entregue <= 0);

    // Simulação do progresso da recarga da sessão
    printf("\nIniciando recarga da sessao %d...\n", sessao.id_sessao);
    for (progresso = 0; progresso <= 100; progresso += 20) {
        printf("Progresso: [%d%%] carregando...\n", progresso);
        sleep(1); 
    }

    // Ajusta o preço do kWh com o valor base para as aplicações de tarifação
    float preco_final_kwh = PRECO_BASE_KWH;
    
    // Aplicação do desconto caso recarga >= 50 e usuário = premium 
    if (sessao.tipo_usuario == 2 && sessao.energia_entregue > LIMITE_PREMIUM) {
        preco_final_kwh *= 0.85; 
        printf("\n>>> Desconto Premium aplicado! <<<\n");
    } else if (sessao.tipo_usuario == 1 && sessao.energia_entregue > 100) {
        preco_final_kwh *= 0.95;
    }

    sessao.custo_total = (sessao.energia_entregue * preco_final_kwh) + TAXA_FIXA;

    // Saída Formatada dos dados da sessão 
    printf("\n========================================\n");
    printf("           EXTRATO DA SESSAO            \n");
    printf("========================================\n");
    printf("ID SESSAO:       %d\n", sessao.id_sessao);
    printf("USUARIO TIPO:    %s\n", (sessao.tipo_usuario == 2 ? "Premium" : "Regular"));
    printf("ENERGIA:         %.2f kWh\n", sessao.energia_entregue);
    printf("PRECO/kWh:       R$ %.2f\n", preco_final_kwh);
    printf("TAXA FIXA:       R$ %.2f\n", TAXA_FIXA);
    printf("----------------------------------------\n");
    printf("TOTAL A PAGAR:   R$ %.2f\n", sessao.custo_total);
    printf("========================================\n");
    printf("Sessao encerrada com sucesso.\n\n");

    return 0;
}