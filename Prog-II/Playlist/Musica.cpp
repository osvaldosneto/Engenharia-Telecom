#include "Musica.h"
#include "Diretorio.h"
#include <taglib.h>
#include <fileref.h>
#include <cstdlib>
#include <iostream>
#include <cctype>

using std::string;
using namespace TagLib;
//construtor para musica
Musica::Musica(string umCaminho, string nome_arquivo){
    caminho = umCaminho;
    nome_arq = umCaminho + "/" + nome_arquivo;
    FileRef f(nome_arq.c_str());
    Tag * tag = f.tag();
    AudioProperties * prop = f.audioProperties(); 
    if (tag == NULL) throw 1; // exceçao: arquivo nao possui tag ID3 !!!
    
    String aux;
    //gerando uma tag artista
    aux = tag->artist();
    artista = aux.toCString();
    //gerando uma tag genero
    aux = tag->genre(); 
    genero = aux.toCString();
    //gerando uma tag album
    aux = tag->album();   
    album = aux.toCString();
    //gerando uma tag titulo
    aux = tag->title(); 
    titulo = aux.toCString();
    //gerando uma tag ano
    ano = tag->year();
    //gerando uma tag trilha
    numero_trilha = tag->track();
    //gerando uma tag duração
    duracao = prop->lengthInSeconds();    
};
//função para obter titulo
string Musica::obtem_titulo(){
    return titulo;
};
//função para obter artista
string Musica::obtem_artista(){
    return artista;
};
//função para obter album
string Musica::obtem_album(){
    return album;
};
//função para obter genero
string Musica::obtem_genero(){
    return genero;
};
//função para obter numero trilha
int Musica::obtem_numero_trilha(){
    return numero_trilha;
};
//função para obter ano
int Musica::obtem_ano(){
    return ano;
};
//função para obter duração
int Musica::obtem_duracao(){
    return duracao;
};
//função para obter arquivo
string Musica::obtem_arquivo(){
    return nome_arq;
};