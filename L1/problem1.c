/** @file problem1.c
 *  @brief Problem Statement 1 : Prints process_ids of created child and grandchild processes
 *
 *  @author Ashutosh Chaubey
 */

#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h> 

/** @brief Problem Statement 1 entrypoint.
 */
int main()

{
  int process_id = -1, process_id1 = -1, process_id2 = -1, process_id11 = -1, process_id12 = -1, process_id21 = -1, process_id22 = -1;
  int new_process_id = getpid();

  process_id1 = fork(); // child1
  process_id2 = fork(); // child2

  if(process_id1>0 && process_id2>0){ //parent
    
    printf("1st child process_id: %d..(%d).\n2nd child process_id: %d.\n", process_id1, new_process_id, process_id2);
  }
  else if(process_id1==0 && process_id2>0)
  { // child1
    process_id11 = process_id2;
    process_id12 = fork();
   
    if(process_id12 != 0){ // child1
      printf("1st Grandchild process_id: %d.\n2nd Grandchild process_id: %d.\n", process_id11, process_id12);
    }
  }

  else if(process_id2==0 && process_id1!=0){
    int i = 1000000;
    while (i > 0){
      i--;
    }
    process_id21 = fork();
    if(process_id21 != 0){ //child2
   
      process_id22 = fork();
      if(process_id22 != 0){ //child2
     
        printf("3rd Grandchild process_id: %d.\n4th Grandchild process_id: %d.\n", process_id21, process_id22);
       
        printf("Parent process_id: %d.\n", new_process_id);
      }
    }
  }
}