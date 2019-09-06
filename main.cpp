#include <iostream>
#include <stdlib.h>

#define X 1
#define O 2
#define empt 0

using namespace std;
typedef struct Node{
    int **estado;
    struct Node * filho[9];
    int v = 2;
}n;
// typedef struct Pilha{
//     Node* node;
//     Pilha* topo;
//     Pilha *prev;
// }p;

n * init_tree();
void fill_tree(n *r);
void clear_state(n *no);
void mark(n *no, int i, int m);
void print_grid(n *no);
void copy_state(n *n1, n*n2);
void free_tree(n * no,int n);
int check_winner(n *no);
void minimax(n *no,int n);
void print_minimax(n* no, int n, int f);
//p* init_pilha();
//void insere_p(n *no);

// Funcao principal
int main(){
    n *raiz = init_tree();
    fill_tree(raiz);
    minimax(raiz,9);
    print_minimax(raiz,9,0);
    //cout << raiz->v << endl;
    free_tree(raiz,9);
    return 0;
}

// Inicia os parametros da raiz
n * init_tree(){
    n * t;
    t = (n*)malloc(1*sizeof(n));

    t->estado = (int **)malloc(3*sizeof(int*));
    clear_state(t);
    //print_grid(t);
    for(int i=0; i<9;i++)
        t->filho[i] = NULL;
    return t;
}

// Prenche a tree com todos os estados possiveis
void fill_tree(n *r){
    n * aux[10];
    int x;
    aux[0] = r;
    for(int i=0;i<9;i++){
        //cout << "test1" << endl;
        aux[0]->filho[i] = (n*) malloc(sizeof(n));
        aux[1] = aux[0]->filho[i];
        clear_state(aux[1]);
        mark(aux[1],i,X);
        //print_grid(aux[1]);
        for(int j=0;j<8;j++){
            //cout << "test2" << endl;
            aux[1]->filho[j] = (n*) malloc(sizeof(n));
            aux[2] = aux[1]->filho[j];
            copy_state(aux[1],aux[2]);
            mark(aux[2],j,O);
            for(int k=0;k<7;k++){
                //cout << "test3" << endl;
                aux[2]->filho[k] = (n*) malloc(sizeof(n));
                aux[3] = aux[2]->filho[k];
                copy_state(aux[2],aux[3]);
                mark(aux[3],k,X);
                for(int l=0;l<6;l++){
                    //cout << "test4" << endl;
                    aux[3]->filho[l] = (n*) malloc(sizeof(n));
                    aux[4] = aux[3]->filho[l];
                    copy_state(aux[3],aux[4]);
                    mark(aux[4],l,O);
                    for(int m=0;m<5;m++){
                        //cout << "test5" << endl;
                        aux[4]->filho[m] = (n*) malloc(sizeof(n));
                        aux[5] = aux[4]->filho[m];
                        copy_state(aux[4],aux[5]);
                        mark(aux[5],m,X);
                        //CHECKAR POR VITORIA A PARTIR DAQUI
                        if(int a=check_winner(aux[5])){
                            aux[5]->v = a;
                        } else {
                            for(int o=0;o<4;o++){
                                //cout << "test6" << endl;
                                aux[5]->filho[o] = (n*) malloc(sizeof(n));
                                aux[6] = aux[5]->filho[o];
                                copy_state(aux[5],aux[6]);
                                mark(aux[6],o,O);
                                if(int a=check_winner(aux[6])){
                                    aux[6]->v = a;
                                } else {
                                    for(int p=0;p<3;p++){
                                        //cout << "test7" << endl;
                                        aux[6]->filho[p] = (n*) malloc(sizeof(n));
                                        aux[7] = aux[6]->filho[p];
                                        copy_state(aux[6],aux[7]);
                                        mark(aux[7],p,X);
                                        if(int a=check_winner(aux[7])){
                                            aux[7]->v = a;
                                        } else {
                                            for(int q=0;q<2;q++){
                                                //cout << "test8" << endl;
                                                aux[7]->filho[q] = (n*) malloc(sizeof(n));
                                                aux[8] = aux[7]->filho[q];
                                                copy_state(aux[7],aux[8]);
                                                mark(aux[8],q,O);
                                                if(int a=check_winner(aux[8])){
                                                    aux[8]->v = a;
                                                } else {
                                                    aux[8]->filho[0] = (n*) malloc(sizeof(n));
                                                    aux[9] = aux[8]->filho[0];
                                                    copy_state(aux[8],aux[9]);
                                                    mark(aux[9],0,X);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }   
        }
    }
}

// Aloca o estado na memoria e poe os valores todos em zero
void clear_state(n *no){
    no->estado = (int**) malloc(3*sizeof(int*));
    for(int i=0;i<3;i++)
        no->estado[i] = (int *)malloc(3*sizeof(int));
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            no->estado[i][j] = empt;
    }
}

/* Marca no estado do no, na n-esima posicao livre o simbolo m
@param1 no
@param2 posicao
@param3 simbolo a ser marcado
*/ 
void mark(n *no, int i, int m){
    int n1,n2,n3,j=0,k=0,l=0;
    
    while(j!=i){
        if(no->estado[k][l] == empt){
            j++;
        }
        l++;
        if(l==3){
            k++;
            l=0;
        }
    }
    while(k<3){
        if(no->estado[k][l] == empt){
            no->estado[k][l] = m;
            break;
        }
        l++;
        if(l==3){
            k++;
            l=0;
        }
    }
}

// Imprime o estado do no
void print_grid(n *no){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            cout << no->estado[i][j] << " ";
        cout << endl;
    }
}

// Copy n1 state to n2 state
void copy_state(n *n1, n*n2){
    n2->estado = (int **)malloc(3*sizeof(int*));
    for(int i=0;i<3;i++){
        n2->estado[i]=(int*)malloc(3*sizeof(int));
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            n2->estado[i][j] = n1->estado[i][j];
        }
    }
}

// Libera o espaco de mem ocupado pela tree
void free_tree(n * no, int n){
    if(n==0){
        for(int j=0;j<3;j++){
            free(no->estado[j]);
        }
        free(no->estado);
        free(no);
        return;
    }

    for(int i=0; i<n; i++){
        if(no->filho[i]!= NULL)
            free_tree(no->filho[i],n-1);
    }
    for(int j=0;j<3;j++){
            free(no->estado[j]);
        }
        free(no->estado);
        free(no);
}

// Verifica se em dado estado teve um vencedor
int check_winner(n *no){
    //Checa linhas
    for(int i=0;i<3;i++){
        if((no->estado[i][0] == no->estado[i][1]) && (no->estado[i][1] == no->estado[i][2])){
            if(no->estado[i][0] == X)
                return 1;
            else 
                return -1;        
        }
    }
    //Checa colunas
    for(int i=0;i<3;i++){
        if((no->estado[0][i] == no->estado[1][i]) && (no->estado[1][i] == no->estado[2][i])){
            if(no->estado[0][i] == X)
                return 1;
            else 
                return -1;        
        }
    }
    //Checa diagonais
    if(((no->estado[0][0] == no->estado[1][1]) && (no->estado[1][1] == no->estado[2][2])) || ((no->estado[0][2] == no->estado[1][1]) && (no->estado[1][1] == no->estado[2][0]))){
        if(no->estado[1][1] == X)
            return 1;
        else 
            return -1;        
    }
    return 0;
}

//depth first recursivo
void minimax(n *no,int n){
    int min=2,max=2;
    
    if(n==1){
        //cout <<  << endl;
        no->v = check_winner(no->filho[0]);   
        //cout << no->v << endl;
        //cout << no->v << endl;
        return;
    }
    for(int i=0;i<n;i++){
        if(no->filho[i]->v == 2) 
            minimax(no->filho[i],n-1);
        //print_grid(no);
    }
    //max
    if(n%2 == 0){
        for(int i=0;i<n;i++){
            if(max==2){
                max=no->filho[i]->v;
            } else if(no->filho[i]->v == 1){
                max = 1;
                break;
            } else if(no->filho[i]->v > max){
                max = no->filho[i]->v;
            }
        }   
        no->v = max;
    } 
    // min 
    else{
        for(int i=0;i<n;i++){
            if(min==2){
                min=no->filho[i]->v;
            } else if(no->filho[i]->v == -1){
                min = -1;
                break;
            } else if(no->filho[i]->v < min){
                min = no->filho[i]->v;
            }
        }   
        no->v = min;
    }
    return;
}
void print_minimax(n* no,int n,int f){
    int l = 10-n;
    if(n==0){
        //cout << "l:" << l << " f:" << f << " v:" << no->v << endl;
        cout << "l:" << l << " v:" << no->v << endl;
        print_grid(no);
        return;
    }
    for(int i=0;i<n;i++){
        if(no->filho[i] != NULL)
            print_minimax(no->filho[i],n-1,i);
    }
    //cout << "l:" << l << " f:" << f << " v:" << no->v << endl;
    cout << "l:" << l << " v:" << no->v << endl;
    print_grid(no);
   
}
// p* init_pilha(){
//     p* pilha = (p*)malloc(sizeof(p));
//     pilha->topo = NULL;
//     pilha->prev = NULL;
// }
// void insere_p(n *no){

// }
 // if(j%2==0)
            //     x = X;
            // else
            //     x = O;  
            // aux->filho[j] = (n*)malloc(sizeof(n));
            // clear_state(r->filho[j]);
            // if(j<3)
            //     aux->filho[j]->estado[0][j] = x;
            // else if(j<6)
            //     aux->filho[j]->estado[1][j] = x;
            // else 
            //     aux->filho[j]->estado[2][j] = x; 