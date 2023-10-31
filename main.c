#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct info{
    int key;
    float value;
}info;


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

void bubble_sort(Info *vetor, int tam, int i, FILE *ARQ){
    clock_t start, end;

    start = clock();
    for (int i = 0; i < tam; i++)
    {
        for (int i = 0; i < tam; i++)
        {
          int n = vetor[i + 1].key;

          if (n>vetor[i].key && (i+1)!=tam)
          {
            vetor[i+1].key = vetor[i].key;
            vetor[i].key = n;
          }
        }
    }
    end = clock();

    fprintf(ARQ, "[%d] - %d ", i+1, (end - start));
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
    fprintf(ARQ, "[%d] - %d ", i+1, (end - start));
}

int main(){
    int tam[5] = {100, 1000, 10000, 100000, 1000000};
    int seeds[10] = {66, 68, 22, 38, 49, 27, 41, 91, 95, 2};
    FILE *ARQ = fopen("Relatorio.txt", "w");

    fprintf(ARQ, "Bubble Sort:");
    for(int i = 0; i<qntd_vetores; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        fprintf(ARQ, "\n\tTipo 1: ");
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            bubble_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }

        fprintf(ARQ, "\n\tTipo 2: ");
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            bubble_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }
        fprintf(ARQ, "\n");
    }
  
    fprintf(ARQ, "Insertion Sort:");
    for(int i = 0; i<5; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        fprintf(ARQ, "\n\tTipo 1: ");
        for(int j = 0; j < 10; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            insertion_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }

        fprintf(ARQ, "\n\tTipo 2: ");
        for(int j = 0; j < 10; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            insertion_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }
        fprintf(ARQ, "\n");
    }
    return 0;
}
