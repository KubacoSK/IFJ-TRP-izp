

Part V.Part V.
Lexical AnalysisLexical Analysis
## 1/35

Get next token Get next token Get next token Get next token Get next token
id :=
## Assignment
## Expr
## *
## Expr Expr
num id
P o s
id
Lexical analyzer
id
## Pos
## : =
## :=
## :=

R a t e
id
id
Rate
## *
## *
## *

## 6 0
int
int
## 60
Source program:
## Example:
Syntax analyzer
## Pos := Rate*60
Lexical Analyzer (Scanner)
Source program
Lexical analyzer
## Scanner
Syntax analyzer
## Parser
Get next token
## Token
Read next char
id :=
## Assignment
## Expr
Lexical analyzer
id
## Pos
## :=

id
Source program:
## Example:
Syntax analyzer
## Pos := Rate*60
Rate
Get next
token
## 1.
## 2.
## 3.
## 2/35

## Scanner: Tasks
Other tasks
- removal of comments and whitespaces
- communication with symbol tables
Main task
- recognition and classification of lexemes
- representing lexemes by their tokens
Relation to Models for RLs
- Regular expressions specify lexemes
- DFAs underlie scanners
## 3/35

Lexemes Recognized by DFAs 1/2
1) Recognition of lexemes by using DFA
## Example:
## Identifier:
s

f

a..z
a..z,0..9
## Integer:
s

f

## 0..9
## 0..9
## Assignment:
s

f

## :
## Operator +:
q

## =
## Operator *: Comparator <:
## Comparator <=: Comparator <>:
f

s

## +
f

s

## *
f

s

## <
s

f

## <
q

## =
s

f

## <
q

## >
## 4/35

DFA that accepts the type 1 lexemes
DFA that accepts the type 2 lexemes
DFA that accepts the type n lexemes
Lexemes Recognized by DFAs 2/2
2) Construction of an FA that accepts all lexemes:
Space,Tab,
EoLn, ...
## {
## }
##   – }
s
p
f
## 2
## ...
q
## 2

Comments and
whitespaces are skipped
before a new lexeme
## ...

## ...

## Lexeme
of type 1
## Lexeme
of type 2
## Lexeme
of type n
f
n
## ...
q
n

f
## 1
## ...
q
## 1

Every final state corresponds
to one type of lexeme
## 5/35

Convert this NFA to DFA.
DFA for Lexemes : Example 1/2
- FA that accepts these lexemes:
Space,Tab,
EoLn, ...
## {
## }
##   – }
s
p
integer
f
## 2
## 0..9
## 0..9
identifier
f
## 1
a..z
a..z,0..9
f
## 3
## :
q
## 3
## =
## :=
f
## 4
## +
## +
## <
f
## 6
## <
## =
## <
f
## 7
q
## 7
## <=
## >
## <
f
## 8
q
## 8
## < >
f
## 5
## *
## *
identifier, integer, :=, +, *, <, <=, < >
## 6/35

DFAs for Lexemes: Example 2/2
- Equivalent DFA:
integer
f
## 2
## 0..9
## 0..9
identifier
f
## 1
a..z
a..z,0..9
f
## 3
## :
q
## 3
## =
## :=
f
## 4
## +
## +
## <
f
## 6
## <
## =
f
## 7
## <=
## >
f
## 8
## < >
f
## 5
## *
## *
identifier, integer, :=, +, *, <, <=, < >
Space,Tab,
EoLn, ...
## {
## }
##   – }
s
p
## 7/35

- Input: DFA  M for the source-program lexemes
- Output: determination of the lexeme type
## • Method:
- while a is the next symbol (character) in SP
and M can make a move with a do:
- read a
- make the move with a
- if M is in a final state then
determine the corresponding lexeme type
else handle the lexical error (write message etc)
Algorithm: Type of Lexeme
## 8/35

id
Type of Lexemes: Example
integer
f
## 2
## 0..9
## 0..9
identifier
f
## 1
a..z
a..z,0..9
f
## 3
## :
q
## 3
## =
## :=
f
## 4
## +
## +
## <
f
## 6
## <
## =
f
## 7
## <=
## >
f
## 8
## < >
f
## 5
## *
## *
o s
No next
configuration!
= id
= int
Space,Tab,
EoLn, ...
## {
## }
##   – }
p
s
p
s s
p
## P
f
## 1
s
f
## 1
s
No next
configuration!
## :
q
## 3
s
## =
f
## 3
q
## 3
## :=
f
## 3
s
id
## R
s
f
## 1
a t e
No next
configuration!
s
f
## 1
f
## 5
s
## *
## *
No next
configuration!
f
## 5
s
int
## 0
f
## 2
## 6
s
End of file
## {1} Pos := Rate*60
f
## 2
## 9/35

Implementation of DFA 1/10
procedure get_Next_Token(var TOKEN: ....);

## ...     {declaration, ...}

str   := '';   {read string}
state  := S;   {actual state}
repeat
symbol = getchar();  {read next character}
case state of
s : begin   {start state}
if symbol in ['a'..'z'] then
begin
state := f1; {identifier}
str := symbol;
end else

## 10/35
identifier
f
## 1
a..z
a..z,0..9
s

Implementation of DFA 2/10
case state of
s : begin   {start state}

## ...

if symbol in ['0'..'9'] then
begin
state := f2; {integer}
str := symbol;
end else

## 11/35
s
integer
f
## 2
## 0..9
## 0..9

Implementation of DFA 3/10
case state of
s : begin   {start state}

## ...

if symbol = ':' then
state := q3; {assignment}
else

## 12/35
s
f
## 3
## :
q
## 3
## =
## :=

Implementation of DFA 4/10
case state of
s : begin   {start state}

## ...

if symbol = '+' then
begin
## TOKEN := ADDITION;
break;
end else
if symbol = '*' then
begin
## TOKEN := MULTIPLICATION;
break;
end else
## 13/35
s
f
## 4
## +
## +
f
## 5
## *
## *

Implementation of DFA 5/10
case state of
s : begin   {start state}

## ...

if symbol = '<' then
state := f6;
else
if symbol = '{' then
state := p;
end; {state s}
## 14/35
s
## <
f
## 6
## <
## =
f
## 7
## <=
## >
f
## 8
## < >
## {
## }
##   – }
p

Implementation of DFA 6/10
case state of
## ...
f1: begin   {identifier}
if symbol in ['a'..'z', '0'..'9'] then
str := str + symbol;
else
begin
ungetchar(symbol); {return symbol}
if is_keyword(str) then {keyword}
TOKEN := get_keyword(str);
else
## TOKEN := IDENTIFIER;
break;
end;
end; {state f1}


## 15/35
identifier
f
## 1
a..z
a..z,0..9
s

Implementation of DFA 7/10
case state of
## ...
f2: begin   {integer}
if symbol in ['0'..'9'] then
str := str + symbol;
else
begin
ungetchar(symbol); {return symbol}
## TOKEN := INTEGER;
{conversion value of str to integer}
break;
end;
end; {state f2}


## 16/35
s
integer
f
## 2
## 0..9
## 0..9

Implementation of DFA 8/10
case state of
## ...
q3: begin   {assignment}
if symbol = '=' then
begin
## TOKEN := ASSIGNMENT;
break;
end; {state q3}


## 17/35
s
f
## 3
## :
q
## 3
## =
## :=

Implementation of DFA 9/10
case state of
## ...
f6: begin
if symbol = '=' then
begin
## TOKEN := LEQ; {<=}
break;
end else
if symbol = '>' then
begin
## TOKEN := NEQ; {<>}
break;
end else
ungetchar(symbol); {return symbol}
## TOKEN := LTN; {<}
break;
end;
end; {state f6}


## 18/35
s
## <
f
## 6
## <
## =
f
## 7
## <=
## >
f
## 8
## < >

Implementation of DFA 10/10
case state of
## ...
p : begin   {comment}
if symbol = '}' then
state := s; {start state}
end; {state p}

until EOF;

## ...

end;
## 19/35
s
## {
## }
##   – }
p

1) Token attributes may vary
[id,Pos],       [int, 60],       [*,     ]
Tokens in Practice
pointer integer nothing
## 20/35
- tokens represent every SP lexeme in a uniform way
- in general, their form is
[type,  attribute]
NOTE: In practice, we often use tokens whose
attributes vary.
2) The same form of tokens
## [1, 2],  [2, 3],  [3, 1]

[id, Pos]             [int, 60]                 [*,   ]
The Same Form of Tokens

Table of id:
## 1: Id1
## 2: Pos
## 1

Table of int:
## 1: 25
## 2: 10000
## 3: 60
## 2

Table of op:
## 1: *
## 2: /
## 3: +
## 3
## 4: –
## [    ,    ] [    ,    ] [    ,    ]
Uniform form of tokens: [1, 2]; [2, 3]; [3, 1]
## 2 1 3 2 1 3
Homogenous structure
## 21/35

3: else
(Tokens have the same form)
## Identifiers  Keywords
Question: How to distinguish identifiers from keywords?

Table of

1: if
2: then
## 4
keywords:
identifier
f
## 1
a..z
a..z,0..9
s
keyword
## ...

## ...

Is this lexeme
in the table?
## YES
## NO
Answer: By a table of keywords.
## ...

## 22/35
if
keyword
 ifj
identifier

Symbol Table (Identifier Table)
## 1: Id1--   -
## 2: Pos--   -
Practical problem:
## ...
## ...
1.2.3.4.5.         n.
Symbol table:
## 3: X----   -
## ...
1) Short identifiers:
- Empty spaces in memory (-)
2) Long identifiers:
- Length(Id)  n
## ...

## ...

## Solution:
Id1#Pos#X#
## ...
## 1:
## 2:
Symbol table
## 3:
## ...

## 23/35

## Symbol Table: Structure
- We need many pieces of information about
identifiers in ST:
- Variable: name, type, length, ...
- Constant: type and value of constant
- Procedure: the number and type of parameters
## ...

Final structure of the symbol table:
Pi Constant; Type: real, Value: 3.1415927
Id1 Variable; Type: integer
## Name Info
## 2:
## 1:
Symbol table
## 24/35

Scope of Identifiers
## • Problem:
Symbol table
## Program P1;
var x, y: integer;
## Procedure Proc1;
var x, y: integer;
begin
... x := 1; ...
end;
begin
... x := 2; ...
end.
## ?
## ?
y ... 5:
x ... 4:
## Proc1 ... 3:
y ... 2:
x ... 1:
- Solution: Scope Rules (Stack structure of ST)
## 25/35

Main Block (B0)
## Scope Rules
Block 1 (B1)
Block 2 (B2)
Entrance of B2:
- Push a pointer to the ST-stack top onto AT-stack
Exit from B2:
- The top of B1 Info becomes the ST-stack top
- Remove the B2 pointer from the AT-stack top
Search in ST:
- from the top towards the bottom
ST-stack:
## B2
## B1
## B0
## Symbol Table=
## Auxiliary
## Table =
## B1 Info
## Top
## B2 Info
## Top
## B0 Info

## Top
AT-stack:
## Search

## 26/35

## Scope Rules: Example
## Program P1;
var x, y: integer;
## Procedure Proc1;
var x, y: integer;
begin
... x := 1; ...
end;
begin
... x := 2; ...
end.
## B1
## B0
This part is
removed to
permanent
memory
y ... 5:
x ... 4:
y ... 5:
x ... 4:
Symbol table:
## Proc1 ... 3:
y ... 2:
x ... 1:
Symbol table
## 27/35

## Lex: Basic Idea
- Automatic construction of a scanner from RE
- Lex compiler and Lex language
## LEX
Regular expressions
Lexical analyzer (scanner)
## Illustration:
## 28/35

Lex: Phases of Compilation
Lex compiler
lex.l
(Lex source program)
Tabular representation
of a DFA constructed
from REs in lex.l
C compiler
lex.yy.c
(C source program)
lex.yy.c
(C source program)
a.out
(unit of scanner)
a.out
## Source
program
## Tokens
## 29/35

Structure of Lex Source Program
## /* Section I: Declaration */

d
## 1
## ,d
## 2
## , ... ,d
i


%% /* End of Section I*/
/* Section II: Translation rules */

r
## 1
## ,r
## 2
## , ... ,r
j


%% /* End of Section II*/
/* Section III: Auxiliary procedures*/

p
## 1
## ,p
## 2
## , ... ,p
k

## 30/35

Basic Regular Expressions in Lex
## [0-9]
## 0 + 1 + 2 + ...+ 9
## [a-z]
a + b + c + ...+ z

r?
r + 
r+
r
## +
r*
r
## *
r|s
r + s
rs
r.s
a
a
RE in
## LEX
Equivalent RE in theory
of formal languages
## 31/35

1) Definitions of manifest constants = token types
2) Definitions based on REs are in the form:
Name_of_RE  RE

-  Name_of_RE represents RE
- {Name_of_RE} is a reference to Name_of_RE
used in other REs
## Section I: Declaration
## Example:
#define IF   256  /* constant for IF */
#define THEN 257  /* constant for THEN */
#define ID   258  /* constant for ID */
#define INT  259  /* constant for NUM */
letter  [a-z]
digit  [0-9]
id  {letter}({letter}|{digit})*
integer {digit}+
## 32/35

- Translation rules are in the form:
RE  Action

- Action is a program routine that specifies what
to do when a lexeme is specified by RE
Section II: Translation Rules
## Example:
if  return(IF);
then  return(THEN);
{id}  { yylval = install_id();
return(ID); }
{integer} { yylval = install_int();
return(INT); }
yylval: value returned by install_id() = attribute of token
## 33/35

- Auxiliary procedures are needed by translation rules
Section III: Auxiliary Procedures
## Example:
## ...
{id}  { yylval = install_id();
return(ID); }
## ...
## %%
## ...
int install_id() {
/* Procedure to install the lexeme into the symbol
table and return a pointer thereto */
## }
## ...
## 34/35

Complete Source Program in Lex
#define   IF   256  /* constant for IF */
#define   THEN 257  /* constant for THEN */
#define   ID   258  /* constant for ID */
#define   INT  259  /* constant for NUM */
int yylval;         /* yylval is visible for parser */
letter    [a-z]
digit     [0-9]
id        {letter}({letter}|{digit})*
integer   {digit}+
## %%
if        return(IF);
then      return(THEN);
{id}      {yylval = install_id() ;return(ID) ;}
{integer} {yylval = install_int();return(INT);}
## %%
int install_id()  { ... }
int install_int() { ... }
## 35/35