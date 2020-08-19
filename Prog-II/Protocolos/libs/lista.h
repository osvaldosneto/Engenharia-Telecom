/* 
 * File:   lista.h
 * Author: msobral
 *
 * Created on 11 de Agosto de 2016, 08:56
 */

#ifndef LISTA2_H
#define	LISTA2_H

#include <cstddef>
#include <ostream>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <memory>
#include <time.h>

namespace prglib {

template <typename T> class lista {
 
 public:
  //construtor: não precisa de parâmetros para criar uma nova lista
  lista();
 
  // construtor de cópia
  lista(const lista &outra);
 
  // destrutor
  ~lista();
 
  // insere "algo" no inicio da lista
  void insere(const T & algo);
 
  // adiciona "algo" no final da lista
  void anexa(const T & algo);
 
  // insere "algo" em uma posição específica da lista  
  void insere(const T & algo, int posicao);
  void insereOrdenado(const T & algo);
 
  // remove o dado que está na "posicao" na lista, e retorna 
  // uma cópia desse dado
  T remove(int posicao);
 
  // remove todos os dados que forem equivalentes a "algo"
  void retira(const T & algo);
  void multiplos();
 
  // estas duas operações são idênticas: retorna
  // uma referência ao dado que está na "posicao" na lista
  T& obtem(int posicao) const;
  T& operator[](int pos) const;
 
  // atribuição: torna esta lista idêntica à outra lista
  lista& operator=(const lista<T> & outra);
 
  // compara duas listas: são iguais se tiverem mesmo comprimento
  // E todos os dados armazenados forem iguais e na mesma ordem
  bool operator==(const lista<T> & outra) const;
 
  // Retorna uma referência a um dado que seja equivalente a "algo"
  T& procura(const T &algo) const; 
 
  // Procura todos os dados equivalentes a "algo", e os
  // anexa a "lista". Retorna uma referência a "lista".
  std::shared_ptr<lista<T>> procuraMuitos(const T &algo) const;
  lista<T> & procuraMuitos(const T &algo, lista<T> & lista) const;
 
  // retorna a quantidade de dados armazenados na lista
  int comprimento() const;
 
  // retorna true se lista estiver vazia
  bool vazia() const;
 
  // Esvazia a lista
  void esvazia();
 
  // apresenta o conteúdo da lista no stream "out"
  void escrevaSe(std::ostream & out) const;
  void escrevaSe(std::ostream & out, const std::string & delim) const;
 
  // ordena a lista
  void ordena();
  void ordenaBolha();
 
  // iteração
  void inicia();
  void iniciaPeloFim();
  bool fim() const;
  bool inicio() const;
  T & proximo();
  T & anterior();
 
  // inverte a ordem dos dados da lista
  void inverte();
 
  // embaralha os dados de uma lista
  void embaralha();
 
  
  int trunca(int posicao);
  void mistura(lista<T> & outra);
  void insere(const lista<T> & dados, int posicao);
  
  
  
  // obtém uma sublista
  lista<T> * sublista(unsigned int pos1, unsigned int pos2) const;
  lista<T> & sublista(unsigned int pos1, unsigned int pos2, lista<T> & outra) const;
 
 private:
  // declaração do tipo Nodo: privativa, porque 
  // é de uso exclusivo da lista
  // Este Nodo visa uma lista duplamente encadeada
  struct Nodo {
    Nodo * proximo, * anterior;
    T dado;
 
    // construtor do Nodo: prático para uso nos métodos
    // da lista
    Nodo(const T & algo) {
      dado = algo;
      proximo = nullptr;
      anterior = nullptr;
    }
  };
 
  // ponteiros para primeiro e último nodos
  Nodo * primeiro, * ultimo;
 
  // ponteiro para nodo atual da iteração
  Nodo * atual;
 
  // comprimento da lista
  long len;
};

} // fim do namespace

#include <libs/lista-impl.h>

#endif	/* LISTA_H */

