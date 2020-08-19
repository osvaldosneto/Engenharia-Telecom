#ifndef VERIFICADOR_H
#define VERIFICADOR_H

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <prglib.h>
#include <fstream>

using prglib::arvore;
using prglib::lista;
using namespace std;

class Verificador{
    
public:
   
    Verificador(string opcao); //método construtor da árvore
    int Verifica(string senha); //método verificador na árvore
    
private:
    
    arvore <string> *a; //arvore
    
};
#endif