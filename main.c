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


int main(){
    clock_t start, end;
    start = clock();
    vet = malloc(sizeof(int) * 1000000);
    end = clock();
    registrar_tempo(start, end, "Relatorio.txt");
    return 0;
}
