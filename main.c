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

void cocktail_sort(Info *vetor, int tam, int i, FILE *ARQ) {

     clock_t start, end;

    start = clock();
    int aux;
    int bottom = 0;
    int top = tam - 1;
    int swapped = 0;
    while(swapped == 0 && bottom < top)//Se não houver troca de posições ou o ponteiro que
    {                                   //sobe ultrapassar o que desce, o vetor esta ordenado
        swapped = 1;
        //Este for é a “ida” para a direita
        for(i = bottom; i < top; i = i + 1)
        {
            if(vetor[i].key > vetor[i + 1].key)   //indo pra direita:testa se o próximo é maior
            {   //indo pra direita:se o proximo é maior que o atual,
                //troca as posições
                aux=vetor[i].key;
                vetor[i].key=vetor[i+1].key;
                vetor[i+1].key=aux;
                swapped = 0;
            }
        }//fecha for
        // diminui o  `top` porque o elemento com o maior valor
        // já está na direita (atual posição top)
        top = top - 1;
        //Este for é a “ida” para a esquerda
        for(i = top; i > bottom; i = i - 1)
        {  if(vetor[i].key < vetor[i - 1].key)
            {
                aux=vetor[i].key;
                vetor[i].key=vetor[i-1].key;
                vetor[i-1].key=aux;
                swapped = 0;
            }
        }
        //aumenta o `bottom` porque o menor valor já está
        //na posição inicial (bottom)
        bottom = bottom + 1;
    }//fecha while
    end = clock();

    fprintf(ARQ, "[%d] - %d ", i+1, (end - start));
 }// fim da funçao


int main(){
    int tam[5] = {1000, 1000, 1000, 1000, 1000};
    int seeds[10] = {66, 68, 22, 38, 49, 27, 41, 91, 95, 2};
    FILE *ARQ = fopen("Relatorio.txt", "w");

    fprintf(ARQ, "Bubble Sort:");
    for(int i = 0; i<5; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        fprintf(ARQ, "\n\tTipo 1: ");
        for(int j = 0; j < 10; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            bubble_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }

        fprintf(ARQ, "\n\tTipo 2: ");
        for(int j = 0; j < 10; j++){
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

    fprintf(ARQ, "Cocktail Sort:");
    for(int i = 0; i<5; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        fprintf(ARQ, "\n\tTipo 1: ");
        for(int j = 0; j < 10; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            cocktail_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }

        fprintf(ARQ, "\n\tTipo 2: ");
        for(int j = 0; j < 10; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            cocktail_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }
        fprintf(ARQ, "\n");
    }
    
    return 0;
}
