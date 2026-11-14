

Part II.
## Introduction
to
## Compilers
## 1/17

## •
## Input:
Source program
## •
## Output:
Target program
## •
## Method:
- A compiler reads a
source program
## (in
source language) and translates them into target program
(in target language).
- Source and target programs are
functionally
equivalent
## .
## Compiler
## 2/17

Lexical analyzer
Syntax analyzer
Intermediate code generator
## Optimizer
Code generator
Structure of Compiler: Phases
Semantic analyzer
## Position := Initial + Rate * 60
T1  := Id3 * 60.0Id1 := Id2 + T1
## Id
## 1
## := Id
## 2
## + Id
## 3
## * 60
fmul R2 , #60.0fmov R3 , Id2fmov R2 , Id3 fadd R2 , R3fmov Id1, R2
## :=
## Id
## 1
## Id
## 2
## Id
## 3
## +
## *
## 60
## :=
## Id
## 1
## Id
## 2
## Id
## 3
## +
## *
## 60
IntToReal
T1  := IntToReal(60)T2  := Id3 * T1T3  := Id2 + T2Id1 := T3
## 3/17

## Source
program
Lexical analyzer
## Scanner
Syntax tree
Intermediate code
Optimized intermediate code
## Target
program
Syntax analyzer
## Parser
## Tokens
## Semantic
analyzer
## Intermediate
code generator
## Optimizer
## Code
generator
Structure of Compiler: Construction
Parse tree simulation
Syntax-Directed
## Translation
## 4/17

Theoretical view.
## Σ
## = {
a
## ,
b
## }
## ,
## L =
## {
a
n
b
n
## :
n
## ≥
## 0}
## Question
## :
aa
bb
## ∈
## L
## ?
Practical view.
## Σ
## = {
begin
## ,
end
## ,
id
## ,
## :=
## , *,
## ;
## , ...}
## ,
## Question
## :
begin
id
## :=
id
## *
id
## ;
end
## ;
## ∈
## L
## Pascal
## ?
## L
## Pascal
## =
## Programming Language Pascal
## YES
: Program is
## OK
## ⇒
Create a target program
## NO
: Program is
not OK
## ⇒
Handle the errors
Languages and Compilers
## 5/17

## •
## Input:
Source program
## •
## Output:
String of tokens
## •
## Method:
- Source program is broken into
lexemes
## =
logically cohesive lexical entities –(identifiers, numbers, key
-words, operators,
## ...
## )
- Lexemes are represented by uniform
tokens
- Some tokens have
attributes
Lexical analyzer (Scanner)
## 6/17

Lexical analyzer: Example
Source program:
## Position := Initial + Rate * 60
## Tokens:
id
## 
## Position
## :=
id
## 
## Initial
## +
id
## 
## Rate
## *
int
## 60
## Position
## :=
## Initial
## +
## Rate
## *
## 60
## Lexemes:
## 7/17

## •
## Input:
String of tokens
## •
## Output:
Simulation of parse tree construction
## •
## Method:
- Parser verifies that the string of tokens
represents a syntactically well-formed program
- If it finds a
parse tree
for the string, it is
correct; otherwise, it is not
- Simulation of parse tree construction is based
on grammatical rules
- Two approach: top
-down and bottom
## -up
Syntax analyzer (Parser)
## 8/17

## Task
## :
Simulate a parse tree
from
grammatical rules!
id
## :=
## Expr
## 1.
Syntax analyzer: Example
## Expr
## Expr
## Expr
## Expr   Expr
## Assignment
## Rules:
## 1.
## 2.
## 3.
## 4.
## 5.
## 6.
## Expr
## +
## Expr
## Expr
## *
## Expr
## (
## Expr
## )
id
int
id   :=
## Expr
## Tokens
id
## 
## Position
## :=
id
## 
## Initial
## +
id
## 
## Rate
## *
int
## 60
## Assignment
## +
## Expr
## Expr
## 2.
## *
## Expr
## Expr
## 3.
id
## 5.
id
## 5.
## Parse
## Tree:
int
## 6.
## 9/17

## •
## Input:
Simulation of parse tree construction
## •
## Output:
Abstract syntax tree
## •
## Method:
- Semantic analyzer checks semantic aspects:
## •
type checking
, which may imply
conversions (for example int-to
## -real)
## •
checking declaration of variables
## •
## Syntax
-Directed Translation:
Parser controls:
- Semantic actions• Generation of syntax tree
Semantic analyzer
## 10/17

## Expr
## Syntax
-Directed Translation: Example
id
## 
## Position
## :=
id
## 
## Initial
## +
id
## 
## Rate
## *
int
## 60
## Assignment
## Expr
## Expr
## Expr
## Expr
## Parse
## Tree:
IntToReal
## 
## Position
## :=
## 
## Initial
## +
## 
## Rate
## *
## 60
IntToReal
## Abstract
## Syntax
## Tree:
## 11/17

## •
## Input:
Abstract syntax tree
## •
## Output:
Intermediate code
## •
## Method:
- Intermediate code generator produces the
internal version of target program calledintermediate code
for these reasons:
-   uniformity•   direct translation to target program is
difficult and “rough”
-   optimization
Intermediate code generator
## 12/17

## Intermed
iate
code generator: Example
## 
## Position
## :=
## 
## Initial
## +
## 
## Rate
## *
## 60
IntToReal
## Abstract
## Syntax
## Tree:
## T1
## T2
## T1 :=
IntToReal
## (60)
## T2 :=
## 
## Rate * T1
## T3 :=
## 
## Initial
## + T2
## 
## Positon := T3
## T3
## Intermediate
code:
## 13/17

## •
## Input:
Intermediate code
## •
## Output:
Optimized intermediate code
## •
## Method:
- Optimizer makes more efficient version of
intermediate code called
optimized intermediate code
## :
## •
Constant propagation:
(a := 1; b := 2; c := a + b
## ⇒
c := 3)
## Note:
Variables a, b have no next use
## •
Copy propagation:
(b := a; c := b; d := c
## ⇒
d := a)
## Note:
Variables b, c have no next use
## •
Dead code elimination:
## (
while
false
do ...
## ⇒
nothing)
## Optimizer
## Note:
Some compilers have no optimizer
## 14/17
## ...

## Optimizer
## : Example
## T1 :=
IntToReal
## (60)
## T2 :=
## 
## Rate * T1
## T3 :=
## 
## Initial
## + T2
## 
## Positon:= T3
## Intermediatecode:
Optimized intermediate code:
## T2 :=
## 
## Rate * 60.0
## 
## Positon :=
## 
## Initial
## +T2
## 15/17

## •
## Input:
Optimized intermediate code
## •
## Output:
Target program
## •
## Method:
- Optimized intermediate code is converted to
target program
- Target program is written in target language• In reality, target language is assembly or
machine language
## Code Generator
## 16/17

## Code Generator
## : Example
## T2 :=
## 
## Rate
## * 60.0
## 
## Positon :=
## 
## Initial
## +T2
Target program:
Optimized intermediate code:
fmov R2,
## 
## Rate
fmul R2, #60.0
## R2
## ≅
## T2
fmov R3,
## 
## Initial
fadd R2, R3
fmov
## 
Position,R2
## 17/17