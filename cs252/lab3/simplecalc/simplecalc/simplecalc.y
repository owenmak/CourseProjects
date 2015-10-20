/* simplecalc.y

   A Yacc grammar for the simple calculator, for purposes of demonstrating the
   basics of Yacc. This should work with bison just fine, but you may need to
   make modifications to the Makefile.

   The calculator evaluates an infix expression, and quits if it finds an
   error.
*/

/* 
   As with Lex, we can do any initial C declarations at the top of the
   definition file by enclosing it with the %{ %} identifiers.
*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void yyerror(const char *s);
int yylex();
void prompt();
%}

/* Use %token for assigning types to terminals, and use %type to assign
   them to nonterminals. */

%token <double_val> NUMBER
%type <double_val> expr_L1 expr_L2 expr_L3 expr_L4

/* Use %token to define all terminals. These will go into
   #defines in your yy.tab.h so if you include this file in your Lex
   definition file, you can use them there. */

%token NOTOKEN EXIT ADD SUB MUL DIV PAREN_OPEN PAREN_CLOSE NEWLINE

/* %union is where the types associated with both terminals and nonterminals
   should go. */

%union {
        double double_val;
    }

%%

goal:
    complete_expressions /* Our goal is several complete expressions */
    ;

complete_expressions: /* Here we define a complete expression to mean... */
    complete_expression /* ...a single complete expression OR ... */
    | complete_expressions complete_expression /* Multiple complete
                                                  expressions. */
    ;

complete_expression:
    expr_L1 NEWLINE { /* Normal behavior: Spit out expression and do prompt. */
            printf(" = %f\n", $1);
            prompt();
         }
    | NEWLINE { /* Spit out a prompt if the expression is empty */
            prompt();
        }
    | EXIT NEWLINE { /* Exit if the user tells us to */
            printf("Goodbye!\n");
            exit(0);
        }
    ;

expr_L1:

    /* Our grammar for expressions consists of three layers, L1, L2 and L3
       which correspond roughly to how tightly each operation will bind. The
       lowest level binds tightest.
    
       We're defining all of our mathematical operations to be left
       associative. This is arbitrary here (except for division), but
       there will be a conflict in our grammar if we don't set it up
       this way. Yacc needs to know which side of the expression to proceed
       on when it parses.

       $$ is the value associated with the nonterminal 
       (type declared in type) and $1...$n are the values associated with
       the different names in the grammar.
    */

    expr_L2
    | expr_L1 ADD expr_L2 { $$ = $1 + $3; }
    | expr_L1 SUB expr_L2 { $$ = $1 - $3; }
    ;


expr_L2:

    /* We want multiplication and division to bind more tightly than
       addition and subtraction, so we include these at a deeper level. When
       Yacc coughs up an expr_L1 nonterminal, we'll have already done
       multiplication and division operations that were part of the
       expression. */

    expr_L3
    | expr_L2 MUL expr_L3 { $$ = $1 * $3; }
    | expr_L2 DIV expr_L3 { $$ = $1 / $3; }
    | expr_L2 expr_L4 { $$ = $1 * $2; }
    ;

expr_L3:

    /* Unary minus and literal numbers are the next level down. This
       provides assurance that expressions such as "4*-3" will evaluate
       correctly. */

    expr_L4
    | SUB expr_L3 { $$ = -$2; }
    | NUMBER
    ;

expr_L4:

    /* Parentheses bind tightest, for obvious reasons. Of course we can
       have any expression inside of parentheses, so expr_L1 is used. */

    PAREN_OPEN expr_L1 PAREN_CLOSE { $$ = $2; }
    ;
    
%%

/* yacc will call yyerror if it encounters a problem. */

void yyerror(const char *err)
{
    fprintf(stderr, "Error: %s\n", err);
    exit(-1);
}

/* Prints out a basic prompt for the calculator */

void prompt()
{
    printf("calc> ");
}

/* We can put our main() inside our yacc file, but we don't necessarily
   have to. For something as simple as the calculator demo, it's fine to
   put it here. */

int main(const char **argc, int argv)
{
    prompt();
    yyparse();
    return 0;
}

