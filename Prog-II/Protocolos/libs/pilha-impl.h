/* 
 * File:   pilha-impl.h
 * Author: msobral
 *
 * Created on 11 de Agosto de 2016, 13:59
 */

#ifndef PILHA_IMPL_H
#define	PILHA_IMPL_H

#include "pilha.h"


namespace prglib {
    
template <typename T> pilha<T>::pilha(unsigned int umaCapacidade) : N(umaCapacidade){
}
 
template <typename T> pilha<T>::pilha(const pilha& outra) : std::stack<T>(outra) {
  N = outra.N;
}
 
template <typename T> pilha<T>::~pilha() {
}

template <typename T> pilha<T> & pilha<T>::operator=(const pilha<T> & outra) {
  N = outra.N;
  esvazia();
  pilha<T> aux(outra);
  pilha<T> aux2(outra.N);
  while (not aux.vazia()) aux2.push(aux.pop());
  while (not aux2.vazia()) push(aux2.pop());
}
 
template <typename T> void pilha<T>::esvazia() {
    while (this->size() > 0) static_cast<std::stack<T>*>(this)->pop();
}
 
template <typename T> void pilha<T>::push(const T & dado) {
    if (cheia()) throw -1;
    static_cast<std::stack<T>*>(this)->push(dado);
}
 
template <typename T> T pilha<T>::pop() {
  if (vazia()) throw -1;
  T dado = static_cast<std::stack<T>*>(this)->top();
  static_cast<std::stack<T>*>(this)->pop();
  return dado;
}
 
template <typename T> const T& pilha<T>::top() const{
  if (vazia()) throw -1;
  return static_cast<const std::stack<T>*>(this)->top();
}

template <typename T> unsigned int pilha<T>::capacidade() const {
    return N;
}

template <typename T> bool pilha<T>::cheia() const {
    return this->size() == N;
}

template <typename T> bool pilha<T>::vazia() const {
    return this->empty();
}

template <typename T> unsigned int pilha<T>::comprimento() const {
    return this->size();
}

template <typename T> void pilha<T>::expande(unsigned int N) {
    this->N = N;
}

}

#endif	/* PILHA_IMPL_H */

