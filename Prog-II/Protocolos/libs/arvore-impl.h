/* 
 * File:   arvore-impl.h
 * Author: sobral
 *
 * Created on 8 de Outubro de 2016, 19:37
 */

#ifndef ARVORE_IMPL_H
#define	ARVORE_IMPL_H
#include <string>
#include "arvore.h"
#include "lista.h"
 
using std::string;

namespace prglib {

template <typename T> arvore<T>::~arvore() {    
}
    
template <typename T> arvore<T>::arvore() {    
}

template <typename T> arvore<T>::arvore(const T & dado) {
    data = dado;
    esq = nullptr;
    dir = nullptr;
}

//template <typename T> arvore<T>::arvore(const arvore<T> & outra) : BasicTree(outra) {}

template <typename T> void arvore<T>::adiciona(const T & algo) {
    arvore<T> *atual = this;
    
    while(true){ //laço de repetição para adicionar algo
        if (algo == atual->data){ //caso algo seja igual a qualquer dado ja armazenado na árvore
            atual->data = algo;
            break; //termina o laço
        }
        if(algo < atual->data){ //caso algo seja menor do que data
            if(atual->esq) atual = atual->esq; //se atual ja existir ele irá percorrer todo até não existir
            else{
                atual->esq = new arvore<T>(algo); //criação de um novo nodo a aponta para esquerda
                break; //termina o laço
            }
        } else{ //caso aldo seja maior que data
            if(atual->dir) atual = atual->dir; //se atual->dir ja existir ele irá percorrer todo até não existir
            else{
                atual->dir = new arvore<T>(algo);
                break; //termina o laço
            }
        }
    }
}

template <typename T> T& arvore<T>::obtem(const T & algo) {
    //metodo recursivo
    if(data == algo) return data; //se achar algo na árvore retorna data
    
    if(data < algo){ //buscando e percorrendo a árvore atrás de algo
        if(dir) dir->obtem(algo); //invocação do método recursivo obtem para o ponteiro da direita
        else throw -1; //caso não exista o dado na árvore;
    }else { //buscando e percorrendo a árvore atrás de algo
        if(esq) esq->obtem(algo); //invocação do método recursivo obtem para o ponteiro da esquerda
        else throw -1;
    }
   
    //metodo normal
    /*arvore<T> *atual = this;
    
    while(true){
        if(atual->data == algo) return atual->data; //se achar algo na árvore retorna data
        
        if(algo < atual->data){ //percorrendo a árvore atrás de algo
            if(atual->esq == nullptr) throw -1; //caso não ache algo na árvore
     else atual = atual->esq; //procurando em novo nodo, lado esquerdo
        }else{
            if(atual->dir == nullptr) throw -1; //caso não ache algo na árvore
     else atual = atual->dir; //procurando em novo nodo, lado direito
        }
    }*/
}

template <typename T> void arvore<T>::listeEmLargura(lista<T> & result) {
    //visitam-se nodos cada nível por vez, da esquerda pra direita
    arvore<T> *atual;
    lista<arvore<T>*> l;
    l.anexa(this);
    
    while(!l.vazia()){
        atual = l.remove(0);
        result.anexa(atual->data);
        if(atual->esq) l.anexa(atual->esq);
        if(atual->dir) l.anexa(atual->dir);
    }
}

template <typename T> void arvore<T>::listeInOrder(lista<T> & result) {
    //sequência esquerda, raiz, direita.
   /* if(esq) esq->listeInOrder(result);
    result.anexa(data);
    if(dir) dir->listeInOrder(result);*/
    
    arvore<T> *atual=this;
    lista<arvore<T>*>l;
    
    while(atual){
        l.insere(atual);
        atual = atual->esq;
    }
    
    while(!l.vazia()){
        atual = l.remove(0);
        result.anexa(atual->data);
        
        if(atual->dir){
            atual = atual->dir;
            while(atual){
                l.insere(atual);
                atual = atual->esq;
            }
        }
    }
}

template <typename T> void arvore<T>::listePreOrder(lista<T> & result) {
    //sequência raiz, esquerda, direita.
    //mesmo do em largura muda insere e ordem esq e dir
   /* result.anexa(data);
    if(esq) esq->listePreOrder(result);
    if(dir) dir->listePreOrder(result);*/
    
    arvore<T> *atual;
    lista<arvore<T>*> l;
    l.anexa(this);
    
    while(!l.vazia()){
        atual = l.remove(0);
        result.anexa(atual->data);
        
        if(atual->dir) l.insere(atual->dir);
        if(atual->esq) l.insere(atual->esq);
    }
}

template <typename T> void arvore<T>::listePostOrder(lista<T> & result) {
    //sequência esquerda, direita, raiz.
    if(esq) esq->listePostOrder(result);
    if(dir) dir->listePostOrder(result);
    result.anexa(data);
}

template <typename T> unsigned int arvore<T>::tamanho() const {
    int size=1;
    
    if(esq) size = size + esq->tamanho();
    if(dir) size = size + dir->tamanho();
    
    return size;
}

template <typename T> int arvore<T>::fatorB()  {
    arvore<T> *atual = this;
    int direita=0, esquerda=0;
    
    if(dir) direita = 1 + dir->altura();
    if(esq) esquerda = 1 + esq->altura();
   
    return (esquerda - direita);
}

template <typename T> unsigned int arvore<T>::altura()  {
    int altura_dir=0, altura_esq=0;

    if(esq) altura_esq = 1 + esq->altura();
    if(dir) altura_dir = 1+ dir->altura();
    
    if(altura_dir > altura_esq) return altura_dir;
    else return altura_esq;   
}

template <typename T> arvore<T>* arvore<T>::balanceia() {
    arvore<T> *atual = this;
    
    if(esq) atual->esq = atual->esq->balanceia(); //metodo resurcivo para verificar nodos
    if(dir) atual->dir = atual->dir->balanceia();
    
    while(atual->fatorB()<-1){ //caso arvore esteja desbalanceada para direita
        if(atual->dir->fatorB() > 0)atual->dir = atual->dir->rotacionaR(); //verificação se nodo direito está balanceado
        atual = atual->rotacionaL(); //rotaciona para esquerda
    }
    while(atual->fatorB()>1){ //caso arvore esteja desbalanceada para esquerda
        if(atual->esq->fatorB() < 0) atual->esq = atual->esq->rotacionaL(); //verificação se nodo esquerdo está balanceado
        atual = atual->rotacionaR(); //rotaciona para direita
    }
    
    return atual;
}

template <typename T> arvore<T>* arvore<T>::balanceia(bool otimo){
    arvore<T> *atual=this;
    
    int antes=0, depois=0;
   
    antes = atual->altura();
    
    if(otimo == false){
        atual = atual->balanceia();
        return atual;
    } 

    while(antes != depois){
        antes = atual->altura();
        atual = atual->balanceia();
        depois = atual->altura();
    }
    return atual;
}

template <typename T> void arvore<T>::inicia() {
   /* stack.esvazia();
    stack.insere(this);
   */
    arvore<T> *atual=this;
        
    if(atual){
        stack.anexa(atual);
        atual = atual->esq;
    }
}

template <typename T> T& arvore<T>::proximo() {
 /*   auto atual = stack.remove(0);
    if(atual->dir) stack.insere(atual->dir);
    if(atual->esq) stack.insere(atual->esq);
    return atual->data;*/
 
    auto atual = stack.remove(0);
    
    T & a = atual->data;
         
    if(atual->dir) stack.insere(atual->dir);
    if(atual->esq) stack.insere(atual->esq);
    
    return a;
}

template <typename T> bool arvore<T>::fim() {
    return stack.vazia();
}

template <typename T> const T& arvore<T>::obtemMenor(){
    arvore<T> *atual = this;

    while(atual->esq) atual = atual->esq;
    return atual->data;  
}

template <typename T> const T& arvore<T>::obtemMaior(){
    arvore<T> *atual = this;
    
    while(atual->dir) atual = atual->dir;
    return atual->data;
}

template <typename T> void arvore<T>::obtemMenoresQue(lista<T> & result, const T & algo) {
    if(data <= algo) result.anexa(data);
    if(dir) dir->obtemMenoresQue(result, algo);
    if(esq) esq->obtemMenoresQue(result, algo);
}

template <typename T> void arvore<T>::obtemMaioresQue(lista<T> & result, const T & algo) {
    if(data >= algo) result.anexa(data);
    if(dir) dir->obtemMaioresQue(result, algo);
    if(esq) esq->obtemMaioresQue(result, algo);
}

template <typename T> void arvore<T>::obtemIntervalo(lista<T>& result, const T& start, const T& end) {
    if((data >= start)&&(data <= end)) result.anexa(data);
    if(esq) esq->obtemIntervalo(result, start, end);
    if(dir) dir->obtemIntervalo(result, start, end);
}

template <typename T> void arvore<T>::escrevaSe(ostream& out) const {
    static int nivel = -1;
    string prefixo;
 
    nivel++;
    prefixo.append(nivel, ' ');
 
    if (dir) dir->escrevaSe(out);
    out << prefixo << data << std::endl;
    if (esq) esq->escrevaSe(out);
    nivel--;
}

template <typename T> arvore<T>* arvore<T>::rotacionaL(){
    
    arvore<T> * n2  = this;
    arvore<T> * n1 = dir;
    arvore<T> * nb = n1->esq;
    
    n2->dir = nb;
    n1->esq = n2;
    
    return n1;
}

template <typename T> arvore<T>* arvore<T>::rotacionaR(){
    
    arvore<T> *n2 = this;
    arvore<T> *n1 = esq;
    arvore<T> *nb = n1->dir;
    
    n2->esq = nb;
    n1->dir = n2;
    
    return n1;
}

template <typename T> T arvore<T>::obtem_sucessor(const T & algo) {
    
    arvore<T> *atual = this;
    
    while(atual){
        if(atual->data==algo){
            atual = atual->dir;
            return atual->data;
        }
        else if(algo>atual->data) atual = atual->dir;
        else{
            T a = atual->data;
            atual = atual->esq;
            if(atual->dir==nullptr) return a;
        }
    }
}

template <typename T> arvore<T> * arvore<T>::subarvore(const T & algo) {
    arvore<T> *atual = this;
    lista<T>l;

    while(atual){
        if(atual->data==algo){
            atual->listePreOrder(l);
            break;
        }
        if(algo<atual->data) atual = atual->esq;
        else atual = atual->dir;
    }
    if(l.comprimento()==0) return nullptr;
    l.inicia();
    arvore<T> *arv = new arvore<T>(l.proximo());
    while(!l.fim()){
         arv->adiciona(l.proximo());
    }
    return arv;
}

template <typename T> arvore<T> * arvore<T>::obtemMaioresQue(const T & algo) {
    
    
    
}

};

#endif	/* ARVORE_IMPL_H */

