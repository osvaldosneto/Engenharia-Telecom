#include "Verificador.h"

Verificador::Verificador(string opcao){
    
    lista<string>l;
    string w;
    int i;
    
    if(opcao == "2"){
        //abertura dos arquivos para inserção em uma lista
        ifstream arq0("arq/american.txt");
        if (! arq0.is_open()) cout << "arquivo 'american.txt' inacessivel";
        while(arq0>> w){//laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){ //laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
       // l.insere("a");
        //abertura dos arquivos para inserção em uma lista
        ifstream arq1("arq/dutch.txt");
        if (! arq1.is_open()) cout << "arquivo inacessivel";
        while(arq1>>w){//laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){//laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
        //abertura dos arquivos para inserção em uma lista
        ifstream arq2("arq/english.txt");
        if (! arq2.is_open()) cout << "arquivo 'english.txt' inacessivel";
        while (arq2 >> w){//laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){//laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
        //abertura dos arquivos para inserção em uma lista
        ifstream arq3("arq/french.txt");
        if (! arq3.is_open()) cout << "arquivo 'french.txt' inacessivel";
        while (arq3 >> w){//laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){//laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
        //abertura dos arquivos para inserção em uma lista
        ifstream arq4("arq/german.txt");
        if (! arq4.is_open()) cout << "arquivo 'german.txt' inacessivel";
        while (arq4 >> w){//laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){//laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
        //abertura dos arquivos para inserção em uma lista
        ifstream arq5("arq/italian.txt");
        if (! arq5.is_open()) cout << "arquivo 'italian.txt' inacessivel";
        while (arq5 >> w){//laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){//laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
        //abertura dos arquivos para inserção em uma lista
        ifstream arq6("arq/japanese.txt");
        if (! arq6.is_open()) cout << "arquivo 'japanese.txt' inacessivel";
        while (arq6 >> w){//laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){//laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
        //abertura dos arquivos para inserção em uma lista
        ifstream arq7("arq/latin.txt");
        if (! arq7.is_open()) cout << "arquivo 'latin.txt' inacessivel";
        while (arq7 >> w){//laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){//laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
        //abertura dos arquivos para inserção em uma lista
        ifstream arq8("arq/literature.txt");
        if (! arq8.is_open()) cout << "arquivo 'literature.txt' inacessivel";
        while (arq8 >> w){//laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){//laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
        //abertura dos arquivos para inserção em uma lista
        ifstream arq9("arq/misc.txt");
        if (! arq9.is_open()) cout << "arquivo 'misc.txt' inacessivel";
        while (arq9 >> w){//laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){//laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
        //abertura dos arquivos para inserção em uma lista
        ifstream arq10("arq/municipios.txt");
        if (! arq10.is_open()) cout << "arquivo 'municipios.txt' inacessivel";
        while (arq10 >> w){//laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){//laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
        //abertura dos arquivos para inserção em uma lista
        ifstream arq11("arq/nomes.txt");
        if (! arq11.is_open()) cout << "arquivo 'nomes.txt' inacessivel";
        while (arq11 >> w){//laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){//laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
        //abertura dos arquivos para inserção em uma lista
        ifstream arq12("arq/portugues.txt");
        if (! arq12.is_open()) cout << "arquivo 'portugues.txt' inacessivel";
        while (arq12 >> w){//laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){//laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
        //abertura dos arquivos para inserção em uma lista
        ifstream arq13("arq/spanish.txt");
        if (! arq13.is_open()) cout << "arquivo 'spanish.txt' inacessivel";
        while (arq13 >> w){ //laço de repetição para arquivamento
            for(i=0;i<w.size(); i++){//laço de repetição para converter todas as letras em minúsculas
                if(isupper(w[i])) w[i] = towlower(w[i]);
            }
            l.insere(w);
        }
        //início de interação da lista para construção da árvore
        l.embaralha();
        l.inicia();
        //inserção de dados na árvore
       // a = new arvore<string>(l.proximo());
        //laço de repetição para adicionar os dados na árvore
       // while(! l.fim()){
       //     a->adiciona(l.proximo());
       // }
       
        //balanceamento da árvore
      //  a = a->balanceia(true); //balanceamento da árvore
        
      //  l.esvazia(); 
        
      //  a->listePreOrder(l); //salvando dados da árvore em uma lista
       
        ofstream arqt("arvore.txt");
        l.inicia();
        while(! l.fim()){
            arqt << l.proximo() << endl; //escrevendo os dados da lista em um arquivo
        }
    }
    
    if(opcao == "1"){ //opçao caso não tenha alterado os arquivos para pesquisa
        fstream arq("arvore.txt"); //abertura do arquivo para leitura dos dados armazenados
        
      //  arq >> w;
      //  a = new arvore<string>(w); //criação da árvore binária
        
     //   while(arq >> w){
     //       a->adiciona(w); //adicionando dados a árvore
     //   }
    }
}

int Verificador::Verifica(string senha){

    try { //retorno de um dado caso exista o nome na arvore
        a->obtem(senha);
        return 1;
    }
    catch (...) { //retorno de um dado caso não exista o nome na arvore
        return 0;
    }
}