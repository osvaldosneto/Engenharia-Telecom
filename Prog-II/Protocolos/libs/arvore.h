/* 
 * File:   arvore.h
 * Author: msobral
 *
 * Created on 12 de Agosto de 2016, 13:12
 */

#ifndef ARVORE_H
#define	ARVORE_H
#include <ostream>

using std::ostream;

namespace prglib {
    
template <typename T> class arvore {
 public:
  arvore();
  //arvore(const arvore<T> & outra);
  arvore(const T & dado);
  ~arvore();

  void adiciona(const T& algo);
  T& obtem(const T & algo);
  void listeInOrder(lista<T> & result);
  void listePreOrder(lista<T> & result);
  void listePostOrder(lista<T> & result);
  void listeEmLargura(lista<T> & result);
  unsigned int tamanho() const;  
  unsigned int altura() ;
  int fatorB() ;
  arvore<T> * balanceia();
  arvore<T> * balanceia(bool otimo);
  
  void inicia();
  bool fim();
  T& proximo();

  void iniciaPeloFim();
  bool inicio();
  T& anterior();
  
  arvore<T> * rotacionaL();     
  arvore<T> * rotacionaR();   
  
  T remove(const T & algo);
  const T& obtemMenor();
  const T& obtemMaior();
  
  
  // obtém o sucessor de algo
  T obtem_sucessor(const T & algo);
  
  
  arvore<T> * subarvore(const T & algo);
  arvore<T> * obtemMaioresQue(const T & algo);
  
  void escrevaSe(ostream & out) const;
  
  void obtemMenoresQue(lista<T> & result, const T & algo);
  void obtemMaioresQue(lista<T> & result, const T & algo);

  // obtém todos valores entre "start" e "end" (inclusive)
  void obtemIntervalo(lista<T> & result, const T & start, const T & end);
  protected:
    T data;
    arvore<T> * esq, * dir;
    lista<arvore<T>*> stack;
     
   // arvore<T> * rotacionaL();     
   // arvore<T> * rotacionaR();     
};

} // fim do namespace

#include <libs/arvore-impl.h>

#endif	/* ARVORE_H */

