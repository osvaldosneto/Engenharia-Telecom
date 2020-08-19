#include "Musica.h"
#include "Playlist.h"
#include "Diretorio.h"
#include <cstdlib>
#include <taglib.h>
#include <fileref.h>
#include <iostream>
#include <string>
#include <prglib.h>
#include<stdio.h>

using namespace std;
using namespace TagLib;

int main(int argc, char** argv) {
    
    string nome_lista;
    string diretorio_arquivos;
    int opcao;
    //dados a inserir para retirada de diretórios, nome da lista a gerar, e opção de ordenamento
    cout << "Informe o Nome da Playlist a criar: ";
    cin >> nome_lista;
    nome_lista = nome_lista + ".m3u";
    cout << endl;
    cout << "Informe o diretório dos arquivos: ";
    cin >> diretorio_arquivos;
    cout << endl;
    //opção para ordenamento
    cout << "Digite: " << endl << " => '1' para ordenamento por artista; "<<endl;
    cout << " => '2' para ordenamento por titulo; " << endl;
    cout << " => '3' para ordenamento por data; " << endl;
    cout << " => '4' para ordenamento por número de faixa; " << endl;
    cout << " => '5' para ordenamento por duração; " << endl;
    cout << " => '6' para ordenamento aleatório; " << endl;
    cin >> opcao;
    //criação playlist musicas
    Playlist musicas (diretorio_arquivos);
    //resposta a opção desejada
    switch (opcao){
        case 1:
            //ordena por artista
            musicas.ordena_artista(nome_lista);
            break;
        case 2:
            //ordena por titulo
            musicas.ordena_titulo(nome_lista);
            break;
        case 3:
            //ordena por data
            musicas.ordena_data(nome_lista);
            break;
        case 4:
            //ordena por numero da trilha
            musicas.ordena_trilha(nome_lista);
            break;
        case 5:
            //ordena por duração
            musicas.ordena_duracao(nome_lista);
            break;
        case 6:
            //embaralha lista
            musicas.embaralha(nome_lista);
            break;
    }
    
    return 0;
}
