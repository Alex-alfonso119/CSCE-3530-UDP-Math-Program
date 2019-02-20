/*
	Alexander Alfonso (aja0167)	CSCE PROGRAM 3 server
*/

#include <math.h>
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAXSIZE 1024


struct Stack
{
	int topIndex;		//	top index
	char arr[MAXSIZE];	//	stack
	double resultStack[MAXSIZE];
	int resultsIndex;
	int size;
};


struct Stack* initStack(int s)
{
	struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->size = s;
    stack->topIndex = -1;
    stack->resultsIndex = -1;
    return stack;
}

int size(struct Stack* stack)
{
	if(stack->topIndex != -1)
	{
		return stack->topIndex+1;
	}
}

int sizeResult(struct Stack* stack)
{
	if(stack->resultsIndex != -1)
	{
		return stack->resultsIndex+1;
	}
}

char top(struct Stack* stack)
{
	char c = stack->arr[stack->topIndex];
	return c;
}

double topResult(struct Stack* stack)
{
	double d = stack->resultStack[stack->resultsIndex];
	return d;
}

int isFull(struct Stack* stack)
{
	return (stack->topIndex == stack->size - 1);
}

int isEmpty(struct Stack* stack)
{
	int check = 0;

	if(stack->topIndex == -1)
	{
		check = 1;
	}
	return check;
}

int isResultsEmpty(struct Stack* stack)
{
	int check = 0;

	if(stack->resultsIndex == -1)
	{
		check = 1;
	}
	return check;
}

void push(struct Stack* stack, char c)
{
	if(isFull(stack))
	{
		return;
	}
	else
	{
		stack->arr[++stack->topIndex] = c;
	}
}

void pushResult(struct Stack* stack, double d)
{
	if(isFull(stack))
	{
		return;
	}
	else
	{
		stack->resultStack[++stack->resultsIndex] = d;
	}
}

void pop(struct Stack* stack)
{
	if(!isEmpty(stack))
	{
		stack->arr[stack->topIndex] = '\0';
		stack->topIndex--;
	}
	return;
}

void popResult(struct Stack* stack)
{
	if(stack->resultsIndex != -1)
	{
		stack->resultStack[stack->resultsIndex] = '\0';
		stack->resultsIndex--;
	}
	return;
}

void display(struct Stack* stack)
{
	int i;
	printf("> stack <\n");
	for(i=stack->topIndex; i != -1; i--)
	{	
		printf("%c \n", stack->arr[i]);
	}
	printf("---------\n");
}

void displayResult(struct Stack* stack)
{
	int i;
	printf("> result stack <\n");
	for(i=stack->resultsIndex; i != -1; i--)
	{	
		printf("%0.4f \n", stack->resultStack[i]);
	}
	printf("----------------\n");
}


int precedence(char c)
{
	if(c == '+' || c == '-'){
	return 1;
	}
	if(c == '*' || c == '/'){
	return 2;
	}
	if(c == '^')// || c == '#'){
	{
	return 3;
	}
	if(c == '!' || c == '@' || c == '$' || c == '#')	//	sin, cos, log
	{
		return 4;	//	 
	}
	return -1;
}

int isOperator(char c)
{
	int check = 0;

	if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
	{
		check = 1;
	}
	return check;
}

int regTokenOp(char *c)
{
	int check = 0;

	if(strcmp(c, "+") == 0)
	{
		check = 1;
	} 
	else if (strcmp(c, "-") == 0)
	{
		check = 2;
	} 
	else if (strcmp(c, "*") == 0)
	{
		check = 3;
	} 
	else if (strcmp(c, "/") == 0)
	{
		check = 4;
	} 
	else if (strcmp(c, "^") == 0)
	{
		check = 5;
	}

	return check;
}

int specTokenOp(char *c)
{
	int check = 0;

	if (strcmp(c, "!") == 0)
	{
		check = 1;
	}
	else if  (strcmp(c, "@") == 0)
	{
		check = 2;
	}
	else if  (strcmp(c, "#") == 0)
	{
		check = 3;
	}
	else if  (strcmp(c, "$") == 0)
	{
		check = 4;
	}

	return check;
}

int isE(char *c)
{
	int check = 0;
	if(strcmp(c, "e") == 0)
	{
		check = 1;
	}
	return check;
}

int isTokenOperator(char *c)
{

	int check = 0;

	if(strcmp(c, "+") == 0)
	{
		check = 1;
	} 
	else if (strcmp(c, "-") == 0)
	{
		check = 1;
	} 
	else if (strcmp(c, "*") == 0)
	{
		check = 1;
	} 
	else if (strcmp(c, "/") == 0)
	{
		check = 1;
	} 
	else if (strcmp(c, "^") == 0)
	{
		check = 1;
	}
	else if  (strcmp(c, "!") == 0)
	{
		check = 1;
	}
	else if  (strcmp(c, "@") == 0)
	{
		check = 1;
	}
	else if  (strcmp(c, "#") == 0)
	{
		check = 1;
	}
	else if  (strcmp(c, "$") == 0)
	{
		check = 1;
	}

	return check;
}

int specOperator(char c)
{
	int check = 0;
	if(c == '!' || c == '@' || c == '#' || c == '$')
	{
		check = 1;
	}
	return check;
}

int isSpecialOperator(char a, char b, char c, char d)
{
	int check = 0;

	if (a == 's' && b == 'i' && c == 'n' && d == '(')
	{
		//	represented as '!'
		check = 1;
	}
	else if (a == 'c' && b == 'o' && c == 's' && d == '(')
	{
		//	represented as '@'
		check = 2;
	}
	else if (a == 's' && b == 'q' && c == 'r' && d == 't')
	{
		//	represented as '#'
		check = 3;
	}
	else if (a == 'l' && b == 'o' && c == 'g' && d == '(')
	{
		//	represented as '$'
		check = 4;
	}

	return check;
}

char* infixToPostfix(struct Stack* stack, char input[])
{
	int i, j, next;
	int op;
	char test[MAXSIZE];
	const char space = ' ';

	for(i=0, j= -1;i<strlen(input); i++)
	{
		if(isdigit(input[i]))
		{	
			next = i+1;

			test[++j] = input[i];

			//	check for multiple digits
			while(isdigit(input[next]) && !isspace(input[next]) && !isOperator(input[next]))
			{
				test[++j] = input[next];
				next++;
			}
			i += (next - i - 1);

			test[++j] = space;
		}
		else if (input[i] == '(' && !isSpecialOperator(input[i-3], input[i+-2], input[i-1], input[i]))
		{
			push(stack, input[i]);
		}
		else if (input[i] == ')' && !isSpecialOperator(input[i-3], input[i+-2], input[i-1], input[i]))
		{
			while(!isEmpty(stack) && top(stack) != '(')
			{
				test[++j] = top(stack);
				pop(stack);
				test[++j] = space;
			}
			if(!isEmpty(stack) && top(stack) != '(')
			{
				printf("error: invalid expression\n");
				exit(0);
			}
			else
			{
				pop(stack);
			}
		}
		else if (isOperator(input[i]))
		{
			while(!isEmpty(stack) && precedence(input[i]) <= precedence(top(stack)))
			{
				test[++j] = top(stack);
				pop(stack);
				test[++j] = space;
			}
			push(stack, input[i]);
		}
		else if (input[i] == 'e')
		{
			test[++j] = input[i];
			test[++j] = space;
		}
		//	not working correctly yet
		else if (isSpecialOperator(input[i], input[i+1], input[i+2], input[i+3]))
		{
			op = isSpecialOperator(input[i], input[i+1], input[i+2], input[i+3]);

			switch(op)
			{
				case 1:	//	sin(x)
					push(stack, '!');
					break;
				case 2:	//	cos(x)
					push(stack, '@');
					break;
				case 3:	//	sqrt(x)
					push(stack, '#');
					break;
				case 4:	//	log(x)
					push(stack, '$');
					break;
			}
		}
		else if (isspace(input[i]))
		{	
			//	skip reading whitespace and execute next iteration
			continue;
		}
	}

	while (!isEmpty(stack))
	{
		test[++j] = top(stack);
		pop(stack);
		test[++j] = space;
	}
	test[++j] = '\0';

	//printf("postfix exp: %s\n", test);

	input = test;

	return input;
}

double evalPostfix(struct Stack* stack, char* exp)
{
	double result = 0.0;
	int i, j=0, next;
	char line[MAXSIZE];	
	char templine[MAXSIZE];
	double val;
	strcpy(line, exp);

	int k, count = 0;

	char *token = strtok(line, " ");
	while(token != NULL)
	{
		val = atof(token);

		if(!isTokenOperator(token) && !isE(token))	//	if its a number
		{
			pushResult(stack, val);
		}
		else if (isE(token))
		{
			pushResult(stack, 2.71828);
		}
		else if (isTokenOperator(token))
		{
			if(regTokenOp(token))
			{
				double y = topResult(stack);
				popResult(stack);

				double x = topResult(stack);
				popResult(stack);


				k = regTokenOp(token);

				switch(k)
				{
					case 1:
						result = x + y;
						pushResult(stack, result);
						break;
					case 2:
						result = x - y;
						pushResult(stack, result);
						break;
					case 3:
						result = x * y;
						pushResult(stack, result);
						break;
					case 4:
						result = x / y;
						pushResult(stack, result);
						break;
					case 5:
						result = pow(x, y);
						pushResult(stack, result);
						break;
				}
			}
			else if (specTokenOp(token))
			{

				double y = topResult(stack);
				popResult(stack);

				k = specTokenOp(token);

				switch(k)
				{
					case 1:	//	sin
						result = sin(y);
						pushResult(stack, result);
						break;
					case 2:	//	cos
						result = cos(y);
						pushResult(stack, result);
						break;
					case 3:	//	sqrt
						result = sqrt(y);
						pushResult(stack, result);
						break;
					case 4:	//	log
						result = log10(y);
						pushResult(stack, result);
						break;
				}
			}
		}
		token = strtok(NULL, " ");
	}

	//	if the user only inputs "e" and nothing else
	if(!isResultsEmpty(stack))
	{
		double e = topResult(stack);
		popResult(stack);
		result = e;
	}

	return result;
}

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv[])
{
	struct Stack* stack;
	char buf[MAXSIZE];
	char* postfixExp;
	double result = 0.0;

	struct sockaddr_in si_me, si_other;
	int s, i, slen = sizeof(si_other) , recv_len;

	stack = initStack(MAXSIZE);

	if(argc != 2)
	{
		printf("usage: ./executable port\n");
		exit(0);
	}
	int portno = atoi(argv[1]);
	
	 //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(portno);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }

    //keep listening for data
    while(1)
    {
    	memset(buf,'\0', MAXSIZE);	

        printf("Waiting for data...\n");
        fflush(stdout);
         
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, MAXSIZE, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
         
        //print details of the client/peer and the data received
        printf("-----\nReceived packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));

        printf("Data: %s\n" , buf);

        //	if user enters only <enter> then it will quit prematurely. 
        if(strncmp(buf, "quit\n", strlen(buf)) == 0)
        {
        	printf("quit received. terminating program...\n");

        	close(s);
        	exit(0);
        }
        else
        {
        	//	does NOT detect invalid expressions
        	//	convert client input to a postfix expression
			postfixExp = infixToPostfix(stack, buf);
			printf("postfixExp: %s\n", postfixExp);

			//	evaluate the postfix expression
			result = evalPostfix(stack, postfixExp);
			printf("result: %0.4f\n", result);
			snprintf(buf, MAXSIZE, "result: %0.4f", result);

			//now reply the client with the result
	        if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
	        {
	            die("sendto()");
	        }
        }

        
    }			

	close(s);
	return 0;
}
