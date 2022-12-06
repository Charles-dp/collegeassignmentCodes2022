
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 50

// A stack data structure
typedef struct stack
{
    char stk[MAX];
    int top;
}stack;

// A utility function to check if the given character is operand
int isOperand(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// A utility function to return precedence of a given operator
// Higher returned value means higher precedence
int prec(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
 
    case '*':
    case '/':
        return 2;
 
    case '^':
        return 3;
    }
    return -1;
}
 
// The main function that converts given infix expression
// to postfix expression. 
void infixToPostfix(char* exp, char* postfix)
{
    int i, j;
    stack s;
 
    // Initialize stack
    s.top = -1;
 
    // Iterate through the expression
    for (i = 0, j = -1; exp[i]; ++i)
    {
        // If the scanned character is an operand
        if (isOperand(exp[i]))
            postfix[++j] = exp[i];
 
        // If the scanned character is an '(', push it to the stack.
        else if (exp[i] == '(')
            s.stk[++s.top] = exp[i];
 
        // If the scanned character is an ')', pop and output from the stack 
        // until an '(' is encountered.
        else if (exp[i] == ')')
        {
            while (s.top != -1 && s.stk[s.top] != '(')
                postfix[++j] = s.stk[s.top--];
            s.top--;
        }
 
        // If an operator is scanned
        else
        {
            while (s.top != -1 && prec(exp[i]) <= prec(s.stk[s.top]))
                postfix[++j] = s.stk[s.top--];
            s.stk[++s.top] = exp[i];
        }
    }
 
    // Pop all the remaining elements from the stack
    while (s.top != -1)
        postfix[++j] = s.stk[s.top--];
 
    postfix[++j] = '\0';
}

// A utility function to reverse a string
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        char temp= *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = temp;
        start++;
        end--;
    }
}

//Function to convert infix to prefix
void infixToPrefix(char* exp, char* prefix)
{
    int len = strlen(exp);
 
    // Reverse the expression
    reverse(exp, len);
 
    // Replace ( with ) and vice versa
    for (int i=0; i<len; i++)
    {
        if (exp[i] == '(')
        {
            exp[i] = ')';
            i++;
        }
        else if (exp[i] == ')')
        {
            exp[i] = '(';
            i++;
        }
    }
 
    // Convert to postfix now
    infixToPostfix(exp, prefix);
 
    // Reverse the postfix expression to get prefix
    reverse(prefix, strlen(prefix));
}
 
// Driver program
int main()
{
    char exp[50];
printf("Enter Expression : ");
scanf("%s",&exp);
    char prefix[MAX];
    infixToPrefix(exp, prefix);
    printf("%s\n", prefix);
    return 0;
}
