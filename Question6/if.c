/* front.c - a lexical analyzer system for simple
 arithmetic expressions */
#include <stdio.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define IF_CODE 12
#define ELSE_CODE 13
#define WHILE_CODE 14
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define MOD_OP 27
#define AND 28
#define OR 29
#define NOT 30
#define DOUBLE 31
#define INT 32
#define FLOAT 33
#define EMPTY_FUNC 34

/******************************************************/
/* main driver */
int main(void) {
	/* Open the input data file and process its contents */
	 if ((in_fp = fopen("front.in", "r")) == NULL)
	 	printf("ERROR - cannot open front.in \n");
	 else {
	 	getChar();
	 do {
	 	lex();
	 } while (nextToken != EOF);
	 }
	 return 0;
}
/******************************************************/
/* lookup - a function to look up operators and
 parentheses and return the token */
int lookup(char ch) {
	 switch (ch) {
		 case '(':
			 addChar();
			 nextToken = LEFT_PAREN;
			 break;
		 case ')':
			 addChar();
			 nextToken = RIGHT_PAREN;
			 break;
		 case '+':
			 addChar();
			 nextToken = ADD_OP;
			 break;
		 case '-':
			 addChar();
			 nextToken = SUB_OP;
			 break;
		 case '*':
			 addChar();
			 nextToken = MULT_OP;
			 break;
		 case '/':
			 addChar();
			 nextToken = DIV_OP;
			 break;
         case '%':
			 addChar();
			 nextToken = MOD_OP;
			 break;
		 default:
			 addChar();
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = '\0';
	} else
	printf("Error - lexeme is too long \n");
}


/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(void) {
	 if ((nextChar = getc(in_fp)) != EOF) {
		 if (isalpha(nextChar))
		 	charClass = LETTER;
		 else if (isdigit(nextChar))
		 	charClass = DIGIT;
		 else
		 	charClass = UNKNOWN;
	 } else
	 	charClass = EOF;
}


/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
	while (isspace(nextChar))
	getChar();
}

/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex(void) {
	 lexLen = 0;
	 getNonBlank();
	 switch (charClass) {
		/* Identifiers */
		 case LETTER:
			 addChar();
			 getChar();
			 while (charClass == LETTER || charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
			 nextToken = IDENT;
			 break;
		/* Integer literals */
		 case DIGIT:
			 addChar();
			 getChar();
			 while (charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
			 nextToken = INT_LIT;
		 	break;
		/* Parentheses and operators */
		 case UNKNOWN:
			 lookup(nextChar);
			 getChar();
			 break;
			/* EOF */
		case EOF:
			 nextToken = EOF;
			 lexeme[0] = 'E';
			 lexeme[1] = 'O';
			 lexeme[2] = 'F';
			 lexeme[3] = '\0';
		 	break;
	 } /* End of switch */
	 printf("Next token is: %d, Next lexeme is %s\n",
	 nextToken, lexeme);
	 return nextToken;
} /* End of function lex */


/*
    EBNF for ifstmt:
    <ifstmt> -> if (<boolexpr>) <statement>
    [else <statement>]
 */
void ifstmt(void) {
 if (nextToken != IF_CODE)
 	error();
 else {
	lex();
 	if (nextToken != LEFT_PAREN)
 		error();
 	else {
 		lex();
 		boolexpr();
 		if (nextToken != RIGHT_PAREN)
 			error();
 		else {
 			lex();
		 	statement();
 			if (nextToken == ELSE_CODE) {
 				lex();
 				statement();
 			}
 		}
 	}
 }
}

/*
    EBNF for whilestmt:
    <whilestmt> -> while (<boolexpr>) <statement>
*/
void whilestmt(void) {
 if (nextToken != WHILE_CODE)
 	error();
 else {
	lex();
 	if (nextToken != LEFT_PAREN)
 		error();
 	else {
 		lex();
 		boolexpr();
 		if (nextToken != RIGHT_PAREN)
 			error();
 		else {
 			lex();
		 	statement();
 		}
 	}
 }
}

/* 
    EBNF for logic/math expr:
    <expr> -> <term> {(+ | - | * | / | % | && | || | ! ) <term>}
*/
void expr(void) {
	 printf("Enter <expr>\n");
	/* Parse the first term */
	 term();
	/* As long as the next token is + or -, get
	 the next token and parse the next term */
	 while (nextToken == ADD_OP || nextToken == SUB_OP
            || nextToken == MULT_OP|| nextToken == DIV_OP
            || nextToken == MOD_OP || nextToken == AND
            || nextToken == OR || nextToken == NOT) {
		 lex();
		 term();
	 }
	 printf("Exit <expr>\n");
}


/*
    EBNF for math assign:
    <assign> -> {(float | int | double)} <ident> = (<statement> | ())
    [()]
 */
void assign(void){
    if(nextToken != FLOAT || nextToken != INT || nextToken != DOUBLE)
        error();
        else{
            lex();
            if(nextToken != IDENT)
                error();
                else{
                    lex();
                    if(nextToken != ASSIGN_OP)
                        error();
                        else{
                            lex();
                            if(nextToken != EMPTY_FUNC)
                               statement();
                            else{
                                lex();
                            }
                        }
                }
        }
}

