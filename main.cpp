#include <iostream>
#include <stdlib.h>

#define O 1
#define X 2
#define empt 0

using namespace std;
typedef struct Node{
    int **estado;
    struct Node * filho[9];
}n;

n * init_tree();
int main(){
    n *raiz = init_tree();

    return 0;
}
n * init_tree(){
    n * t;
    t = (n*)malloc(1*sizeof(n));

    t->estado = (int **)malloc(3*sizeof(int*));
    for(int i=0;i<3;i++)
        t->estado[i] = (int *)malloc(3*sizeof(int));
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            t->estado[i][j] = empt;
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            cout << t->estado[i][j] << " ";
        cout << endl;
    }
    for(int i=0; i<9;i++)
        t->filho[i] = NULL;
    return t;
}