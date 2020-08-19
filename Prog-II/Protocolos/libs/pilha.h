/* 
 * File:   pilha.h
 * Author: msobral
 *
 * Created on 11 de Agosto de 2016, 13:59
 */

#ifndef PILHA_H
#define	PILHA_H

#include <cstdlib>
#include <stack>

namespace prglib {
    
template <typename T> class pilha : private std::stack<T> {
 public:
  // construtor: deve-se informar a capacidade da pilha
  pilha(unsigned int umaCapacidade);
 
  // construtor de cópia: cria uma pilha que é cópia de outra
  pilha(const pilha<T>& outra);
 
  // destrutor da pilha
  ~pilha();
 
  // operador de atribuição: torna esta pilha uma cópia de outra pilha
  pilha<T> & operator=(const pilha<T> & outra);
 
  // operações da pilha
 
  virtual void push(const T & dado); // empilha um dado
 
  T pop(); // desempilha um dado
 
  virtual const T& top() const; // retorna o dado do topo da pilha, sem retirá-lo

  // remove todos os dados da pilha
  void esvazia();
  
  bool vazia() const;
  bool cheia() const;
  unsigned int comprimento() const;
  unsigned int capacidade() const;
  
  void expande(unsigned int N);
 private:
  unsigned int N;
};

} // fim do namespace

#include <libs/pilha-impl.h>

#endif	/* PILHA_H */

