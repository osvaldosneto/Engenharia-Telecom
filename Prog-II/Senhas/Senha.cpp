#include "Senha.h"

Senha::Senha(string sen){ //construtor da senha
    senha = sen;
}

string Senha::inversa(){ //método de inversão da palavra
    
    string aux, senha_nova;
    int tam = senha.size();
    
    for(int i=0; i<tam; i++){ //laço de repetição para inversão da palavra
        aux = senha.substr(senha.size()-1,1); //copia a última letra e insere no ińicio da palavra
        senha_nova = senha_nova + aux;
        senha.erase(senha.size()-1,1);
    }
    return senha_nova;
}

string Senha::estendida(){ //método de correção da palavra, retirada de ".,;:!?<>(){}[]/=+-*&%$#@ "
    
    while ((senha.find_first_of(".,;:!?<>(){}[]/=+-*&%$#@ ")) != string::npos){ //procura dos carácteres
        int pos = senha.find_first_of(".,;:!?<>(){}[]/=+-*&%$#@ ");
        senha.erase(senha.find_first_of(".,;:!?<>(){}[]/=+-*&%$#@ "),1); //retirada dos caracteres
    }
    return senha;
}

string Senha::numerada(){ //método de retirada de números do início e fim da palavra
    
    int pos;
    if(senha.find_first_of("1234567890")==0){ //retirada dos números no início da palavra
        pos = senha.find_first_not_of("0123456789");
        senha.erase(0,pos);
    }
    
    if(senha.find_last_of("1234567890") == senha.size()-1){ //retirada dos números no fim da palavra
        pos = senha.find_last_not_of("0123456789");
        senha.erase(pos+1, senha.size());
    }
    
    return senha;
}

string Senha::substituida(){ //método de substituir 3 por e, 5 por s, 0 por o, 4 por a e 1 por l
       
    while((senha.find_first_of("35041")) != string::npos){
       
        while((senha.find_first_of("3")) != string::npos){ //procura da letra 3 e substituição do mesmo por e
            if(senha.compare(senha.find_first_of("3"),1, "3")==0){
                senha.replace(senha.find_first_of("3"),1,"e");
            }
        }
        while((senha.find_first_of("0")) != string::npos){ //procura da letra 0 e substituição do mesmo por o
            if(senha.compare(senha.find_first_of("0"),1, "0")==0){
                senha.replace(senha.find_first_of("0"),1,"o");
            }
        }
        while((senha.find_first_of("5")) != string::npos){ //procura da letra 5 e substituição do mesmo por s
            if(senha.compare(senha.find_first_of("5"),1, "5")==0){
                senha.replace(senha.find_first_of("5"),1,"s");
            }
        }
        while((senha.find_first_of("4")) != string::npos){ //procura da letra 4 e substituição do mesmo por a
            if(senha.compare(senha.find_first_of("4"),1, "4")==0){
                senha.replace(senha.find_first_of("4"),1,"a");
            }
        }
        while((senha.find_first_of("1")) != string::npos){ //procura da letra 1 e substituição do mesmo por l
            if(senha.compare(senha.find_first_of("1"),1, "1")==0){
                senha.replace(senha.find_first_of("1"),1,"l");
            }
        }
    }
    return senha;
}

lista<string> Senha::rotacionada(){ //método para rotacionar a palavra

    lista<string>l; //lista utilizada para armazenar as palavras
    
    int tam, i;
    string aux = senha;
    tam = aux.size();
    string w;
    
    for (i=0; i<tam; i++){ //laço de repetição para rotacionar as palavras
        w=senha.substr(0,1);
        senha.erase(0,1);
        senha = senha + w;
        l.insere(senha);
    }
    return l;
}