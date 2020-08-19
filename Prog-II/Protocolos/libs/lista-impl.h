#ifndef LISTA2_IMPL_H
#define	LISTA2_IMPL_H

#include "lista.h"

namespace prglib {

template <typename T> lista<T>::lista() {
    len = 0; //criação da lista com seus parâmetros iniciais
    primeiro = nullptr;
    ultimo = nullptr;
}

template <typename T> lista<T>::lista(const lista<T> & outra) {
    Nodo *ptr = outra.primeiro; //cópia de uma lista com os mesmos dados
    
    primeiro = nullptr;
    ultimo = nullptr;
    len = 0;
    
    Nodo *novo = new Nodo(ptr->dado); 
    primeiro = novo;
    ultimo = novo;
    len ++;
    ptr = ptr->proximo;  
    
    while(ptr != nullptr){ //laço de repetição para armazenamento dos dados da lista original
        Nodo *novo = new Nodo(ptr->dado);
        ultimo->proximo = novo;
        ultimo = novo;
        len++;
        ptr = ptr->proximo;
    }
}

template <typename T> lista<T>::~lista() {
}

template <typename T> void lista<T>::insere(const T& algo) {
    Nodo * novo = new Nodo(algo);
    
    if(len > 0){
        novo->proximo = primeiro;
        primeiro->anterior = novo;
        primeiro = novo;
    }else{
        primeiro = novo;
        ultimo = novo;
    }
    len++;
}

template <typename T> void lista<T>::anexa(const T& algo) {
    Nodo * novo = new Nodo(algo);
    
    if(len > 0){
        novo->anterior = ultimo;
        ultimo->proximo = novo;
    }else primeiro = novo;
    ultimo = novo;
    len++;
}

template <typename T> int lista<T>::comprimento() const {
    return  len;
}

template <typename T> void lista<T>::esvazia() {
    Nodo *ptr = primeiro;
    while(primeiro != nullptr){
        ptr = primeiro;
        primeiro = ptr->proximo;
        len --;
        delete ptr;
    }
    len = 0;
    primeiro = nullptr;
    ultimo = nullptr;
}

template <typename T> void lista<T>::insere(const T& algo, int posicao) {
    if(posicao>=len) anexa(algo);
    else{
        if(posicao == 0) insere(algo);
        else{
            Nodo * novo = new Nodo(algo);
            Nodo *ptr = primeiro;
            Nodo *next = primeiro;
            next = next->proximo;
            posicao--;
            
            for(int i=0; i<posicao; i++){
                ptr = ptr->proximo;
                next = next->proximo;
            }
            next->anterior = novo;
            novo->proximo = ptr->proximo;
            ptr->proximo=novo;
            novo->anterior=ptr;
            len ++;
        }
    }
}

template <typename T> T& lista<T>::obtem(int posicao) const {
    if(posicao<0) throw-1;
    if(posicao>len) throw -1;
    
    Nodo *ptr = primeiro;
    
    for(int i=0; i<posicao; i++) ptr = ptr->proximo;
    return ptr->dado;    
}

template <typename T> T& lista<T>::operator[](int pos) const {
    if(pos<0) throw-1;
    if(pos>len) throw -1;
    
    Nodo *ptr = primeiro;
    
    for(int i=0; i<pos; i++) ptr = ptr->proximo;
    return ptr->dado;   
}

template <typename T> void lista<T>::escrevaSe(std::ostream& out) const {
    if(len == 0) return;
    Nodo *ptr = primeiro;
    Nodo *contador = primeiro;
    
    contador = contador->proximo; //nodo auxiliar para contagem dos nodos
    
    while(contador != nullptr){ //laço de repetição para inicio de escrita
        out << ptr->dado << "\n"; //escrita dos dados com quebra de linha
        ptr = ptr->proximo;
        contador = contador->proximo;
    }
    out << ptr->dado; //escrita do ultimo dado
}

template <typename T> void lista<T>::escrevaSe(std::ostream& out, const std::string & delim) const {
    if(len == 0) return; //verificação se existe lista
    Nodo *ptr = primeiro; 
    Nodo *contador = primeiro;
    
    contador = contador->proximo; //nodo auxiliar para contagem dos nodos
    
    while(contador != nullptr){ //laço de repetição para inicio de escrita
        out << ptr->dado << delim; //escrita dos dados
        ptr = ptr->proximo;
        contador = contador->proximo;
    }
    out << ptr->dado; //escrita do ultimo dado
}

template <typename T> T lista<T>::remove(int posicao) {
    Nodo *before = primeiro;
    Nodo *ptr = primeiro;
    Nodo *aux;
    
    if(posicao<0) throw-1;
    else if(posicao>=len) throw -1;
    
    else if(posicao==0){
        len --;
        if(len == 0){
            ultimo = nullptr;
            primeiro = ultimo;
        } else{
            primeiro = ptr->proximo;
            primeiro->anterior = nullptr;
        }
        T a = ptr->dado;
        delete ptr;
        return a;
    }else{
        posicao --;
        for(int i=0; i<posicao; i++){
            ptr = ptr->proximo;
            before = before->proximo;
        }
        ptr = ptr->proximo;
        if(ptr->proximo == nullptr){
            ultimo = before;
            before->proximo = nullptr;
        }else{
            aux = ptr->proximo;
            before->proximo = aux;
            aux->anterior = before;
        }
        len --;
        T a = ptr->dado;
        delete ptr;
        return a;
    }
}

template <typename T> void lista<T>::retira(const T& algo) {
    Nodo *ptr = primeiro;
    Nodo *before = primeiro;
    Nodo *aux;
    
    while(ptr != nullptr){
        if(ptr->dado == algo){
            if(len == 1){
                ultimo = nullptr;
                primeiro = ultimo;
                len --;
                delete ptr;
                ptr = nullptr;
            }else if(ptr == primeiro){
                aux = ptr->proximo;
                primeiro = aux;
                primeiro->anterior = nullptr;
                len --;
                delete ptr;
                ptr = aux;
            }else{
                 if(ptr->proximo != nullptr){
                    before = ptr->anterior;
                    aux = ptr->proximo;
                    before->proximo = aux;
                    aux->anterior = before;
                    delete ptr;
                    ptr = aux;
                    len--;
                }else{
                    before = ptr->anterior;
                    ultimo = before;
                    len --;
                    delete ptr;
                    before->proximo = nullptr;
                    ptr = nullptr;
                }
            }
        }else ptr = ptr->proximo;
    }
}

template <typename T> bool lista<T>::vazia() const {
    return len==0;
}

template <typename T> void lista<T>::insereOrdenado(const T & algo) {
    Nodo *ptr = primeiro;
    Nodo *before = primeiro;
    
    if(len == 0) insere(algo);
    
    else if(ptr->dado >= algo) insere(algo);
    
    else{
        ptr = ptr->proximo;
        while(ptr!=nullptr){
            if(ptr->dado >= algo){
                Nodo * novo = new Nodo(algo);
                novo->proximo = ptr;
                novo->anterior = before;
                before->proximo = novo; 
                ptr->anterior = novo;
                len ++;
                break;
            }else{
                ptr = ptr->proximo;
                before = before->proximo;
            }
        }
        if(ptr == nullptr) anexa(algo);  
    }
}

template <typename T> void lista<T>::ordena() {
}

template <typename T> void lista<T>::ordenaBolha() {
    
    Nodo *ptr = primeiro;
    Nodo *last = ultimo;
    while(last!=nullptr){
        while(ptr != last){
            if(last->dado >= ptr->dado) ptr = ptr->proximo;
            else{
                T aux = last->dado;
                last->dado = ptr->dado;
                ptr->dado = aux;
                ptr = ptr->proximo;
            }
        }
        ptr = primeiro;
        last = last->anterior;
    }
}

template <typename T> T& lista<T>::procura(const T& algo) const {
    Nodo *ptr = primeiro;
    
    while(ptr != nullptr){
        if(ptr->dado == algo) return ptr->dado;
        else ptr = ptr->proximo;
    }
    throw -1;
}

template <typename T> lista<T>& lista<T>::procuraMuitos(const T& algo, lista<T>& outra) const {
    Nodo *ptr = primeiro;
    
    while(ptr != nullptr){
        if(ptr->dado == algo) outra.anexa(ptr->dado);
        ptr = ptr->proximo;
    }
    return outra;
}

template <typename T> std::shared_ptr<lista<T>> lista<T>::procuraMuitos(const T& algo) const {
    //verificar se está correta
    Nodo *ptr = primeiro;
    
    lista<T> * outra = new lista<T>;
    
    while(ptr != nullptr){
        if(ptr->dado == algo) outra->anexa(ptr->dado);
        ptr = ptr->proximo;
    }
    return outra;  
}

template <typename T> lista<T>& lista<T>::operator=(const lista<T>& outra) {
    Nodo *ptr = outra.primeiro;
    
    primeiro = nullptr;
    ultimo = nullptr;
    len = 0;
    
    Nodo *novo = new Nodo(ptr->dado);
    primeiro = novo;
    ultimo = novo;
    len ++;
    ptr = ptr->proximo;  
    
    while(ptr != nullptr){
        Nodo *novo = new Nodo(ptr->dado);
        ultimo->proximo = novo;
        ultimo = novo;
        len++;
        ptr = ptr->proximo;
    }
}

template <typename T> bool lista<T>::operator==(const lista<T>& outra) const {
    Nodo *ptr1 = primeiro;
    Nodo *ptr2 = outra.primeiro;
    
    while((ptr1 != nullptr)||(ptr2 != nullptr)){
        if(ptr1->dado == ptr2->dado){
            ptr1 = ptr1->proximo;
            ptr2 = ptr2->proximo;
        }else return 0;
    }
    return 1;
}

template <typename T> void lista<T>::inverte() {
    lista<T> l;
    Nodo *ptr;
    
    while(primeiro !=nullptr){
        ptr = primeiro;
        l.insere(ptr->dado);
        primeiro = ptr->proximo;
        delete ptr;
        len--;
    }
    l.inicia();
    while(!l.fim()) anexa(l.proximo());
}

template <typename T> bool lista<T>::inicio() const {
    return atual == nullptr;
}

template <typename T> bool lista<T>::fim() const {
    return atual == nullptr;
}

template <typename T> void lista<T>::inicia() {
    atual = primeiro;
}

template <typename T> void lista<T>::iniciaPeloFim() {
    atual = ultimo;
}

template <typename T> T& lista<T>::proximo() {
    T & dado = atual->dado;
    atual = atual->proximo;
    return dado;
}

template <typename T> T& lista<T>::anterior() {
    T & dado = atual->dado;
    atual = atual->anterior;
    return dado;
}

template <typename T> lista<T>& lista<T>::sublista(unsigned int pos1, unsigned int pos2, lista<T> & outra) const {
    if((pos1<0)||(pos2<0)||(pos1>len)||(pos2>len)||(pos1>pos2)) throw -1;
 
    Nodo *ptr = primeiro;
    
    for (int i=0; i<pos1; i++) ptr = ptr->proximo;
    
    for(pos1 ; pos1<=pos2; pos1++){
        outra.anexa(ptr->dado);
        ptr = ptr->proximo;
    }
}

template <typename T> lista<T>* lista<T>::sublista(unsigned int pos1, unsigned int pos2) const {
    if((pos1<0)||(pos2<0)||(pos1>len)||(pos2>len)||(pos1>pos2)) throw -1;
    
    lista<T> * outra = new lista<T>;
    
    Nodo *ptr = primeiro;
    
    for (int i=0; i<pos1; i++) ptr = ptr->proximo;
        
    for(pos1 ; pos1<=pos2; pos1++){
        outra->anexa(ptr->dado);
        ptr = ptr->proximo;
    }
    return outra;
}

template <class T> void lista<T>::embaralha() {
    srand (time(NULL));
    for (int i=0; i<len; i++){
        int n = rand() % len;
        T a = remove(n);
        anexa(a);
    }
}

template <typename T> int lista<T>::trunca(int posicao) {
    
    Nodo *ptr = primeiro;
    Nodo *aux = primeiro;
    
    int cont=0;
    if(len==0) return 0;
    
    if(posicao>len) return 0;
    
    if(posicao==0){
        while(primeiro != nullptr){
            ptr = primeiro;
            primeiro = ptr->proximo;
            len --;
            delete ptr;
            cont ++;
        }
        len = 0;
        primeiro = nullptr;
        ultimo = nullptr;
        return cont;
    }
    
    posicao --;
    for(int i=0; i<posicao; i++){
        ptr = ptr->proximo;
        aux = aux->proximo;
    }
    
    while(ptr->proximo){
        aux = ptr->proximo;
        delete ptr;
        ptr = aux;
        len--;
        cont ++;
    }
    
    ultimo = aux;
       
    return cont;
}


template <typename T> void lista<T>::multiplos() {
    ordena();
    
    inicia();
    
    
    
    
    
}

template <class T> void lista<T>::mistura(lista<T> & outra) {
    
    int pos=1;
    if(len >= outra.comprimento()){
        outra.inicia();
        while(!outra.fim()){
            insere(outra.proximo(),pos);
            pos = pos+2;
        }
    }else if(len<outra.comprimento()){
        outra.inicia();
        while(!outra.fim()){
            insere(outra.proximo(),pos);
            pos = pos+2;
        }
    }
    

}

template <typename T> void lista<T>::insere(const lista<T> & dados, int posicao) {
    Nodo *px = primeiro;
    Nodo *ptr = primeiro;
    if(posicao == 0){
        int tam = dados.comprimento();
        tam--;
        for(int i=tam; i>=0; i--) insere(dados.obtem(i));  
    }
    else if(posicao < len){
        posicao --;
        for(int i=0; i<posicao; i++){
            ptr = ptr->proximo;
            px = px->proximo;
        }
        px = px->proximo;
    
        for(int i=0; i<dados.comprimento(); i++){
            T a = dados.obtem(i);
            Nodo * novo = new Nodo(a);
            ptr->proximo = novo;
            novo->anterior = ptr;
            novo->proximo = px;
            px->anterior = novo;
            ptr = novo;
            len++;
        }
    }else{
        for(int i=0; i<dados.comprimento(); i++) anexa(dados.obtem(i));  
    }
}
  
} // fim namespace

#endif	/* LISTA_IMPL_H */