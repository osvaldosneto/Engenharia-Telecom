/* 
 * File:   fila-imp.h
 * Author: msobral
 *
 * Created on 11 de Agosto de 2016, 13:59
 */

#ifndef FILA_IMP_H
#define	FILA_IMP_H

namespace prglib {
    
template <typename T> fila<T>::fila(unsigned int N) : N(N){
}

template <typename T> fila<T>::fila(const fila& orig) {
    *this = orig;
}

template <typename T> fila<T>::~fila() {
}

template <typename T> fila<T>& fila<T>::operator=(const fila& outra) {
    N = outra.N;
    static_cast<std::queue<T>*>(this)->operator=(outra);
    return *this;
}

template <typename T> void fila<T>::enfileira(const T& algo) {
    if (this->size() == N) throw -1;
    this->push(algo);
}

template <typename T> T fila<T>::desenfileira() {
    if (this->size() == 0) throw -1;
    T dado = this->front();
    this->pop();
    return dado;
}

template <typename T> const T & fila<T>::frente() const {
    if (this->size() > 0) return this->front();
    throw -1;
}

template <typename T> bool fila<T>::vazia() const {
    return this->empty();
}

template <typename T> bool fila<T>::cheia() const {
    return this->size() == N;
}

template <typename T> unsigned int fila<T>::capacidade() const {
    return N;
}

template <typename T> unsigned int fila<T>::comprimento() const {
    return this->size();
}

template <typename T> void fila<T>::expande(unsigned int N) {
    this->N = N;
}

template <typename T> void fila<T>::esvazia() {
    while (this->size() > 0) static_cast<std::queue<T>*>(this)->pop();
}

} // fim namespace

#endif	/* FILA_IMP_H */

