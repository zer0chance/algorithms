#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define POP_AND_CALCULATE switch (op[op_pos])       \
{                                                   \
    case '+':                                       \
        num[num_pos - 1] += num[num_pos];           \
        num_pos--;                                  \
        op_pos--;                                   \
        break;                                      \
    case '-':                                       \
        num[num_pos - 1] -= num[num_pos];           \
        num_pos--;                                  \
        op_pos--;                                   \
        break;                                      \
    case '/':                                       \
        num[num_pos - 1] /= num[num_pos];           \
        num_pos--;                                  \
        op_pos--;                                   \
        break;                                      \
    case '*':                                       \
        num[num_pos - 1] *= num[num_pos];           \
        num_pos--;                                  \
        op_pos--;                                   \
        break;                                      \
    default:                                        \
        return EXIT_FAILURE;                        \
}                                                   \


int isoperation(char op)
{
    switch (op)
    {
        case '+':
            return 1;
        case '-':
            return 1;
        case '/':
            return 1;
        case '*':
            return 1;  
        case '(':
            return 1;
        case ')':
            return 1;                  
        default:
            return 0;
    }
}


int priority(char op) // Returns 1 if operand need to be placed on stack
{
    switch (op)
    {
        case '+':
            return 1;
        case '-':
            return 1;
        case '/':
            return 2;
        case '*':
            return 2;   
        case '(':
            return 0;             
        default:
            return 0;
    }    
}


int handle_expression(char* exp)
{
    char op[20];
    int num[20];

    int op_pos  = -1;
    int num_pos = -1;
    int isNegative = 0;

    if (*exp == '-')
    {
        exp++;
        isNegative = 1;
    }

    while(*exp != '\0')
    {
        printf("%s\n", exp);
        if(isoperation(*exp)) 
        {
            if (*exp == ')') {
                while (op[op_pos] != '(')
                {
                    POP_AND_CALCULATE
                }
                op[op_pos--] = ' ';    // Delete opening bracket '('
            } else if (op_pos == -1) {
                op[++op_pos] = *exp;
            } else if (*exp == '(') {
                op[++op_pos] = *exp;
            } else if (priority(*exp) > priority(op[op_pos])) {
                op[++op_pos] = *exp;        
            } else {
                POP_AND_CALCULATE
                continue;
            }

            exp++;
        } else if(isdigit(*exp)) {
            num[++num_pos] = strtol(exp, &exp, 10);
        } else {
            return EXIT_FAILURE;
        }
    }

    while (op_pos >= 0)
    {
        POP_AND_CALCULATE
    }

    int result = num[0];

    if(isNegative) 
        return result *= (-1);
    else
        return result;
}


int main()
{
    char* exp = "1+2*(3+4/2-(1+2))*2+1";

    int result = handle_expression(exp);

    printf("\n Result: %d \n\n", result);

    return 0;
}
