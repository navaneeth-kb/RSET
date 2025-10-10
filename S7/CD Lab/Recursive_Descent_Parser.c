#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char input[100];
int i = 0;

// E → T Eʹ
// Eʹ → + T Eʹ | ε
// T → F Tʹ
// Tʹ → * F Tʹ | ε
// F → (E) | id

void E();
void Eprime();
void T();
void Tprime();
void F();

void skipSpaces() {
  while (input[i] == ' ')
    i++;
}

void error() {
  printf("Invalid expression\n");
  exit(0);
}

void match(char t) {
  skipSpaces();
  if (input[i] == t) {
    i++;
  } 
  else 
  {
    error();
  }
}

void E() {
  skipSpaces();
  T();
  Eprime();
}

void Eprime() {
  skipSpaces();
  if (input[i] == '+') {
    match('+');
    T();
    Eprime();
  }
  // else epsilon → do nothing
}

void T() {
  skipSpaces();
  F();
  Tprime();
}

void Tprime() {
  skipSpaces();
  if (input[i] == '*') {
    match('*');
    F();
    Tprime();
  }
  // else epsilon → do nothing
}

void F() {
  skipSpaces();
  if (input[i] == '(') {
    match('(');
    E();
    match(')');
  } 
  else if (strncmp(&input[i], "id", 2) == 0) {
    i += 2; // consume "id"
  } 
  else {
    error();
  }
}

int main() {
  printf("Enter expression: ");
  fgets(input, sizeof(input), stdin);
  input[strcspn(input, "\n")] = '\0'; // strip newline
  E();
  skipSpaces();
  if (input[i] == '\0')
    printf("Valid expression\n");
  else
    printf("Invalid expression\n");
  return 0;
}
