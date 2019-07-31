/** @file problem2.cpp
 *  @brief Problem Statement 2 :  C program to demonstrate both Zombie process and Orphan Process
 *  @author Ashutosh Chaubey
 */

#include <stdio.h>
#include <unistd.h>

/** @brief Problem Statement 2 entrypoint.
 */
int main() {
   int child = fork(); //create child process
   if (child > 0) //if child is non zero, then it is parent process
      printf("Inside Parent---- PID is : %d\n", getpid());
   else if (child == 0) { //for child process child will be 0
      sleep(50); //wait for some times
      child = fork();
      if (child > 0) {
         printf("Inside Child---- PID :%d and PID of parent : %d\n", getpid(), getppid());
         while(1)
            sleep(1);
         printf("Inside Child---- PID of parent : %d\n", getppid());
      }else if (child == 0)
      printf("Inside grandchild process---- PID of parent : %d\n", getppid());
   }
   return 0;
}