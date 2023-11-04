#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define qntd_seeds 10
#define qntd_tams 5

typedef struct info{
    long key;
    float value;
}Info;


Info* criar_vetor_tipo1(int tam, int seed){
    Info *vetor = (Info*) malloc(sizeof(Info)*tam);
    srand(seed);
    for(int i = 0; i < tam; i++){
        vetor[i].key = rand();
        vetor[i].value = 100 + rand();
    }
    return vetor;
}

Info* criar_vetor_tipo2(int tam, int seed){
    Info *vetor = (Info*) malloc(sizeof(Info)*tam);
    srand(seed);
    vetor[0].key = rand();
    vetor[0].value = 100 + rand();
    for(int i = 1; i < tam; i++){
        vetor[i].key = (rand() % 10) + vetor[i-1].key;
        vetor[i].value = 100 + rand();
    }
    return vetor;
}

void printar_vetor(Info *vetor, int tam){
    for(int i = 0; i < tam; i++){
        printf("key: %d, value: %f\n", vetor[i].key, vetor[i].value);
    }
}


void bubble_sort(Info *vetor, int tam, int i, FILE *ARQ) {

    clock_t start, end;

    start = clock();
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 1; j < tam - i ; j++) {
            if (vetor[j].key < vetor[j + 1].key) {
                int temp = vetor[j].key;
                vetor[j].key = vetor[j + 1].key;
                vetor[j + 1].key = temp;
            }
        }
    }
    end = clock();


    fprintf(ARQ, "\n\tCaso %d - %d milisegundos ", i+1, (end - start));
}

void insertion_sort(Info *vetor, int tam, int i, FILE *ARQ){
    clock_t start, end;
    int k, j;
    Info aux;

    start = clock();
    for(k = 1; k <= tam - 1; k++){
        aux = vetor[k];
        j = k - 1;
        while (j >= 0 && aux.key > vetor[j].key) {
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = aux;
    }
    end = clock();

    fprintf(ARQ, "\n\tCaso %d - %d milisegundos ", i+1, (end - start));
}


void cocktail_sort(Info *vetor, int tam, int i, FILE *ARQ) {

     clock_t start, end;

    start = clock();
    int aux;
    int lim_inf = 0;
    int lim_sup = tam - 1;
    int swapped = 0;
    while(swapped == 0 && lim_inf < lim_sup)
    {                                   
        swapped = 1;//se não houver troca, swapped não é atualizado no loop o vetor está ordenado

        
        for(i = lim_inf; i < lim_sup; i++)//for da direita para a esquerda
        {
            if(vetor[i].key < vetor[i + 1].key) //se limite inferior for menor que limite inferior + 1, troca
            {   
                aux=vetor[i].key;
                vetor[i].key=vetor[i+1].key;
                vetor[i+1].key=aux;
                swapped = 0;
            }
        }
        lim_sup--; //diminui o limite superior porque o maior valor já está na posição cprreta 
        
        for(i = lim_sup; i > lim_inf; i--)//for da esquerda para a direita
        {  if(vetor[i].key > vetor[i - 1].key)//se limite superior for maior que limite superior - 1, troca
            {
                aux=vetor[i].key;
                vetor[i].key=vetor[i-1].key;
                vetor[i-1].key=aux;
                swapped = 0;
            }
       }
       lim_inf++; //aumenta o limite inferior porque o menor valor já está na posição correta
    }
    end = clock();

    fprintf(ARQ, "\n\tCaso %d - %d milisegundos ", i+1, (end - start));
 }

void shell_sort(Info *vetor, int tam, int i, FILE *ARQ){
    clock_t start, end;
    int k, j, h = 1;
    Info aux;

    start = clock();
    while(h < tam){
        h = 3*h + 1;
    }
    while(h > 1){
        h = h/3;
        for(k = h; k <= tam - 1; k++){
            aux = vetor[k];
            j = k - h;
            while (j >= 0 && aux.key > vetor[j].key) {
                vetor[j+h] = vetor[j];
                j = j - h;
            }
            vetor[j+h] = aux;
        }
    }
    end = clock();

    fprintf(ARQ, "\n\tCaso %d - %d milisegundos ", i+1, (end - start));
}

       
        





int main(){
    clock_t start, end, start_master, end_master;
    int tam[qntd_tams] = {10000, 50000, 100000, 500000, 1000000};
    int seeds[qntd_seeds] = {66, 68, 22, 38, 49, 27, 41, 91, 95, 2};
    FILE *ARQ = fopen("Relatorio.txt", "w");
    start_master = clock();


    start = clock();
    printf("Shell Sort:"); //TESTE
    fprintf(ARQ, "\n\nShell Sort:");
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        for(int j = 0; j < qntd_seeds; j++){

            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            shell_sort(vetor, tam[i], j, ARQ);
            free(vetor);
            printf("\n\t\tCaso %d - ok", j+1); //TESTE
        }


        fprintf(ARQ, "\n\n\tTipo 2: ");
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            shell_sort(vetor, tam[i], j, ARQ);
            free(vetor);
            printf("\n\t\tCaso %d - ok", j+11); //TESTE
        }
        fprintf(ARQ, "\n");
    }

    end = clock();
    fprintf(ARQ, "\nTempo total Shell: %d\n", (end - start));


    start = clock();
    printf("Insertion Sort:"); //TESTE

    fprintf(ARQ, "Insertion Sort:");
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            insertion_sort(vetor, tam[i], j, ARQ);
            free(vetor);
            printf("\n\t\tCaso %d - ok", j+1); //TESTE
        }

        fprintf(ARQ, "\n\n\tTipo 2: ");
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            insertion_sort(vetor, tam[i], j, ARQ);
            free(vetor);
            printf("\n\t\tCaso %d - ok", j+11); //TESTE
        }
        fprintf(ARQ, "\n");       
    }
    end = clock();
    fprintf(ARQ, "\nTempo total Insertion: %d\n", (end - start));
  
start = clock();
    printf("Cocktail Sort:"); //TESTE

    fprintf(ARQ, "Cocktail Sort:");
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            insertion_sort(vetor, tam[i], j, ARQ);
            free(vetor);
            printf("\n\t\tCaso %d - ok", j+1); //TESTE
        }

        fprintf(ARQ, "\n\n\tTipo 2: ");
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            insertion_sort(vetor, tam[i], j, ARQ);
            free(vetor);
            printf("\n\t\tCaso %d - ok", j+11); //TESTE
        }
        fprintf(ARQ, "\n");       
    }
    end = clock();
    fprintf(ARQ, "\nTempo total Cocktail %d\n", (end - start));
    

    start = clock();
    fprintf(ARQ, "Bubble Sort:");
    printf("Bubble Sort:"); //TESTE
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            bubble_sort(vetor, tam[i], j, ARQ);
            free(vetor);
            printf("\n\t\tCaso %d - ok", j+1); //TESTE
        }

        fprintf(ARQ, "\n\n\tTipo 2: ");
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            bubble_sort(vetor, tam[i], j, ARQ);
            free(vetor);
            printf("\n\t\tCaso %d - ok", j+11); //TESTE
        }
        fprintf(ARQ, "\n");
    }
    end = clock();
    fprintf(ARQ, "\nTempo total Bubble: %d\n", (end - start));

    end_master = clock();
    fprintf(ARQ, "\n\nTempo total: %d", (end_master - start_master));

    return 0;
}
