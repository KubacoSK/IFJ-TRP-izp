

Part IX.
## Syntax Directed Translation
and Intermediate Code
## 1/69

## Syntax
-Directed Tran
slation
## Gist:
Semantic actions
are attached to gramatical
rules. Most importantly, these actions make intermediate code generation and type checking.
## Rule:
## Semantic Action:
## E
i
## →
## E
j
## +
## E
k
## {
## E
i
## .a
## :=
## E
j
## .a
## +
## E
k
## .a
## }
## E
i
## →
## E
j
## *
## E
k
## {
## E
i
## .a
## :=
## E
j
## .a
## *
## E
k
## .a
## }
## E
i
## →
## (
## E
j
## )
## {
## E
i
## .a
## :=
## E
j
## .a
## }
## E
i
## →
i
## {
## E
i
## .a
## :=
i.val
## }
## +
## *
i
i
i
## Example:
## 1
## +
## 2
## *
## 3
## Rule:
## Action:
## E
## 1
## E
## 1
## →
i
## E
## 2
## E
## 2
## →
i
## E
## 3
## E
## 3
## →
i
## E
## 4
## E
## 4
## →
## E
## 2
## *
## E
## 3
## E
## 5
## E
## 5
## →
## E
## 1
## +
## E
## 4
## E
## 1
## .a
## :=
i.val
## E
## 1
## .a = 1
## E
## 2
## .a
## :=
i.val
## E
## 2
## .a = 2
## E
## 3
## .a
## :=
i.val
## E
## 3
## .a = 3
## E
## 4
## .a
## :=
## E
## 2
## .a
## *
## E
## 3
## .a
## E
## 4
## .a = 6
## E
## 5
## .a
## :=
## E
## 1
## .a
## +
## E
## 4
## .a
## E
## 5
## .a = 7
## 2/69

## Intermediate Code: Three
–Address Code
- Instruction in
three–address code
## (
## 3A
## C
) has the form:
## (
o
## ,
## 
a
## ,
## 
b
## ,
## 
r
## )
## •
o
– operator     (
## +
## , –, *, ...)
## •
a
– operand 1  (
## 
a
= address of
a
## )
## •
b
– operand 2  (
## 
b
= address of
b
## )
## •
r
– result
## (
## 
r
= address of
r
## )
Examples:(:=  ,  a,  , c )
## ...
c
## :=
a
(+   ,  a, b, c )
## ...
c
## :=
a + b
(not ,  a,  , b )
## ...
b
## :=
not
## (
a
## )
## (goto,   ,  , L1)
## ...
goto L1
(goto,  a,  , L1)
## ...
if a = true then goto L1
## (lab , L1,  ,   )
## ...
label L1
## :
## 3/69

## Syntax
-Directed
Generation of 3AC
## 4/69
## 1)
## P
arser directs the creation of an
abstract-syntax
tree
## (AST)
, which is then converted to
## 3AC
## .
Basic approaches:
## 2)
Parser directs the creation of a
postfix notation
## (PN)
, which is then converted to
## 3AC
## .
## 3)
A parser directs the creation of
## 3AC.
## AST
## Syntax
analyzer
## Semantic
analyzer
## Intermediate
code generator
## 3AC
## Stack-code
## Syntax
analyzer
## Semantic
analyzer
## Intermediate
code generator
## 3AC
## Syntax
analyzer
## Semantic
analyzer
## 3AC

From a Parse Tree (PT) to an AST: Example
## 5/69
## •
PT for
x
## =
a
## *
b
## +
a
## *
b
## :
## S
## •
AST for
x
## =
a
## *
b
## +
a
## *
b
## :
## E
## E
## E
## =
## *
i
i
i
x
## =
a
## *
b
## *
i
i
a
## *
b
## +
## +
## E
## E
## E
## E
## 
x
## =
## *
## +
## 
a
## 
b
## 
a
## 
b
## *

Generation of AST
## 6/69
Gist: A parser simulates the construction of PT
and, simultaneously, calls some semantic actions to create AST.
## Example:
## Rule:
## Semantic Action:
## S
## →
i
## :=
## E
k
## {
## S.a
:= MakeTree(‘=’,
i.a
## ,
## E
k
## .a
## )
## }
## E
i
## →
## E
j
## +
## E
k
## {
## E
i
## .a
:= MakeTree(‘+’,
## E
j
## .a
## ,
## E
k
## .a
## )  }
## E
i
## →
## E
j
## *
## E
k
## {
## E
i
## .a
:= MakeTree(‘*’,
## E
j
## .a
## ,
## E
k
## .a
## )  }
## E
i
## →
## (
## E
j
## )
## {
## E
i
## .a
## :=
## E
j
## .a
## }
## E
i
## →
i
## {
## E
i
## .a
:= MakeLeaf(
i.a
## )
## }
## Notes:•
MakeTree(
o
## ,
a
## ,
b
## )
creates a new node
o
, attaches
sons
a
(left) and
b
, and returns a pointer to node
o
## •
MakeLeaf(
i.a
## )
creates a new node
i.a
## (
i.a
is a symbol-table address) and returns a pointer
to this new node

AST Generation: Example 1/2
## 7/69
## Pushdown  Input
## Rule
Semantic action
## $
i
## = (
i
## +
i
## ) *
i
## $
## $
i
## = (
i
## +
i
## ) *
i
## $
## $
i
## =
## (
i
## +
i
## ) *
i
## $
## $
i
## = (
i
## +
i
## ) *
i
## $
## $
i
## = (
i
+ i) *
i
## $
## E
## 1
## →
i
## E
## 1
## .
a
:= MakeLeaf(
i
## .
a
## )
## $
i
## = (
## E
## 1
## +
i
## ) *
i
## $
## $
i
## = (
## E
## 1
## +
i
## ) *
i
## $
## $
i
## = (
## E
## 1
## +
i
## ) *
i
## $
## E
## 2
## →
i
## E
## 2
## .
a
:= MakeLeaf(
i
## .
a
## )
## $
i
## = (
## E
## 1
## +
## E
## 2
## ) *
i
## $
## E
## 3
## →
## E
## 1
## +
## E
## 2
## E
## 3
## .
a
## :=
MakeTree(‘+’,
## E
## 1
## .
a
## ,
## E
## 2
## .
a
## )
## $
i
## = (
## E
## 3
## ) *
i
## $
## $
i
## = (
## E
## 3
## )
## *
i
## $
## E
## 4
## →
## (
## E
## 3
## )
## E
## 4
## .
a
## :=
## E
## 3
## .
a
## $
i
## =
## E
## 4
## *
i
## $
## $
i
## =
## E
## 4
## *
i
## $
## $
i
## =
## E
## 4
## *
i
## $
## E
## 5
## →
i
## E
## 5
## .
a
:= MakeLeaf(
i
## .
a
## )
## $
i
## =
## E
## 4
## *
## E
## 5
## $
## E
## 6
## →
## E
## 4
## *
## E
## 5
## E
## 6
## .
a
## :=
MakeTree(‘*’,
## E
## 4
## .
a
## ,
## E
## 5
## .
a
## )
## $
i
## =
## E
## 6
## $
## S
## →
i
## =
## E
## 6
## S.a
:= MakeTree(‘=’,
i
## .
a
## ,
## E
## 6
## .
a
## )
## $
## S
## $
## Bottom
-Up parsing
Semantic actions

AST Generation: Example 2/2
## 8/69
Simulated Parse tree:
Abstract syntax tree:
## E
## 3
## →
## E
## 1
## +
## E
## 2
## E
## 3
## .
a
## :=
MakeTree(‘+’,
## E
## 1
## .
a
## ,
## E
## 2
## .
a
## )
## +
## E
## 3
## E
## 3
## .
a
## +
## Rule:
## Semantic Action:
x
## =
a
## +
b
c
## (
## )
## *
i
## E
## 1
## →
i
## E
## 1
## .
a
:= MakeLeaf(
i
## .
a
## )
## 
a
## E
## 1
## E
## 1
## .
a
i
## E
## 2
## →
i
## E
## 2
## .
a
:= MakeLeaf(
i
## .
a
## )
## 
b
## E
## 2
## E
## 2
## .
a
i
## E
## 5
## →
i
## E
## 5
## .
a
:= MakeLeaf(
i
## .
a
## )
## 
c
## E
## 5
## E
## 5
## .
a
## *
## E
## 6
## →
## E
## 4
## *
## E
## 5
## E
## 6
## .
a
## :=
MakeTree(‘*’,
## E
## 4
## .
a
## ,
## E
## 5
## .
a
## )
## *
## E
## 6
## E
## 6
## .
a
## =
i
## S
## →
i
## =
## E
## 6
## S.a
:= MakeTree(‘=’,
i
## .
a
## ,
## E
## 6
## .
a
## )
## S
## =
## 
x
## S.
a
## (
## )
## E
## 4
## →
## (
## E
## 3
## )
## E
## 4
## .
a
## :=
## E
## 3
## .
a
## E
## 4
## E
## 4
## .
a

Direct Acyclic Graph(DAG): Example
## 9/69
## •
Parse tree for
x
## =
a
## *
b
## +
a
## *
b
## :
## S
## •
DAG for
x
## =
a
## *
b
## +
a
## *
b
## :
## E
## E
## E
## =
## *
i
i
i
x
## =
a
## *
b
## *
i
i
a
## *
b
## +
## +
## E
## E
## E
## E
## 
x
## =
## *
## +
## 
a
## 
b
## Note:
DAG has no redundant nodes.

## Postfix Notation
## 10/69
## Gist: Every
operator occurs behind  its
operands.
## Note:
Postfix notation is achievable by the
postorder traversal of AST
## .
Infix notation
Postfix notation
a
## +
b
a b
## +
a
## =
b
a b
## =
if
## C
then
## S
## 1
else
## S
## 2
## C S
## 1
## S
## 2
if-then
## -else
## Example:

Infix to Postfix Directed by a BU Parser
## 11/69
## Example:
## Rule:
## Semantic Action:
## 1
## :
## E
## →
## E
## +
## E
## {
generate
## (‘
## +
## ’)}
## 2
## :
## E
## →
## E
## *
## E
## {
generate
## (‘
## *
## ’) }
## 3
## :
## E
## →
## (
## E
## )
## { -
## }
## 4
## :
## E
## →
i
## {
generate
## (
i.a
## ) }
a
## +
b
c
## *
## Input:
## Output:
c
## 4
i
## E
## +
## 1
## E
## +
## *
## 2
## E
## *
b
i
## E
## 4
a
## E
i
## 4
## Gist: S
emantic actions produce the postfix version
of  the tokenized source program.

## Translation Grammars
## 12/69
Gist: Translation grammars translate input
strings to output strings
Parser based on
an input grammar
1) Translation by two grammars:
Input string
## Output
grammar
## Left-parse
## Output
string
2) Translation by a single grammar
Input string:
## Output
string:
Parser based on a grammar with rules
having two right-hand sides
## Note:
During the parse of an input string, a
simultaneous generation f an output string occurs

## Two
-Grammar Translation
## 13/69
Rules of G
## 1
Rules of G
## 2
## 1
## :
## E
## →
## E
## +
## T
## 1
## :
## E
## →
## ET
## +
## 2
## :
## E
## →
## T
## 2
## :
## E
## →
## T
## 3
## :
## T
## →
## T
## *
## F
## 3
## :
## T
## →
## TF
## *
## 4
## :
## T
## →
## F
## 4
## :
## T
## →
## F
## 5
## :
## F
## →
## (
## E
## )
## 5
## :
## F
## →
## E
## 6
## :
## F
## →
i
## 6
## :
## F
## →
i
## E
a
## +
b
c
## *
## Input:
## E
## Output:
## T
## E
## +
## +
## 1
## F
## T
## *
## *
## 3
## T
## 2
## F
## 4
i
a
## 6
## F
## 4
i
b
## 6
i
c
## 6
## T
## +
## E
## 1
## 1
## T
## 2
## 2
## F
## 4
## 4
i
## 6
## 6
## T
## F
## *
## 3
## 3
## F
## 4
## 4
i
## 6
## 6
i
## 6
## 6
Left parse:
Infix to postfix translation:

## One
-Grammar Translation
## 14/69
## Rule
## Tran. Element
## 1
## :
## E
## →
## E
## +
## T
## ET
## +
## 2
## :
## E
## →
## T
## T
## 3
## :
## T
## →
## T
## *
## F
## TF
## *
## 4
## :
## T
## →
## F
## F
## 5
## :
## F
## →
## (
## E
## )
## E
## 6
## :
## F
## →
i
i
## E
a
## +
b
c
## *
## Input:
## E
## Output:
## T
## +
## E
## 1
## T
## E
## +
## +
## 1
## T
## F
## *
## 3
## F
## T
## *
## *
## 3
## T
## 2
## T
## 2
## F
## 4
## F
## 4
i
## 6
i
a
## 6
## F
## 4
## F
## 4
i
## 6
i
b
## 6
i
## 6
i
c
## 6
Infix to postfix translation:

Direct Generation of 3AC
## 15/69
a
## +
b
c
## *
## Input:
Gist: BU parser directs the gen
eration of
## 3AC
directly.
## Example:
## Rule:
## Semantic Action:
## 1
## :
## S
## →
i
## =
## E
k
{ generate(‘=’,
## E
k
## .loc
## ,   ,
i.loc
## )}
## 2
## :
## E
i
## →
## E
j
## +
## E
k
{ generate(‘+’,
## E
j
## .loc
## ,
## E
k
## .loc
## ,
## E
i
## .loc
## )}
## 3
## :
## E
i
## →
## E
j
## *
## E
k
{ generate(‘*’,
## E
j
## .loc
## ,
## E
k
## .loc
## ,
## E
i
## .loc
## )}
## 4
## :
## E
i
## →
## (
## E
j
## )
{ generate(‘=’,
## E
j
## .loc
## ,   ,
## E
i
## .loc
## )}
## 5
## :
## E
i
## →
i
{ generate(‘=’,
i.loc
## ,   ,
## E
i
## .loc
## )}
x
## =
## Output:
## E
## 1
i
## 5
## (‘=’,
## 
a
## ,   ,
## E
## 1
## .loc
## )
i
## E
## 2
## 5
## (‘=’,
## 
b
## ,   ,
## E
## 2
## .loc
## )
## 5
i
## E
## 3
## (‘=’,
## 
c
## ,   ,
## E
## 3
## .loc
## )
## 3
## E
## 4
## *
## (‘*’,
## E
## 2
## .loc
## ,
## E
## 3
## .loc
## ,
## E
## 4
## .loc
## )
## 2
## E
## 5
## +
## (‘+’,
## E
## 1
## .loc
## ,
## E
## 4
## .loc
## ,
## E
## 5
## .loc
## )
## (‘=’,
## E
## 5
## .loc
## ,   ,
## 
x
## )
## S
## =
i
## 1

## Top
-Down Translation: Introduction
## 16/61
## •
## LL
-grammar with attributes
## •
Two pushdown:
## •
parser pushdown
× semantic pushdown
## •
Two type of attributes:
## •
synthesized:
iherited:
(from children to parent)
## A
## B
## C
## A.s
## B.
## ?
(from parent to childrenor between siblings)
## A
## B
## A.
## ?
## B.i
## D
## C
## D
## C.
## ?
## D.i

## Top
-Down Translation: Expressions
## 17/61
## E
## 1
## F
## 1
## R
## 1
## +
## T
## 2
## Q
## 2
i
## 1
## =
a
ε
## F
## 2
## R
## 2
## T
## 1
## Q
## 1
i
## 2
## =
b
## *
## F
## 3
## R
## 3
Parse tree for
a
## +
b
## *
c
## :
i
## 3
## =
c
ε
## Grammar:
## E
## →
## TQ
## Q
## →
## +
## TQ
## Q
## →
ε
## T
## →
## FR
## R
## →
## *
## FR
## R
## →
ε
## F
## →
## (
## E
## )
## F
## →
i
## +
ε
## *

## Expression
s: Variable
## & Parentheses
## 18/69
## F
i
## Variable:
## Parentheses:
## F
## →
i
## {
## F.s
## :=
i.value
## }
## F
## (
## )
## E
i.value
## F.s
## E.s
## F.s
## E
## →
## (
## F
## )
## {
## F.s
## :=
## E.s
## }

## Expression
s: Addition 1/4
## 19/69
## E
## Q
## Expression
## E
## →
## T
## T.s
## Q.s
## E.s
## Q.i
## {
## Q.i
## :=
## T.s
## }
## Q
## {
## E.s
## :=
## Q.s
## }
## T
## ...
## I.

## Expression
s: Addition 2/4
## 20/69
## Q
## 1
## T
## Expression
## +
## Expression
## Q
## 2
## T.s
## Q
## 1
## .i
## Q
## 2
## .i
## Q
## 2
## .s
## Q
## 1
## .s
## +
## Q
## 1
## →
## +
## T
## {
## Q
## 2
## .i
## :=
## Q
## 1
## .i + T.s
## }
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## ...
## ...
## II.

## Expression
s: Addition 3/4
## 21/69
## Q
ε
## Q
## →
ε
## {
## Q.s
## :=
## Q.i
## }
## Q.i
## Q.s
## Expression
## ...
## III.

## +
## T
## 3
## Q
## 3
## Expression
s: Addition 4/4
## 22/69
## Q
## 1
## T
## 1
## Expression
## Summary
## :
## E
## Expression
## +
## Q
## 2
## T
## 2
## Expression
## Q
n
ε
## +
## +
## ...
## T
## 2
## .s
## Q
## 2
## .i
## Q
## 2
## .s
## Q
n
## .i   Q
n
## .s
## T
## 1
## .s
## Q
## 1
## .i
## Q
## 1
## .s
## E.s
## T
## 3
## .s
## ...
## ...

## Expression
s: Multiplication
## 1/4
## 23/69
## T
## R
## Expression
## T
## →
## F
## F.s
## R.s
## T.s
## R.i
## {
## R.i
## :=
## F.s
## }
## R
## {
## T.s
## :=
## R.s
## }
## F
## ...
## I.

## Expression
s: Multiplication
## 2/4
## 24/69
## R
## 1
## F
## Expression
## *
## Expression
## R
## 2
## F.s
## R
## 1
## .i
## R
## 2
## .i
## R
## 2
## .s
## R
## 1
## .s
## *
## R
## 1
## →
## *
## F
## {
## R
## 2
## .i
## :=
## R
## 1
## .i * F.s
## }
## Q
## 2
## {
## R
## 1
## .s
## :=
## R
## 2
## .s
## }
## ...
## ...
## II.

## Expression
s: Multiplication
## 3/4
## 25/69
## R
ε
## R
## →
ε
## {
## R.s
## :=
## R.i
## }
## R.i
## R.s
## Expression
## ...
## III.

## *
## F
## 3
## R
## 3
## Expression
s: Multiplication
## 4/4
## 26/69
## R
## 1
## F
## 1
## Expression
## Summary
## :
## T
## Expression
## *
## R
## 2
## F
## 2
## Expression
## R
n
ε
## *
## *
## ...
## F
## 2
## .s
## R
## 2
## .i
## R
## 2
## .s
## R
n
## .i   R
n
## .s
## F
## 1
## .s
## R
## 1
## .i
## R
## 1
## .s
## T.s
## F
## 3
## .s
## ...
## ...

Grammar for Expressions
## : Summary
## 27/69
## 1.
## E
## →
## T
## {
## Q.i
## :=
## T.s
## }
## Q
## {
## E.s
## :=
## Q.s
## }
## 2.
## Q
## 1
## →
## +
## T
## {
## Q
## 2
## .i
## :=
## Q
## 1
## .i
## +
## T.s
## }
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## 3.
## Q
## →
ε
## {
## Q.s
## :=
## Q.i
## }
## 4.
## T
## →
## F
## {
## R.i
## :=
## F.s
## }
## R
## {
## T.s
## :=
## R.s
## }
## 5.
## R
## 1
## →
## *
## F
## {
## R
## 2
## .i
## :=
## R
## 1
## .i
## *
## F.s
## }
## R
## 2
## {
## R
## 1
## .s
## :=
## R
## 2
## .s
## }
## 6.
## R
## →
ε
## {
## R.s
## :=
## R.i
## }
## 7.
## F
## →
## (
## E
## {
## F.s
## :=
## E.s
## }
## )
## 8.
## F
## →
i
## {
## F.s
## :=
i.value
## }

Evaluation of Expressions: Example
## 1/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## E
## $
Parser pushdown:
Semantic pushdown:
## Input:
i
## 1
+ i
## 2
## $
## Rule:
## E
## →
## T
## 1
## {
## Q
## 1
## .i
## :=
## T
## 1
## .s
## }
## Q
## 1
## {
## E.s
## :=
## Q
## 1
## .s
## }
## 28/69
## Illustration:
## E
## 10
## +
## 20

Evaluation of Expressions: Example
## 2/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## T
## 1
## {
## Q
## 1
## .i
## :=
## T
## 1
## .s
## }
## Q
## 1
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
Semantic pushdown:
## Input:
i
## 1
+ i
## 2
## $
## Rule:
## T
## 1
## →
## F
## 1
## {
## R
## 1
## .i
## :=
## F
## 1
## .s
## }
## R
## 1
## {
## T
## 1
## .s
## :=
## R
## 1
## .s
## }
## 29/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## Illustration:

Evaluation of Expressions: Example
## 3/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## F
## 1
## {
## R
## 1
## .i
## :=
## F
## 1
## .s
## }
## R
## 1
## {
## T
## 1
## .s
## :=
## R
## 1
## .s
## }
## {
## Q
## 1
## .i
## :=
## T
## 1
## .s
## }
## Q
## 1
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
Semantic pushdown:
## Input:
i
## 1
+ i
## 2
## $
## Rule:
## F
## 1
## →
i
## 1
## {
## F
## 1
## .s
## :=
i.value
## }
## 30/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 1
## R
## 1
## Illustration:

Evaluation of Expressions: Example
## 4/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
i
## 1
## {
## F
## 1
## .s :
## =
i.value
## }
## {
## R
## 1
## .i
## :=
## F
## 1
## .s
## }
## R
## 1
## {
## T
## 1
## .s
## :=
## R
## 1
## .s
## }
## {
## Q
## 1
## .i
## :=
## T
## 1
## .s
## }
## Q
## 1
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
Semantic pushdown:
## Input:
i
## 1
+ i
## 2
## $
## Rule:
## 31/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 1
## R
## 1
i
## 1
## Illustration:

Evaluation of Expressions: Example
## 5/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## {
## F
## 1
## .s :
## =
i.value
## }
## {
## R
## 1
## .i
## :=
## F
## 1
## .s
## }
## R
## 1
## {
## T
## 1
## .s
## :=
## R
## 1
## .s
## }
## {
## Q
## 1
## .i
## :=
## T
## 1
## .s
## }
## Q
## 1
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
Semantic pushdown:
## Input:
+ i
## 2
## $
## Rule:
## 32/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 1
## R
## 1
i
## 1
## Illustration:

Evaluation of Expressions: Example
## 6/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## {
## R
## 1
## .i
## :=
## F
## 1
## .s
## }
## R
## 1
## {
## T
## 1
## .s
## :=
## R
## 1
## .s
## }
## {
## Q
## 1
## .i
## :=
## T
## 1
## .s
## }
## Q
## 1
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
## F
## 1
## .
s
## =
## 10
Semantic pushdown:
## Input:
+ i
## 2
## $
## Rule:
## 33/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 1
## R
## 1
i
## 1
## Illustration:
## R
## 1
## {
## T
## 1
## .s
## :=
## R
## 1
## .s
## }
## {
## Q
## 1
## .i
## :=
## T
## 1
## .s
## }
## Q
## 1
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
## R
## 1
## .
i
## =
## 10
## R
## 1
## →
ε
## {
## R
## 1
## .s
## :=
## R
## 1
## .i
## }

Evaluation of Expressions: Example
## 7/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## {
## R
## 1
## .s
## :=
## R
## 1
## .i
## }
## {
## T
## 1
## .s
## :=
## R
## 1
## .s
## }
## {
## Q
## 1
## .i
## :=
## T
## 1
## .s
## }
## Q
## 1
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
## R
## 1
## .
i
## =
## 10
Semantic pushdown:
## Input:
+ i
## 2
## $
## Rule:
## {
## T
## 1
## .s
## :=
## R
## 1
## .s
## }
## {
## Q
## 1
## .i
## :=
## T
## 1
## .s
## }
## Q
## 1
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
## R
## 1
## .
s
## =
## 10
## 34/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 1
## R
## 1
i
## 1
ε
## Illustration:
## {
## Q
## 1
## .i
## :=
## T
## 1
## .s
## }
## Q
## 1
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
## T
## 1
## .
s
## =
## 10
## Q
## 1
## →
## +
## T
## 2
## {
## Q
## 2
## .i
## :=
## Q
## 1
## .i
## +
## T
## 2
## .s
## }
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## Q
## 1
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
## Q
## 1
## .
i
## =
## 10

Evaluation of Expressions: Example
## 8/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## +
## T
## 2
## {
## Q
## 2
## .i
## :=
## Q
## 1
## .i
## +
## T
## 2
## .s
## }
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
## Q
## 1
## .
i
## =
## 10
Semantic pushdown:
## Input:
+ i
## 2
## $
## Rule:
## 35/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 1
## R
## 1
i
## 1
ε
## Illustration:
## T
## 2
## Q
## 2
## +

Evaluation of Expressions: Example
## 9/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## T
## 2
## {
## Q
## 2
## .i
## :=
## Q
## 1
## .i
## +
## T
## 2
## .s
## }
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
## Q
## 1
## .
i
## =
## 10
Semantic pushdown:
## Input:
i
## 2
## $
## Rule:
## T
## 2
## →
## F
## 2
## {
## R
## 2
## .i
## :=
## F
## 2
## .s
## }
## R
## 2
## {
## T
## 2
## .s
## :=
## R
## 2
## .s
## }
## 36/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 1
## R
## 1
i
## 1
ε
## Illustration:
## T
## 2
## Q
## 2
## +

Evaluation of Expressions: Example
## 10/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## F
## 2
## {
## R
## 2
## .i
## :=
## F
## 2
## .s
## }
## R
## 2
## {
## T
## 2
## .s
## :=
## R
## 2
## .s
## }
## {
## Q
## 2
## .i
## :=
## Q
## 1
## .i
## +
## T
## 2
## .s
## }
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
## Q
## 1
## .
i
## =
## 10
Semantic pushdown:
## Input:
i
## 2
## $
## Rule:
## F
## 2
## →
i
## 2
## {
## F
## 2
## .s
## :=
i.value
## }
## 37/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 2
## R
## 2
## F
## 1
## R
## 1
i
## 1
ε
## Illustration:
## T
## 2
## Q
## 2
## +

Evaluation of Expressions: Example
## 11/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
i
## 2
## {
## F
## 2
## .s
## :=
i.value
## }
## {
## R
## 2
## .i
## :=
## F
## 2
## .s
## }
## R
## 2
## {
## T
## 2
## .s
## :=
## R
## 2
## .s
## }
## {
## Q
## 2
## .i
## :=
## Q
## 1
## .i
## +
## T
## 2
## .s
## }
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
## Q
## 1
## .
i
## =
## 10
Semantic pushdown:
## Input:
i
## 2
## $
## Rule:
## 38/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 2
## R
## 2
## F
## 1
## R
## 1
i
## 1
ε
i
## 2
## Illustration:
## T
## 2
## Q
## 2
## +

Evaluation of Expressions: Example
## 12/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## {
## F
## 2
## .s
## :=
i.value
## }
## {
## R
## 2
## .i
## :=
## F
## 2
## .s
## }
## R
## 2
## {
## T
## 2
## .s
## :=
## R
## 2
## .s
## }
## {
## Q
## 2
## .i
## :=
## Q
## 1
## .i
## +
## T
## 2
## .s
## }
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
## Q
## 1
## .
i
## =
## 10
Semantic pushdown:
## Input:
## $
## Rule:
## 39/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 2
## R
## 2
## F
## 1
## R
## 1
i
## 1
ε
i
## 2
## Illustration:
## T
## 2
## Q
## 2
## +

Evaluation of Expressions: Example
## 13/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## {
## R
## 2
## .i
## :=
## F
## 2
## .s
## }
## R
## 2
## {
## T
## 2
## .s
## :=
## R
## 2
## .s
## }
## {
## Q
## 2
## .i
## :=
## Q
## 1
## .i
## +
## T
## 2
## .s
## }
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
## F
## 2
## .
s
## =
## 20
## Q
## 1
## .
i
## =
## 10
Semantic pushdown:
## Input:
## $
## Rule:
## 40/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 2
## R
## 2
## F
## 1
## R
## 1
i
## 1
ε
i
## 2
## Illustration:
## R
## 2
## {
## T
## 2
## .s
## :=
## R
## 2
## .s
## }
## {
## Q
## 2
## .i
## :=
## Q
## 1
## .i
## +
## T
## 2
## .s
## }
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
## R
## 2
## .
i
## =
## 20
## Q
## 1
## .
i
## =
## 10
## R
## 2
## →
ε
## {
## R
## 2
## .s
## :=
## R
## 2
## .i
## }
## T
## 2
## Q
## 2
## +

Evaluation of Expressions: Example
## 14/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## {
## R
## 2
## .s
## :=
## R
## 2
## .i
## }
## {
## T
## 2
## .s
## :=
## R
## 2
## .s
## }
## {
## Q
## 2
## .i
## :=
## Q
## 1
## .i
## +
## T
## 2
## .s
## }
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
## R
## 2
## .
i
## =
## 20
## Q
## 1
## .
i
## =
## 10
Semantic pushdown:
## Input:
## $
## Rule:
## {
## T
## 2
## .s
## :=
## R
## 2
## .s
## }
## {
## Q
## 2
## .i
## :=
## Q
## 1
## .i
## +
## T
## 2
## .s
## }
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
## R
## 2
## .
s
## =
## 20
## Q
## 1
## .
i
## =
## 10
## 41/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 2
## R
## 2
## F
## 1
## R
## 1
i
## 1
ε
ε
i
## 2
## Illustration:
## {
## Q
## 2
## .i
## :=
## Q
## 1
## .i
## +
## T
## 2
## .s
## }
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
## T
## 2
## .
s
## =
## 20
## Q
## 1
## .
i
## =
## 10
## T
## 2
## Q
## 2
## +

Evaluation of Expressions: Example
## 15/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## Q
## 2
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
## Q
## 2
## .
i
## =
## 30
Semantic pushdown:
## Input:
## $
## Rule:
## Q
## 2
## →
ε
## {
## Q
## 2
## .s
## :=
## Q
## 2
## .i
## }
## 42/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 2
## R
## 2
## F
## 1
## R
## 1
i
## 1
ε
ε
i
## 2
## Illustration:
## T
## 2
## Q
## 2
## +
## +

Evaluation of Expressions: Example
## 16/16
Example for
a
## +
b
, where
a
## .
value
## = 10
## ,
b
## .
value
## = 20
## {
## Q
## 2
## .s
## :=
## Q
## 2
## .i
## }
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
Parser pushdown:
## Q
## 2
## .
i
## =
## 30
Semantic pushdown:
## Input:
## $
## Rule:
## {
## Q
## 1
## .s
## :=
## Q
## 2
## .s
## }
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
## Q
## 2
## .
s
## =
## 30
## 43/69
## E
## 10
## +
## 20
## T
## 1
## Q
## 1
## F
## 2
## R
## 2
## F
## 1
## R
## 1
i
## 1
ε
ε
ε
## T
## 2
## Q
## 2
## +
i
## 2
## Illustration:
## +
## {
## E.s
## :=
## Q
## 1
## .s
## }
## $
## Q
## 1
## .
s
## =
## 30
## $
## E
## .
s
## =
## 30

## Semantic Analysis: Type
## Checking
## 44/69
idE
op
## 1)
## Action:   E
## .type :=
id
## .type
## E
## 2)
## E
## 1
## E
## 2
Rule:Rule:
## Operation
op
is
defined over types:
t
## 1
op
t
## 2
## →
t
## 3
## Action:if
## (
## E
## 1
## .type =
t
## 1
or
## E
## 1
.type is convertable to
t
## 1
## )
and(
## E
## 2
## .type =
t
## 2
or
## E
## 2
.type is convertable to
t
## 2
## )
thenE
## .type :=
t
## 3
elseSemantic Error
## .

## Type
## Checking: Example 1/3
## 45/69
## Rule:
## F
## →
i
## {
## F
## .
type
## :=
i
## .
type
## ;
generate
## (:=,
i
## .
loc
## , ,
## F
## .
loc
## ) }
## Rule:
## F
i
## →
## (
## E
j
## )
## {
## F
i
## .
type
## :=
## E
j
## .
type
## }
## •
Make a type-checking for a grammar:
## •
## G
expr
## 1
## = (
## N
## ,
## T
## ,
## P
## ,
## E
), where
## N
## = {
## E
## ,
## F
## ,
## T
## },
## T
## = {
i
## ,
## +
## ,
## *
## ,
## (
## ,
## )
## },
## P
## = {
## E
## →
## E
## +
## T
## ,
## E
## →
## T
## ,
## T
## →
## T
## *
## F
## ,
## T
## →
## F
## ,
## F
## →
## (
## E
## )
## ,
## F
## →
i
## }
## •
## Operators
## *
## ,
## +
are defined as:
## Rule:
## T
i
## →
## F
j
## {
## T
i
## .
type
## :=
## F
j
## .
type
## }
## Rule:
## E
i
## →
## T
j
## {
## E
i
## .
type
## :=
## T
j
## .
type
## }
## •
int
## *
int
## →
int
## •
int
## +
int
## →
int
## •
real
## *
real
## →
real
## •
real
## +
real
## →
real
## Possible Conversion:
## •
## From
int
to
real

## Type
## Checking: Example 2/3
## 46/69
## Rule:
## E
i
## →
## E
j
## +
## T
k
{  if
## E
j
## .
type
## =
## T
k
## .
type
then begin
## E
i
## .
type
## :=
## E
j
## .
type
generate
## (+,
## E
j
## .loc
## ,
## T
k
## .loc
## ,
## E
i
## .loc
## )
endelse begin
generate
## (
new.loc
## ,
h
## , ,  )
if
## E
j
## .
type
## =
int
then begin
generate
## (
int-to-real
## ,
## E
j
## .loc
## , ,
h
## )
generate
## (+,
h
## ,
## T
k
## .loc
## ,
## E
i
## .loc
## )
endelse begin
generate
## (
int-to-real
## ,
## T
k
## .loc
## , ,
h
## )
generate
## (+,
## E
j
## .loc
## ,
h
## ,
## E
i
## .loc
## )
endE
i
## .
type
## :=
real
end
## }

## Type
## Checking: Example 3/3
## 47/69
## Rule:
## T
i
## →
## T
j
## *
## F
k
{  if
## T
j
## .
type
## =
## F
k
## .
type
then begin
## T
i
## .
type
## :=
## T
j
## .
type
generate
## (*,
## T
j
## .loc
## ,
## F
k
## .loc
## ,
## T
i
## .loc
## )
endelse begin
generate
## (
new.loc
## ,
h
## , ,  )
if
## T
j
## .
type
## =
int
then begin
generate
## (
int-to-real
## ,
## T
j
## .loc
## , ,
h
## )
generate
## (*,
h
## ,
## F
k
## .loc
## ,
## T
i
## .loc
## )
endelse begin
generate
## (
int-to-real
## ,
## F
k
## .loc
## , ,
h
## )
generate
## (*,
## T
j
## .loc
## ,
h
## ,
## T
i
## .loc
## )
end
## T
i
## .
type
## :=
real
end
## }

## 1)
## (
a
and
b
## ) =
p
## :
if
a
## =
false
then
p
## =
false
else
p
## =
b
## 2)
## (
a
or
b
## ) =
p
## :
if
a
## =
true
then
p
## =
true
else
p
## =
b
Short Evaluation (Jumping Code)
## 48/69
## Idea:•
a
## =
true
implies
a
or
## (
## ...   ?   ...
## )
## =
true
## •
a
## =
false
implies
a
and
## (
## ...   ?   ...
## )
## =
false
## Note: (
## ...   ?   ...
) is
not evaluated
## .

## Short Evaluation: Graphic Representation
## 49/69
a
true
## True
## False
b
c
false
true
true
false
false
- Simulation of this graphic representation by 3AC j
umps
if
a
goto
## True
goto
## X
## X
## :
if
b
goto
## Y
goto
## False
## Y
## :
if
c
goto
## False
goto
## True
## True
## : ...
## False
## : ...
## Example:
a
or
## (
b
and
## (
not
c
## )):

Short Evaluation Using AST: Introduction
## 50/69
## Example:
a
or
## (
b
and
## (
not
c
## )):
or
and
not
a
c
b
## X:
## Y:
true  false
true  false
true  false
## AST:
## True:
## False:
if
a
goto
## True
goto
## X
## X
## :
if
b
goto
## Y
goto
## False
## Y
## :
if
c
goto
## False
goto
## True
## True
## : ...
## False
## : ...

Short Evaluation Using AST: Implementation
## 51/69
- Every AST node,
## X
,  has assigned two attributes
## X
## .t
## ,
## X
## .f
Elementary ASTs:
## A
or
## B
## A
## .t
## :=
or
## .t
## A
## .f
## :=
## L
## B
## .t
## :=
or
## .t
## B
## .f
## :=
or
## .f
or
## .t
or
## .f
## L
## :
## A
and
## B
## A
## .t
## :=
## L
## A
## .f
## :=
and
## .f
## B
## .t
## :=
and
## .t
## B
## .f
## :=
and
## .f
and
## .t
and
## .f
## L
## :
not
## A
## A
## .t
## :=
not
## .f
## A
## .f
## :=
not
## .t
not
## .t
not
## .f
## 1)
## 2)
## 3)
## •
## Note:
## L
= a new label
## •
## Initialization:
## Let
## R
is the root of AST, then:
## R
## .t
## :=
## True
## ,
## R
## .f
## :=
## False
## (
## True
## &
## False
are labels)
## •
## Propagation:
Attributes are propagated from root to leaves
in AST using rules
## 1)
## ,
## 2)
and
## 3)
## .
## •
## Note:
## L
= a new label

Short Evaluation Using AST: Example
## 52/69
## Example:
a
or
## (
b
and
## (
not
c
## )):
or
and
not
a
c
b
## X:
## Y:
## AST:
or
## .t
## :
## =
## T
or
## .f
## :
## =
## F
a
## .t
## :=
or
## .t
a
## .f
## :=
## X
## (=
## T
## )
b
## .t
## :=
## Y
b
## .f
## :=
and
## .f
## (=
## F
## )
c
## .t
## :=
not
## .f
c
## .f
## :=
not
## .t
## (=
## F
## )
## Note:•
## T
## =
## True
## •
## F
## =
## False
## (=
## T
## )
and
## .t
## :
## =
or
## .t
and
## .f
## :
## =
or
## .f
## (=
## T
## )
## (=
## F
## )
not
## .t
## :
## =
and
## .t
not
## .f
## :
## =
and
## .f
## (=
## T
## )
## (=
## F
## )
## T
## : ...
## F
## : ...
## X
## :
if
b
goto
## Y
goto
## F
if
a
goto
## T
goto
## X
## Y
## :
if
c
goto
## F
goto
## T

## Short Evaluation: Direct Code Generation 1
## /5
## 53/69
## •
Grammar for boolean expression
s:
## Note:
## Ambiguity
## !
## •
Modification of grammar:
## E
## E
## Rules:
## 1.
## 5.
## E
or
## E
## (
## E
## )
id
## E
## 2.
## E
and
## E
## E
## 3.
not
## E
## E
## 4.
## 1)
Replace rules
## 1.
## &
## 2.
with:
## E
## E
or
## M E
## E
## E
and
## M E
## M
ε
## 2)
Assign to each rule the following semantic action

## Short Evaluation: Direct Code Generation 2/5
## 54/69
## M
i
## →
ε
## {generate “
## M
i
## .
lab
## :
”} // Generation of
a new label
## E
j
or
## M
i
## E
i
## E
i
## .true
## E
i
## .false
## E
j
## .true
## E
j
## .false
## :=
## L
i
newlab:
ε
## L
i
## :
## E
k
## E
k
## .true
## E
k
## .false
## E
i
## →
## E
j
or
## M
i
## E
k
## {
## M
i
## .
lab
## :=
GenerateNewLab
## ;
## E
j
## .
true
## :=
## E
i
## .
true
## ;
## E
j
## .
false
## :=
## M
i
## .
lab
## E
k
## .
true
## :=
## E
i
## .
true
## ;
## E
k
## .
false
## :=
## E
i
## .
false
## }
## Illustration:

## Short Evaluation: Direct Code Generation 3/5
## 55/69
## E
j
and
## M
i
## E
i
## E
i
## .true
## E
i
## .false
## E
j
## .true
## :=
## L
i
## E
j
## .false
newlab:
ε
## L
i
## :
## E
k
## E
k
## .true
## E
k
## .false
## E
i
## →
## E
j
and
## M
i
## E
k
## {
## M
i
## .
lab
## :=
GenerateNewLab
## ;
## E
j
## .
true
## :=
## M
i
## .
lab
## ;
## E
j
## .
false
## :=
## E
i
## .
false
## E
k
## .
true
## :=
## E
i
## .
true
## ;
## E
k
## .
false
## :=
## E
i
## .
false
## }
## Illustration:

## Short Evaluation: Direct Code Generation 4/5
## 56/69
## E
i
## →
not
## E
j
## {
## E
j
## .
true
## :=
## E
i
## .
false
## ;
## E
j
## .
false
## :=
## E
i
## .
true
## }
## E
j
not
## E
i
## E
i
## .true
## E
i
## .false
## E
j
## .true
## E
j
## .false
Illustration:E
i
## →
## (
## E
j
## )
## {
## E
j
## .
true
## :=
## E
i
## .
true
## ;
## E
j
## .
false
## :=
## E
i
## .
false
## }
## E
i
## →
id
j
{ generate “
if
id
j
## .
val
goto
## E
i
## .
true
## ”;
generate “
goto
## E
i
## .
false
## ”
## }

## Short Evaluation: Direct Code Generation 5/5
## 57/69
a
or
b
and
## E
## 0
. t
## :=
## L
true
## E
## 0
. f
## :=
## L
false
## Example:
a
and
b
or
c
and
d
## :
## E
## 3
. t
## :=
## L
## 1
## E
## 3
. f
## :=
## E
## 1
## .
f
## E
## 4
. t
## :=
## E
## 1
## .
t
## E
## 4
. f
## :=
## E
## 1
## .
f
## E
## 3
## M
## 1
## E
## 4
c
d
and
## E
## 5
. t
## :=
## L
## 2
## E
## 5
. f
## :=
## E
## 2
## .
f
## E
## 6
. t
## :=
## E
## 2
## .
t
## E
## 6
. f
## :=
## E
## 2
## .
f
## E
## 5
## M
## 2
## E
## 6
## E
## 0
## E
## 1
. t
## :=
## E
## 0
## .
t
## E
## 1
. f
## :=
## L
## 0
## E
## 1
## E
## 2
## M
## 0
## E
## 2
. t
## :=
## E
## 0
. t
## E
## 2
. f
## :=
## E
## 0
## .
f
if
a
goto
## L
## 1
goto
## L
## 0
if
b
goto
## L
true
goto
## L
## 0
ε
## L
## 1
## :
if
c
goto
## L
## 2
goto
## L
false
ε
## L
## 0
## :
if
d
goto
## L
true
goto
## L
false
ε
## L
## 2
## :
## L
true
## :
## ...
## L
false
## :
## ...

Branching: If-Then
## <if-then>
if
## <cond>
then
## <stat
## 1
## >
// evaluation of
cond
// to c.val
(not , c.val, , c.val)(goto, c.val, , L1   )
// code of
stat
## 1
## (lab , L1   , ,      )
Rule:Semantic action:
## 58/69

Branching: If-Then
-Else
## <if-then
## -else>
if
## <cond>
then
## <stat
## 1
## >
else
## <stat
## 2
## >
// evaluation of
cond
// to c.val
(not , c.val, , c.val)(goto, c.val, , L1   )
// code of
stat
## 1
## (goto,      , , L2   )(lab , L1   , ,      )
// code of
stat
## 2
## (lab , L2   , ,      )
Rule:Semantic action:
## 59/69

## While Loop
## <while-loop>
while
## <cond>
do
## <stat>
## (lab , L1   , ,      )
// evaluation of
cond
// to c.val
(not , c.val, , c.val)(goto, c.val, , L2   )
// code of
stat
## (goto,      , , L1   )(lab ,  L2  , ,      )
Rule:Semantic action:
## 60/69

## Repeat Loop
## <repeat-loop>
repeat
## <stat>
until
## <cond>
## (lab , L1   , ,      )
// code of
stat
// evaluation of
cond
// to c.val
(not , c.val, , c.val)(goto, c.val, , L1   )
Rule:Semantic action:
## 61/69

## Yacc: Basic Idea
- Automatic construction of
parser
from
## CFG
- Yacc compiler
## ×
Yacc language
## •
## Yacc
from
## Y
et
a
nother
c
ompiler
c
ompiler
## YACC
Context-free grammar,
## G
Parser for
## G
## 62/69
## Ilustrace:

## Yacc
: Phases of Compilation
Yacc compiler
translate.y
(Yacc source program)
## LR
-parser constructed
from CFG
during
translate.y
C compiler
y.tab
## .c
(C source program)
y.tab
## .c
(C source program)
a.out
## (parser)
a.out
String of
## Tokens,
x
Parse of
x
made by
a.out
## 63/69

Structure of Yacc
## Source Program
## /*
## Section I:
## Declaration */
d
## 1
## ,d
## 2
## , ... ,d
i
## %%
/* End of Section I*/
## /*
Section II:
Translation rules */
r
## 1
## ,r
## 2
## , ... ,r
j
## %%
/* End of Section II*/
## /*
Section III:
Auxiliary procedures*/
p
## 1
## ,p
## 2
## , ... ,p
k
## 64/69

Description of Grammar in Yacc
## 65/69
## •
## Nonterminals:
names (= strings)
## •
## Example:
prog
## ,
stat
## ,
expr
## , ...
## •
## Terminals:
Characters in quotes or declared tokens
## •
## Example:
## ‘+’
## ,
## ‘*’
## ,
## ‘(’
## ,
## ‘)’
## ,
## ID
## ,
## INTEGER
## •
## Rules:
Set of
## A
## -rules {
## A
## →
x
## 1
## ,
## A
## →
x
## 2
## , ...
## A
## →
x
n
## }
is written as
## A
## :
x1
## |
x2
## ...|
xn
## •
## Example:
expr
## :
expr
## ‘+’
expr
## |
## ID
## •
## Start Nonterminal:
A left side of the first rule.

## 1)
Declaration of tokens
## %token
## TYPE_OF_TOKEN
## 2)
Specification of
asociativity
## &
precedence
in
an ambigous grammar.
## Section I: Declaration
## Example:%token
## INTEGER
## %token
## ID
## %left
## ‘+’
## %left
## ‘*’
## 66/69
## %left
op
i1
, op
i2
## , ... ,op
im
## %left
op
j1
, op
j2
## , ... ,op
jm
## ...%right
op
k1
, op
k2
## , ... ,op
kp
The same precedence
## Higher
precedence
## Associativity
of the following operators

- Translation rules are in the form:
## Rule
Semantic_Action
## •
Semantic_Action
is a program routine that
specifies what to do if
## Rule
is used.
Special symbols for a rule,
r
## :
## $$
= attribute of
r
’s left-hand side
## $
i
= attribute of the
i
-th symbols on
r
’s right-hand side
Section II: Translation Rules
## Example:expr
## :
expr
## ‘+’
expr
## {$$ = $1 + $3}
## |
expr
## ‘*’
expr
## {$$ = $1 * $3}
## |
## ‘(’
expr
## ‘)’
## {$$ = $2}
## |
## INTEGER
## |
## ID
## 67/69

## •
Auxiliary procedures used by translation rules
Section III: Auxiliary Procedures
## Example:
int yylex() {
/* Get the next token */&yylval = attribute;return TYPE_OF_TOKEN;
## }
## 68/69
## Note:
If the Yacc-parser do not  cooperate with a scanner

(e.g. Lex), then there is
yylex()
implemented in this
section.

Complete Source Program in Yacc
## %token
## INTEGER
## %token
## ID
## %left
## ‘+’
## %left
## ‘*’
## %%expr
## :
expr
## ‘+’
expr
## {$$ = $1 + $3}
## |
expr
## ‘*’
expr
## {$$ = $1 * $3}
## |
## ‘(’
expr
## ‘)’
## {$$ = $2}
## |
## INTEGER
## |
## ID
%%int yylex () {
## ...
## }
## 69/69