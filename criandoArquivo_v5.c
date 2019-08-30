#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct table_char
{
    unsigned char cHar;
    long count;
}table_c;

typedef struct lista{
    long quantidade;
    unsigned char byte;
    struct lista *prox;
}Lista;

Lista *criando_lista(){
    return NULL;
}

Lista *inserir(Lista *cabeca, long numero, unsigned char byte){
    if(cabeca == NULL){
        Lista *novo_no = (Lista *)malloc(sizeof(Lista));
        novo_no->quantidade = numero;
        novo_no->prox = NULL;
        novo_no->byte = byte;
        return (novo_no);
    }
    else{
        Lista *aux = cabeca, *anterior = NULL;
        Lista *novo_no = (Lista *)malloc(sizeof(Lista));
        novo_no->quantidade = numero;
        novo_no->byte = byte;
        if(numero <= (cabeca->quantidade)){
            novo_no->prox = cabeca;
            aux = novo_no;
            return aux;
        }
        else{
            while((cabeca->quantidade < numero)&&(cabeca->prox != NULL)){
            anterior = cabeca;
            cabeca = cabeca->prox;
            }
            if(cabeca->quantidade < numero){
                cabeca->prox = novo_no;
                novo_no->prox = NULL;
                return aux;
            }
            else{
                novo_no->prox = anterior->prox;
                anterior->prox = novo_no;
                return aux;
            }
        }
    }
}

void print_lista(Lista *cabeca){
    int cont = 1;
    while(cabeca != NULL){
        printf("%d --- >> %c = %ld\n", cont, cabeca->byte, cabeca->quantidade);
        cabeca = cabeca->prox;
        cont += 1;
    }
}

int main()
{
    FILE * pFile;
    FILE * pFile2;
    long lSize;
    unsigned char * buffer;
    size_t result;
    table_c tb[256];
    unsigned char c;
    int i, j, k;

    Lista *lista;
    lista = criando_lista();

    pFile = fopen ("teste_video.mp4", "rb");
    if (pFile==NULL)
    {
        fputs ("File error",stderr);
        exit (1);
    }

    // obtém o tamanho do arquivo
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    // alocar memória para conter o arquivo inteiro
    buffer = (unsigned char*) malloc (sizeof(unsigned char)*lSize);
    if (buffer == NULL)
    {
        fputs ("Memory error",stderr);
        exit (2);
    }

    // Copie o arquivo para o buffer
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize)
    {
        fputs ("Reading error",stderr);
        exit (3);
    }
    /* o arquivo inteiro está agora carregado no buffer de memória */

	// contador de quantas vezes o byte se repete//
    i = 0, j = 0, k = 0;
    while(k < lSize)
    {
        c = *(buffer+k);
        if(i == 0)
        {
            tb[i].cHar = c;
            tb[i].count = 1;
            i++;
        }
        else
        {
            for(j = 0; j < i; ++j)
            {
                if(tb[j].cHar == c)
                {
                    tb[j].count++;
                    break;
                }
                else if(j == (i-1))
                {
                    tb[i].cHar = c;
                    tb[i].count = 0;
                    i++;
                }
            }

        }
        k++;
    }

    /*
    j = 0;
    while(j < i)
    {
        printf("%d Char = %c quant => %ld \n", j, tb[j].cHar, tb[j].count);
        j++;
    }
    */
    for(j = 0; j < i; ++j){
        lista = inserir(lista, tb[j].count, tb[j].cHar);
    }

    print_lista(lista);

    //-------------------

    // Cria o novo arquivo aparti do buffer.
    pFile2 = fopen ("znovo", "wb");
    fwrite (buffer , sizeof(unsigned char), lSize, pFile2);
    //

    // terminate
    fclose (pFile);
    fclose (pFile2);
    free (buffer);
    return 0;
}
