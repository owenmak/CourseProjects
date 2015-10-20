/* simplecalc.l

 A Lex scanner for the simple calculator, for purposes of demonstrating the
 basics of Lex. It should work with Flex as well.

*/

/* *** Section 1: Pattern Definitions ***

  All of your pattern definitions (and includes) go here. You don't necessarily
  have to make definitions in this section if you put the appropriate regular
  expressions in the one that follows, but it may make it clearer to the reader.

  Make sure the %{ %} are unindented. Anything you put between them will show up
  in the Lex file.

*/

%{ 
#include "y.tab.h"
#include <math.h>
%}

/* These are not tokens. They are pattern definitions. */
NEWLINE  \n
WSPACE   [ \t\r]*
WORDCHAR [A-Za-z_]
NUMBER   [0-9]*\.?[0-9]*

%%

{NEWLINE}  {   /* Code that you want run when Lex encounters your pattern 
                  goes between the curly brackets. */

               return NEWLINE;
           }

{WSPACE}    {
                /* Discard */
            }

"exit" {
         return EXIT;
       }

{WORDCHAR} {
                /* Discard */
           }

{NUMBER}  {
              yylval.double_val = atof(yytext);
              return NUMBER;
          }

"+" {
      return ADD;
    }

"-" {
      return SUB;
    }

"*" { 
      return MUL;
    }

"/" {
      return DIV;
    }   

"(" {
      return PAREN_OPEN;
    }

")" { 
      return PAREN_CLOSE;
    }

%%

/* Finally, in this section you would have any user code you want copied to
   the lex.yy.c file. In our case we do not need any code here.
*/

