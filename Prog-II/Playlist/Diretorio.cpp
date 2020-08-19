/* 
 * File:   Diretorio.cpp
 * Author: msobral
 * 
 * Created on 18 de Agosto de 2016, 09:10
 */

#include "Diretorio.h"
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <cstdlib>

Entrada::Entrada(const string & basedir, const string& name) {
    nome = name;
    string path = basedir + '/' + name;
    struct stat st;
    
    if (stat(path.c_str(), &st) < 0) throw errno;

    bytes = st.st_size;
    if (S_ISREG(st.st_mode)) {        
        if (st.st_mode & (S_IXOTH | S_IXGRP | S_IXUSR)) tipo = Tipo::Programa;
        else tipo = Tipo::Arquivo;
    }
    else if (S_ISDIR(st.st_mode)) tipo = Tipo::Diretorio;
    else if (S_ISCHR(st.st_mode)) tipo = Tipo::Chardev;
    else if (S_ISBLK(st.st_mode)) tipo = Tipo::Blockdev;
    else if (S_ISLNK(st.st_mode)) tipo = Tipo::Link;
    else tipo = Tipo::Nenhum;

}

Diretorio::Diretorio() : dir(nullptr), dent(nullptr), path(".") {    
}

Diretorio::Diretorio(const string & pathname) : path(pathname), dir(nullptr), dent(nullptr) {
    Entrada teste(path, ".");
}

Diretorio::Diretorio(const string & pathname, bool criar) : path(pathname), dir(nullptr), dent(nullptr) {
    try {
        Entrada teste(path, ".");
    } catch (int err) {
        if (not criar) throw err;
        if (mkdir(path.c_str(), 0700) < 0) throw errno;
    }
    
}

Diretorio::Diretorio(const Diretorio& orig) {
    *this = orig;
}

Diretorio::~Diretorio() {
    if (dir != nullptr) closedir(dir);
}

Diretorio& Diretorio::operator =(const Diretorio& orig) {
    if (dir != nullptr) closedir(dir);
    path = orig.path;
    dir = nullptr;
    dent = nullptr;
}

void Diretorio::muda(const string& pathname) {
    if (dir != nullptr) closedir(dir);
    if (pathname[0] == '/') path = pathname;
    else {
        path += '/'+pathname;
    }
    dir = nullptr;
    dent = nullptr;
}

unsigned int Diretorio::entradas() const {
    DIR * dp = opendir(path.c_str());
    if (dp == nullptr) return 0;
    
    unsigned int n = 0;
    dirent * ptr;
    while ((ptr = readdir(dp)) != nullptr) n++;
    closedir(dp);
    
    return n;    
}

void Diretorio::inicia_listagem() {
    if (dir != nullptr) closedir(dir);
    dir = opendir(path.c_str());
    if (dir == nullptr) throw -1;
    dent = readdir(dir);
}

Entrada Diretorio::proximo() {
    if (dir == nullptr or dent == nullptr) throw -1;
    dirent * ptr = dent;
    dent = readdir(dir);
    if (dent == nullptr) {
        closedir(dir);
        dir = nullptr;
    }
    
    return Entrada(path, ptr->d_name);
}

bool Diretorio::fim_listagem() const {
    return dent == nullptr;
}

string Diretorio::caminho_absoluto() const {
    char abspath[PATH_MAX];
    
    char * ptr = realpath(path.c_str(), abspath);
    if (ptr != nullptr) return string(ptr);
    throw errno;
}
