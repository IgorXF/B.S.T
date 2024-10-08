#include <iostream>

using namespace std;


struct arvore{
    int item;
    arvore *pai;
    arvore *esquerda;
    arvore *direita;
};

arvore* construir_no(int x, arvore* pai) {
    arvore *novo_no = new arvore;
    novo_no->item = x;
    novo_no->esquerda = novo_no->direita = NULL;
    novo_no->pai = pai;
    return novo_no;
}

void inserir(arvore **l, int valor, arvore* pai){
    if(*l == nullptr){
        *l = construir_no(valor, pai);
        return;
    }

    if(valor < (*l)->item){
        inserir(&((*l)->esquerda), valor, *l);
    } else
        inserir(&((*l)->direita), valor, *l);
}

void imprimir_item(int item){
    cout<< item << endl;
}

void em_Ordem(arvore *l){
    if(l != NULL){
        em_Ordem(l->esquerda);
        imprimir_item(l->item);
        em_Ordem(l->direita);
    }
}

void pre_Ordem(arvore *l) {
    if(l != NULL) {
        imprimir_item(l->item); // Processa o nó atual
        pre_Ordem(l->esquerda);  // Visita a subárvore esquerda
        pre_Ordem(l->direita);   // Visita a subárvore direita
    }
}

void pos_Ordem(arvore *l) {
    if(l != NULL) {
        pos_Ordem(l->esquerda);  // Visita a subárvore esquerda
        pos_Ordem(l->direita);   // Visita a subárvore direita
        imprimir_item(l->item); // Processa o nó atual
    }
}

arvore* buscar_no(arvore *l, int valor){
    if(l == NULL){
        return NULL;
    } else if((l->item) == valor){
        return l;
    } else if(valor < (l->item)){
        return buscar_no(l->esquerda, valor);
    } else {
        return buscar_no(l->direita, valor);
    }
}

arvore* buscar_min(arvore* t){
    arvore* minimo = t;
    while (minimo && minimo->esquerda != NULL){
        minimo = minimo->esquerda;
    }
    return minimo;
}

void remover_no(arvore **l, int valor){
    arvore* remover = buscar_no(*l, valor);

    if (remover == NULL) {
        cout << "Elemento nao encontrado na arvore." << endl;
        return;
    }
    
    else if(remover->esquerda == NULL && remover->direita == NULL){ // caso 1: num tem fio
        if(remover->pai == NULL){
            *l = NULL; //removendo a raiz e unico nó da arvore
        } else if(remover->pai->esquerda == remover){
            remover->pai->esquerda = NULL; //removendo filho a esquerda
        } else if(remover->pai->direita == remover){
            remover->pai->direita = NULL; //removendo filho a direita
        }
        delete remover;
    } else if(remover->esquerda == NULL ||  remover->direita == NULL){ //caso 2: tem um fio
        arvore *filho;
        if (remover->esquerda != NULL) { // Nó com filho à esquerda
            filho = remover->esquerda;
        } else { // Nó com filho à direita
            filho = remover->direita;
        }

        if(remover->pai == NULL){
            *l = filho; // removendo a raiz
        }else if(remover->pai->esquerda == remover){ //verifica se o removido ta a esquerda do pai
            remover->pai->esquerda = filho; //pai aponta para o fi do removido nesse caso e o fi a esquerda
        }else {
            remover->pai->direita = filho;//pai aponta para o fi do removido nesse caso e o fi a direita
        }

        if(filho != NULL){
            filho->pai = remover->pai; //o fi que era do removido agora é fi do pai do removido então o fi precisa apontar pro seu novo pai, que era pai do removido
        }
        delete remover; //joga essa praga fora
    } else { //caso 3: tem 2 fi (quando é assim a gente pega o elemento minimo da subArvore a direita do removido)
        arvore *sucessor = buscar_min(remover->direita); //pegando o elemento minimo a direita do removido
        remover->item = sucessor->item;// agora o item do removido 'não é mais o valor que queriamos remover, é o item do sucessor
        remover_no(&(remover->direita), sucessor->item); //chama a funçao dnv p remover o sucessor q ta na arvore 2x
    }
}

int main() {
    arvore* t = NULL;
    inserir(&t, 10, NULL);
    inserir(&t, 5, NULL);
    inserir(&t, 15, NULL);
    inserir(&t, 2, NULL);
    inserir(&t, 7, NULL);
    inserir(&t, 12, NULL);
    inserir(&t, 18, NULL);
    inserir(&t, 1, NULL);
    inserir(&t, 3, NULL);
    inserir(&t, 6, NULL);
    inserir(&t, 8, NULL);
    inserir(&t, 11, NULL);
    inserir(&t, 13, NULL);
    inserir(&t, 17, NULL);
    inserir(&t, 20, NULL);

    cout << "Arvore antes da remocao:" << endl;
    em_Ordem(t);

    remover_no(&t, 2);

    cout << "\nArvore apos a remocao de 2:" << endl;
    em_Ordem(t);

    return 0;
}
