#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/wait.h>
void handler(int s){
        while(waitpid(-1,NULL,WNOHANG)>0) ;
}
int sem_create(int key){
        return semget(key,1,IPC_CREAT|0644) ;
}
union semnu {
        int val ;
} ;
void sem_setval(int semid,int val){
        union semnu su ;
        su.val = val ;
        semctl(semid,0,SETVAL,su) ;
}
void P(int semid){
        struct sembuf sb ;
        sb.sem_num = 0 ;
        sb.sem_op = -1 ;
        sb.sem_flg = 0 ;
        semop(semid,&sb,1) ;
}
void V(int semid){
        struct sembuf sb ;
        sb.sem_num = 0 ;
        sb.sem_op = 1 ;
        sb.sem_flg = 0 ;
        semop(semid,&sb,1) ;
}
void printc(char c,int semid){
        int i ;
        for(i=0;i<10;++i){
                P(semid) ;
                printf("%c",c) ;
                fflush(stdout) ;
                sleep(rand()%2) ;
                printf("%c",c) ;
                fflush(stdout) ;
                sleep(rand()%2) ;
                V(semid) ;
        }
}
void main(){
        struct sigaction act ;
        act.sa_handler = handler ;
        act.sa_flags = 0 ;
        sigemptyset(&act.sa_mask) ;
        sigaction(SIGCHLD,&act,NULL) ;
        srand(getpid()) ;
        int semid = sem_create(1234) ;
        sem_setval(semid,1) ;
        pid_t pid = fork() ;
        if(pid == 0){
                printc('O',semid) ;
        }else{
                printc('X',semid) ;
                // wait(NULL) ;
        }
}
