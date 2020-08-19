#include "Calculadora.h"
#include <iostream>
#include <string>
#include <prglib.h>

using prglib::pilha;
using prglib::fila;
using namespace std;

int main(int argc, char** argv) {

    Calculadora calc(1000);
    string comando;
    
    
    while(true){
        
        cout<< ">";
        cin >> comando;
                  
        while(true){
            //calculadora retorna ultimo operando
            if(comando == "!"){
                cout << calc.ultimo_operando() << endl;
                break;
            }
            //calculadora mostra todos os operandos armazenados
            else if(comando == "?"){
                cout << calc.todos_operandos() << endl;
                break;
            }
            //calculadora limpa memória
            else if(comando == "z"){
                calc.todos_operandos_excluidos();
                break;
            }
            //calculadora substitui o ultimo numero pelo primeiro número primo de menor valor
            else if(comando == "p"){
                calc.substitui_num_primo();
                break;
            }
            //calculadora soma dois ultimos numeros
            else if(comando == "+"){
                calc.soma();    
                break;
            }
            //calculadora subtrai dois ultimos numeros
            else if(comando == "-"){
                calc.sub();
                break;
            }
            //calculadora divide dois ultimos numeros
            else if(comando == "/"){
                calc.divide();
                break;
            }
            //calculadora multiplica dois ultimos numeros
            else if(comando == "*"){
                calc.multiplica();
                break;
            }
            //armazena numeros
            else  {
                double numero;
                numero = stod(comando);
                calc.armazena(numero);
                break;
            }
        }
    }
    return 0;
}