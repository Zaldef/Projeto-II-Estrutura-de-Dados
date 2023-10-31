#include <stdlib.h>
#include <stdio.h>
#include <time.h>


typedef struct info{
    int key;
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

    fprintf(ARQ, "[%d] - %d ", i+1, (end - start));
}


int main(){
    clock_t start, end, start_master, end_master;
    int qntd_vetores = 5;
    int qntd_seeds = 10;
    int tam[5] = {100, 1000, 10000, 100000, 1000000};
    int seeds[10] = {66, 68, 22, 38, 49, 27, 41, 91, 95, 2};
    FILE *ARQ = fopen("Relatorio.txt", "w");
    start_master = clock();

    //
    start = clock();
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
    end = clock();
    fprintf(ARQ, "\nTempo total Bubble: %d\n", (end - start));

    start = clock();
    fprintf(ARQ, "Insertion Sort:");
    for(int i = 0; i<qntd_vetores; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        fprintf(ARQ, "\n\tTipo 1: ");
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            insertion_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }

        fprintf(ARQ, "\n\tTipo 2: ");
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            insertion_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }
        fprintf(ARQ, "\n");
    }
    end = clock();
    fprintf(ARQ, "\nTempo total Insertion: %d\n", (end - start));
    
    start = clock();
    fprintf(ARQ, "\n\nShell Sort:");
    for(int i = 0; i<qntd_vetores; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        fprintf(ARQ, "\n\tTipo 1: ");
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            shell_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }

        fprintf(ARQ, "\n\tTipo 2: ");
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            shell_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }
        fprintf(ARQ, "\n");
    }
    end = clock();
    fprintf(ARQ, "\nTempo total Shell: %d\n", (end - start));

    end_master = clock();
    fprintf(ARQ, "\n\nTempo total: %d", (end_master - start_master));
    return 0;
}
