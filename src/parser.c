#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <libintl.h>
#include <config.h>
#include <stdbool.h>

enum { halt, brancr, brancl, plus, divi, minus, mul };

struct stack{
  struct stack * ptr;
  int value;
  bool op;
}typedef stack;

stack * push_stack(struct stack * stack_ptr, int value, bool op){
  stack * temp_stack;
  temp_stack = (stack *)malloc(sizeof(stack *));
  temp_stack->value = value;
  temp_stack->ptr = stack_ptr;
  temp_stack->op = op;
  return temp_stack;
}

int pop_stack(stack * stack_ptr, bool * ret_op){
  int temp=stack_ptr->value;
  *ret_op = stack_ptr->op;
  free(stack_ptr);
  return temp;
}

stack * exch_stack(stack * stack_ptr){
  stack * temp_stack;
  stack * prev_stack;
  temp_stack = stack_ptr->ptr;
  prev_stack = temp_stack->ptr;
  stack_ptr->ptr = prev_stack;
  temp_stack->ptr = stack_ptr;
  return temp_stack;
}

stack * parse_null(stack * stack_ptr){
  return NULL;
}

stack * parse_first(stack * stack_ptr){
  stack * temp_stack;
  temp_stack = stack_ptr->ptr;
  pop_stack(stack_ptr, NULL);
  return temp_stack;
}

stack * parse_add(stack * stack_ptr){
  
}

stack * tokenize_parse(char * code, stack * now_stack){
  stack * temp_stack;
  stack * nnow_stack;
  nnow_stack = now_stack;
  for(int index=0, num=0; code[index] != EOF; index++){
    switch (code[index]) {
    case ' ': break;
    case '\n': break;
    case '+': temp_stack=push_stack(nnow_stack, plus, true); nnow_stack=temp_stack; break;
    case '-': temp_stack=push_stack(nnow_stack, minus, true); nnow_stack=temp_stack; break;
    case '/': temp_stack=push_stack(nnow_stack, divi, true); nnow_stack=temp_stack; break;
    case '*': temp_stack=push_stack(nnow_stack, mul, true); nnow_stack=temp_stack; break;
    case '(': temp_stack=push_stack(nnow_stack, brancr, true); nnow_stack=temp_stack; break;
    case ')': temp_stack=push_stack(nnow_stack, brancl, true); nnow_stack=temp_stack; break;
    default: if(0<sscanf((char *)(code+index), "%d", &num)){ temp_stack=push_stack(nnow_stack, num, false); nnow_stack=temp_stack; num=sprintf(code, "%d", num); index+=(num-1); }; break;
    }
  }
  return nnow_stack;
}

stack * stack_op(char cmd, stack * now_stack){
  int num=0;
  stack * temp_stack;
  bool op;
  switch(cmd){
  case 'c': printf("num = "); fscanf(stdin, "%d", &num); temp_stack=push_stack(now_stack, num, false); now_stack=temp_stack; break; 
  case 'd': temp_stack=now_stack->ptr; num=pop_stack(now_stack, &op); now_stack=temp_stack; printf("%d:%s", num, op?"op":"val"); break;
  case 'p': printf("%d", now_stack->value); break;
  case '.': printf("%x", now_stack); break;
  case '<': printf("%x", now_stack->ptr); break;
  case 't': printf("tokenize...\ninput code :"); char buf[1000]; fscanf(stdin, "%[^.]", buf); temp_stack=tokenize_parse(buf, now_stack); now_stack=temp_stack; break;
  case 'e': temp_stack = exch_stack(now_stack); now_stack = temp_stack; break;
  default: printf(">>"); break;
    /* default: printf("cmd = %c", cmd); break; */
  }
  return now_stack;
}

char * read_buf(char *buf)
{
  char * tmp = (char *)malloc(sizeof(char *)*50000);
  /* for(char tmp_iter[32]; strcmp(tmp_iter, "stop,"); scanf("%s", tmp_iter),strcat(tmp_iter, ",")) */
  /*   strcat(tmp, tmp_iter); */
  buf = tmp;
  return buf;
}

int main(void)
{
  setlocale(LC_ALL, "");
  bindtextdomain(PACKAGE,LOCALEDIR);
  textdomain(PACKAGE);
  printf(">>");
  char cmd;
  stack * now_stack=(stack *)malloc(sizeof(stack *));
  stack * temp_stack;
  now_stack->ptr = NULL;
  now_stack->value = 0;
  now_stack->op = true;
  while((cmd=getchar()) != 'q'){
    temp_stack = stack_op(cmd, now_stack); if(temp_stack == NULL){return -1;} now_stack = temp_stack;
  }
  char *buf;
  /* buf=read_buf(buf); */
  /* printf("%s", buf); */
  return 0;
}
