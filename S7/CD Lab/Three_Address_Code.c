#include <stdio.h>
#include <ctype.h>
#include <string.h>

char stack[100];
int top = -1;

int tempCount = 0;

void push(char c) 
{
  stack[++top] = c;
}

char pop() 
{
  return stack[top--];
}

int precedence(char c) 
{
  if (c == '+' || c == '-') return 1;
  if (c == '*' || c == '/') return 2;
  return 0;
}

// Convert infix to postfix
void infixToPostfix(char infix[], char postfix[]) {
  int i, k = 0;
  for (i = 0; infix[i] != '\0'; i++) 
  {
    char ch = infix[i];
    if (isalnum(ch)) 
    {
      postfix[k++] = ch;
    } 
    else if (ch == '(') 
    {
      push(ch);
    } 
    else if (ch == ')') 
    {
      while (top != -1 && stack[top] != '(') 
      {
        postfix[k++] = pop();
      }
      pop(); // remove '('
    } 
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') 
    {
      while (top != -1 && precedence(stack[top]) >= precedence(ch)) 
      {
        postfix[k++] = pop();
      }
      push(ch);
    }
  }
  while (top != -1) 
  {
    postfix[k++] = pop();
  }
  postfix[k] = '\0';
}

// Generate intermediate code from postfix
void generateTAC(char postfix[], char lhs) 
{
  char st[100][100];
  int t = -1;
  char temp[3];
  for (int i = 0; postfix[i] != '\0'; i++) 
  {
    char ch = postfix[i];
    if (isalnum(ch)) 
    {
      char str[2] = {ch, '\0'};
      strcpy(st[++t], str);
    } 
    else 
    {
      char op2[100], op1[100];
      strcpy(op2, st[t--]);
      strcpy(op1, st[t--]);
      sprintf(temp, "T%d", ++tempCount);
      printf("%s = %s %c %s\n", temp, op1, ch, op2);
      strcpy(st[++t], temp);
    }
  }
  printf("%c = %s\n", lhs, st[t]);
}

int main() 
{
  char expr[100];
  printf("Enter the expression: ");
  scanf("%s", expr);
  char lhs = expr[0]; // LHS of assignment
  char rhs[100];
  strcpy(rhs, expr + 2); // RHS after '='
  char postfix[100];
  infixToPostfix(rhs, postfix);
  printf("\nIntermediate Code (Three Address Code):\n\n");
  generateTAC(postfix, lhs);
  return 0;
}

explain line by line
