/* 
 * File:   hash.h
 * Author: msobral
 *
 * Created on 11 de Agosto de 2016, 13:59
 */

#ifndef HASH_H
#define	HASH_H

#include <unordered_map>
#include <string>
#include <libs/lista.h>
#include <memory>

namespace prglib {

template <typename T> class thash : private std::unordered_map<std::string,T> {
 public:
  // cria uma tabela hash com num_linhas linhas
  thash(int num_linhas);
 
  thash(const thash &outra); // construtor de copia
 
  // destrutor
  virtual ~thash();
 
  // adiciona um dado à tabela. Se já existir na tabela um par contendo a chave
  // "chave", o dado desse par deve ser substituído por "algo". Caso contrário,
  // um novo par deve ser adicionado à tabela.
  void adiciona(const std::string& chave, const T& algo);
 
  // remove a chave "chave" e o dado a ela associado.
  T remove(const std::string& chave);
 
  // retorna o dado associado a "chave"
  T& operator[](const std::string& chave);
  T& obtem(const std::string& chave);
 
  // retorna uma lista com as chaves existentes na tabela
  std::shared_ptr<lista<std::string>> chaves() const;
 
  // retorna uma lista com os dados existentes na tabela
  std::shared_ptr<lista<T>> valores() const;
 
  // retorna verdadeiro se "chave" existe na tabela
  bool existe(const std::string& chave) const;
 
  // esvazia a tabela
  void esvazia();
 
  // retorna a quantidade de dados (ou chaves) existentes na tabela
  unsigned int tamanho() const;
 
 private:
  unsigned int linhas; // a quantidade de linhas da tabela
};

}

#include <libs/hash-impl.h>

#endif	/* HASH_H */

