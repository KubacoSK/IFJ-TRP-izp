

Part VIII.
## Bottom
-Up Parsing
## 1/12

## Bottom
-Up
## Parsing: Problems
1) Two or more rules have the same
handle
## Note:
## A
handle
is the right-hand side of a rule.
## X
## 1
## X
## 2
## X
n
## A
## ...
r
## 1
## :
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
r
## 2
## :
## B
## →
## X
## 1
## X
## 2
## ...
## X
n
handle
tokens
## X
## 1
## X
## 2
## X
n
## B
## ...
tokens
Use rule
r
## 1
or
r
## 2
## ?
## E   E
## E   E
Which of these tree to create?
2) Ambiguous grammars
## G
expr
## 2
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
## 1
## :
## E
## →
## E
## +
## E
## ,
## 2
## :
## E
## →
## E
## *
## E
## ,
## 3
## :
## E
## →
## (
## E
## )
## ,
## 4
## :
## E
## →
i
## }
## E
## E
## E
## +
## *
i
i
i
## E
## E
## E
## +
## *
i
i
i
## 2/12

## Bottom
-Up Parsers
## Bottom
-Up
## Parser
## $
## Table(s)
## ...
a
i
a
n
a
## 1
a
## 2
## ...
## X
y
## $
## ...
## Pushdown:
Right parse
## =
reverse
sequence of rules used in
the
rightmost derivation
of the
tokenized source program
1) Operator-precedence parser
- the least powerful, but simple & easy-to-make
## •
Model of Bottom
-Up parser:
2) LR parser
- the most powerful
Input string:
## 3/12

Operator-Precedence Parser
- No two distinct nonterminals have the same handle• No
ε
## -rules.
a
## 1
## ......
## Table[
a
i
## ,
a
j
## ]
## ∈
## {<
## ,
## =
## ,
## >
## ,
blank
## }
## Precedence-table:
## • Let
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
) be CFG, where
## T
## = {
a
## 1
## ,
a
## 2
## , ... ,
a
n
## }
a
i
a
n
## $
a
## 1
## ...
## ...
a
j
a
n
## $
## S
a
## <
b
Illustration of meaning of <, =, >:
a
## =
b
a
## >
b
## S
## S
## ...
## ...
## ...
a
## A
b
## ...
a
## A
b
## ...
## A
b
## ...
a
## 4/12
## ...
## ...

## •
## Input:
Precedence-table for
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
## );
x
## ∈
## T
## *
## •
## Output:
Right parse of
x
if
x
## ∈
## L
## (
## G
); otherwise,
error
## •
## Method:
## • Push
## $
onto the pushdown;
## •
repeat
- let
a
= the topmost
terminal
on the pushdown and
b
= the current token
## •
case
## Table[
a
## ,
b
## ]
of:
## •
## =
## :
push(
b
) & read next
b
from input string
## •
## <
## :
replace
a
with
a
## <
on the pushdown &
push(
b
) & read next
b
from input string
## •
## >
: if
## <
y
is the pushdown top string
and
r
## :
## A
## →
y
## ∈
## P
then
replace
## <
y
with
## A
& write
r
to output
else
error
## •
blank
: if
a
## =
## $
and
b
## =
## $
then
success
else
error
until
success
or
error
Operator-Precedence Parser: Algorithm
## 5/12

Operator-Precedence Parser: Example
Precedence-table for
## G
expr
## 2
## :
## +
## G
expr
## 2
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
## 1
## :
## E
## →
## E
## +
## E
## ,
## 2
## :
## E
## →
## E
## *
## E
## ,
## 3
## :
## E
## →
## (
## E
## )
## ,
## 4
## :
## E
## →
i
## }
## Note:
Operator associativity and
precedence rules underlie the precedence table:
## E
## E
## E
## +
## *
i
i
i
## E   E
## E
## E
## E
## +
## *
i
i
i
## E   E
## *
## (
## )
i
## $
## +
## *
## ()
i
## $
## >>>><<
## <>>><<
## <<<<
## >>>>=
## <<<<
## >>>>
Input token
Pushdown topmost terminal
Right parse:
## 44142
Right parse:
## 44421
## 4
## 4
## 4
## 2
## 1
## 4
## 4
## 4
## 2
## 1
## ☺
Right tree:
## 
Wrong tree:
## 6/12

Operator-Precedence Parsing: Example
## 1
## :
## E
## →
## E
## +
## E
## 2
## :
## E
## →
## E
## *
## E
## 3
## :
## E
## →
## (
## E
## )
## 4
## :
## E
## →
i
Input string:
i
## +
i * i
## $
## Pushdown    Op   Input
## Rule
## $
## <
i
## +
i*i
## $
## Success
Right parse:
## 44421
## Rules:
## +
## *
## (
## )
i
## $
## +
## *
## ()
i
## $
## >>>><<
## <>>><<
## <<<<
## >>>>=
## <<<<
## >>>>
## $<
i
## >
## +
i*i
## $
## 4
## :
## E
## →
i
## $
## E
## <
## +
i*i
## $
## $<
## E
## +
## <
i
## *i
## $
## $<
## E+<
i
## >
## *
i
## $
## 4
## :
## E
## →
i
## $<
## E
## +
## E
## <
## *
i
## $
## $<
## E+
## <
## E
## *
## <
i
## $
## $<
## E+
## <
## E*
## <
i
## >
## $
## 4
## :
## E
## →
i
## $<
## E+
## <
## E
## *
## E
## >
## $
## 2
## :
## E
## →
## E
## *
## E
## $<
## E
## +
## E
## >
## $
## 1
## :
## E
## →
## E
## +
## E
## $
## E
## $
## 7/12

Construction of Pre
cedence
## Table 1/5
## • Let
## G
expr
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
## },
## T
## = {
## (
## ,
## )
## ,
id
## 1
## ,
id
## 2
## , ...,
id
m
## ,
op
## 1
## ,
op
## 2
## , ...
op
n
## },
## P
## = {
## E
## →
## (
## E
## )
## ,
## E
## →
id
## 1
## ,
## E
## →
id
## 2
## , ...
## ,
## E
## →
id
m
## ,
## E
## →
## E
op
## 1
## E
## ,
## E
## →
## E
op
## 2
## E
## , ...,
## E
## →
## E
op
n
## E
## }
## Note:
id
## 1
## ,
id
## 2
## , ...,
id
m
are identifiers,
op
## 1
## ,
op
## 2
## , ...
op
n
are different operators
1) Precedence of operators:• If
op
i
has
higher precedence
than
op
j
then
op
i
## >
op
j
and
op
j
## <
op
i
## +
## *
## +
## *
## >
## <
## Example:
Precedence-table part derived from
the precedence of operators in
## G
expr
## 2
## *
## >
## +
## +
## <
## *
## 8/12

Construction of Pre
cedence
## Table 2/5
## 2) Associativity:
## • Let
op
i
and
op
j
have
equal precedence
## • If
op
i
and
op
j
are
left associative
then
## • If
op
i
and
op
j
are
right associative
then
## +
## *
## +
## *
## >
## >
## Note:•
op
i
is left-associative
## ⇔
a
op
i
b
op
i
c
## =
## (
a
op
i
b
## )
op
i
c
## •
op
i
is right-associative
## ⇔
a
op
i
b
op
i
c
## =
a
op
i
## (
b
op
i
c
## )
op
i
## >
op
j
and
op
j
## >
op
i
op
i
## <
op
j
and
op
j
## <
op
i
## +
is left-associative
## *
is left-associative
## 9/12
## Example:
Precedence-table part derived from
the associativity of operators in
## G
expr
## 2

Construction of Precedence
## Table 3/5
## 3) Identifiers:
id
i
## >
a
## +
## *
## (
## )
i
## $
## +
## *
## ()
i
## $
## >  >
## >
## <<<<
## >
## 10/12
## • If
a
## ∈
## T
may
precede
id
i
, then
## • If
a
## ∈
## T
may
follow
id
i
, then
a
## <
id
i
## Example:
Precedence-table part for identifiers
## $
## ,
## (
## ,
## +
## ,
## *
may precede
i
## $
i
## *
## (
i
## +
i
## )
## *
i
## *
## ,
## +
## ,
## )
## ,
## $
may follow
i
i
## *
## (
i
## +
i
## )
## *
i
## $

a
## >
## )
Construction of Precedence
## Table 4/5
4) Parentheses:• A pair of parentheses:  • Let
a
## ∈
## T
## – {
## )
## ,
## $
## }. Then,
## • Let
a
## ∈
## T
## – {
## (
## ,
## $
## }. Then,
## • Let
a
## ∈
## T
and
a
may
precede
## (
## . Then,
## • Let
a
## ∈
## T
and
a
may
follow
## )
## . Then,
## (
## <
a
a
## <
## (
## )
## >
a
## +
## *
## (
## )
i
## $
## +
## *
## ()
i
## $
## ><
## ><
## <<<<
## >>>>=  <
## >
## 11/12
## Example:
## Precedence-table
part for parentheses.
## (
## =
## )
## $
## (
i
## +
## (
## (
i
## *
## (
i
## +
## (
i + i
## )))))
## $
## ,
## (
## ,
## *
## ,
## +
may precede
## (
## (((((
i + i
## )
## +
i
## )
## *
i
## )
## )
## +
i
## )
## $
## +
## ,
## *
## ,
## )
## ,
## $
may follow
## )

Construction of Precedence Table 5/5
## 5) End Marker
## $
## • Let
op
i
be any operator. Then:
## $
## <
op
i
and
op
i
## >
## $
## $
## $
## >>
## <  <
## +
## *
## +
## *
## +
## *
## (
## )
i
## $
## +
## *
## ()
i
## $
## >>>><<
## <>>><<
## <<<<
## >>>>=
## <<<<
## >>>>
## Summary:
## 12/12
## Example:
Precedence-table part
for end-markers.
## $
## <
## +
## $
## <
## *
## +
## >
## $
## *
## >
## $