/* 
 * File:   hash-impl.h
 * Author: msobral
 *
 * Created on 11 de Agosto de 2016, 13:59
 */

#ifndef HASH_IMPL_H
#define	HASH_IMPL_H

namespace prglib {
    
template <typename T> thash<T>::thash(int num_linhas) : linhas(num_linhas){
    this->rehash(linhas);
}

template <typename T> thash<T>::thash(const thash & outro) : std::unordered_map<std::string,T>(outro) {
    linhas = outro.linhas;
}

template <typename T> thash<T>::~thash() {
}

template <typename T> void thash<T>::adiciona(const std::string& chave, const T& algo) {
    try {
        this->at(chave) = algo;        
    } catch (...) {
        std::pair<std::string,T> par(chave, algo);
        this->insert(par);
    }
}

template <typename T> T& thash<T>::operator[](const std::string& chave) {
    try {
        return this->at(chave);        
    } catch (...) {
        throw -1;
    }
}

template <typename T> T& thash<T>::obtem(const std::string& chave) {
    return (*this)[chave];
}

template <typename T> bool thash<T>::existe(const std::string& chave) const {
    typename std::unordered_map<std::string,T>::const_iterator it;
    it = this->find(chave);
    return it != this->end();
}

template <typename T> void thash<T>::esvazia() {
    this->clear();
}

template <typename T> T thash<T>::remove(const std::string& chave) {
    try {
        T dado = (*this)[chave];
        this->erase(chave);
        return dado;
    } catch (...) {
        throw -1;
    }    
}

template <typename T> unsigned int thash<T>::tamanho() const {
    return this->size();
}

template <typename T> std::shared_ptr<lista<std::string>> thash<T>::chaves() const {
    //auto l = new lista<std::string>;
    std::shared_ptr<lista<std::string>> l(new lista<std::string>);
    for (auto it = this->begin(); it != this->end(); it++) {
        l->anexa(it->first);
    }
    return l;    
}

template <typename T> std::shared_ptr<lista<T>> thash<T>::valores() const {
    //auto l = new lista<T>;
    std::shared_ptr<lista<T>> l(new lista<T>);
    
    for (auto it = this->begin(); it != this->end(); it++) {
        l->anexa(it->second);
    }
    return l;    
}
    
}

#endif	/* HASH_IMPL_H */

