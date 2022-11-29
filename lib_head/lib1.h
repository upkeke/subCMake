#ifdef  __cplusplus
extern "C" {
#endif

#ifndef EX_LIB1_H
#define EX_LIB1_H

#include <string>

typedef void (*FUNP)();
typedef void (*FUNP1)(char *ch);
void hello();
void echo(char *text);
void printUser(char *user, unsigned int age);
char *getName(char *userName);
int sum(int a, int b);
void *getVoidData(void *data);
void *getVoidData1(void *data, int *addr);
void callback(FUNP funp);
void callback1(FUNP1 funp1, char *text);

#endif

#ifdef  __cplusplus
}
#endif