#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sstream>

using namespace std;

int shmid;
int size = 1024 ;
char *mem;
int flag = 0;
char *ptr_msg;
int i;

int main(int argc, char** argv) {
    
	char *mem = (char*)argv[0];
	int soma = stoi(mem);
    int meu_saldo = soma;
    int novo_saldo = meu_saldo + 4*100;
    printf("Novo saldo = %i ", novo_saldo);
    soma = novo_saldo;
    printf(" -  Pid = %d \n", getpid());
    string no = to_string(soma);   
    ptr_msg = (char*) malloc (256);         
    strcpy((char*)ptr_msg, no.c_str()); 
    strcpy(mem, (char*)ptr_msg); //compartilhando a memoria]
	sleep(2);

	execl("./filho5", mem,  (char  *) NULL );

    return (EXIT_SUCCESS);
}


