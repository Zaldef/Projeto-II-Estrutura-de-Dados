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
        printf("key: %ld, value: %f\n", vetor[i].key, vetor[i].value);
    }
}

int verifica_vetor_ordenado(Info *vetor, int tam) {
    int i;
    for (i = 0; i < tam - 1; i++) {
        if (vetor[i].key < vetor[i + 1].key) {
            return 0; // Retorna 0 se não estiver ordenado decrescente
        }
    }
    return 1; // Retorna 1 se estiver ordenado decrescente
}

void bubble_sort(Info *vetor, int tam, int caso, FILE *ARQ) {

    clock_t start, end;

    start = clock();
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i ; j++) {
            if (vetor[j].key < vetor[j + 1].key) {
                int temp = vetor[j].key;
                vetor[j].key = vetor[j + 1].key;
                vetor[j + 1].key = temp;
            }
        }
    }
    end = clock();

    printf("\n\tCaso %d - %ld milisegundos ", caso+1, (end - start)); // TESTE
    fprintf(ARQ, "\n\tCaso %d - %ld milisegundos ", caso+1, (end - start));
}

void insertion_sort(Info *vetor, int tam, int caso, FILE *ARQ){
    clock_t start, end;
    int i, j;
    Info aux;

    start = clock();
    for(i = 1; i <= tam - 1; i++){
        aux = vetor[i];
        j = i - 1;
        while (j >= 0 && aux.key > vetor[j].key) {
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = aux;
    }
    end = clock();

    printf("\n\t\tCaso %d - %ld milisegundos ", caso+1, (end - start)); // TESTE
    fprintf(ARQ, "\n\t\tCaso %d - %ld milisegundos ", caso+1, (end - start));
}

void cocktail_sort(Info *vetor, int tam, int caso, FILE *ARQ) {
    clock_t start, end;
    int aux;
    int lim_inf = 0;
    int lim_sup = tam - 1;
    int swapped = 0;

    start = clock();
    while(swapped == 0 && lim_inf < lim_sup)
    {
        swapped = 1;//se não houver troca, swapped não é atualizado no loop o vetor está ordenado
        for(int i = lim_inf; i < lim_sup; i++)//for da direita para a esquerda
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

        for(int i = lim_sup; i > lim_inf; i--)//for da esquerda para a direita
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
    printf("\n\tCaso %d - %ld milisegundos ", caso+1, (end - start)); // TESTE
    fprintf(ARQ, "\n\tCaso %d - %ld milisegundos ", caso+1, (end - start));
}

void shell_sort(Info *vetor, int tam, int caso, FILE *ARQ){
    clock_t start, end;
    int i, j, h = 1;
    Info aux;

    start = clock();
    while(h < tam){
        h = 3*h + 1;
    }
    while(h > 1){
        h = h/3;
        for(i = h; i <= tam - 1; i++){
            aux = vetor[i];
            j = i - h;
            while (j >= 0 && aux.key > vetor[j].key) {
                vetor[j+h] = vetor[j];
                j = j - h;
            }
            vetor[j+h] = aux;
        }
    }
    end = clock();

    printf("\n\tCaso %d - %ld milisegundos ", caso+1, (end - start)); // TESTE
    fprintf(ARQ, "\n\tCaso %d - %ld milisegundos ", caso+1, (end - start));
}

void merge(Info *v, Info *c, int lim_i, int med_vet, int lim_s){
    int i = lim_i, j = med_vet+1, k = lim_i;
    while(i <= med_vet && j <= lim_s){
        if(v[i].key >= v[j].key){
            c[k] = v[i];
            i++;
        }else{
            c[k] = v[j];
            j++;
        }
        k++;
    }
    while(i <= med_vet){
        c[k] = v[i];
        i++;
        k++;
    }
    while(j <= lim_s){
        c[k] = v[j];
        j++;
        k++;
    }
    for(k = lim_i; k <= lim_s; k++){
        v[k] = c[k];
    }
}

void sort(Info *v, Info *c, int lim_i, int lim_s){
    int med_vet;
    if(lim_i < lim_s){
        med_vet = (lim_i + lim_s)/2;
        sort(v, c, lim_i, med_vet);
        sort(v, c, med_vet+1, lim_s);
        if(v[med_vet].key < v[med_vet+1].key){
            merge(v, c, lim_i, med_vet, lim_s);
        }
    }
}

void merge_sort(Info *v, int tam, int pos, FILE *ARQ){
    clock_t start, end;
    Info *c = (Info*) malloc(sizeof(Info)*tam);
    c->key = 0;
    c->value = 0;

    start = clock();
    sort(v,c,0,tam-1);
    end = clock();
    free(c);

    fprintf(ARQ, "\n\tCaso %d - %ld milisegundos ", pos+1, (end - start));
    printf("\n\tCaso %d - %ld milisegundos ", pos+1, (end - start)); // TESTE
}

void troca_elem_vetor(Info *v, int p1, int p2){
    int aux_key = v[p1].key;
    int aux_value = v[p1].value;
    v[p1].key = v[p2].key;
    v[p1].value = v[p2].value;
    v[p2].key = aux_key;
    v[p2].value = aux_value;
}

int divisao(Info *v, int lim_i, int lim_s){
    int pivo, E = lim_i, D = lim_s;
    pivo = v[lim_i].key;
    while(E<D){
        while(v[E].key >= pivo && E < lim_s) E++;
        while(v[D].key < pivo && D > lim_i) D--;
        if(E<D){
            troca_elem_vetor(v, E, D);
        }
    }
    troca_elem_vetor(v, lim_i, D);
    return D;
}

void quick_sort(Info *v, int lim_i, int lim_s){
    if(lim_i<lim_s){
        int d;
        d = divisao(v,lim_i,lim_s);
        quick_sort(v,lim_i,d-1);
        quick_sort(v,d+1,lim_s);
    }
}

int divisao_2(Info *v, int lim_i, int lim_s){
    int pivo, E = lim_i, D = lim_s;
    int pos_pivo = (lim_i+lim_s)/2;
    pivo = v[pos_pivo].key;
    while(E<=D){
        while(v[E].key > pivo && E < lim_s) E++;
        while(v[D].key < pivo && D > lim_i) D--;
        if(E<=D){
            troca_elem_vetor(v, E, D);
            E++;
            D--;
        }
    }
    return E;
}

void quick_sort_2(Info *v, int lim_i, int lim_s){
    if(lim_i<lim_s){
        int d;
        d = divisao_2(v,lim_i,lim_s);
        if(lim_i < d - 1){
            quick_sort_2(v, lim_i, d - 1);
        }
        if(d < lim_s){
            quick_sort_2(v, d, lim_s);
        }
    }
}

int divisao_3(Info *v, int lim_i, int lim_s){
    int pivo, E = lim_i, D = lim_s;
    pivo = v[lim_s].key;
    while(E<D){
        while(v[E].key > pivo && E < lim_s) E++;
        while(v[D].key <= pivo && D > lim_i) D--;
        if(E<D){
            troca_elem_vetor(v, E, D);
        }
    }
    troca_elem_vetor(v, lim_s, E);
    return E;
}

void quick_sort_3(Info *v, int lim_i, int lim_s){
    if(lim_i<lim_s){
        int d;
        d = divisao_3(v,lim_i,lim_s);
        quick_sort_3(v,lim_i,d-1);
        quick_sort_3(v,d+1,lim_s);
    }
}

int main(){
    //definindo variaveis de tempo
    clock_t start, end;
    int tam[qntd_tams] = {10000, 50000, 100000, 500000, 1000000};
    int seeds[qntd_seeds] = {66, 68, 22, 38, 49, 27, 41, 91, 95, 2};

    //criando arquivo para guardar os tempos
    FILE *ARQ = fopen("Relatorio.txt", "w");

// Insertion Sort
    printf("\nInsertion Sort:"); //TESTE
    fprintf(ARQ, "Insertion Sort:");
    //loop para percorrer os tamanhos dos vetores
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        //loop para percorrer as seeds no tipo 1
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTipo 1: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            insertion_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }
        //loop para percorrer as seeds no tipo 2
        fprintf(ARQ, "\n\n\tTipo 2: ");
        printf("\n\tTipo 2: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            insertion_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }

        fprintf(ARQ, "\n");
        printf("\n"); //TESTE
    }

// Bubble Sort
    printf("\nBubble Sort:"); //TESTE
    fprintf(ARQ, "\nBubble Sort:");
    //loop para percorrer os tamanhos dos vetores
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        //loop para percorrer as seeds no tipo 1
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTipo 1: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            bubble_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }
        //loop para percorrer as seeds no tipo 2
        fprintf(ARQ, "\n\n\tTipo 2: ");
        printf("\n\tTipo 2: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            bubble_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }

        fprintf(ARQ, "\n");
        printf("\n"); //TESTE
    }

// Shell Sort
    printf("\nShell Sort:"); //TESTE
    fprintf(ARQ, "\nShell Sort:");
    //loop para percorrer os tamanhos dos vetores
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTipo 1: "); //TESTE
        //loop para percorrer as seeds no tipo 1
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            shell_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }
        //loop para percorrer as seeds no tipo 2
        fprintf(ARQ, "\n\n\tTipo 2: ");
        printf("\n\tTipo 2: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            shell_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }

        fprintf(ARQ, "\n");
        printf("\n"); //TESTE
    }

// Merge Sort
    printf("\nMerge Sort:"); //TESTE
    fprintf(ARQ, "\nMerge Sort:");
    //loop para percorrer os tamanhos dos vetores
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTipo 1: "); //TESTE
        //loop para percorrer as seeds no tipo 1
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            merge_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }
        //loop para percorrer as seeds no tipo 2
        fprintf(ARQ, "\n\n\tTipo 2: ");
        printf("\n\n\tTipo 2: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            merge_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }

        fprintf(ARQ, "\n");
        printf("\n"); //TESTE
    }

// Quick Sort I-LI
    fprintf(ARQ, "Quick Sort I-LI:");
    printf("\nQuick Sort I-LI:"); //TESTE
    //loop para percorrer os tamanhos dos vetores
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        //loop para percorrer as seeds no tipo 1
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTipo 1: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            start = clock();
            quick_sort(vetor, 0, tam[i]-1);
            end = clock();
            printf("\n\t\tCaso %d - %ld milisegundos ", j+1, (end - start)); // TESTE
            fprintf(ARQ, "\n\t\tCaso %d - %ld milisegundos ", j+1, (end - start));
            free(vetor);
        }
        //loop para percorrer as seeds no tipo 2
        fprintf(ARQ, "\n\n\tTipo 2: ");
        printf("\n\tTipo 2: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            start = clock();
            quick_sort(vetor, 0, tam[i]-1);
            end = clock();
            printf("\n\t\tCaso %d - %ld milisegundos ", j+1, (end - start)); // TESTE
            fprintf(ARQ, "\n\t\tCaso %d - %ld milisegundos ", j+1, (end - start));
            free(vetor);
        }

        fprintf(ARQ, "\n");
        printf("\n"); //TESTE
    }


// Quick Sort II-LM
    fprintf(ARQ, "Quick Sort II-LM:");
    printf("\nQuick Sort II-LM:"); //TESTE
    //loop para percorrer os tamanhos dos vetores
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        //loop para percorrer as seeds no tipo 1
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTipo 1: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            start = clock();
            quick_sort_2(vetor, 0, tam[i]-1);
            end = clock();
            printf("\n\t\tCaso %d - %ld milisegundos ", j+1, (end - start)); // TESTE
            fprintf(ARQ, "\n\t\tCaso %d - %ld milisegundos ", j+1, (end - start));
            free(vetor);
        }
        //loop para percorrer as seeds no tipo 2
        fprintf(ARQ, "\n\n\tTipo 2: ");
        printf("\n\tTipo 2: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            start = clock();
            quick_sort_2(vetor, 0, tam[i]-1);
            end = clock();
            printf("\n\t\tCaso %d - %ld milisegundos ", j+1, (end - start)); // TESTE
            fprintf(ARQ, "\n\t\tCaso %d - %ld milisegundos ", j+1, (end - start));
            free(vetor);
        }

        fprintf(ARQ, "\n");
        printf("\n"); //TESTE
    }

// Quick Sort III-LS
    fprintf(ARQ, "Quick Sort III-LS:");
    printf("\nQuick Sort III-LS:"); //TESTE
    //loop para percorrer os tamanhos dos vetores
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        //loop para percorrer as seeds no tipo 1
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTipo 1: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            start = clock();
            quick_sort_3(vetor, 0, tam[i]-1);
            end = clock();
            printf("\n\t\tCaso %d - %ld milisegundos ", j+1, (end - start)); // TESTE
            fprintf(ARQ, "\n\t\tCaso %d - %ld milisegundos ", j+1, (end - start));
            free(vetor);
        }
        //loop para percorrer as seeds no tipo 2
        fprintf(ARQ, "\n\n\tTipo 2: ");
        printf("\n\tTipo 2: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            start = clock();
            quick_sort_3(vetor, 0, tam[i]-1);
            end = clock();
            printf("\n\t\tCaso %d - %ld milisegundos ", j+1, (end - start)); // TESTE
            fprintf(ARQ, "\n\t\tCaso %d - %ld milisegundos ", j+1, (end - start));
            free(vetor);
        }

        fprintf(ARQ, "\n");
        printf("\n"); //TESTE
    }

// Cocktail Sort
    fprintf(ARQ, "Cocktail Sort:");
    printf("\nCocktail Sort:"); //TESTE
    //loop para percorrer os tamanhos dos vetores
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        //loop para percorrer as seeds no tipo 1
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTipo 1: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            cocktail_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }
        //loop para percorrer as seeds no tipo 2
        fprintf(ARQ, "\n\n\tTipo 2: ");
        printf("\n\tTipo 2: "); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);
            cocktail_sort(vetor, tam[i], j, ARQ);
            free(vetor);
        }

        fprintf(ARQ, "\n");
        printf("\n"); //TESTE
    }

// // TESTE ORDENACAO
// Info *vetor = criar_vetor_tipo1(10, seeds[0]);
// printar_vetor(vetor, 10);
// //insertion_sort(vetor, 10, 0, ARQ);
// //bubble_sort(vetor, 10, 0, ARQ);
// //shell_sort(vetor, 10, 0, ARQ);
// //merge_sort(vetor, 10, 0, ARQ);
// //quick_sort(vetor, 0, 9);
// //quick_sort_2(vetor, 0, 9);
// //quick_sort_3(vetor, 0, 9);
// //cocktail_sort(vetor, 10, 0, ARQ);
// if(verifica_vetor_ordenado(vetor, 10) == 1){
//     printf("\n\t\tVETOR ORDENADO DECRESCENTE\n"); //TESTE ORDENADO
// }else{
//     printf("\n\t\tVETOR NAO ORDENADO DECRESCENTE\n"); //TESTE ORDENADO
// }
// printar_vetor(vetor, 10);
// free(vetor);

    return 0;
}
