#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <libintl.h>
#include <config.h>

enum { plus, minus, divi, mul };

struct stack{
  struct stack * ptr;
  int value;
}typedef stack;

stack * push_stack(struct stack * stack_ptr, int value){
  stack * temp_stack;
  temp_stack = (stack *)malloc(sizeof(stack *));
  temp_stack->value = value;
  temp_stack->ptr = stack_ptr;
  return temp_stack;
}

int pop_stack(stack * stack_ptr){
  int temp=stack_ptr->value;
  free(stack_ptr);
  return temp;
}

stack * stack_op(char cmd, stack * now_stack){
  int num=0;
  stack * temp_stack;
  switch(cmd){
  case 'c': printf("num = "); fscanf(stdin, "%d", &num); temp_stack=push_stack(now_stack, num); now_stack=temp_stack; break; 
  case 'd': temp_stack=now_stack->ptr; num=pop_stack(now_stack); now_stack=temp_stack; printf("%d", num); break;
  case 'p': printf("%d", now_stack->value); break;
  case '.': printf("%x", now_stack); break;
  case '<': printf("%x", now_stack->ptr); break;
  default: printf(">>"); break;
    /* default: printf("cmd = %c", cmd); break; */
  }
  return now_stack;
}

char * read_buf(char *buf)
{
  char * tmp = (char *)malloc(sizeof(char *)*500000);
  /* for(char tmp_iter[32]; strcmp(tmp_iter, "stop,"); scanf("%s", tmp_iter),strcat(tmp_iter, ",")) */
  /*   strcat(tmp, tmp_iter); */
  scanf("%500000[^\EOF]s", tmp);
  buf = tmp;
  return buf;
}

int main(void)
{
  setlocale(LC_ALL, "");
  bindtextdomain(PACKAGE,LOCALEDIR);
  textdomain(PACKAGE);
  /* printf(">>"); */
  /* char cmd; */
  /* stack * now_stack=(stack *)malloc(sizeof(stack *)); */
  /* stack * temp_stack; */
  /* now_stack->ptr = NULL; */
  /* now_stack->value = 0; */
  /* while((cmd=getchar()) != 'q'){ */
  /*   temp_stack = stack_op(cmd, now_stack); if(temp_stack == NULL){return -1;} now_stack = temp_stack; */
  /* } */
  char *buf;
  buf=read_buf(buf);
  printf("%s", buf);
  return 0;
}
