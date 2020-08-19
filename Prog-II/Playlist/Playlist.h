#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Musica.h"
#include "Diretorio.h"
#include <taglib.h>
#include <fileref.h>
#include <cstdlib>
#include <iostream>
#include <prglib.h>

using prglib::lista;
using namespace std;
using namespace TagLib;

class Playlist {
    
private:
    //objetos da classe Playlist.h, são acessíveis somente dentra das funções da classe
    lista<Musica> musicas;
    lista<Musica> musicas2;
    
public:
    //funções executas pela classe Playlist
    Playlist(string arquivo);
    void ordena_duracao(string nome_arquivo);
    void ordena_artista(string nome_arquivo);
    void ordena_titulo(string nome_arquivo);
    void ordena_trilha(string nome_arquivo);
    void ordena_data(string nome_arquivo);
    void embaralha(string nome_arquivo);
    
};

#endif /* PLAYLIST_H */