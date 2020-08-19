#ifndef SENHA_H
#define SENHA_H

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <prglib.h>
#include <fstream>

using prglib::arvore;
using prglib::lista;
using namespace std;

class Senha {
    
private:
    string senha; //senha utilizada nos métodos

public:
    Senha(string senha); //metodo construtor da senha
    string numerada(); //método de retirada de números do início e fim da palavra
    string inversa(); //método de inversão da palavra
    string estendida(); //método de correção da palavra, retirada de ".,;:!?<>(){}[]/=+-*&%$#@ "
    lista<string> rotacionada();  //método para rotacionar a palavra
    string substituida(); //método de substituir 3 por e, 5 por s, 0 por o, 4 por a e 1 por l
   
};
#endif /* SENHA_H */