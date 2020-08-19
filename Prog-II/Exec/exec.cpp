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
#include <cstdlib>

using namespace std;

int shmid;
int size = 1024 ;
char *mem ;
int flag = 0;
char *ptr_msg;

int main(int argc, char** argv) {
    
    int saldo = 1000;
    int f, p;
    shmid = shmget (IPC_PRIVATE, size, S_IRUSR | S_IWUSR);
    if (shmid == -1) {
        perror("Erro na memoria");
        exit(1) ;
    }
    
    mem =(char *) shmat(shmid, 0, flag);
    if (mem == (char *)(-1)) {
	perror("shmat");
	exit(1);
    }
    
    string aux = to_string(saldo);
    
    ptr_msg = (char*) malloc (256);         
    strcpy((char*)ptr_msg, aux.c_str());
    strcpy(mem, (char*)ptr_msg); //compartilhando a memoria
 
    execl("./filho1", mem,  (char  *) NULL );
    
    return 0;
}

