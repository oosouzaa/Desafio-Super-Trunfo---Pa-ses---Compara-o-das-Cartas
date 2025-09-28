#include <stdio.h>
#include <string.h>  // Para manipulação de strings (ex.: strcmp, se necessário)

// ============================================
// ESTRUTURA DE DADOS: Representa uma carta de cidade
// ============================================
typedef struct {
    char estado[50];         // Nome do estado (string)
    int codigo;              // Código da carta (int)
    char nome[50];           // Nome da cidade (string)
    long long populacao;     // População (long long para valores grandes)
    double area;             // Área em km² (double)
    double pib;              // PIB em bilhões (double)
    int pontos_turisticos;   // Número de pontos turísticos (int)
} Carta;

// Função auxiliar para calcular densidade populacional (pop / area)
double calcularDensidade(const Carta *carta) {
    if (carta->area > 0) {
        return (double)carta->populacao / carta->area;
    }
    return 0.0;  // Evita divisão por zero
}

// ============================================
// FUNÇÕES COMUNS A TODOS OS NÍVEIS
// ============================================

/**
 * Cadastra uma carta interativamente via terminal.
 * Valida entradas numéricas básicas (ex.: população > 0).
 * @param carta Ponteiro para a struct a ser preenchida.
 */
void cadastrarCarta(Carta *carta) {
    printf("=== CADASTRO DA CARTA ===\n");
    printf("Estado: ");
    scanf(" %[^\n]s", carta->estado);  // Lê string com espaços
    printf("Código da carta: ");
    scanf("%d", &carta->codigo);
    printf("Nome da cidade: ");
    scanf(" %[^\n]s", carta->nome);
    printf("População: ");
    scanf("%lld", &carta->populacao);
    while (carta->populacao <= 0) {  // Validação básica
        printf("População deve ser maior que 0. Tente novamente: ");
        scanf("%lld", &carta->populacao);
    }
    printf("Área (km²): ");
    scanf("%lf", &carta->area);
    while (carta->area <= 0) {
        printf("Área deve ser maior que 0. Tente novamente: ");
        scanf("%lf", &carta->area);
    }
    printf("PIB (bilhões): ");
    scanf("%lf", &carta->pib);
    printf("Pontos turísticos: ");
    scanf("%d", &carta->pontos_turisticos);
    while (carta->pontos_turisticos < 0) {
        printf("Pontos turísticos não podem ser negativos. Tente novamente: ");
        scanf("%d", &carta->pontos_turisticos);
    }
    printf("Cadastro concluído!\n\n");
}

/**
 * Exibe os detalhes de uma carta de forma organizada.
 * Inclui densidade calculada.
 * @param carta A struct a ser exibida.
 * @param titulo Opcional: título para exibição (ex.: "Carta 1").
 */
void exibirCarta(const Carta *carta, const char *titulo) {
    double densidade = calcularDensidade(carta);
    printf("%s:\n", titulo);
    printf("  Estado: %s\n", carta->estado);
    printf("  Código: %d\n", carta->codigo);
    printf("  Cidade: %s\n", carta->nome);
    printf("  População: %lld\n", carta->populacao);
    printf("  Área: %.2f km²\n", carta->area);
    printf("  PIB: %.2f bilhões\n", carta->pib);
    printf("  Pontos Turísticos: %d\n", carta->pontos_turisticos);
    printf("  Densidade Populacional: %.2f hab/km²\n\n", densidade);
}

// ============================================
// NÍVEL NOVATO: Comparação básica com if/else
// ============================================

/**
 * Nível Novato: Cadastra 2 cartas e compara por população (atributo fixo).
 * Usa if/else simples para determinar vencedora (maior população vence).
 * Exibe resultados.
 */
void nivelNovato() {
    Carta carta1, carta2;
    printf("🏅 NÍVEL NOVATO - Comparação Básica por População\n\n");
    
    printf("Cadastrando Carta 1...\n");
    cadastrarCarta(&carta1);
    exibirCarta(&carta1, "Carta 1");
    
    printf("Cadastrando Carta 2...\n");
    cadastrarCarta(&carta2);
    exibirCarta(&carta2, "Carta 2");
    
    // Comparação básica com if/else
    printf("=== COMPARAÇÃO POR POPULAÇÃO ===\n");
    if (carta1.populacao > carta2.populacao) {
        printf("Vencedora: %s (%s) com população %lld!\n", 
               carta1.nome, carta1.estado, carta1.populacao);
    } else if (carta2.populacao > carta1.populacao) {
        printf("Vencedora: %s (%s) com população %lld!\n", 
               carta2.nome, carta2.estado, carta2.populacao);
    } else {
        printf("Empate na população!\n");
    }
    printf("\n");
}

// ============================================
// NÍVEL AVENTUREIRO: Menu com switch e if aninhados
// ============================================

/**
 * Compara duas cartas por um atributo específico usando if aninhados.
 * @param c1 Primeira carta.
 * @param c2 Segunda carta.
 * @param atributo Código do atributo (1=pop, 2=area, etc.).
 * @return 1 se c1 vence, 2 se c2 vence, 0 se empate.
 */
int compararPorAtributo(const Carta *c1, const Carta *c2, int atributo) {
    double val1, val2;
    int menorVence = 0;  // Flag para atributos onde menor vence (ex.: densidade)
    
    // If aninhado para definir valores e regra
    if (atributo == 1) {  // População
        val1 = c1->populacao;
        val2 = c2->populacao;
    } else if (atributo == 2) {  // Área
        val1 = c1->area;
        val2 = c2->area;
    } else if (atributo == 3) {  // PIB
        val1 = c1->pib;
        val2 = c2->pib;
    } else if (atributo == 4) {  // Pontos turísticos
        val1 = c1->pontos_turisticos;
        val2 = c2->pontos_turisticos;
    } else if (atributo == 5) {  // Densidade (menor vence)
        val1 = calcularDensidade(c1);
        val2 = calcularDensidade(c2);
        menorVence = 1;
    } else {
        printf("Atributo inválido!\n");
        return 0;
    }
    
    // If aninhado para decidir vencedor
    if (menorVence) {
        if (val1 < val2) return 1;  // c1 tem menor densidade
        else if (val2 < val1) return 2;
    } else {
        if (val1 > val2) return 1;  // c1 tem maior valor
        else if (val2 > val1) return 2;
    }
    return 0;  // Empate
}

/**
 * Nível Aventureiro: Menu interativo com switch para escolher atributo.
 * Cadastra 2 cartas e compara com base na escolha.
 */
void nivelAventureiro() {
    Carta c1, c2;
    int escolha, vencedor;
    printf("🥈 NÍVEL AVENTUREIRO - Menu Interativo com Switch\n\n");
    
    printf("Cadastrando Carta 1...\n");
    cadastrarCarta(&c1);
    exibirCarta(&c1, "Carta 1");
    
    printf("Cadastrando Carta 2...\n");
    cadastrarCarta(&c2);
    exibirCarta(&c2, "Carta 2");
    
    // Menu com switch
    printf("Escolha o atributo para comparação:\n");
    printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos Turísticos\n5 - Densidade Populacional\n");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("=== COMPARAÇÃO POR POPULAÇÃO ===\n");
            break;
        case 2:
            printf("=== COMPARAÇÃO POR ÁREA ===\n");
            break;
        case 3:
            printf("=== COMPARAÇÃO POR PIB ===\n");
            break;
        case 4:
            printf("=== COMPARAÇÃO POR PONTOS TURÍSTICOS ===\n");
            break;
        case 5:
            printf("=== COMPARAÇÃO POR DENSIDADE POPULACIONAL (MENOR VENCE) ===\n");
            break;
        default:
            printf("Opção inválida! Usando população por padrão.\n");
            escolha = 1;
            break;
    }
    
    vencedor = compararPorAtributo(&c1, &c2, escolha);
    if (vencedor == 1) {
        printf("Vencedora: %s (%s)!\n", c1.nome, c1.estado);
    } else if (vencedor == 2) {
        printf("Vencedora: %s (%s)!\n", c2.nome, c2.estado);
    } else {
        printf("Empate!\n");
    }
    printf("\n");
}

// ============================================
// NÍVEL MESTRE: Menus dinâmicos, dois atributos, ternários e aninhados
// ============================================

/**
 * Nível Mestre: Menu dinâmico em loop while com switch.
 * Permite escolher 2 atributos e compara com lógica complexa.
 * Usa operadores ternários para decisões rápidas e if aninhados para empates.
 */
void nivelMestre() {
    Carta c1, c2;
    int opcao, attr1, attr2, vencedor1, vencedor2;
    char continuar = 's';
    
    printf("🥇 NÍVEL MESTRE - Menus Dinâmicos e Lógica Complexa\n\n");
    
    printf("Cadastrando Carta 1...\n");
    cadastrarCarta(&c1);
    exibirCarta(&c1, "Carta 1");
    
    printf("Cadastrando Carta 2...\n");
    cadastrarCarta(&c2);
    exibirCarta(&c2, "Carta 2");
    
    // Menu dinâmico: Loop while para múltiplas comparações
    while (continuar == 's' || continuar == 'S') {
        printf("=== MENU DE COMPARAÇÃO (Escolha 2 atributos) ===\n");
        printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos Turísticos\n5 - Densidade Populacional\n");
        printf("Digite o primeiro atributo: ");
        scanf("%d", &attr1);
        printf("Digite o segundo atributo: ");
        scanf("%d", &attr2);
        
        // Validação básica
        if (attr1 < 1 || attr1 > 5 || attr2 < 1 || attr2 > 5) {
            printf("Atributos inválidos! Tente novamente.\n");
            continue;
        }
        
        // Primeira comparação
        vencedor1 = compararPorAtributo(&c1, &c2, attr1);
        
        // Lógica complexa: If aninhado + ternário para decidir final
        printf("=== COMPARAÇÃO COMPLEXA ===\n");
        printf("Atributo 1 (%d): ", attr1);
        if (vencedor1 == 1) {
            printf("%s vence o primeiro round!\n", c1.nome);
        } else if (vencedor1 == 2) {
            printf("%s vence o primeiro round!\n", c2.nome);
        } else {
            printf("Empate no primeiro atributo!\n");
            // Se empate no primeiro, compara o segundo com ternário
            vencedor2 = compararPorAtributo(&c1, &c2, attr2);
            int vencedorFinal = (vencedor2 == 1) ? 1 : (vencedor2 == 2 ? 2 : 0);
            if (vencedorFinal == 1) {
                printf("Vencedora final: %s (%s) pelo segundo atributo!\n", c1.nome, c1.estado);
            } else if (vencedorFinal == 2) {
                printf("Vencedora final: %s (%s) pelo segundo atributo!\n", c2.nome, c2.estado);
            } else {
                printf("Empate total!\n");
            }
            printf("Deseja comparar novamente? (s/n): ");
            scanf(" %c", &continuar);
            continue;
        }
        
        // Se não empate no primeiro, usa ternário para exibir
        printf("Atributo 2 (%d) não necessário (primeiro decidiu).\n", attr2);
        int vencedorFinal = (vencedor1 == 1) ? 1 : (vencedor1 == 2 ? 2 : 0);
        if (vencedorFinal == 1) {
            printf("Vencedora final: %s (%s)!\n", c1.nome, c1.estado);
        } else if (vencedorFinal == 2) {
            printf("Vencedora final: %s (%s)!\n", c2.nome, c2.estado);
        } else {
            printf("Empate no primeiro (segundo não testado)!\n");
        }
        
        printf("Deseja comparar novamente? (s/n): ");
        scanf(" %c", &continuar);
    }
    printf("\n");
}

// ============================================
// FUNÇÃO PRINCIPAL: Menu para escolher níveis
// ============================================

int main() {
    int nivel;
    printf("=== DESAFIO SUPER TRUNFO - PAÍSES ===\n");
    printf("Escolha o nível para executar:\n");
    printf("1 - Nível Novato\n2 - Nível Aventureiro\n3 - Nível Mestre\n");
    scanf("%d", &nivel);
    
    switch (nivel) {
        case 1:
            nivelNovato();
            break;
        case 2:
            nivelAventureiro();
            break;
        case 3:
            nivelMestre();
            break;
        default:
            printf("Nível inválido! Executando Novato por padrão.\n");
            nivelNovato();
            break;
    }
    
    printf("=== Fim do Desafio ===\n");
    return 0;
}
