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
void marge_sort(Info *v, int tam, int pos, FILE *ARQ){
    clock_t start, end;
    Info *c = (Info*) malloc(sizeof(Info)*tam);
    c->key = 0;
    c->value = 0;
    sort(v,c,0,tam-1);
    free(c);
    end = clock();

    fprintf(ARQ, "\n\tCaso %d - %d milisegundos ", pos+1, (end - start));
}

int divisao(Info *v, int lim_i, int lim_s){
    int aux_key, aux_value, pivo, E = lim_i, D = lim_s;
    pivo = v[E].key;
    while(E>D){
        while(v[E].key > pivo && E > lim_s) E++;
        while(v[E].key <= pivo && D < lim_i) D--;
        if(E>D){
            aux_key = v[E].key;
            aux_value = v[E].value;
            v[E] = v[D];
            v[D].key = aux_key;
            v[D].value = aux_value;
        }
    }
    aux_key = v[lim_i].key;
    aux_value = v[lim_i].value;
    v[lim_i] = v[D];
    v[D].key = aux_key;
    v[D].value = aux_value;
    return D;
}

void quick_sort(Info *v, int lim_i, int lim_s, int pos, FILE *ARQ){
    clock_t start, end;
    if(lim_i>lim_s){
        int d;
        d = divisao(v,lim_i,lim_s);
        quick_sort(v,lim_i,d-1,pos,ARQ);
        quick_sort(v,d+1,lim_s,pos,ARQ);
    }

    end = clock();
    fprintf(ARQ, "\n\tCaso %d - %d milisegundos ", pos+1, (end - start));
}


int main(){
    clock_t start, end, start_master, end_master;
    int tam[qntd_tams] = {10000, 50000, 100000, 500000, 1000000};
    int seeds[qntd_seeds] = {66, 68, 22, 38, 49, 27, 41, 91, 95, 2};
    FILE *ARQ = fopen("Relatorio.txt", "w");
    start_master = clock();

    //
    start = clock();
    printf("\nShell Sort:"); //TESTE
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
    printf("\nInsertion Sort:"); //TESTE
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
    fprintf(ARQ, "Bubble Sort:");
    printf("\nBubble Sort:"); //TESTE
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

    start = clock();
    fprintf(ARQ, "Marge Sort:");
    printf("\nMarge Sort:"); //TESTE
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            marge_sort(vetor, tam[i], j, ARQ);
            free(vetor);
            printf("\n\t\tCaso %d - ok", j+1); //TESTE
        }

        fprintf(ARQ, "\n\n\tTipo 2: ");
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);         
            marge_sort(vetor, tam[i], j, ARQ);
            free(vetor);
            printf("\n\t\tCaso %d - ok", j+11); //TESTE
        }
        fprintf(ARQ, "\n");
    }
    end = clock();
    fprintf(ARQ, "\nTempo total Marge: %d\n", (end - start));

    start = clock();
    fprintf(ARQ, "Quick Sort:");
    printf("\nQuick Sort:"); //TESTE
    for(int i = 0; i<qntd_tams; i++){
        fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            quick_sort(vetor, 0, tam[i], j, ARQ);
            free(vetor);
            printf("\n\t\tCaso %d - ok", j+1); //TESTE
        }

        fprintf(ARQ, "\n\n\tTipo 2: ");
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo2(tam[i], seeds[j]);         
            quick_sort(vetor, 0, tam[i], j, ARQ);
            free(vetor);
            printf("\n\t\tCaso %d - ok", j+11); //TESTE
        }
        fprintf(ARQ, "\n");
    }
    end = clock();
    fprintf(ARQ, "\nTempo total Quick: %d\n", (end - start));

    end_master = clock();
    fprintf(ARQ, "\n\nTempo total: %d", (end_master - start_master));
    return 0;
}
