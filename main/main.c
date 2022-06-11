/*Trabalho Arvore Rubro Negra
Disciplina: Estrutura de Dados II
Engenharia da Computacao
Alunos: Lazaro Jose, Pedro Henrique Goes
*/

#include "rubroNegra.c"


/* Funcao que insere todos os dados de um artigo*/
Artigo *insereArtigo(){
    int id, ano;
    char autor[200], titulo[200], revista[200];
    char doi[200], plvrChave[200];
    printf("Insira o id do artigo: ");
    scanf("%i", &id);
    printf("Insira o ano do artigo: ");
    scanf("%i", &ano);
    printf("Insira o autor do artigo: ");
    fgets(autor, 200, stdin);
    scanf("%[^\n]s", autor);
    printf("Insira o titulo do artigo: ");
    fgets(titulo, 200, stdin);
    scanf("%[^\n]s", titulo);
    printf("Insira a revista do artigo: ");
    fgets(revista, 200, stdin);
    scanf("%[^\n]s", revista);+
    printf("Insira o DOI do artigo: ");
    fgets(doi, 200, stdin);
    scanf("%[^\n]s", doi);
    printf("Insira as palavras chaves do artigo: ");
    fgets(plvrChave, 200, stdin);
    scanf("%[^\n]s", plvrChave);

    return createArtigo(id, ano, autor, titulo, revista, doi, plvrChave);
}

/*Função adequada para a impressão de todos os dados contidos em um nó passado como argumento*/
void printNodeRN(NodeRN *node){
    printf("ID: %i\n", node->art->id);
    printf("Ano de publicacao: %i\n", node->art->ano);
    printf("Nome do Autor: %s\n", node->art->autor);
    printf("Titulo: %s\n", node->art->titulo);
    printf("Revista: %s\n", node->art->revista);
    printf("DOI: %s\n", node->art->DOI);
    printf("Palavras-chave: %s\n\n", node->art->palavraChave);
}

int main(){
    arvore *T = createArvore();
    NodeRN *root;
    int resp = 0, aux;
    Artigo *art;
    while(resp !=5){
        printf("[1] Para inserir um novo artigo\n");
        printf("[2] Para remover um artigo\n");
        printf("[3] Para buscar um artigo\n");
        printf("[4] Para imprimir a arvore\n");
        printf("[5] Para sair\n");
        printf("Insira a opcao que deseja realizar: ");
        scanf("%d", &resp);

        switch (resp)
        {
        case 1:
            art = insereArtigo();
            insertRN(T,art);
            printf("\n");
            printRN(T,T->raiz,2);
            printf("\n");
            break;
        case 2:
            printf("Digite o ID do artigo a ser removido: ");
            scanf("%d", &aux);
            deleteRN(T,aux);
            printf("\n");
            printRN(T,T->raiz,2);
            printf("\n");
            break;
        case 3:
            printf("Digite o ID do artigo a ser buscado: ");
            scanf("%d", &aux);
            root = searchRN(T,T->raiz,aux);
            if(root != NULL){
                printf("\nArtigo encontrado!\n\n");
                printNodeRN(root);
            }
            else printf("\nArtigo nao se encontra em nosso banco de dados!\n\n");
            break;
        case 4:
            printf("\n");
            printRN(T,T->raiz,2);
            printf("\n");
            break;
        case 5:
            printf("\nSaida Realizada!\n\n");
            break;
        default:
            printf("\nOpcao Invalida!\n\n");
            break;
        }
    }
    return 0;
}
