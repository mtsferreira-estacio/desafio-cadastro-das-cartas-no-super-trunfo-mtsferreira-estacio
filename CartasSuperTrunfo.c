#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char estado[3];
    char codCarta[5];
    char cidade[30];
    unsigned long long populacao;
    double pib;
    double area;
    double densPop;
    double pibPerCapta;
    int pontosTuristicos;
    double superPoder;
}Cartas;

void cadastroCartas(Cartas *carta);
void mostrarCartas(Cartas *carta, int numCartas);
void calcularPropriedades(Cartas *carta);
void compararCartas(Cartas *carta1, Cartas *carta2);
double calcular_pibPerCapta(Cartas *carta);
double calcular_densidadePopulacional(Cartas *carta);
double calcular_superPoder(Cartas *carta);

int main() {
    setlocale(LC_ALL, "Portuguese");
    setlocale(LC_NUMERIC, "C");

    int numCartas=2, esc1=1, esc2=2;

    do{printf("Digite quantas cartas a serem cadastradas(min2): ");
    scanf("%d", &numCartas);
    while(getchar() != '\n');
    if(numCartas<2){
        printf("\nERRO! Quantidade mínima de cartas(2)\n");
    }
    }while(numCartas<2);

    Cartas *carta = (Cartas *)malloc(numCartas * sizeof(Cartas)); // Criando um array de cartas

    if(carta ==  NULL){
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    //Cadastro das cartas
    printf("----- Cadastro de Cartas SUPER TRUNFO -----\n\n");

    for(int i = 0; i < numCartas; i++){
        printf("----- Cadastro da Carta #%d -----\n", i+1);
        cadastroCartas(&carta[i]);
        calcularPropriedades(&carta[i]);
    }

    // Output das cartas
    mostrarCartas(carta, numCartas);

    // Comparação das Cartas
    printf("\n     ----- Comparação das Cartas -----\n");
    printf("-------------------------------------------\n");
    printf("Escolha a primeira carta (1 a %d): ", numCartas);
    scanf("%d", &esc1);
    printf("Escolha a segunda carta (1 a %d): ", numCartas);
    scanf("%d", &esc2);

    if(esc1>0 && esc2<=numCartas && esc2>0 && esc2 <= numCartas){
        compararCartas(&carta[esc1-1], &carta[esc2-1]);
    }else{
        printf("Escolhas invalidas. Por favor, digite números entre 1 e %d.\n", numCartas);
    }

    // libera o malloc
    free(carta); 
    carta = NULL; 

    printf("Pressione qualquer teclar para finalizar...\n");
    while(getchar() != '\n');
    getchar();

    return 0;
}

void calcularPropriedades(Cartas *carta){
    carta->pibPerCapta=calcular_pibPerCapta(carta);
    carta->densPop=calcular_densidadePopulacional(carta);
    carta->superPoder=calcular_superPoder(carta);
}

void cadastroCartas(Cartas *carta){
    char tempCod[3];

    printf("Estado(SP,RJ,RS,BA):");
    scanf(" %2s", carta->estado);
    while(getchar() != '\n');

    printf("Código da Carta (01, 02): ");
    scanf(" %2s", tempCod);
    while(getchar() != '\n');

    sprintf(carta->codCarta, "%s%s", carta->estado, tempCod);

    printf("Cidade: ");
    fgets(carta->cidade, sizeof(carta->cidade), stdin);
    carta->cidade[strcspn(carta->cidade, "\n")] = 0;

    printf("População: ");
    scanf("%llu", &carta->populacao);
    while(getchar() != '\n');
    
    printf("Quantidade de pontos turísticos: ");
    scanf("%d", &carta->pontosTuristicos);
    while(getchar() != '\n');

    printf("Área(em km²): ");
    scanf("%lf", &carta->area);
    while(getchar() != '\n');
   
    printf("PIB(em bi): ");
    scanf("%lf", &carta->pib);
    while(getchar() != '\n');

}

double calcular_pibPerCapta(Cartas *carta){
    // Função para calcular pib per capta das cartas
    // Parâmetros:
    // - carta: A struct da carta 
    // Return:
    // O pib per capta calculado ou 0, caso a população seja 0

    // (pib * 1000000000) / populacao
    if(carta->populacao > 0){

        return (carta->pib * 1e9) / carta->populacao;
    }
    
    return 0.0;
}

double calcular_densidadePopulacional(Cartas *carta){
    // Função para calcular densidade populacional das cartas
    // Parâmetros:
    // - carta: A struct da carta 
    // Return:
    // A densidade populacional calculada ou 0, caso a area seja 0

    if(carta->area > 0){
        return (double)carta->populacao / carta->area; // Cast de double para populacao lida em int anteriormente.
    }

    return 0.0;
}

double calcular_superPoder(Cartas *carta){
    double inversoDens = 0.0;

    if(carta->densPop > 0){
        inversoDens = 1.0 / carta->densPop;
    }
    // Soma todos os atributos numéricos. Dividindo por 1 milhão para deixar mais legível.
    return ((double)carta->populacao + carta->area + carta->pib +
    (double)carta->pontosTuristicos + carta->pibPerCapta + inversoDens)  / 1e6;
}

void mostrarCartas(Cartas *carta, int numCartas){
    printf("\n\n----- Cartas Cadastradas -----\n\n");
    for(int i=0;i<numCartas;i++){
        printf("\n----- Carta #%d -----\n",i+1);
        printf("Estado: %s\n",carta[i].estado);
        printf("Código da Carta: %s\n",carta[i].codCarta);
        printf("Cidade: %s\n",carta[i].cidade);
        printf("População: %llu\n",carta[i].populacao);
        printf("PIB: %.2lf bilhões de reais\n",carta[i].pib);
        printf("PIB per capta: %.2lf R$\n",carta[i].pibPerCapta);
        printf("Área: %.2lf km²\n",carta[i].area);
        printf("Densidade Populacional: %.2lf hab/km²\n",carta[i].densPop);
        printf("Pontos Turísticos: %d\n",carta[i].pontosTuristicos);
        printf("Super Poder: %.2lf\n", carta[i].superPoder);
    }
}

void compararCartas(Cartas *carta1, Cartas *carta2){
    int pontCarta1=0, pontCarta2=0;

    printf("\n----- Comparando Carta 1: %s vs Carta 2: %s -----\n", carta1->cidade, carta2->cidade);

    // Comparacoes das Propriedades
    // Populacao
    printf("\n----- População -----\n");
    if(carta1->populacao > carta2->populacao){
        printf("\nCarta 1 vence!\n");
        pontCarta1++;
    }else if(carta1->populacao < carta2->populacao){
        printf("\nCarta 2 vence!\n");
        pontCarta2++;
    }else{
        printf("\nEmpate!\n");  
    }

    //Área
    printf("\n----- Área -----\n");
    if(carta1->area > carta2->area){
        printf("\nCarta 1 vence!\n");
        pontCarta1++;
    }else if(carta1->area < carta2->area){
        printf("\nCarta 2 vence!\n");
        pontCarta2++;
    }else{
        printf("\nEmpate!\n");  
    }

    //PIB
    printf("\n----- PIB -----\n");
    if(carta1->pib > carta2->pib){
        printf("\nCarta 1 vence!\n");
        pontCarta1++;
    }else if(carta1->pib < carta2->pib){
        printf("\nCarta 2 vence!\n");
        pontCarta2++;
    }else{
        printf("\nEmpate!\n");  
    }

    //Pontos Turísticos
    printf("\n----- Pontos Turísticos -----\n");
    if(carta1->pontosTuristicos > carta2->pontosTuristicos){
        printf("\nCarta 1 vence!\n");
        pontCarta1++;
    }else if(carta1->pontosTuristicos < carta2->pontosTuristicos){
        printf("\nCarta 2 vence!\n");
        pontCarta2++;
    }else{
        printf("\nEmpate!\n");  
    }

    // Densidade Populacional (Menor vence)
    printf("\n----- Densidade Populacional -----\n");
    if(carta1->densPop < carta2->densPop){
        printf("\nCarta 1 vence!\n");
        pontCarta1++;
    }else if(carta1->densPop > carta2->densPop){
        printf("\nCarta 2 vence!\n");
        pontCarta2++;
    }else{
        printf("\nEmpate!\n");  
    }

    // PIB per Capita   
    printf("\n----- PIB per Capita -----\n");
    if(carta1->pibPerCapta > carta2->pibPerCapta){
        printf("\nCarta 1 vence!\n");
        pontCarta1++;
    }else if(carta1->pibPerCapta < carta2->pibPerCapta){
        printf("\nCarta 2 vence!\n");
        pontCarta2++;
    }else{
        printf("\nEmpate!\n");  
    }

    // Super Poder   
    printf("\n----- Super Poder -----\n");
    if(carta1->superPoder > carta2->superPoder){
        printf("\nCarta 1 vence!\n");
        pontCarta1++;
    }else if(carta1->superPoder < carta2->superPoder){
        printf("\nCarta 2 vence!\n");
        pontCarta2++;
    }else{
        printf("\nEmpate!\n");  
    }
    printf("\n----- Resultado -----\n");
    if(pontCarta1>pontCarta2){
        printf("\nCarta 1: %s venceu com %d pontos!\n", carta1->cidade,pontCarta1);
    }else{
        printf("\nCarta 2: %s venceu com %d pontos!\n", carta2->cidade,pontCarta2);
    }

}
