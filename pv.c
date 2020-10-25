#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

void  main(){
	// 根据 key 创建1个信号量
        int semid=semget(1234,1,IPC_CREAT|0644) ;
        if(semid==-1) perror("semget") , exit(0) ;
        printf("create sem ok\n") ;
}
// set
union semun{
        int val ;
} ;
void  main(){
        int semid = semget(1234,0,0) ;
        printf("val:") ;
    
        union semun su ;    
        scanf("%d",&su.val) ;
    
        semctl(semid,0,SETVAL,su) ;
}

// get
void  main(){
        int semid = semget(1234,0,0) ;
    
        int num = semctl(semid,0,GETVAL,0) ;
        printf("%d\n",num) ;
}

// P
void  main(){
        int semid = semget(1234,0,0) ;
        struct sembuf sb ;
        sb.sem_num = 0 ; 
        sb.sem_op  = -1 ;
        sb.sem_flg = 0 ; 
    
        semop(semid,&sb,1) ;
}
// V
void  main(){
        int semid = semget(1234,0,0) ;
        struct sembuf sb ;
        sb.sem_num = 0 ; 
        sb.sem_op  = 1 ; 
        sb.sem_flg = 0 ; 
        semop(semid,&sb,1) ;
}
