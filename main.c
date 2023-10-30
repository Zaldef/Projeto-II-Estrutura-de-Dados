#include <stdlib.h>
#include <stdio.h>
#include <time.h>

clock_t start(){
    return clock();
}

clock_t end(){
    return clock();
}

clock_t duration(clock_t start, clock_t end){
    return end - start;
}

void registrar_tempo(clock_t start, clock_t end, char *nome_arquivo){
    FILE *ARQ;
    ARQ = fopen(nome_arquivo, "a");
    fprintf(ARQ, "O programa durou: %d milisegundos \n", duration(start, end));
    fclose(ARQ);
}

typedef struct info{
    int key;
    float value;
}Info;

int main(){
    clock_t start, end;
    // cria um vetor inteiro de um milhao de posicoes
    start = clock();
    Info *vetor = (Info*) malloc(sizeof(Info)*1000000);

    end = clock();
    registrar_tempo(start, end, "Relatorio.txt");

    // preenche o vetor com valores aleatorios
    start = clock();

    for(int i = 0; i < 1000000; i++){
        vetor[i].key = rand();
        vetor[i].value = 100 + rand();
    }

    end = clock();
    registrar_tempo(start, end, "Relatorio.txt");

    //printa o vetor
    start = clock();

    for(int i = 0; i < 1000000; i++){
        printf("%d - %.2f \n", vetor[i].key, vetor[i].value);
    }

    end = clock();
    registrar_tempo(start, end, "Relatorio.txt");
    free(vetor);
    return 0;
}
