#ifndef ANALISADOR_H
#define ANALISADOR_H

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <prglib.h>

using prglib::pilha;
using prglib::thash;
using namespace std;
//classe analisador
class Analisador{
 
private:
       
    struct Dados{ //struct reservada para Dados
        string hora_inicio;
        string hora_fim;
        string endereco_origem;
        string IP_origem;
        string endereco_destino;
        string flags;
        string comprimento;
        int pacotes=0;
        int inicio_este=0;
        int inicio_outro=0;
        string fim;
    };
    
    string IP;
    string arquivo;
    thash<Dados>tab;
    struct Dados dados;

public:
      
    Analisador(); //construtor de tabela hash
    void extract(string arquivo, string IP); //metodo para extração de dados que por sua vez serão colocados em um struct
    string cria_chaves(struct Dados dados); //metodo para criação das chaves
    void cria_tabela(string chave, struct Dados dados); //metodo criação da tabela de struct dados
    string duracao (string hr_inicio, string hr_fim); //metodo calculo da diferença entre termino e inicio de comunicação
    string comprimento(string comprimento); //metodo calculo para comprimento da comunicação em bytes
    void imprime_tabela(string IP); //metodo para impressão dos dados em um arquivo de texto gerado pelo programa
};
#endif
