#include "Calculadora.h"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <prglib.h>

using prglib::pilha;
using prglib::fila;
using namespace std;

const int tam = 1000;

Calculadora::Calculadora(int tam) : p(tam){
}
//armazena numeros
void Calculadora::armazena(double numero){
    p.push(numero);
}
//calculadora soma dois ultimos numeros
void Calculadora::soma(){
    double n1, n2, n3;
    
    n1 = p.pop();
    n2 = p.pop();
    n3 = n1 + n2;
    p.push(n3);
}
//calculadora subtrai dois ultimos numeros
void Calculadora::sub(){
    double n1, n2, n3;
    
    n1 = p.pop();
    n2 = p.pop();
    n3 = n2 - n1;
    p.push(n3);
}
//calculadora multiplica dois ultimos numeros
void Calculadora::multiplica(){
    double n1, n2, n3;
    
    n1 = p.pop();
    n2 = p.pop();
    n3 = n2 * n1;
    p.push(n3);
}
//calculadora divide dois ultimos numeros
void Calculadora::divide(){
    double n1, n2, n3;
    
    n1 = p.pop();
    n2 = p.pop();
    n3 = n2 / n1;
    p.push(n3);
}
//calculadora retorna ultimo operando
double Calculadora::ultimo_operando(){
    double n;
    
    n = p.pop();
    p.push(n);
    return n;
}
//calculadora mostra todos os operandos armazenados
string Calculadora::todos_operandos(){

    fila<double> f(p.comprimento());
    pilha<double> p2(p);
    pilha<double> p3(p2.comprimento());
    string n;
    while(not p2.vazia()){
        p3.push(p2.pop());
    }
    while(not p3.vazia()){
        f.enfileira(p3.pop());
    }
    while(not f.vazia()){
        n = n + " " +  to_string(f.desenfileira());
    }
    return n;
}
//calculadora limpa memória
void Calculadora::todos_operandos_excluidos(){
    p.esvazia();   
}
//calculadora substitui o ultimo numero pelo primeiro número primo de menor valor
void Calculadora::substitui_num_primo(){
    fila<double> fil1(10000);
    fila<double> primos(10000);
    
    int ultimo_numero = p.pop();
    int resto, divisor, dividendo, r, i, n, tam, aux;
    
    r = sqrt(ultimo_numero);
    
    for(i=2; i<=ultimo_numero; i++){
        fil1.enfileira(i);
    }
   
    for (n=0; n<r; n++){
  
        divisor = fil1.desenfileira();
        tam = fil1.comprimento();
        
        for (i=0; i<tam; i++){
                        
            dividendo = fil1.frente();
            resto = dividendo%divisor;
            if (resto!=0){
                fil1.desenfileira();
                fil1.enfileira(dividendo);
            }
            else{
                fil1.desenfileira();
            }
        }
        fil1.enfileira(divisor);
    }
    
    tam = fil1.comprimento();
 
    for (i=n; i<tam; i++){
        aux = fil1.desenfileira();
        fil1.enfileira(aux);
    }
    
    for (i=0; i<tam ; i++){
        aux = fil1.desenfileira();
        primos.enfileira(aux);
    }
    
    tam = primos.comprimento();
    
    for (i=0; i<tam-1; i++){
        aux=primos.desenfileira();
    }
   
    aux = primos.desenfileira();
    p.push(aux);
}