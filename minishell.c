#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/wait.h>
int main()
{
  while(1){
    printf("[coutinho@localhost]$");
    fflush(stdout);
    char tmp[1024];
    gets(tmp);
    char* argv[32]={NULL};
    char* ptr=tmp;
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
    //for(int j=0;j<i;j++){
    // printf("%s ",argv[j]);
    //}
    pid_t pid=fork();
    if(pid==0){
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
