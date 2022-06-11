/*Trabalho Arvore Rubro Negra
Disciplina: Estrutura de Dados II
Engenharia da Computacao
Alunos: Lazaro Jose, Pedro Henrique Goes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "rubroNegra.h"

Artigo *createArtigo(int id, int ano, char *autor, char *titulo,
                     char *revista, char *doi, char *plvrChave){
    Artigo *aux = (Artigo *)malloc(sizeof(Artigo));
    if(aux != NULL){
        aux->id = id;
        aux->ano = ano;
        strcpy(aux->autor, autor);
        strcpy(aux->titulo, titulo);
        strcpy(aux->revista, revista);
        strcpy(aux->DOI, doi);
        strcpy(aux->palavraChave, plvrChave);
    }
    return aux;
}

NodeRN *createNode(Artigo *chave, arvore *T){
    NodeRN *ptr = (NodeRN *) malloc(sizeof(NodeRN));
    if(ptr){
        ptr->art = chave;
        ptr->cor = RUBRO;
        ptr->esq = T->sentinela;
        ptr->dir = T->sentinela;
        ptr->pai = T->sentinela;
        return ptr;
    }
    return NULL;;
}

NodeRN *createSentinela(){
    NodeRN *ptr = (NodeRN *)malloc(sizeof(NodeRN));
    char aux[200] = "0";
    Artigo *artg = createArtigo(0,0,aux,aux,aux,aux,aux);
    if(ptr){
        ptr->art = artg;
        ptr->cor = NEGRO;
        ptr->esq = NULL;
        ptr->dir = NULL;
        ptr->pai = NULL;
        return ptr;
    }
    return NULL;
}

arvore *createArvore(){
    arvore *T = (arvore*)malloc(sizeof(arvore));
	if(T){
		T->sentinela = createSentinela();
		T->raiz = T->sentinela;
		return T;
	}
	return NULL;
}

NodeRN *searchRN(arvore *T, NodeRN *root, int ch){
    if(T->raiz == NULL || root == T->sentinela) return NULL;             //Caso a raiz seja NULL ou o ID procurado nao esteja presente, retorna-se NULL
    if(ch == root->art->id) return root;
    else if(ch < root->art->id) return searchRN(T, root->esq, ch);
    else return searchRN(T, root->dir, ch);
}

void RotacaoEsq(arvore *T, NodeRN *arv){
    NodeRN *aux = arv->dir;                         //Considera-se o pivo sendo o no a direita da arvore dada como argumento

    arv->dir = aux->esq;;
    if(aux->esq != T->sentinela) aux->esq->pai = arv;

    aux->pai = arv->pai;
    if(arv->pai == T->sentinela) T->raiz = aux;
    else if(arv == arv->pai->esq) arv->pai->esq = aux;
    else arv->pai->dir = aux;

    aux->esq = arv;
    arv->pai = aux;
}

void RotacaoDir(arvore *T, NodeRN *arv){
    NodeRN *aux = arv->esq;                         //Considera-se o pivo sendo o no a esquerda da arvore dada como argumento

    arv->esq = aux->dir;
    if (aux->dir != T->sentinela) aux->dir->pai = arv;

    aux->pai = arv->pai;
    if (arv->pai == T->sentinela) T->raiz = aux;
    else if(arv == arv->pai->dir) arv->pai->dir = aux;
    else arv->pai->esq = aux;

    aux->dir = arv;
    arv->pai = aux;
}

void insertFixup(arvore *T, NodeRN *z){
    while(z->pai->cor == RUBRO){	   //Como o pai de z eh rubro, a propriedade 4 foi violada

        if(z->pai == z->pai->pai->esq){
            NodeRN *tio = z->pai->pai->dir;

            if(tio->cor == RUBRO){      //Caso o tio seja rubro, temos uma propriedade violada
				z->pai->cor = NEGRO;    //eh necessario a troca de cores entre os nos de referencia
                tio->cor = NEGRO;
                z->pai->pai->cor = RUBRO;
                z = z->pai->pai;
            }

            else{                         //Caso o tio seja negro, verifica-se onde esta o no da insercao
				if(z == z->pai->dir){     //Se estiver pela direita, rotaciona-se apropriadamente para o terceiro caso
					z = z->pai;
                	RotacaoEsq(T,z);
        		}
            z->pai->cor = NEGRO;          //Se estiver pela esquerda, rotaciona-se para a direita para o equilibrio
            z->pai->pai->cor = RUBRO;
            RotacaoDir(T,z->pai->pai);
            }
        }
        else{                              //De forma analoga, realiza-se de forma oposta para caso o avo esteja a direita
            NodeRN *tio = z->pai->pai->esq;
            if(tio->cor == RUBRO){    //CASO 1
				z->pai->cor=NEGRO;
                tio->cor = NEGRO;
                z->pai->pai->cor = RUBRO;
                z=z->pai->pai;
            }
            else{
				if(z == z->pai->esq){  //CASO 2
					z = z->pai;
                	RotacaoDir(T,z);
        		}
            z->pai->cor = NEGRO;  //CASO 3
            z->pai->pai->cor = RUBRO;
            RotacaoEsq(T,z->pai->pai);
            }
		}
    }
    T->raiz->cor = NEGRO;
}

void insertRN(arvore *T, Artigo *art){
    NodeRN *novoNo = createNode(art,T);
    NodeRN *pai = T->sentinela;
    NodeRN *root = T->raiz;

    while(root != T->sentinela){                   //Laco de repeticao para encontrar onde inserir o no, mantendo sempre um ponteiro para seu pai
        pai = root;
        if(novoNo->art->id == root->art->id){
            printf("\nID do artigo ja inserido no banco de dados!\n");
            return;
        }
        else if(novoNo->art->id < root->art->id) root = root->esq;
        else root = root->dir;
    }
    novoNo->pai = pai;

    if(pai == T->sentinela) T->raiz = novoNo;
    else if(novoNo->art->id < pai->art->id) pai->esq = novoNo;
    else pai->dir = novoNo;

    insertFixup(T,novoNo);                         //Modulo para encontrar se houve algum desrespeito as propriedades de arvore rubro-negra
}

void repointRN(arvore *T, NodeRN *auxa, NodeRN *auxb){
    if(auxa->pai == T->sentinela) T->raiz = auxb;
    else if(auxa == auxa->pai->esq) auxa->pai->esq = auxb;
    else auxa->pai->dir = auxb;
    auxb->pai = auxa->pai;
}

NodeRN *sucessorRN(arvore *T, NodeRN *suc){            //Sucessor do no eh o filho mais a esquerda da subarvore direita
    while(suc->esq != T->sentinela) suc = suc->esq;
    return suc;
}

void deleteFixup(arvore *T, NodeRN *arv){
    NodeRN *aux;

    while((arv != T->raiz) && (arv->cor == NEGRO)){
        if(arv == arv->pai->esq){       //Caso o arv esteja na esquerda
            aux = arv->pai->dir;
            if(aux->cor = RUBRO){       //Caso o no "aux" seja rubro
                aux->cor = NEGRO;       //E necessario a troca de cores entre os nos de referencia
                arv->pai->cor = RUBRO;
                RotacaoEsq(T,arv->pai);
                aux = arv->pai->dir;
            }
            if((aux->esq->cor == NEGRO) && (aux->dir->cor == NEGRO)){   //Caso o "aux" seja negro e os dois filhos dele sejam negros
                aux->cor = RUBRO;                                       //Deixa o "aux" como rubro
                arv = arv->pai;
            }
            else{
                if(aux->dir->cor == NEGRO){     //Caso "aux" seja negro seu filho esquerdo e rubro e o direito e negro
                    aux->esq->cor = NEGRO;      //Troca-se as cores entre "aux" e seu filho esquerdo
                    aux->cor = RUBRO;
                    RotacaoDir(T,aux);          //Executa a rotacao direita no aux sem violar nenhuma das propriedades rubro-negras
                    aux - arv->pai->dir;
                }
                aux->cor = arv->pai->cor;   //Caso o "aux" seja negro e seu filho a direita seja rubro
                arv->pai->cor = NEGRO;      //Altera a cor do pai e do aux para negro
                aux->dir->cor = NEGRO;
                RotacaoEsq(T,arv->pai);     //Executa a rotacao esquerda no pai sem violar nenhuma das propriedades rubro-negras
                arv = T->raiz;
            }
        }
        else{           //De forma analoga, realiza-se de forma oposta para caso o arv esteja a direita
            aux = arv->pai->esq;
            if(aux-> cor == RUBRO){ //CASO 1
                aux->cor = NEGRO;
                arv->pai->cor = RUBRO;
                RotacaoDir(T,arv->pai);
                aux = arv->pai->esq;
            }
            if((aux->esq->cor == NEGRO) && (aux->dir->cor == NEGRO)){   //CASO 2
                aux->cor = RUBRO;
                arv = arv->pai;
            }
            else{
                if(aux->dir->cor == NEGRO){ //CASO 3
                    aux->esq->cor = NEGRO;
                    aux->cor = RUBRO;
                    RotacaoEsq(T,aux);
                    aux = arv->pai->esq;
                }
                aux->cor = arv->pai->cor;   //CASO 4
                arv->pai->cor = NEGRO;
                aux->dir->cor = NEGRO;
                RotacaoDir(T, arv->pai);
                arv = T->raiz;
            }
        }
    }
    arv->cor = NEGRO;
}

void deleteRN(arvore *T, int ch){
    NodeRN *busca = searchRN(T, T->raiz, ch);
    if(busca == NULL){
        printf("\nArtigo procurado nao foi encontrado para a remocao\n");
        return;
    }
    NodeRN *auxa;
    NodeRN *auxb = busca;
    int corAuxb = auxb->cor;

    if(busca->esq == T->sentinela){         //Para caso tenha apenas filho a direita ou nenhum filho
        auxa = busca->dir;
        repointRN(T,busca,busca->dir);
    }
    else if(busca->dir == T->sentinela){     //Caso tenha apenas filho a esquerda
        auxa = busca->dir;
        repointRN(T, busca, busca->esq);
    }
    else{                                    //Caso tenha 2 filhos nao nulos
        auxb = sucessorRN(T, busca->dir);
        corAuxb = auxb->cor;
        auxa = auxb->dir;
        if(auxb->pai == busca) auxa->pai = auxb;
        else{
            repointRN(T, auxb, auxb->dir);
            auxb->dir = busca->dir;
            auxb->dir->pai = auxb;
        }
        repointRN(T, busca, auxb);
        auxb->esq = busca->esq;
        auxb->esq->pai = auxb;
        auxb->cor = busca->cor;
    }

    free(busca);
    if(corAuxb == NEGRO) deleteFixup(T,auxa);    //Caso o no removido seja negro, eh importante verificar se nao ocorreu
                                                 //mudanca na altura negra da arvore
}

/*Impressão completa da árvore, sendo para entendimento, a impressão do id do artigo + a cor do nó*/
void printRN(arvore *T, NodeRN *root, int nivel){
    int i;
    char cor[6];

    if(root == T->sentinela) return;
    for(i=0; i<nivel; i++) printf("\t");
    if(root->cor == 0) strcpy(cor, "NEGRO");
    else strcpy(cor,"RUBRO");
    printf("[%i] [%s]\n" , root->art->id, cor);
    printRN(T,root->esq,nivel-1);
    printRN(T, root->dir,nivel+1);
    return;
}
