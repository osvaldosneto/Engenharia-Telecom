#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <prglib.h>

using prglib::pilha;
using prglib::fila;
using namespace std;

class Calculadora{
   
public:
   
    Calculadora(int tam);
    void armazena(double numero);//armazena numeros
    void soma();//calculadora soma dois ultimos numeros
    void sub();//calculadora subtrai dois ultimos numeros
    void multiplica();//calculadora multiplica dois ultimos numeros
    void divide();//calculadora divide dois ultimos numeros
    double ultimo_operando();//calculadora retorna ultimo operando
    string todos_operandos();//calculadora mostra todos os operandos armazenados
    void todos_operandos_excluidos();//calculadora limpa memória
    void substitui_num_primo();//calculadora substitui o ultimo numero pelo primeiro número primo de menor valor
    
  private:
    
  pilha<double> p;//construtor de pilha para uso da calculadora
};
#endif