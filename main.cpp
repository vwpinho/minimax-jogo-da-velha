#include <iostream>
#include <stdlib.h>

#define O 1
#define X 2
#define empt 0

using namespace std;
typedef struct Node{
    int **estado;
    struct Node * filho[9];
    int v;
}n;

n * init_tree();
void fill_tree(n *r);
void clear_state(n *no);
void mark(n *no, int i, int m);
void print_grid(n *no);
void copy_state(n *n1, n*n2);
void free_tree(n * no,int n);


int main(){
    n *raiz = init_tree();
    fill_tree(raiz);
    free_tree(raiz,9);
    return 0;
}


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
void fill_tree(n *r){
    n * aux[9];
    int x;
    aux[0] = r;
    for(int i=0;i<9;i++){
        //cout << "test1" << endl;
        aux[0]->filho[i] = (n*) malloc(sizeof(n));
        aux[1] = aux[0]->filho[i];
        clear_state(aux[1]);
        mark(aux[1],i,X);
        print_grid(aux[1]);
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
                        for(int o=0;o<4;o++){
                            //cout << "test6" << endl;
                            aux[5]->filho[o] = (n*) malloc(sizeof(n));
                            aux[6] = aux[5]->filho[o];
                            copy_state(aux[5],aux[6]);
                            mark(aux[6],o,O);
                            for(int p=0;p<3;p++){
                                //cout << "test7" << endl;
                                aux[6]->filho[p] = (n*) malloc(sizeof(n));
                                aux[7] = aux[6]->filho[p];
                                copy_state(aux[6],aux[7]);
                                mark(aux[7],p,X);
                                for(int q=0;q<2;q++){
                                    //cout << "test8" << endl;
                                    aux[7]->filho[q] = (n*) malloc(sizeof(n));
                                    aux[8] = aux[7]->filho[q];
                                    copy_state(aux[7],aux[8]);
                                    mark(aux[8],q,O);
                                    mark(aux[8],1,X);
                                }
                            }
                        }
                    }
                }
            }
           
        }

    }
}
void clear_state(n *no){
    no->estado = (int**) malloc(3*sizeof(int*));
    for(int i=0;i<3;i++)
        no->estado[i] = (int *)malloc(3*sizeof(int));
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            no->estado[i][j] = empt;
    }
}
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

void free_tree(n * no, int n){
    if(n=0)
        return;
    for(int i=0; i<n; i++){
        free_tree(no->filho[i],n-1);
        for(int j=0;j<3;j++){
            free(no->estado[j]);
        }
        free(no->estado);
        free(no);
    }
}
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