/*******************************
 * Caulculate Postfix Expression
 * ****************************/
#include<stdio.h>
#include<stdlib.h>
#define Max 100

int main(){
    char Expression[Max];
    gets(Expression);           //read in postfix expression such as 6 2 / 3 - 4 2 * + = 
    double stack[Max];
    int top = -1;               //top of the stack
    int cur = 0;                //current position in array expression
    double num1, num2;
    double outcome = 0;
    while(Expression[cur] != '='){
        if(Expression[cur] >= '0' && Expression[cur] <= '9'){
            stack[++top] = Expression[cur] - '0';
            cur++;
        }else if(Expression[cur] == ' '){
            cur++;
            continue;
        }
        else{
            if(top <= 0){
                printf("Not a postfix expression.");
                exit(0);
            }
            num2 = stack[top--];
            num1 = stack[top--];
            if(Expression[cur] == '+') 
                outcome = num1 + num2;
            else if(Expression[cur] == '-')
                outcome = num1 - num2;
            else if(Expression[cur] == '*')
                outcome = num1 * num2;
            else if(Expression[cur] == '/')
                outcome = num1 / num2;
            else{
                printf("Include invalid character.");
                exit(0);
            }
            stack[++top] = outcome;
            cur++;
        }
    }
    if(top == 0) printf("Answer is %lf", stack[0]);
    else printf("Not a postfix Expression");
    while(1);
}