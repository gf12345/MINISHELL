#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/wait.h>
#include<string.h>
#include <fcntl.h>
int main()
{
  while(1){
    printf("[coutinho@localhost]$");
    fflush(stdout);
    char tmp[1024];
    gets(tmp);
    char *ptr=tmp;
    char* argv[32]={NULL};
    int num=0;
    char *file=NULL;
    while(*ptr!='\0'){
      if(*ptr=='>'){
        *ptr='\0';
        num=1;
        ptr++;
        if(*ptr=='>'){
          num=2;
          *ptr='\0';
          ptr++;
        } 
        while(*ptr==' '&&*ptr!='\0')
          ptr++;
        file=ptr;
        while(*ptr!=' '&&*ptr!='\0')
          ptr++;
        *ptr='\0';
      }
      ptr++;
    }
    ptr=tmp;
    int i=0;
    while(*ptr!='\0'){
      if(*ptr!=' '/*!isspace(*ptr)*/){
        argv[i]=ptr;
        i++;
        while(*ptr!=' '&&*ptr!='\0'){
          ptr++;
        }
        *ptr='\0';
      }
      ptr++;
    }
    argv[i]=NULL;
    // for(int j=0;j<i;j++){
    // printf("%s\n",argv[j]);
    //}
    if(strcmp(argv[0],"cd")==0){
      chdir(argv[1]);
      continue;
    }
    pid_t pid=fork();
    if(pid==0){
      if(num==1){
        int fd1=open(file,O_RDWR|O_CREAT|O_TRUNC);
        dup2(fd1,1);
      }
      else if(num==2){
        int fd2=open(file,O_RDWR|O_CREAT|O_APPEND);
        dup2(fd2,1);
      }
      execvp(argv[0],argv);
      exit(0);
    }
    else if(pid<0){
      perror("fork error\n");
      return -1;
    }
    wait(NULL);//等待子进程退出
  }
  return 0;
}
