#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char str[200];
int c=0;

void Program();
void declarations();
void identifier_list();
void statement_list();
void statement();
void assign_stat();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();

void invalid(char *msg)
{
	printf("ERROR: expected %s at position %d\n", msg, c);
	exit(0);
}

void valid()
{
	printf("-----------SUCCESS-----------\n");
	exit(0);
}

/* Program -> main(){ declarations statement_list } */

void Program()
{
	if(strncmp(&str[c],"main",4)==0)
	{
		c+=4;

		if(str[c]=='(')
		{
			c++;
			if(str[c]==')')
			{
				c++;

				if(str[c]=='{')
				{
					c++;

					declarations();
					statement_list();

					if(str[c]=='}')
					{
						c++;
						return;
					}
					else invalid("'}'");
				}
				else invalid("'{'");
			}
			else invalid("')'");
		}
		else invalid("'('");
	}
	else invalid("'main'");
}

/* identifier_list -> id | id[number] | id , identifier_list */

void identifier_list()
{
	if(isalpha(str[c]))
	{
		c++;

		if(str[c]=='[')
		{
			c++;

			if(isdigit(str[c]))
			{
				while(isdigit(str[c])) c++;

				if(str[c]==']')
					c++;
				else
					invalid("']'");
			}
			else invalid("number");
		}

		if(str[c]==',')
		{
			c++;
			identifier_list();
		}
	}
	else
		invalid("identifier");
}

/* declarations */

void declarations()
{
	if(isalpha(str[c]))
	{
		identifier_list();

		if(str[c]==';')
			c++;
		else
			invalid("';'");
	}
}

/* statement_list */

void statement_list()
{
	while(isalpha(str[c]))
	{
		statement();
	}
}

/* statement -> assign_stat ; */

void statement()
{
	assign_stat();

	if(str[c]==';')
		c++;
	else
		invalid("';'");
}

/* assign_stat -> id = expn */

void assign_stat()
{
	if(isalpha(str[c]))
	{
		c++;

		if(str[c]=='=')
		{
			c++;
			expn();
		}
		else
			invalid("'='");
	}
	else
		invalid("identifier");
}

/* expn -> simple_expn eprime */

void expn()
{
	simple_expn();
	eprime();
}

/* eprime -> relop simple_expn | e */

void eprime()
{
	if(str[c]=='<' || str[c]=='>' || str[c]=='!' || str[c]=='=')
	{
		relop();
		simple_expn();
	}
}

/* simple_expn -> term seprime */

void simple_expn()
{
	term();
	seprime();
}

/* seprime -> addop term seprime | e */

void seprime()
{
	if(str[c]=='+' || str[c]=='-')
	{
		addop();
		term();
		seprime();
	}
}

/* term -> factor tprime */

void term()
{
	factor();
	tprime();
}

/* tprime -> mulop factor tprime | e */

void tprime()
{
	if(str[c]=='*' || str[c]=='/' || str[c]=='%')
	{
		mulop();
		factor();
		tprime();
	}
}

/* factor -> id | num */

void factor()
{
	if(isalpha(str[c]))
	{
		c++;
	}
	else if(isdigit(str[c]))
	{
		while(isdigit(str[c])) c++;
	}
	else
		invalid("identifier or number");
}

/* relop */

void relop()
{
	if(str[c]=='<' || str[c]=='>' || str[c]=='=' || str[c]=='!')
	{
		c++;

		if(str[c]=='=')
			c++;
	}
	else
		invalid("relational operator");
}

/* addop */

void addop()
{
	if(str[c]=='+' || str[c]=='-')
		c++;
	else
		invalid("'+' or '-'");
}

/* mulop */

void mulop()
{
	if(str[c]=='*' || str[c]=='/' || str[c]=='%')
		c++;
	else
		invalid("'*' '/' or '%'");
}

int main()
{
	printf("Enter string: ");
	scanf("%s",str);

	Program();

	if(str[c]=='$')
		valid();
	else
		invalid("'$'");
}
