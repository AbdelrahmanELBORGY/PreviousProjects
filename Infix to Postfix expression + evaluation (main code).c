#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float data;
    struct node *next;
}node;
typedef struct{
    node *top;
}Stack;

Stack* initialize()
{
    Stack *s = malloc (sizeof(Stack));
    s->top = NULL;
    return s;
}
node* newnode (float x)
{
    node* n = malloc(sizeof(node));
    n->data = x;
    n->next = NULL;

    return n;
}
void push(Stack *s, float x)
{
    node *n = newnode(x);

    if(s->top == NULL)
       s->top= n;
    else{
        n->next = s->top;
        s->top = n;
        }
}
int isEmpty(Stack *s)
{
    return (s->top == NULL);
}
float pop(Stack *s)
{
    if (!isEmpty(s))
    {
        if (s->top->next == NULL)
        {
            float x = s->top->data;
            free (s->top);
            s->top = NULL;
            return x;
        }
        else{

            node *temp = s->top;
            float y = s->top->data;
            s->top = s->top->next ;
            free(temp);
            return y;
        }
    }
}

float peek (Stack *s)
{
    if(s->top != NULL)
    return s->top->data;
}

int priority(char op)
{
    if(op== '+' || op == '-')
        return 1;
    else if(op== '*' || op == '/' || op == '%')
        return 2;
     else if(op== '^')
        return 3;
    else return 0;
}

int isOperator(char c)
{
    if (c== '(' || c== ')' || c== '+' || c== '-' || c== '*' || c== '/' || c== '%' || c== '^' )
return 1;
else return 0;
}

char* infixTopostfix(char* infix)
{
    int i, j = 0;
    Stack* s = initialize();
    char* post = malloc(strlen(infix) + 1);
    char * portion = strtok(infix, " ");
    while(portion != NULL)
    {
        if(isdigit(portion[0]) || (isdigit(portion[1]) && strlen(portion) > 1 ))
        {
            for(i = 0 ; i < strlen(portion) ; i++)
            {
                post[j++] = portion[i];
            }
            post[j++] = ' ';
        }
        else if(isEmpty(s) ||( peek(s) == '(' && portion[0] != ')'))
        {
            push(s, portion[0]);
        }
        else if(portion[0] == ')')
        {
            while(peek(s) != '(')
            {
                post[j++] = pop(s);
                post[j++] = ' ';
            }
            pop(s);
        }
        else if(portion[0] == '(')
        {
            push(s, portion[0]);
        }
        else
        {
            while(!isEmpty(s) && priority(peek(s)) >= priority(portion[0]))
            {
                post[j++] = pop(s);
                post[j++] = ' ';
            }
            push(s, portion[0]);
        }
        portion = strtok(NULL, " ");
    }
    while(!isEmpty(s))
    {
        post[j++] = pop(s);
        post[j++] = ' ';
    }
    post[--j] = '\0';
    return post;
}

float evaluate(char* x, float op1, float op2)
{
   if(strcmp(x,"+") == 0)
       return op1 + op2;

   if(strcmp(x,"-") == 0)
       return op1 - op2;

   if(strcmp(x,"*") == 0)
       return op1 * op2;

   if(strcmp(x,"/") == 0)
        return (op1/op2);
   if(strcmp(x,"^") == 0)
        return (pow(op1, op2));
}

float convFloat(char* exp)
{
    float x;
   if( strcmp(exp ,"+") != 0 && strcmp(exp ,"-") != 0  && strcmp(exp  ,"*") != 0 && strcmp(exp,"/") != 0 && strcmp(exp  ,"%") !=0 && strcmp(exp  ,"^") !=0)
   {
       x= atof(exp);
       return x;
   }
   else return 0;
}

int isFloat(char* exp)
{
    if( strcmp(exp ,"+") != 0 && strcmp(exp ,"-") != 0  && strcmp(exp  ,"*") != 0 && strcmp(exp,"/") != 0 && strcmp(exp  ,"%") !=0 && strcmp(exp  ,"^") !=0)
            return 1;
    else return 0;

}
float evaluatePostfix(char *exp)
{
    Stack *s = initialize();
    float op1, op2, val;
    float x;
    char *portion = strtok(exp," ");
    while(portion != NULL)
    {
        if(isFloat(portion))
        {
            x= convFloat(portion);
            push(s, x);

        }

     else
        {
            op2 =pop(s);
            op1 =pop(s);
            val= evaluate(portion, op1, op2);
            push(s,val);

        }
       portion = strtok(NULL, " ");
    }
    val =pop(s);
    return val;
}

int main()
{
    int i,j;
    char infix[100];
    printf("Enter INFIX expression (include spaces): \n");
    printf("Example: 2 + ( -2.5 + 3.14 ) * ( -5.4 + 8.1 ) ^ ( -0.5 )\n");
    gets(infix);
    char postfix[100];
    strcpy(postfix, infixTopostfix(infix));
    printf("POSTFIX expression: %s",postfix);
    float y = evaluatePostfix(postfix);
    printf("\nResult of Expression: %.2f\n", y);
    return 0;
}
