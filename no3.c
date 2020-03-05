#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
int count=1;
  while (1) {
    // Tulis program kalian di sini
    FILE *ygDiBuka, *untukBackup;
    
    char nama[80],pch; 
    ygDiBuka=fopen("/home/seijaku/Documents/Sisop/Latihan2/diary.txt", "r+");
    if(ygDiBuka == NULL)
    {
      printf("Invalid Input\n");
      exit(0);
    }
    snprintf(nama, 53, "/home/seijaku/Documents/Sisop/Latihan2/diary.log.%d",count);
    //printf("%s\n",nama);
    count++;  
    untukBackup=fopen(nama, "w+");
    if(untukBackup == NULL)
    {
      printf("Output bermasalah\n");
      fclose(untukBackup);
      exit(0);
    }
    while((pch = fgetc(ygDiBuka)) != EOF){
        fputc(pch,untukBackup);
    }
    //putw(count,untukBackup);
    fclose(untukBackup);
    fclose(ygDiBuka);
    ygDiBuka=fopen("/home/seijaku/Documents/Sisop/Latihan2/diary.txt", "w");
    fclose(ygDiBuka);
    sleep(10);
  }
}