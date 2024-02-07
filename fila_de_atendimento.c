// Aluno: João Paulo Mota Santana
// Data: 20/11/2022

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define TAM 10

typedef struct{
	  int valor; 
    char  nome[100];
}tpatend;

typedef struct{
	tpatend C[TAM];
	int ini, fim;
}tpNo; 


void def (tpNo *pNo){	
	pNo->fim = 0;
	pNo->ini = 0;
}
int filavaz (tpNo *pNo){
	return (pNo->ini == pNo->fim);
}
int filach (tpNo *pNo){
	return (pNo->ini == ((pNo->fim + 1) % TAM));
}


int inserirfil (tpNo *pNo, tpatend *item){
	if (filach(pNo))
		return 0;
	pNo->fim = (pNo->fim + 1) % TAM ;
	pNo->C[pNo->fim].valor = item->valor;
	strcpy(pNo->C[pNo->fim].nome, item->nome);
	return 1;
}

int removerfil(tpNo *pNo, tpatend *item){
	if (filavaz(pNo))
		return 0;
	pNo->ini = (pNo->ini+1) % TAM;
	(*item).valor=pNo->C[pNo->ini].valor;
	strcpy((*item).nome , pNo->C[pNo->ini].nome);
	return 1;
}


tpatend * inicio_fila (tpNo *pNo){
	if (filavaz(pNo))
		return NULL;
	tpatend *pAtend =(tpatend *)malloc(sizeof(tpatend));
	int index = (pNo->ini+1) % TAM;
	pAtend->valor = pNo->C[index].valor;
	strcpy(pAtend->nome, pNo->C[index].nome);
	return pAtend;
}

struct Lista {
	  int valor; 
    char  *nome; 
    struct Lista *proximo;      
   } Lista; 

typedef struct Lista tplista;   
tplista *lista; 
tplista *Plista;

void inserir_ordenado(tplista *lista, int num, char *nome){
    tplista *aux, *novo = malloc(sizeof(tplista));

    if(novo){
        novo->valor = num;
        novo->nome=(char *) malloc(sizeof(nome));
        strcpy(novo->nome,nome);
        if(lista== NULL){
            novo->proximo = NULL;
            lista= novo;
        }
        else if(novo->valor < (lista)->valor){
            novo->proximo = lista;
            novo->nome=(char *) malloc(sizeof(nome));
            strcpy(novo->nome,nome);
            lista= novo;
        }
        else{
            aux = lista;
            while(aux->proximo && novo->valor > aux->proximo->valor)
                aux = aux->proximo;
            novo->proximo = aux->proximo;
            aux->proximo = novo;
            novo->nome=(char *) malloc(sizeof(nome));
            strcpy(novo->nome,nome);          
        }
    }
    else
        printf("Erro ao alocar memoria!\n");
}

tplista* remover(tplista *lista, int num){
    tplista *aux, *remover = NULL;
    if(lista){
        if((lista)->valor == num){
            remover = lista;
            lista = remover->proximo;
        }
        else{
            aux = lista;
            while(aux->proximo && aux->proximo->valor != num)
                aux = aux->proximo;
            if(aux->proximo){
                remover = aux->proximo;
                aux->proximo = remover->proximo;
            }
        }
    }
    return remover;
}

tplista * iniciar() {
   lista = (tplista *) malloc (sizeof(tplista)); 
   lista->valor=0;
   lista->nome=NULL;
   lista->proximo = NULL; 
   return lista;
}
int lista_vazia(void){
	return ((lista == NULL)||(lista -> valor == 0 && lista -> proximo == NULL));
}

tplista *buscar(tplista *lista, int valor) {
	if(!lista_vazia()){ 
   		tplista *aux, *ant;
	    aux=lista;   
		  ant=NULL;		   
    	while((aux -> valor != valor) && (aux -> proximo != NULL)){
			ant = aux;
    	aux = aux -> proximo;
    	}
    	if(aux->valor==valor){
     		printf("id encontrado!");
     		return aux;
   		}else{
   			printf("id n encontrado!");
   			return NULL; 
   		}
   	}
}

void imprimir(tplista *lista){
    printf("\n\tLista: ");
    while(lista){
        printf("%d - %s ", lista->valor, lista->nome);
        lista = lista->proximo;
    }
    printf("\n\n");
}

 int main(void){
	  int valor, opcao;
    tplista *removido= NULL;
	  char nome[100];
	  tpatend *pAtend =(tpatend *)malloc(sizeof(tpatend));
	  tpNo *Fila = (tpNo *) malloc(sizeof(tpNo));
    def(Fila);
    Plista=iniciar();
    do {
	    printf("\n\t1 - InserirO\n\t2 - Remover\n\t3 - Imprimir\n\t4 - Buscar e Inserir na fila de atendimento\n\t5 - Atender\n\t6 - Imprimir Fila\n");
        scanf("%d", &opcao);
    switch(opcao){
      case 1:
           printf("\nDigite um id: ");
           scanf("%d", &valor);
           printf("\nDigite um nome: ");
           scanf("%s", nome);           
           inserir_ordenado(Plista, valor, nome);
           break;
      case 2:
           printf("\nDigite um id: ");
            scanf("%d", &valor);
            removido = remover(Plista, valor);
            if(removido){
                printf("id removido: %d\n", removido->valor);
                free(removido);
            }
            else
                printf("id nao existe!\n");
           break;
      case 3:
         	 imprimir(lista);
           break;
      case 4:
           printf("\nDigite um id: ");
           scanf("%d", &valor);
           tplista *aux=buscar (Plista, valor);
           if(aux!=NULL){
	           pAtend->valor = valor;		    
	           strcpy(pAtend->nome, aux->nome);
    	       strcpy(pAtend->nome,nome);
        	   inserirfil(Fila,pAtend);
        	}
           break;
      case 5:
           if(removerfil(Fila, pAtend))
           		printf("\nid atendido:\n id: %d nome: %s \n",pAtend->valor, pAtend->nome);
         	else
           		printf("\nFila vazia.\n");
          break;
      case 6:
        	for(int f = Fila -> ini+1; f <= Fila-> fim; f++){
      		printf("\nid em espera %d:\n id: %d nome: %s \n",f,Fila->C[f].valor, Fila->C[f].nome);
			}	
        }  
	} while (opcao !=7);
    return 0;
}