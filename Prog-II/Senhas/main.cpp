#include "Verificador.h"
#include "Senha.h"
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <wctype.h>
#include <prglib.h>
#include <fstream>

using prglib::arvore;
using prglib::lista;
using namespace std;

int main() {
    
    lista<string> l; //lista utilizada para resgatar os dados do método rotaciona
    string senha_outra, senha, w, senha_original, opcao, e;
    int i=0, var=0;
    
    cout << "Digite '1' caso os arquivos não tenham sido alterados, ou '2' caso tenham sido atualizados:";
    cin >> opcao;
    
    getline(cin, e);
    
    Verificador verificador(opcao); //criação do objeto verificador

    while(true){       
  
        cout << "Digite as palavras para verificação:";
        getline(cin,senha_outra);
        senha_outra = senha_outra + " "; //acrescenta espaço no final para correção da string
           
        ofstream arq("senhas.txt"); //abertura para escrita em arquivo onde serão armazenadas as senhas a examinar
        
        while(senha_outra.find_first_of(" ") != string::npos){ //metodo utiliazado para escrever as senhas em um aquivo
            w = senha_outra.substr(0, senha_outra.find(" "));
            senha_outra.erase(0, senha_outra.find(" ")+1);
            arq << w << endl;
        }
               
        ifstream arq1("senhas.txt"); //resgate de senhas para analise das mesmas
        if (! arq1.is_open()) cout << "arquivo de senhas inacessivel"; //caso arquivo não seja possível abrir
        while(arq1 >> senha ){ //laço de repetição para armazenamento da senha
            
            senha_original = senha; //metodo para armazenar a senha original para posteriormente utilizar
            for(i=0;i<senha.size(); i++){ //laço de repetição para converter maiúsculos em minúsculos
                senha[i] = towlower(senha[i]);
            }
            Senha s(senha); //construtor do objeto senha     
            var = verificador.Verifica(senha); //construtor do objeto verificador
            
            if(! var){ 
            var = verificador.Verifica(s.estendida()); //verificação da existência da senha na árvore no método estendida
            
                if(! var){ 
                    var = verificador.Verifica(s.numerada()); //verificação da existência da senha na árvore no método numerada
               
                    if(! var){ 
                        var = verificador.Verifica(s.substituida()); //verificação da existência da senha na árvore no método substituida
                  
                        if(! var){
                            l = s.rotacionada(); //verificação da existência da senha na árvore no método rotacionada
                            l.inicia();
                        
                            while(! l.fim()){ //laço de repetição para interação
                                var = verificador.Verifica(l.proximo());
                                if(var) break; //interrupção do laço caso ache a senha na árvore
                            }
                            if(! var){
                                string inversa = s.inversa();
                                if(! var){ //verificação da existência da senha na árvore no método inversa
                                    var = verificador.Verifica(inversa);
                                    if(! var){
                                        cout << "A senha " << senha_original << " é boa."<< endl;
                                    }
                                    else{ //confirmação da verificação de existência na senha na árvore
                                        cout << "A senha " << senha_original << " é ruim."<< endl;
                                    }
                                }
                                else{ //confirmação da verificação de existência na senha na árvore
                                    cout << "A senha " << senha_original << " é ruim."<< endl;
                                }
                            }
                            else{ //confirmação da verificação de existência na senha na árvore
                                cout << "A senha " << senha_original << " é ruim."<< endl;
                            }
                        }
                        else{ //confirmação da verificação de existência na senha na árvore
                            cout << "A senha " << senha_original << " é ruim."<< endl;
                        }
                    }
                    else{ //confirmação da verificação de existência na senha na árvore
                        cout << "A senha " << senha_original << " é ruim."<< endl;
                    }
                }
                else{ //confirmação da verificação de existência na senha na árvore
                    cout << "A senha " << senha_original << " é ruim."<< endl;
                }
            }
            else{ //confirmação da verificação de existência na senha na árvore
                cout << "A senha " << senha_original << " é ruim."<< endl;
            }   
        }
    }
}