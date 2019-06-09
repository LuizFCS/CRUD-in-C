#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--------------------------------------*/

struct dados
{
    char nome [20],
         dtnasc[11],
         end[20],
         cidade[20],
         estado[3],
         cep[10];
};

void registro();
void cadastrar();
int procurar();
void alterar();
void excluir();

/*--------------------------------------*/

int main()
{

        FILE *p1;
        struct dados info; // declaracao
        struct dados *p;
        int opcao = 0, cont;
        int i;
        int tam;    //n. de bytes da estrutura

        p = &info;
        tam = sizeof(info);
        /*---------------------------------------------------*/

        for(i = 0; i < sizeof(info); i++)
        {
            info.nome[i]=0;
        }

        // RESETA A ESTRUTURA DE DADOS.

        /*---------------------------------------------------*/

        while(1)
        {
            /*---------------------------------------------------*/

            system("cls");
            printf("\n----------------------");
            printf("----------------------");
            printf("\n\tCADASTRO DE PESSOAS\n");
            printf("\n   1. CONSULTAS");
            printf("\n   2. CADASTROS");
            printf("\n   3. PROCURAR");
            printf("\n   4. ALTERAR");
            printf("\n   5. EXCLUIR");
            printf("\n   6. SAIR");

            /*---------------------------------------------------*/

            p1 = fopen("contador.txt", "r");
            if(p1 != NULL)
            {
                fscanf(p1,"%d",&cont);
                fclose(p1);
            }

            // ESSE BLOCO IMPLICA QUE NA PRIMEIRA ABERTURA DO ARQUIVO, SE DER
            // ERRO NA LEITURA DO CONTADOR (QUE GERALMENTE ACONTECE SE VOCÊ
            // ABRIR O PROGRAMA PELA PRIMEIRA VEZ), ELE NÃO MOSTRA O NUMERO
            // DE USUÁRIOS. PORÉM SE CADASTRAR UM USUÁRIO ELE MOSTRA.

            /*---------------------------------------------------*/

            printf("\n\n   Escolha o numero da opcao que deseja.\n-->");
            scanf("%d", &opcao);
            getchar();

            /*---------------------------------------------------*/
            switch(opcao)
            {
                case 1:
                    registro(p, tam);
                    break;
                case 2:
                    cadastrar(p, tam);
                    break;
                case 3:
                    procurar(p, tam);
                    break;
                case 4:
                    alterar(p, tam);
                    break;
                case 5:
                    excluir(p, tam);
                    break;
                case 6:
                    printf("Tchau!\n");
                    exit(0);
                default:
                    printf( "\nEscolha uma opcao valida.\n");
            }
            /*---------------------------------------------------*/
        }
}

void cadastrar(struct dados *ps, int tam) //-----------------------------------------------------------------CADASTRAR
{
    FILE *p, *p1;
    int cont = 0;
    int i;

    /*--------------------------------------*/

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    fclose(p1);
    // TESTAR DELETAR ESSE BLOCO DEPOIS PRA TESTAR.

    /*--------------------------------------*/

    for(i=0;i<tam;i++){ // ZERA OS DADOS DA ESTRUTURA
        ps -> nome[i]=0;
    }
    // TESTAR DELETAR ESSE BLOCO DEPOIS PRA TESTAR.

    /*--------------------------------------*/

    p = fopen("arquivo.txt", "a");
    if(p == NULL)
    {
        printf("\nERRO NA ABERTURA DO ARQUIVO PARA ADICIONAR USUÁRIOS.\nRETORNANDO AO MENU INICIAL.");
        return;
    }

    /*--------------------------------------*/


    printf("\n\tCADASTRAR USUARIO:\n");
    printf("Cadastro do usuario %d:\n", (cont + 1));
    printf("\n---> Nome do usuario (max 20 dig): ");
    gets(ps->nome);

    printf("\n---> Data de nascimento do usuario (DD/MM/AA): ");
    gets(ps->dtnasc);

    printf("\n---> Endereco do usuario (max 20 dig): ");
    gets(ps->end);

    printf("\n---> Cidade do usuario (max 20 dig): ");
    gets(ps->cidade);

    printf("\n---> Estado do usuario (max 2 dig): ");
    gets(ps->estado);

    printf("\n---> CEP do usuario (max 10 dig): ");
    gets(ps->cep);

    fwrite(ps,tam,1,p);

    //INSERE AS INFORMAÇÕES ACIMA NO ARQUIVO.

    fclose(p);

    /*--------------------------------------*/
    cont++;
    p1 = fopen("contador.txt", "w");
    fprintf(p1,"%d",cont);
    fclose(p1);
    // AUMENTA O NUMERO DE PESSOAS NO CADASTRO
    /*--------------------------------------*/
    system("pause");
}


void registro(struct dados *ps, int tam) //-----------------------------------------------------------------REGISTRO
{
    /*--------------------------------------*/

    FILE *p, *p1;
    FILE *a;
    struct dados info;
    int i, pesq;
    int cont,comp, del = 0;
    // DECLARAÇÕES

    /*--------------------------------------*/

    p1 = fopen("contador.txt", "r");
    if(p1 == NULL)
    {
        printf("\n\tERRO EM ABERTURA DE ARQUIVO. RETORNADO AO MENU PRINCIPAL.\n");
        system("pause");
        return;
    }
    // TESTE DE ABERTURA DO CONTADOR

    fscanf(p1, "%d", &cont);
    fclose(p1);
    // PEGA O ARQUIVO ABERTO NO BLOCO ACIMA, LÊ A INFORMAÇÃO DADA E GUARDA NO cont.

    /*--------------------------------------*/

    p = fopen("arquivo.txt", "r");
    if(p == NULL)
    {
        printf("\n\tERRO EM ABERTURA DE ARQUIVO. RETORNADO AO MENU PRINCIPAL.\n");
        system("pause");
        return;
    }

    /*--------------------------------------*/
    a = fopen("contador.txt", "r");
    fscanf(a, "%d", &cont);
    fclose(a);

    /*--------------------------------------*/
    do
    {
        system("cls");
        printf("\n\tREGISTRO COMPLETO DOS USUÁRIOS CADASTRADOS:\n\n");
        printf("\n--------------------------------------------------------------------\n");
        printf("\n COD -  NOME\n");
        for(i = 0; i < cont; i++)
        {
            comp = i * tam;
            // MULTIPLICA O INDICE DO for PELO tam DADO COMO PARAMETRO NA FUNÇAO.
            // O tam É O TAMANHO DA ESTRUTURA DE DADOS, E AO MULTIPLICAR VOCE PEGA
            // O NUMERO QUE REPRESENTA O ENDEREÇO EXATO DA INFORMAÇÃO.

            fseek(p, comp, 0);
            // POSICIONA O PONTEIRO p NA LOCALIZAÇÃO comp NO ARQUIVO.

            fread(ps,sizeof(info),1,p);
            // LÊ O REGISTRO E GUARDA NA VARIAVEL ps UMA INFORMAÇÃO COM O TAMANHO
            // DO sizof(info).


            if(ps->nome[0] != '*') // VERIFICA SE O ARQUIVO ESTÁ APAGADO.
            {                      // SE NÃO ESTIVER, SEGUE PRINTAGEM:
                printf("\n%2d   - %10s\n", (i + 1), ps->nome);
            }
            else
                del++;
        }
        printf("\n--------------------------------------------------------------------\n");
        printf("\n\n\tREGISTRO TERMINADO. %d PESSOAS CADASTRADAS E ATIVAS.\n\n\n", cont - del);

        /*--------------------------------------*/

        for(i=0;i<tam;i++)
        { // ZERA OS DADOS DA ESTRUTURA
            ps -> nome[i]=0;
        }


        printf("\nDIGITE O COD DE USUARIO PARA DETALHAR ALGUEM OU DIGITE  0  PRA SAIR:");
        scanf("%d", &pesq);
        if(pesq != 0)
        {
            for(i = 0; i < cont; i++)
                if((pesq - 1) == i)
                {
                    if(ps->nome[0] != '*')
                    {
                        comp = i * tam;
                        fseek(p, comp, 0);
                        fread(ps,sizeof(info),1,p);
                        printf("\n--------------------------------------\n");
                        printf("\nUSUARIO NUMERO %d:", pesq);
                        printf("\nNome: %s", ps->nome);
                        printf("\nData de Nascimento: %s", ps->dtnasc);
                        printf("\nEndereco: %s", ps->end);
                        printf("\nCidade: %s", ps->cidade);
                        printf("\nEstado: %s", ps->estado);
                        printf("\nCep: %s", ps->cep);
                        printf("\n--------------------------------------\n");
                        system("pause");
                    }
                    else
                    {
                        printf("\nUSUARIO APAGADO.\n");
                        system("pause");
                    }

                }
        }
    } while(pesq != 0);

    /*--------------------------------------*/

    fclose(p);
    printf("\n");
    system("pause");

    /*--------------------------------------*/

}

int procurar(struct dados *ps, int tam) //-----------------------------------------------------------------PROCURAR
{
    //FILE *p;
    FILE *a;
    int opcao = 0;
    char c;
    int i = 0, y;
    int cont;
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);

    /*--------------------------------------*/

    printf("VOCE DESEJA PROCURAR:\n");
    printf("1 - POR NOME INTEIRO,\n");
    printf("2 - PELA PRIMEIRA LETRA DO NOME,\n");
    printf("3 - POR MES DE ANIVERSARIO,\n");
    printf("4 - OU POR CEP?\n\n");
    printf("ESCOLHA UMA OPCAO:\n-->");

    scanf("%d", &opcao);

    switch(opcao)
    {
        case 1:
            y = sub_procurar_nome(ps, tam);
            break;
        case 2:
            y = sub_procurar_pletra(ps, tam);
            // A PROCURA DE LETRA MOSTRA O RESULTADO DENTRO DA FUNÇÃO
            break;
        case 3:
            y = sub_procurar_mesniver(ps, tam);
            break;
        case 4:
            y = sub_procurar_cep(ps, tam);

    }

    if(y == -1)
    {
        printf("\nREGISTRO NAO ENCONTRADO...\n");
        system("pause");
        return -1;
    }

    /*--------------------------------------*/

    for(i; i < cont; i++)
        if(y == i)
        {
            if(ps->nome[0] != '*')
            {
                printf("\n--------------------------------------\n");
                printf("\nUSUARIO NUMERO %d:", (y + 1));
                printf("\nNome: %s", ps->nome);
                printf("\nData de Nascimento: %s", ps->dtnasc);
                printf("\nEndereco: %s", ps->end);
                printf("\nCidade: %s", ps->cidade);
                printf("\nEstado: %s", ps->estado);
                printf("\nCep: %s", ps->cep);
                printf("\n--------------------------------------\n");
                system("pause");
                return y;
            }
            else
            {
                return -1;
            }

        }


}

int sub_procurar_mesniver(struct dados *ps, int tam)
{
    /*--------------------------------------*/
    FILE *p;
    FILE *a;
    int cont, y, x;
    char mes[3];
    char afirm[2];
    /*--------------------------------------*/

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);

    /*--------------------------------------*/
    printf("Informe um mes para pesquisa: (dois digitos)\n");
    scanf("%s", &mes[0]);
    /*--------------------------------------*/

    for(y = 0; y < cont; y++)
    {
        fread(ps,tam,1,p);
        if(mes[0] == ps->dtnasc[3] && mes[1] == ps->dtnasc[4])
        {
            printf("\n--------------------------------------\n");
            printf("\nUSUARIO NUMERO %d:", (y + 1));
            printf("\nNome: %s", ps->nome);
            printf("\n--------------------------------------\n");
            printf("ESSE E O USUARIO QUE PROCURA? (digite 's' pra confirmar ou 'n' pra continuar busca) \n-->");
            scanf("%s", &afirm[0]);
            getchar();
            if(afirm[0] == 's')
                return y;
        }
    }
    system("pause");
    return -1;

    /*--------------------------------------*/
}

int sub_procurar_pletra(struct dados *ps, int tam)
{
    /*--------------------------------------*/
    FILE *p;
    FILE *a;
    int cont, y;
    char letra[2];
    char afirm[2];
    /*--------------------------------------*/

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);

    // INSERIR AQUI PROCURA MES

    /*--------------------------------------*/
    printf("Informe uma letra para pesquisa: ");
    scanf("%s", &letra);
    /*--------------------------------------*/

    for(y = 0; y < cont; y++)
    {
        fread(ps,tam,1,p);
        if(letra[0] == ps->nome[0])
        {
            printf("\n--------------------------------------\n");
            printf("\nUSUARIO NUMERO %d:", (y + 1));
            printf("\nNome: %s", ps->nome);
            printf("\n--------------------------------------\n");
            printf("ESSE E O USUARIO QUE PROCURA? (digite 's' pra confirmar ou 'n' pra continuar busca) \n-->");
            scanf("%s", &afirm[0]);
            getchar();
            if(afirm[0] == 's')
                return y;
        }
    }
    system("pause");
    return -1;

    /*--------------------------------------*/
}

int sub_procurar_nome(struct dados *ps, int tam)
{
    /*--------------------------------------*/
    FILE *p;
    FILE *a;
    int cont, y, x;
    char nome1[20];
    /*--------------------------------------*/

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);

    // INSERIR AQUI PROCURA CEP

    /*--------------------------------------*/
    printf("Informe um nome para pesquisa: ");
    scanf("%s", &nome1);
    getchar();
    /*--------------------------------------*/

    for(y = 0; y < cont; y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; nome1[x] != '\0';x++)
            if(nome1[x] != ps -> nome[x])
                break;

        if(nome1[x] == '\0' && ps -> nome[x] == '\0')
            return y;

    /*--------------------------------------*/

    }
    return -1;
}

int sub_procurar_cep(struct dados *ps, int tam)
{
    /*--------------------------------------*/
    FILE *p;
    FILE *a;
    int cont, y, x;
    char cep[10];
    /*--------------------------------------*/

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);

    /*--------------------------------------*/
    printf("Informe um nome para pesquisa: ");
    scanf("%s", &cep);
    /*--------------------------------------*/

    for(y = 0; y < cont; y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; cep[x] != '\0';x++)
        {
            if(cep[x] != ps -> cep[x])
                break;
        }


        if(cep[x] == '\0' && ps -> cep[x] == '\0')
            return y;
    /*--------------------------------------*/
    }
    return -1;
}

void alterar(struct dados *ps, int tam) //-----------------------------------------------------------------ALTERAR
{
    system("cls");
    printf("ALTERACAO DE USUARIO:\n");
    FILE *p;
    int n_reg;
    int n_bytes;

    printf("\nPRIMEIRO, INFORME O USUARIO A SER ALTERADO:\n");
    n_reg = procurar(ps, tam);     //pesquisa o registro no arquivo
    if(n_reg == -1)
    {
        printf("\nUSUARIO NAO ENCONTRADO PARA ALTERACAO\n");
        system("pause");
        return;
    }

    printf("\nENCONTRADO USUARIO N: %d\n",(n_reg + 1));
    n_bytes = tam * n_reg;

    p = fopen("arquivo.txt", "r+");

    fseek(p,n_bytes,0);            //posiciona o ponteiro do arquivo no registro a ser alterado
    fread(ps, tam, 1, p );         //le registro do arquivo
    system("cls");
    printf("\nALTERAR INFORMACOES:\n-----------------------------------------------------------------------------\n");
    printf("\n---> Nome do usuario (max 20 dig): ");
    scanf("%s", &ps->nome);

    printf("\n---> Data de nascimento do usuario (DD/MM/AA): ");
    scanf("%s", &ps->dtnasc);

    printf("\n---> Endereco do usuario (max 20 dig): ");
    scanf("%s", &ps->end);

    printf("\n---> Cidade do usuario (max 20 dig): ");
    scanf("%s", &ps->cidade);

    printf("\n---> Estado do usuario (max 2 dig): ");
    scanf("%s", &ps->estado);

    printf("\n---> CEP do usuario (max 10 dig): ");
    scanf("%s", &ps->cep);
    printf("\n-----------------------------------------------------------------------------\n");

    fseek(p,n_bytes,0);            //posiciona o ponteiro do arquivo no inicio do regisro a ser alterado
    fwrite(ps, tam,1,p);           //escreve o registro no arquivo

    fclose(p);
    system("pause");
    return;
}
void excluir(struct dados *ps, int tam)
{
    system("cls");
    printf("\nDELETAR REGISTRO:\n");
    char nom = '*';
    FILE *p, *a; //DELET A
    p = fopen("arquivo.txt", "r+");
    int n_reg, cont = 0;
    int n_bytes;
    //--------------------------------------
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    //--------------------------------------
    // USA A PROCURA PARA INFORMAR O USUARIO A FUNCAO, IGUAL A ALTERAR

    printf("\nPRIMEIRO, INFORME O USUARIO A SER DELETADO:\n");
    n_reg = procurar(ps, tam);
    if(n_reg == -1)
    {
        printf("\nUSUARIO NAO ENCONTRADO PARA DELETAR\n");
        system("pause");
        return;
    }

    // PEGA O USUARIO, CALCULA A POSICAO E USA O FSEEK

    printf("\nENCONTRADO USUARIO N: %d\n",(n_reg + 1));
    n_bytes = tam * n_reg;

    fseek(p, n_bytes, 0);
    fread(ps, tam, 1, p);

    printf("REGISTRO PARA APAGAR: %s.  <--- DELETADO!\n\n",ps -> nome);
    ps->nome[0] = '*';

    // REGISTRA O USUARIO COM UM ASTERISCO PARA QUE ELE NAO SEJA CONTADO NA CONSULTA

    system("pause");

    fseek(p,n_bytes,0);
    fwrite(ps,tam,1,p);

    fclose(p);

}
