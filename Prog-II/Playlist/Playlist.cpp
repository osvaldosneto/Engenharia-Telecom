#include "Playlist.h"

#include "Musica.h"
#include "Diretorio.h"
#include <taglib.h>
#include <fstream>
#include <fileref.h>
#include <cstdlib>
#include <iostream>
#include <prglib.h>

using prglib::lista;
using namespace std;
using namespace TagLib;
//construtor playlist
Playlist::Playlist(string arquivo){
    //construtor da playlist, abertura de diretórios e verificação de arquivos
    Diretorio dir(arquivo);
    dir.inicia_listagem();
    string caminho=arquivo;
    while (! dir.fim_listagem()) {
        Entrada e = dir.proximo();
        if (e.tipo != Tipo::Diretorio) {
            if(e.nome.rfind(".mp3")!= string::npos){
                string sub = e.nome;
                Musica m(arquivo, sub);
                musicas.insere(m);
            }
        }
    }
}

//ordena as musicas de acordo com sua duração
void Playlist::ordena_duracao(string nome_arquivo){ 
    //inicio da lista musicas
    musicas.inicia();
    int comp=musicas.comprimento();
    //laço de repetição para achar musica com maior duração
    for (int i=0; i<comp; i++){
        //atribuição de valores a variável maxima
        Musica temp1 = musicas.remove(0);
        int max = temp1.obtem_duracao();
        int tam=musicas.comprimento();
        //laço de repetição para comparação de variáveis MAX vs N
        for (int i=0; i<tam; i++){
            Musica temp2 = musicas.remove(0);
            int n = temp2.obtem_duracao();
            //caso max for maior ou igual a n
            if(max>=n){
                musicas.anexa(temp2);
            }
            //caso max for menor que n
            if(max<n){
                Musica aux = temp1;
                musicas.anexa(temp1);
                temp1=temp2;// troca de variáveis para o novo maximo obtido
                max=n;// troca de variáveis para o novo maximo obtido
            }
        }
        //inserção da lista de musicas na sequência
        musicas2.insere(temp1);
    }
    //geração do arquivo m3u
    ofstream arq(nome_arquivo);
    if (not arq.is_open()) { // caso abrir e acusar algum erro
        cerr << "Algum erro ao abrir o arquivo ..." << endl;
    }
    arq << "#EXTM3U" << endl;
    musicas2.inicia(); //inicio de impressão da lista
    while (not musicas2.fim()){
        Musica temp = musicas2.proximo();
        arq << "#EXTINF:" << temp.obtem_duracao() << "," << temp.obtem_artista() << " - " << temp.obtem_titulo() << endl;
        arq << temp.obtem_arquivo() << endl;
    }
}
//ordena a lista de músicas de acordo com o nome do artista
void Playlist::ordena_artista(string nome_arquivo){
    // faz a iteração da lista musica
    musicas.inicia();
    int comp=musicas.comprimento();
    int cont = 1;
        
    for (int i=0; i<comp; i++){
        //primeiro laço de repetição, pego uma variável para comparar com as restantes
        Musica temp1 = musicas.remove(0);
        string max = temp1.obtem_artista();
        string auxmax = max;
        max.erase(0, max.find_first_not_of(" "));
        max.erase(max.find_first_not_of(" ")+1, max.size());
        
        int tam=musicas.comprimento();
        //segundo laço vou retirando as variáveis a serem comparadas com a primeira
        for (int i=0; i<tam; i++){
            Musica temp2 = musicas.remove(0);
            string n = temp2.obtem_artista();
            string auxn = n;
            n.erase(0,n.find_first_not_of(" "));
            n.erase(n.find_first_not_of(" ")+1, n.size());
           //se a primeira variavel for maior ou igual a segunda variavel, anexamos a segunda na lista novamente
            if(max>n){
                musicas.anexa(temp2);
            }
            //se a segunda variavel for maior que primeira, a primeira variavel é anexada
            //a lista musicas, e a segunda passa a ser o maximo que será comparado com as demais variaveis da lista
            if(max<=n){
                musicas.anexa(temp1);
                temp1=temp2;
                max=n;
            }
        }
        //insere na nova lista na sequencia desejada
        musicas2.insere(temp1);
    }
    //cria nomo arquivo .m3u
    ofstream arq(nome_arquivo);
    if (not arq.is_open()) {//tratamento de erro caso não crie o arquivo
        cerr << "Algum erro ao abrir o arquivo ..." << endl;
    }//escreve no novo arquivo .m3u
    arq << "#EXTM3U" << endl;
    musicas2.inicia();
    while (not musicas2.fim()){
        Musica temp = musicas2.proximo();
        arq << "#EXTINF:" << temp.obtem_duracao() << "," << temp.obtem_artista() << " - " << temp.obtem_titulo() << endl;
        arq << temp.obtem_arquivo() << endl;
    }
}
//ordena a lista de musica pela número da música
void Playlist::ordena_trilha(string nome_arquivo){
    //iteração da lista   
    musicas.inicia();
    int comp=musicas.comprimento();
        
    for (int i=0; i<comp; i++){
        //primeiro laço de repetição, pego uma variável para comparar com as restantes
        Musica temp1 = musicas.remove(0);
        int max = temp1.obtem_numero_trilha();
        int tam=musicas.comprimento();
        //segundo laço vou retirando as variáveis a serem comparadas com a primeira
        for (int i=0; i<tam; i++){
            Musica temp2 = musicas.remove(0);
            int n = temp2.obtem_numero_trilha();
           //se a primeira variavel for maior ou igual a segunda variavel, anexamos a segunda na lista novamente
            if(max>=n){
                musicas.anexa(temp2);
            }
            //se a segunda variavel for maior a primeira, a primeira variavel é anexada
            //a lista musicas, e a segunda passa a ser o maximo que será comparado com as demais variaveis da lista
            if(max<n){
                Musica aux = temp1;
                musicas.anexa(temp1);
                temp1=temp2;
                max=n;
            }
        }
        //insere na nova lista na forma desejada
        musicas2.insere(temp1);
    }
    //abertura de arquivo
    ofstream arq(nome_arquivo);
    if (not arq.is_open()) {//tratamento de erro caso nao abra o arquivo
        cerr << "Algum erro ao abrir o arquivo ..." << endl;
    }
    //escreve no arquivo .m3u
    arq << "#EXTM3U" << endl;
    musicas2.inicia();
    while (not musicas2.fim()){
        Musica temp = musicas2.proximo();
        arq << "#EXTINF:" << temp.obtem_duracao() << "," << temp.obtem_artista() << " - " << temp.obtem_titulo() << endl;
        arq << temp.obtem_arquivo() << endl;
    }
}
//ordena a lista de musica pelo titulo da música
void Playlist::ordena_titulo(string nome_arquivo){
    //iteração da lista 
    musicas.inicia();
    int comp=musicas.comprimento();
    int cont = 1;
    //primeiro laço de repetição, pego uma variável para comparar com as restantes  
    for (int i=0; i<comp; i++){
        
        Musica temp1 = musicas.remove(0);
        string max = temp1.obtem_titulo();
        string auxmax = max;
        max.erase(0, max.find_first_not_of(" "));
        max.erase(max.find_first_not_of(" ")+1, max.size());
        
        int tam=musicas.comprimento();
        //segundo laço vou retirando as variáveis a serem comparadas com a primeira
        for (int i=0; i<tam; i++){
            Musica temp2 = musicas.remove(0);
            string n = temp2.obtem_titulo();
            string auxn = n;
            n.erase(0,n.find_first_not_of(" "));
            n.erase(n.find_first_not_of(" ")+1, n.size());
            //caso sejam iniciadas com o mesmo caractere
            if(max==n){
                while(max==n){
                    string max = temp1.obtem_titulo();
                    string auxmax = max;
                    max.erase(0, max.find_first_not_of(" ")+cont);
                    max.erase(max.find_first_not_of(" ")+1, max.size());
                                     
                    string n = temp2.obtem_titulo();
                    string auxn = n;
                    n.erase(0,n.find_first_not_of(" ")+cont);
                    n.erase(n.find_first_not_of(" ")+1, n.size());
                    //se a primeira variavel for maior ou igual a segunda variavel, anexamos a segunda na lista novamente                   
                    if(max>n){
                        musicas.anexa(temp2);
                        break;                        
                    }
                    //se a segunda variavel for maior a primeira, a primeira variavel é anexada
                    //a lista musicas, e a segunda passa a ser o maximo que será comparado com as demais variaveis da lista
                    if(max<n){
                        Musica aux = temp1;
                        musicas.anexa(temp1);
                        temp1=temp2;
                        max=n;
                        break;
                    }
                    cont++;
                }
            }
            //anexa variavel for maior
            if(max>n){
                musicas.anexa(temp2);
            }
            //se a segunda variavel for maior a primeira, a primeira variavel é anexada
            //a lista musicas, e a segunda passa a ser o maximo que será comparado com as demais variaveis da lista
            if(max<n){
                Musica aux = temp1;
                musicas.anexa(temp1);
                temp1=temp2;
                max=n;
            }
        }
        //insere na nova lista na forma desejada
        musicas2.insere(temp1);
    }
    
    ofstream arq(nome_arquivo);
    if (not arq.is_open()) {//tratamento de erro caso nao abra o arquivo
        cerr << "Algum erro ao abrir o arquivo ..." << endl;
    }
    //escreve no arquivo .m3u
    arq << "#EXTM3U" << endl;
    musicas2.inicia();
    while (not musicas2.fim()){
        Musica temp = musicas2.proximo();
        arq << "#EXTINF:" << temp.obtem_duracao() << "," << temp.obtem_artista() << " - " << temp.obtem_titulo() << endl;
        arq << temp.obtem_arquivo() << endl;
    }
}
//ordena a lista por data de gravação
void Playlist::ordena_data(string nome_arquivo){
    //inicio de interação da lista
    musicas.inicia();
    int comp=musicas.comprimento();
    //laço de repetição para comparação de variáveis 
    for (int i=0; i<comp; i++){
        //retirada de informações da primeira musica
        Musica temp1 = musicas.remove(0);
        int max = temp1.obtem_ano();
        int tam=musicas.comprimento();
        //inicio de laço para comparação da segunda variável
        for (int i=0; i<tam; i++){
            //retirada de informações da segunda musica
            Musica temp2 = musicas.remove(0);
            int n = temp2.obtem_ano();
            //comparação de tamanho, caso for maior ou igual continua como max
            if(max>=n){
                musicas.anexa(temp2);
            }
            //comparação de tamanho, caso for menor ou envia ao final da lista e troca de maximo
            if(max<n){
                musicas.anexa(temp1);
                temp1=temp2;
                max=n;
            }
        }
        //insere na lista
        musicas2.insere(temp1);
    }
    //geração de lista m3u
    ofstream arq(nome_arquivo);
    if (not arq.is_open()) {
        cerr << "Algum erro ao abrir o arquivo ..." << endl;//tratamento de erro
    }
    arq << "#EXTM3U" << endl;
    musicas2.inicia();// impressão da lista
    while (not musicas2.fim()){
        Musica temp = musicas2.proximo();
        arq << "#EXTINF:" << temp.obtem_duracao() << "," << temp.obtem_artista() << " - " << temp.obtem_titulo() << endl;
        arq << temp.obtem_arquivo() << endl;
    }
}
//embaralha a lista de musicas
void Playlist::embaralha(string nome_arquivo){
    //cria um novo arquivo .m3u
    ofstream arq(nome_arquivo);
    if (not arq.is_open()) {//tratamento de erro caso nao crie o arquivo
        cerr << "Algum erro ao abrir o arquivo ..." << endl;
    }
    //escreve no arquivo .m3u
    arq << "#EXTM3U" << endl;
    musicas.embaralha();
    musicas.inicia();
    while (not musicas.fim()){
        Musica temp = musicas.proximo();
        arq << "#EXTINF:" << temp.obtem_duracao() << "," << temp.obtem_artista() << " - " << temp.obtem_titulo() << endl;
        arq << temp.obtem_arquivo() << endl;
    }
}