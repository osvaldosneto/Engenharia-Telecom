#include "Analisador.h"
//construtor para tabela do analisador
Analisador::Analisador(): tab(61123){}

//metodo para extração de dados e inserir na struct
void Analisador::extract(string arquivo, string IP){
    string linha, aux, IP_aux;
    int pos;
    string find = "length";
    
    Analisador analisa;
    //abertura do arquivo para leitura de linhas
    ifstream arq(arquivo);
 
    if (not arq.is_open()) cerr << "Erro ao abrir o arquivo ..." << endl;
    //laço de repetição para iniciar captura e quebra de linhas    
    while (getline(arq, linha)){
        aux = linha; 
        dados.inicio_outro=0;
        dados.inicio_este=0;
        dados.hora_inicio = aux.substr(0,15); //tratamento da string aux para captura de hora
        aux.erase(0,19);
        dados.endereco_origem = aux.substr(0,aux.find_first_of(" ")); //tratamento da string aux para captura de endereço de origem
        IP_aux=dados.endereco_origem; //extração da string IP para comparação
        IP_aux.erase(IP_aux.find_last_of("."), IP_aux.size()); //extração da string IP para comparação
        aux.erase(0,aux.find_first_of(" ")+3);
        dados.endereco_destino = aux.substr(0,aux.find_first_of(":")); //tratamento da string aux para captura de endereço de origem
        aux.erase(0, aux.find_first_of(":")+9);
        dados.flags = aux.substr(0,1); //tratamento da string aux para captura das flags
        aux.erase(0, aux.find("length")+7);//tratamento da string para captura dos dados
        pos = aux.find_first_of(":");
        if(IP_aux != IP){ //metodo realizado para incremento de somatório de ip de origem e ip de destino
            dados.inicio_outro ++; //incremento de inicio de comunicação por outro IP
        }
        else{
            dados.inicio_este ++; //incremento de inicio de comunicação por este IP
        }
       
        if(pos > 1){ // metodo realizado para extrair string comprimento
            dados.comprimento = aux.erase(pos, aux.size()); //tratamento da string para captura de comprimento
        }
        else{ // metodo realizado para extrair string comprimento
            dados.comprimento = aux; //tratamento da string para captura de comprimento
        }
        string chaves = analisa.cria_chaves(dados); //invocação de metodo que cria as strings para as chaves
        analisa.cria_tabela(chaves, dados); //invocação de metodo que cria as tabelas
    }
    
    analisa.imprime_tabela(IP); //invocação de metodo para gerar documento "arquivo.txt" com as informações
    
}

//metodo de criação das strings chaves
string Analisador::cria_chaves(struct Dados dados) {
    string chave;
    if(dados.endereco_origem>dados.endereco_destino){ //organização das chaves para comparação
        chave = dados.endereco_destino + " > " + dados.endereco_origem;
    }
    else{ //organização das chaves para comparação
        chave = dados.endereco_origem + " > " + dados.endereco_destino;
    }
    return chave;
}

//metodo para criação das tabelas hash
void Analisador::cria_tabela(string chave, struct Dados dados){
   
    if(! tab.existe(chave)){ //inicio de criação da tabela "tab"
        if(dados.flags == "S"){ //comparação da flag, caso não exista e seja igual a "S" será criada uma tabela
            dados.pacotes ++; //incremento de pacotes
            tab.adiciona(chave, dados); //devolve os dados para a tabela
        }
    }
    if(tab.existe(chave)){ //tratamento da struct Dados para incremento de informações como tempo e comprimento
        Dados aux= tab.remove(chave); //invocação da tabela existente para incremento de dados
        if(aux.fim != "end"){ //metodo para verificar se é necessário a soma de mais alguma linha caso fim = end programa não faz nada
            if(dados.flags == "F"){ //verificação de dados.flags para ver se resgato chave existente para incremento de dados
                aux.hora_fim = dados.hora_inicio; //acrescentando horas de final de comunicação
                aux.comprimento = aux.comprimento + " " + dados.comprimento; //incremento de comprimento da comunicação
                aux.fim = "end"; //variável delarada em caso de fim da listagem de dados
                tab.adiciona(chave, aux); //devolve os dados para a tabela
            }
        
            else{ //caso não exista flags
                aux.comprimento = aux.comprimento + " " + dados.comprimento; //incremento do comprimento
                aux.pacotes ++; //incremento de pacotes
                tab.adiciona(chave, aux); //devolve os dados para a tabela
            }
        }
        else{
            tab.adiciona(chave, aux); //devolve os dados para a tabela
        }
    }
}

//metodo para retornar a duração da comunicação
string Analisador::duracao(string hr_inicio, string hr_fim){
    
    string tempo, miliseg;
    int resto;
    int hr_1, min_1, seg_1, mili_1, hr_2, min_2, seg_2, mili_2, hr, min, seg, mili;
    
    hr_1 = stoi(hr_inicio.substr(0, hr_inicio.find_first_of(":"))); //conversão de hora para inteiro
    min_1 = stoi(hr_inicio.substr(hr_inicio.find_first_of(":")+1,2)); //conversão de minutos para inteiro
    seg_1 = stoi(hr_inicio.substr(hr_inicio.find_last_of(":")+1,2)); //conversão de segundos para inteiro
    mili_1 = stoi(hr_inicio.substr(hr_inicio.find_first_of(".")+1,6)); //conversão de milisegundos para inteiro
 
    hr_2 = stoi(hr_fim.substr(0, hr_fim.find_first_of(":"))); //conversão de hora para inteiro
    min_2 = stoi(hr_fim.substr(hr_fim.find_first_of(":")+1,2)); //conversão de minutos para inteiro
    seg_2 = stoi(hr_fim.substr(hr_fim.find_last_of(":")+1,2));  //conversão de segundos para inteiro
    mili_2 = stoi(hr_fim.substr(hr_fim.find_first_of(".")+1,6)); //conversão de milisegundos para inteiro
    
    if(mili_2 < mili_1){ //soma dos milisegundos em caso do primeiro ser menor que o segundo
        mili_2 = mili_2 + 1000000;
        seg_2 = seg_2 - 1;
        mili = mili_2 - mili_1;
       
        if ((mili%1000)>500){ //coreção dos milisegundos para ficar com apenas 3 casas decimais
            mili=((mili/1000) + 1); //arredondamento caso seja <500 ou >500 aumenta 1 ou diminui 1
        }
        else{
            mili = mili/1000; //arredondamento caso seja <5 ou >5 aumenta 1 ou diminui 1
        }
    }
    else{ //soma dos milisegundos em caso do segundo ser menor que o primeiro
        mili = mili_2 - mili_1;
        
        if ((mili%1000)>500){ //coreção dos milisegundos para ficar com apenas 3 casas decimais
            mili=((mili/1000) + 1); //arredondamento caso seja <500 ou >500 aumenta 1 ou diminui 1
        }
        else{
            mili = mili/1000; //arredondamento caso seja <5 ou >5 aumenta 1 ou diminui 1
        }
    }
              
    if(seg_2 < seg_1){ //soma dos segundos em caso do primeiro ser menor que o segundo
        min_2 = min_2 - 1;
        seg_2 = seg_2 + 60;
        seg = seg_2 - seg_1;
    }
    else{ //soma dos segundos em caso do segundo ser menor que o primeiro
        seg = seg_2 - seg_1;
    }
            
    if(min_2 < min_1){ //soma dos minutos em caso do primeiro ser menor que o segundo
        hr_2 = hr_2 - 1;
        min_2 = min_2 + 60;
        min = min_2 - min_1;
    }
    else{ //soma dos minutos em caso do segundo ser menor que o primeiro
        min = min_2 - min_1;
    }
    miliseg = to_string(mili); //correção para incluisão de 0(zeros) caso mili seja menor que 100
    if(miliseg.size() == 1){
        miliseg = "00" + miliseg;
    }
    else if(miliseg.size() == 2){ //correção para incluisão de 0(zeros) caso mili seja menor que 100
        miliseg = "0" + miliseg;
    }
    hr = hr_2 - hr_1;
    if(hr > 0){ //criando string para enviar string a impressão
       tempo = to_string(hr) + ":" + to_string(min) + ":" + to_string(seg) + "." + miliseg;
    }
    else if(min > 0){ //criando string para enviar string a impressão
       tempo = to_string(min) + ":" + to_string(seg) + "." + miliseg;
    }
    else{ //criando string para enviar string a impressão
       tempo = to_string(seg) + "." + miliseg;
    }
    return tempo;
}

//metodo para retornar o comprimento
string Analisador::comprimento(string comprimento){
   
    string temp; //variável auxiliar para captação dos valores
    string aux = comprimento +" ";
    int bytes=0; //parametro a retornar da função
    aux.erase(0, aux.find_first_of(" ")+1); //correção de lista, pois ela me retorna duas vezes o primeiro comprimento armazenado
    while(aux.size() != 0){ //laço de repetição para contabilizar a variável comprimento da tabela
        temp = aux.substr(0, aux.find_first_of(" ")); //extração da variável
        aux.erase(0, aux.find_first_of(" ")+1); //correção da string para captação da próxima variável
        bytes = bytes + stoi(temp); //convertendo em inteiro para contabilizar e incrementar
    }
    return to_string(bytes); //variável a retornar do metodo
}

//metodo para gerar arquivo.txt com as informações
void Analisador::imprime_tabela(string IP){
    Dados aux;
    Analisador analisa;
    int comunicacoes = 0;
    int total_bytes = 0;
    int este = 0;
    int outro = 0;
      
    ofstream arq("relatorio.txt"); //gerando arquivo para inicio de escrita
    if (not arq.is_open()) {//tratamento de erro caso nao abra o arquivo
        cerr << "Algum erro ao abrir o arquivo ..." << endl;
    }
    
    auto l1 = tab.chaves(); //transforma as chaves em uma lista de chaves
    
    l1->inicia(); //inicio para a interação com a lista de chaves
        
    while(! l1->fim()){ //inicio de interação com a lista de chaves
      
        string chave = l1->proximo();
        aux = tab[chave];
        string time = aux.hora_fim;
        string chave_aux = chave;
        string ip1 = chave_aux.substr(0,chave_aux.find_first_of(">")-1);
        string ip2 = chave_aux.substr(chave_aux.find_first_of(">")+2, chave_aux.size());
        string port1 = ip1.substr(ip1.find_last_of("."), ip1.size());
        string port2 = ip2.substr(ip2.find_last_of("."), ip2.size());
        
        if(aux.inicio_este == 1){ //organização para colocar ip de inicio de comunicação primeiro
            int pos = ip1.find_last_of(".");
            if(IP == ip1.substr(0,pos)){
                chave = ip1+ " > " + ip2; //tratamento string chave
            }
            else{
                chave = ip2 + " > " + ip1; //tratamento string chave
            }
        }
        if(aux.inicio_outro == 1){ //organização para colocar ip de inicio de comunicação primeiro
            int pos = ip1.find_last_of(".");
            if(IP != ip1.substr(0,pos)){
                chave = ip1+ " > " + ip2; //tratamento string chave
            }
            else{
                chave = ip2 + " > " + ip1; //tratamento string chave
            }
        }
        
        
        if(time.size() != 0){ //filtro para imprissão de todos as comunicações finalizadas, caso hr final de comunicação exista
            string duracao = analisa.duracao(aux.hora_inicio, aux.hora_fim); //envia strings de inicio e fim para calculo das mesmas
            string comprimento = analisa.comprimento(aux.comprimento); //envia uma string para o metodo analisa comprimento para calculo de comprimento
            int pkts = aux.pacotes-1; //soma de pacotes de dados
            total_bytes = total_bytes + stoi(comprimento); //soma do total de bytes trafegados entre as comunicações
            comunicacoes ++; //incremento de dados nas comunicações;
            este = aux.inicio_este + este;  //incremento de dados para comunicações a partir deste computador
            outro = aux.inicio_outro + outro; //incremento de dados para comunicações a partir de outro computador
            arq << chave << ": " << "length=" << comprimento << ", pkts=" << pkts << ", dt=" << duracao << endl;
        }
    }
    //impressão dos restantes do relatório final do projeto
    arq << "Total de bytes: " << total_bytes << endl;
    arq <<"Total de comunicações: " << comunicacoes << endl;
    arq <<"Comunicações deste computador ("<< IP <<"): "<< este << endl;
    arq<<"Comunicações de outros computadores: " << outro << endl;
}