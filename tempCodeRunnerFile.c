fprintf(ARQ, "\n\tTamanho do vetor: %d", tam[i]);
        fprintf(ARQ, "\n\tTipo 1: ");
        printf("\n\tTamanho do vetor: %d", tam[i]); //TESTE
        for(int j = 0; j < qntd_seeds; j++){
            Info *vetor = criar_vetor_tipo1(tam[i], seeds[j]);
            printf("\nVetor antes:\n");
            printar_vetor(vetor, tam[i]);
            quick_sort(vetor, 0, tam[i]-1, j, ARQ);
            printf("\nVetor depois:\n");
            printar_vetor(vetor, tam[i]);
            free(vetor);
            printf("\n\t\tCaso %d - ok", j+1); //TESTE
        }