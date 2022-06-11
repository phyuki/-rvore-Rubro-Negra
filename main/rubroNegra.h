/*Trabalho Arvore Rubro Negra
Disciplina: Estrutura de Dados II
Engenharia da Computacao
Alunos: Lazaro Jose, Pedro Henrique Goes
*/

#ifndef _H_RUBRONEGRA
#define _H_RUBRONEGRA

//Declaracao das bibliotecas
#include<stdio.h>
#include<stdlib.h>

//Definicao das cores
#define RUBRO 1
#define NEGRO 0

//Estrtutura do artigo
typedef struct{
    int id;
    int ano;
    char autor[200];
    char titulo[200];
    char revista[200];
    char DOI[200];
    char palavraChave[200];
}Artigo;


//Estrututra do no
typedef struct no{
    int cor;
    struct no *esq, *dir, *pai;
    Artigo *art;
}NodeRN;

//Estrutura da arvore
typedef struct tno{
    NodeRN *raiz, *sentinela;
}arvore;


/*Metodo aplicado para alocação dinamica e atribuição de valores pré-definidos
de um objeto do tipo artigo no qual será inserido na arvore como seu dado de interesse*/
Artigo *createArtigo(int id, int ano, char *autor, char *titulo, char *revista, char *doi, char *plvrChave);


/*Função de alocação dinamica de um nó da arvore que recebe como parametro uma variavel do tipo artigo
ja alocada na memoria e um ponteiro de uma arvore RN, inicializando seus ponteiros de caminho sendo nulos, pintando
o nó criado de rubro e realizando o apontamento dos dados definidos pelo objeto artigo*/
NodeRN *createNode(Artigo *chave, arvore *T);

/*Funcao que cria um no sentinela*/
NodeRN *createSentinela();

/*Funcao que cria um no para uma arvore*/
arvore *createArvore();

/*Função para a busca por um nó da árvore, usando como parametro de relevância o id do artigo postado.
É de importancia lembrar que ainda se baseia no paradigma no qual afirma que nós com id menor estarão a esquerda
e nós com id maior estarão a direita*/
NodeRN *searchRN(arvore *T, NodeRN *root, int ch);

/*Rotação simples a esquerda: Considerando o pivô o nó a direita do parâmetro passado, rotacionamos em torno dele
para a esquerda, trocando os apontamentos e suas cores de tal forma que o pivô receba a cor de seu pai e o mesmo
se torna rubro*/

void RotacaoEsq(arvore *T, NodeRN *arv);

/*Rotação simples a direita: Considerando o pivô o nó a esquerda do parâmetro passado, rotacionamos em torno dele
para a direita, trocando os apontamentos e suas cores de tal forma que o pivô receba a cor de seu pai e o mesmo
se torna rubro*/
void RotacaoDir(arvore *T, NodeRN *arv);

/*Metodo auxiliar cuja funcionalidade se baseia em verificar e manipular as condiçoes de arvore rubro-negra,
utilizando de rotações ou apenas trocando as cores dos nós*/
void insertFixup(arvore *T, NodeRN *root);

/*Função que realiza a chamada da inserção de um objeto do tipo artigo na chave caso possível. Sua funcionalidade
se resume a manter a cor da raiz sempre negra para respeitar as leis da árvore rubro-negra, além de mostrar para
o usuario caso a inserção realmente tenha sido efetuada*/
void insertRN(arvore *T, Artigo *art);

/*Funcao que realiza reapontamentos necessarios para a remocao de um no*/
void repointRN(arvore *T, NodeRN *auxa, NodeRN *auxb);

/*Funcao que busca o sucessor de um no, sendo o sucessor o filho mais a esquerda da subarvore direita de uma arvore*/
NodeRN *sucessorRN(arvore *T, NodeRN *suc);

/*Funcao que auxilia a funcao deleteRN avaliando e reestabelecendo as propriedades de uma arvore RN no no inserido*/
void deleteFixup(arvore *T, NodeRN *arv);

/*Funcao que remove um no de umar arvore RN*/
void deleteRN(arvore *T, int ch);

/*Impressão completa da árvore, sendo para entendimento, a impressão do id do artigo + a cor do nó*/
void printRN(arvore *T, NodeRN *root, int nivel);

#endif
