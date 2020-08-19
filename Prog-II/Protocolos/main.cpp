#include "Analisador.h"
#include <iostream>
#include <string>
#include <prglib.h>

using prglib::lista;
using prglib::thash;
using namespace std;

int main(int argc, char** argv) {

    Analisador analisador;
       
    string arquivo = "/home/user/Documentos/cap/dados1.cap";
    string IP = "177.2.57.118";
      
  //  cout << endl <<"Digite o IP desde computador:"; 
   // cin >> IP;
    
  //  cout << endl << "Digite o caminho completo do arquivo:";
 //   cin >> arquivo;
    
    cout << endl << "Será gerado um documento de texto chamado 'Relatório.txt' no diretório do projeto." << endl;
    
    analisador.extract(arquivo, IP); 
}