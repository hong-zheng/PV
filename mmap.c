
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

struct stu{
        long id ;
        char name[1024] ;
} ;

void hand(int s){ 
        printf("recv %d\n",s) ;
        exit(0) ;
}

void main(){
        struct sigaction act ;
        act.sa_handler = hand ;
        act.sa_flags = 0 ; 
        sigemptyset(&act.sa_mask) ;
        sigaction(SIGBUS,&act,NULL) ;

        int fd = open("tmp.txt",O_RDWR|O_CREAT|O_TRUNC,0644) ;
        struct stu* p = (struct stu*)mmap(NULL,sizeof(struct stu),PROT_READ|PROT_WRITE|PROT_EXEC,MAP_SHARED,fd,0) ;     
        ftruncate(fd,sizeof(struct stu)) ;
        p->id = 10 ;
        strcpy(p->name,"zhenghong") ;

        munmap(p,sizeof(struct stu)) ;
        close(fd) ;
}


/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>


struct stu{
        long id ;
        char  name[1024] ;
} ;
void main(){
        int fd = open("tmp.txt",O_RDWR) ;
        struct stu* p = (struct stu*)mmap(NULL,sizeof(struct stu),PROT_READ,MAP_SHARED,fd,0) ;  
        printf("%d\n",p->id) ;
        printf("%s\n",p->name) ;
        munmap(p,sizeof(struct stu)) ;

        printf("%d\n",sizeof(long)) ;
        printf("%d\n",sizeof(int)) ;
}


*/
