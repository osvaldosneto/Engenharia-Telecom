#ifndef MUSICA_H
#define MUSICA_H

#include <taglib.h>
#include <fileref.h>
#include <cstdlib>
#include <iostream>
#include <prglib.h>

using prglib::lista;
using namespace std;
using namespace TagLib;

class Musica {
public:
    //funções executadas pela classe Musica, acessíveis ao usuário
    Musica(string umCaminho, string nome_arquivo);
    string obtem_titulo();
    string obtem_artista();
    string obtem_album();
    string obtem_genero();
    int obtem_numero_trilha();
    int obtem_ano();
    int obtem_duracao();
    string obtem_arquivo();

private:
    //objetos da classe, acessíveis apenas para as funções da classe
    string caminho;
    string titulo;
    string artista;
    string album;
    string genero;
    int numero_trilha;
    int ano;
    int duracao;
    string nome_arq;
};

#endif /* MUSICA_H */

