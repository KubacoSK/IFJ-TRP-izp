

Part VII.
## Top
-Down
## Parsing
## 1/57

## Top
-Down Parsing: Introduction
## S
## A
a
x
y
## Problem:
Which rule to use?
Basic idea
## :
## Table:
## ...
a
## ...
## ......
## A
t
## (
p
## ,
a
## )
α
## (
## A
## ,
a
## )
α
Use rule
r
## :
## A
## →
x
## Question:
Could you construct
this table for
any
## CFG
## ?
## Answer:
## NO
## 2/57

## A Table
-Based Selection of a Rule
## S
## A
a
x
## A
## X
## 1
## X
## 2
## X
n
## ...
## Rule
r
## 1
## :
## A
## Y
## 1
## Y
## 2
## Y
m
## ...
## Rule
r
## 2
## :
## Table:
## ...
a
## ...
## ......
## A
t
## (
p
## ,
a
## )
α
## (
## A
## ,
a
## )
α
Use rule
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
Use rule
r
## 2
## :
## A
## →
## Y
## 1
## Y
## 2
## ...
## Y
m
## ?
Which rule to use?
a
x
## 1
a
x
## 2
## 3/57

## Set
## First
## Definition:
## Let
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
) be a CFG. For
every
x
## ∈
## (
## N
## ∪
## T
## )
## *
,we define the set
## First
## (
x
) as
## First
## (
x
## ) = {
a
## :
a
## ∈
## T
## ,
x
## ⇒
## *
a
y
## ;
y
## ∈
## (
## N
## ∪
## T
## )
## *
## }.
## Gist:
## First
## (
x
) is the set of all terminals that can
begin a string
derivable from
x
## .
## Illustration:
x
## =
## X
## 1
## X
## 2
## X
n
## ...
a
y
x
## =
## X
## 1
## X
## 2
## ...
## X
n
## ⇒
## *
a
y
a
## ∈
## First
## (
x
## )
## 4/57

LL Grammars
without
ε
## -rules
## Definition:
## Let
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
) be a CFG without
ε
## -rules.
## G
is an
## LL
grammar
if for every
a
## ∈
## T
and every
## A
## ∈
## N
there is
no more than one
rule
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## ∈
## P
such that
a
## ∈
## First
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
## Illustration:
## A
## X
## 1
## X
## 2
## X
n
## ...
## Rule
r
## 1
## :
## A
## Y
## 1
## Y
## 2
## Y
m
## ...
## Rule
r
## 2
## :
a
x
## 1
a
x
## 2
## Table:
## ...
a
## ...
## ......
## A
α
## (
## A
## ,
a
## )
α
a
## ∈
## First
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
a
## ∈
## First
## (
## Y
## 1
## Y
## 2
## ...
## Y
m
## )
Ruled out in an LL grammar
Only rule
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
## 5/57

## S
imple
## P
rogramming
## L
anguage (SPL)
## 1:
## <prog>
## →
begin
## <st-list>
## 2:
## <st-list>
## →
## <stat>
## ;
## <st-list>
## 3:
## <st-list>
## →
end
## 4:
## <stat>
## →
read id
## 5:
## <stat>
## →
write
## <item>
## 6:
## <stat>
## →
id :=
add (
## <item>
## <it-list>
## 7:
## <it-list>
## →
## ,
## <item>
## <it-list>
## 8:
## <it-list>
## →
## )
## 9:
## <item>
## →
int
## 10:
## <item>
## →
id
begin
read i;j := add(i, 1);write j;
end
## Example:
## ∈
## SPL
## Note:
## G
## SPL
is LL  grammar
## 6/57

## •
## Input:
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
## )
without
ε
## -rules
## •
## Output:
## First
## (
## X
) for every
## X
## ∈
## N
## ∪
## T
## •
## Method:
- for each
a
## ∈
## T
## :
## First
## (
a
## ) := {
a
## }
## •
Apply the following rule until no
## First
set
can be changed:
- if
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## ∈
## P
, then add
## First
## (
## X
## 1
) to
## First
## (
## A
## )
## Algorithm
## :
## First
## (
## X
## )
1) for each
a
## ∈
## T
## :
## First
## (
a
## ) := {
a
## }
because
a
## ⇒
## 0
a
## Illustration:
a
## ∈
## First
## (
## A
## )
## A
## X
## 1
## X
## 2
## ...
## X
n
## 2)
a
## ∈
## First
## (
## X
## 1
## )
## ...
a
## 7/57

## First
## (
## X
) for SPL
## : Example
## First
## (
begin
## )
## := {
begin
## }
## First
## (
end
## )
## := {
end
## }
## First
## (
read
## )
## := {
read
## }
## First
## (
write
## )
## := {
write
## }
## First
## (
## ,
## )
## := {
## ,
## }
## First
## (
## (
## )
## := {
## (
## }
## First
## (
## )
## )
## := {
## )
## }
## First
## (
## ;
## )
## := {
## ;
## }
## <st-list>
## →
end
## ∈
## P
## :
add
## First
## (
end
## )
to
## First
## (
## <st-list>
## )
## <st-list>
## →
## <stat>
## ...
## ∈
## P
: add
## First
## (
## <stat>
## )
to
## First
## (
## <st-list>
## )
## Summary:
## First
## (
## <st-list>
## )
## = {
id
## ,
write
## ,
read
## ,
end
## }
## <prog>
## →
begin
## ...
## ∈
## P
:    add
## First
## (
begin
## )
to
## First
## (
## <prog>
## )
## Summary:
## First
## (
## <prog>
## )
## = {
begin
## }
## First
## (
id
## )
## := {
id
## }
## First
## (
int
## )
## := {
int
## }
## First
## (
## :=
## )
## := {
## :=
## }
## First
## (
add
## )
## := {
add
## }
## <item>
## →
id
## ∈
## P
## :
add
## First
## (
id
## )
to
## First
## (
## <item>
## )
## <item>
## →
int
## ∈
## P
## :
add
## First
## (
int
## )
to
## First
## (
## <item>
## )
## Summary:
## First
## (
## <item>
## )
## = {
id
## ,
int
## }
## <it-list>
## →
## )
## ∈
## P
## :
add
## First
## (
## )
## )
to
## First
## (
## <it-list>
## )
## <it-list>
## →
## ,
## ...
## ∈
## P
## :
add
## First
## (
## ,
## )
to
## First
## (
## <it-list>
## )
## Summary:
## First
## (
## <it-list>
## )
## = {
## )
## ,
## ,
## }
## <stat>
## →
id
## ...
## ∈
## P
## :
add
## First
## (
id
## )
to
## First
## (
## <stat>
## )
## <stat>
## →
write
## ...
## ∈
## P
## :
add
## First
## (
write
## )
to
## First
## (
## <stat>
## )
## <stat>
## →
read
## ...
## ∈
## P
## :
add
## First
## (
read
## )
to
## First
## (
## <stat>
## )
## Summary:
## First
## (
## <stat>
## )
## = {
id
## ,
write
## ,
read
## }
## 8/57

Construction of LL Table
## ...
a
## ...
## ......
## A
t
## (
p
## ,
a
## )
α
## (
## A
## ,
a
## )
α
α
## (
## A
## ,
a
## ) =
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## ∈
## P
if
a
## ∈
## First
## (
## X
## 1
); otherwise,
α
## (
## A
## ,
a
) is blank
## ⇒
## ERROR
Construct the rest
analogically.
## {
begin
## }
## {
id
## ,
write
## ,
read
## }
## {
end
## }
## {
read
## }
## {
write
## }
## {
id
## }
## {
## ,
## }
## {
## )
## }
## {
int
## }
## {
id
## }
## Rule
r
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
## First
## (
## X
## 1
## )
## <prog><st-list><stat><it-list><item>
## 1:
## <prog>
## →
begin
## ...
## 2:
## <st-list>
## →
## <stat>
## ...
## 3:
## <st-list>
## →
end
## 4:
## <stat>
## →
read
## ...
## 5:
## <stat>
## →
write
## ...
## 6:
## <stat>
## →
id
## ...
## 7:
## <it-list>
## →
## ,
## ...
## 8:
## <it-list>
## →
## )
## 9:
## <item>
## →
int
## 10:
## <item>
## →
id
## Task:
LL table for SPL
id
int  :=
## ...
id
## ∈
## First
## (<
stat>
## )
## 2
id
## ∈
## First
## (
id
## )
## 6
id
## ∈
## First
## (
id
## )
## 10
## 9/57

begin
write
int
## 25
## ;
end
Parsing Based on LL Table: Example
## 1:
## <prog>
## →
begin
## <st-list>
## 2:
## <st-list>
## →
## <stat>
## ;
## <st-list>
## 3:
## <st-list>
## →
end
## 4:
## <stat>
## →
read id
## 5:
## <stat>
## →
write
## <item>
## <prog>
## 6:
## <stat>
## →
id := add (
## ...
## 7:
## <it-list>
## →
## ,
## <item> <it-list>
## 8:
## <it-list>
## →
## )
## 9:
## <item>
## →
int
## 10:
## <item>
## →
id
## <st-list>
begin
## 1
## ;
## <stat>
## <st-list>
## 2
int
## 9
end
## 3
## <item>
write
## 5
Source program:
begin write 25; end
## Lexical
## Analyzer
## <prog><st-list><stat><it-list><item>
## 3
## 1
## 42
## 52
## 62
## 10
## 9
## 8
## 7
beg  end   rd   wr    id   int     ,      (       )
;     :=   add
## 10/57

LL Grammars: Useful Transformations
## Generaly:
CFG are stronger that LL grammars
The family of languages
generated by
CFGs
The family of languages
generated by
LL grammars
## Illustration:
## •
## Some
CFGs can be converted to equivalent LL grammars
Basic conversions:1)
## Factorization
## 2)
Left recursion replacement
## ⊂
## Note:
A rule of the form
## A
## →
## A
x
, where
## A
## ∈
## N
## ,
x
## ∈
## (
## N
## ∪
## T
## )
## *
is called a
left recursive rule
## .
## 11/57

## Factorization
## A
x
y
## 1
## A
x
y
n
## ...
## A
x
y
## 1
x
y
n
## ...
## A
## ’
## A
## ’
## Example:
## <stat>
## →
write
id
## <stat>
## →
write
int
## Illustration:
## Idea:
Replace rules of the form
## A
## →
x
y
## 1
## ,
## A
## →
x
y
## 2
## ,
## ...
## ,
## A
## →
x
y
n
with
## A
## →
x
## A
## ’
## ,
## A
## ’
## →
y
## 1
## ,
## A
## ’
## →
y
## 2
## ,
## ...
## ,
## A
## ’
## →
y
n
## ,
where
## A
## ’
is a new nonterminal
## A
## <stat>
## →
write
## <item>
## <item>
## →
id
## <item>
## →
int
## 12/57

## Left Recursion Replacement
## A
## A
x
y
## ...
## Illustration:
## Idea:
Replace rules of the form
## A
## →
## A
x
## ,
## A
## →
y
with
## A
## →
y
## A
## ’
## ,
## A
## ’
## →
x
## A
## ’
## ,
## A
## ’
## →
ε
, where
## A
## ’
is a
new nonterminal.
## Example:
## E
## →
## E
## +T
## E
## →
## T
## T
## →
## T
## *F
## T
## →
## F
## F
## →
## (
## E
## )
## F
## →
i
x
## A
## A
x
## ...
## A
## ’
x
y
## ...
x
## A
x
## ...
## A
## ’
## A
## ’
## A
## ’
ε
## E
## →
## T
## E
## ’
## ,
## E
## ’
## →
## +T
## E
## ’
## ,
## E
## ’
## →
ε
## T
## →
## F
## T
## ’
## ,
## T
## ’
## →
## *F
## T
## ’
## ,
## T
## ’
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
## 13/57

LL Grammars with
ε
## -rules: Introduction
Simplification of this part:
## A
## X
## 1
## X
## 2
## X
n
## ...
## Rule
r
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
a
x
## S
y
## Why
ε
## -rules?
-    elimination of the left recursion introduces
ε
## -rule
## •
ε
-rules often make the language specification cleare
r
Assume that every input string of tokens ends with
## $
## .
## Note:
## $
acts as an
end marker
## .
Main problem with
ε
## -rules:
ε
ε
## ...
ε
## Maybe:
a
## ∉
## First
## (
## A
## ):
## 14/57
## Note
: We must define other sets:
## Empty
## ,
## Follow
and
## Predict.

Grammar for Arithmetical Expressions
## •
## G
expr
## 3
## = (
## N
## ,
## T
## ,
## P
## ,
## E
), where
## •
## N
## = {
## E
## ,
## E
## ’
## ,
## T
## ,
## T
## ’
## ,
## F
## },
## •
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
## •
## P
## = {
## 1
## :
## E
## →
## TE
## ’
## ,
## 2
## :
## E
## ’
## →
## +
## TE
## ’
## ,
## 3
## :
## E
## ’
→ ε
## ,
## 4
## :
## T
## →
## FT
## ’
## ,
## 5
## :
## T
## ’
## →
## *
## FT
## ’
## ,
## 6
## :
## T
## ’
→ ε
## ,
## 7
## :
## F
## →
## (
## E
## )
## ,
## 8
## :
## F
## →
i
## }
## Example:
## (
i
## +
i
## )*(
i
## +
i
## )
## ∈
## L
## (
## G
expr
## 3
## )
## 15/57

## Set
## Empty
## Definition:
## Let
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
) be a CFG.
## Empty
## (
x
## ) = {
ε
} if
x
## ⇒
## *
ε
; otherwise,
## Empty
## (
x
## ) =
## ∅
, where
x
## ∈
## (
## N
## ∪
## T
## )
## *
## .
## Gist:
## Empty
## (
x
) is the set that includes
ε
if
x
derives
the empty string; otherwise,
## Empty
## (
x
) is empty
## Illustration:
x
## =
## X
## 1
## X
## 2
## X
n
## ...
x
## =
## X
## 1
## X
## 2
## ...
## X
n
## ⇒
## *
ε
## Empty
## (
x
## ) = {
ε
## }
ε
ε
ε
## ...
ε
## 16/57

## •
## Input:
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
## )
## •
## Output:
## Empty
## (
## X
) for every
## X
## ∈
## N
## ∪
## T
## •
## Method:
## •
for each
a
## ∈
## T
## :
## Empty
## (
a
## ) :=
## ∅
## •
for each
## A
## ∈
## N
## :
if
## A
→ ε
## ∈
## P
then
## Empty
## (
## A
## ) := {
ε
## }
else
## Empty
## (
## A
## ) :=
## ∅
## •
Apply the following rule until no
## Empty
set can be
changed:
## •
if
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## ∈
## P
and
## Empty
## (
## X
i
## ) = {
ε
} for all
i
## = 1, ...,
n
then
## Empty
## (
## A
## ) := {
ε
## }
## Algorithm
## :
## Empty
## (
## X
## )
## 17/57

## Previous Algorithm: Illustration
## 1)
for each
a
## ∈
## T
## :
## Empty
## (
a
## ) :=
## ∅
because
a
## ⇒
## *
ε
## 2)
for each
r
## :
## A
## →
ε
## ∈
## P
## :
## Empty
## (
## A
## ) := {
ε
} because
## A
## ⇒
## 1
ε
## [
r
## ]
## Empty
## (
## A
## ) = {
ε
## }
ε
ε
ε
## ...
ε
## •
if
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## ∈
## P
and
## Empty
## (
## X
i
## ) = {
ε
## }
for all
i
## = 1, ...,
n
then
## Empty
## (
## A
## ) := {
ε
## }
## A
## X
## 1
## X
## 2
## ...
## X
n
3) Apply the following rules until no
## Empty
set can be
changed:
## 18/57

## Empty
## (
## X
) for
## G
expr
## 3
## : Example
## Empty
## (
i
## )
## :=
## ∅
## Empty
## (
## +
## )
## :=
## ∅
## Empty
## (
## *
## )
## :=
## ∅
## Empty
## (
## (
## )
## :=
## ∅
## Empty
## (
## )
## )
## :=
## ∅
## 19/57
## Initialization:
## Empty
## (
## E
## )
## :=
## ∅
## Empty
## (
## E
## ’
## )
## := {
ε
## }
## Empty
## (
## T
## )
## :=
## ∅
## Empty
## (
## T
## ’
## )
## := {
ε
## }
## Empty
## (
## F
## )
## :=
## ∅
## •
## No
## Empty
set can be changed.
## G
expr
## 3
## = (
## N
## ,
## T
## ,
## P
## ,
## E
), where:
## N
## = {
## E
## ,
## E
## ’
## ,
## T
## ,
## T
## ’
## ,
## F
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
## TE
## ’
## ,
## 2
## :
## E
## ’
## →
## +
## TE
## ’
## ,
## 3
## :
## E
## ’
## →
ε
## ,
## 4
## :
## T
## →
## FT
## ’
## 5
## :
## T
## ’
## →
## *
## FT
## ’
## ,
## 6
## :
## T
## ’
## →
ε
## ,
## 7
## :
## F
## →
## (
## E
## )
## ,
## 8
## :
## F
## →
i
## }

## •
## Input:
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
## )
## •
## Output:
## First
## (
## X
) for every
## X
## ∈
## N
## ∪
## T
## •
## Method:
## •
for each
a
## ∈
## T
## :
## First
## (
a
## ) := {
a
## }
## •
for each
## A
## ∈
## N
## :
## First
## (
## A
## ) :=
## ∅
## •
Apply the following rule until no
## First
set can be
changed:•
if
## A
## →
## X
## 1
## X
## 2
## ...
## X
k
## -1
## X
k
## ...
## X
n
## ∈
## P
then
- add all symbols from
## First
## (
## X
## 1
) to
## First
## (
## A
## )
## •
if
## Empty
## (
## X
i
## ) = {
ε
} for all
i
## = 1,...,
k
-1, where
k
## ≤
n
then
add all symbols from
## First
## (
## X
k
) to
## First
## (
## A
## )
## Algorithm
## :
## First
## (
## X
## )
## 20/57

## •
if
## A
## →
## X
## 1
## X
## 2
## ...
## X
k
## -1
## X
k
## ...
## X
n
## ∈
## P
then
## Previous Algorithm: Illustration
## 1)
for each
a
## ∈
## T
## :
## First
## (
a
## ) := {
a
} because
a
## ⇒
## 0
a
## 2)
for each
## A
## ∈
## N
## :
## First
## (
## A
## ) :=
## ∅
## (inicialization)
ε
a
## ∈
## First
## (
## X
k
## )
a
## ∈
## First
## (
## A
## )
ε
ε
ε
## ...
3b) if
## Empty
## (
## X
i
## ) = {
ε
} for all
i
## = 1, ...,
k
-1, where
k
## ≤
n
then
add all symbols from
## First
## (
## X
k
) to
## First
## (
## A
## ):
## A
## X
## 1
## X
## 2
## X
k
## -1
## ...
## X
n
## X
k
## ...
## 3b:
3) Apply the following rules until no
## First
set or
## Empty
set can be changed:
## ...
a
## 21/57
a
## ∈
## First
## (
## X
## 1
## )
a
## ∈
## First
## (
## A
## )
## ...
a
## 3a:
## A
## X
## 1
## X
## 2
## ...
## X
n
## 3a)
add all symbols from
## First
## (
## X
## 1
) to
## First
## (
## A
## )

## First
## (
## X
) for
## G
expr
## 3
## : Example
## F
## →
i
## ∈
## P
## :
add
## First
## (
i
## ) =
## {
i
## }
to
## First
## (
## F
## )
## F
## →
## (
## E
## )
## ∈
## P
## :
add
## First
## (
## (
## ) =
## {
## (
## }
to
## First
## (
## F
## )
## Summary:
## First
## (
## F
## ) = {
i
## ,
## (
## }
## T
## ’
## →
## *
## FT
## ’
## ∈
## P
:    add
## First
## (
## *
## ) =
## {
## *
}     to
## First
## (
## T
## ’
## )
## Summary:
## First
## (
## T
## ’
## ) = {
## *
## }
## T
## →
## FT
## ’
## ∈
## P
## :
add
## First
## (
## F
## ) =
## {
i
## ,
## (
}  to
## First
## (
## T
## )
## Summary:
## First
## (
## T
## )
## = {
i
## ,
## (
## }
## E
## ’
## →
## +
## TE
## ’
## ∈
## P
:   add
## First
## (
## +
## ) =
## {
## +
}    to
## First
## (
## E
## ’
## )
## Summary:
## First
## (
## E
## ’
## ) = {
## +
## }
## E
## →
## TE
## ’
## ∈
## P
## :
add
## First
## (
## T
## ) =
## {
i
## ,
## (
}  to
## First
## (
## E
## )
## Summary:
## First
## (
## E
## )
## = {
i
## ,
## (
## }
## 22/57
## First
## (
i
## )
## := {
i
## }
## First
## (
## +
## )
## := {
## +
## }
## First
## (
## *
## )
## := {
## *
## }
## First
## (
## (
## )
## := {
## (
## }
## First
## (
## )
## )
## := {
## )
## }
## Initialization:
## First
## (
## E
## )
## :=
## ∅
## First
## (
## E
## ’
## )
## :=
## ∅
## First
## (
## T
## )
## :=
## ∅
## First
## (
## T
## ’
## )
## :=
## ∅
## First
## (
## F
## )
## :=
## ∅
## •
## No
## First
set can be changed.

## First
## (
## X
## ) &
## Empty
## (
## X
) for
## G
expr
## 3
## : Summary
## 23/57
## Empty
## (
i
## )
## :=
## ∅
## Empty
## (
## +
## )
## :=
## ∅
## Empty
## (
## *
## )
## :=
## ∅
## Empty
## (
## (
## )
## :=
## ∅
## Empty
## (
## )
## )
## :=
## ∅
## Empty
## (
## E
## )
## :=
## ∅
## Empty
## (
## E
## ’
## )
## := {
ε
## }
## Empty
## (
## T
## )
## :=
## ∅
## Empty
## (
## T
## ’
## )
## := {
ε
## }
## Empty
## (
## F
## )
## :=
## ∅
## G
expr
## 3
## = (
## N
## ,
## T
## ,
## P
## ,
## E
), where:
## N
## = {
## E
## ,
## E
## ’
## ,
## T
## ,
## T
## ’
## ,
## F
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
## TE
## ’
## ,
## 2
## :
## E
## ’
## →
## +
## TE
## ’
## ,
## 3
## :
## E
## ’
## →
ε
## ,
## 4
## :
## T
## →
## FT
## ’
## 5
## :
## T
## ’
## →
## *
## FT
## ’
## ,
## 6
## :
## T
## ’
## →
ε
## ,
## 7
## :
## F
## →
## (
## E
## )
## ,
## 8
## :
## F
## →
i
## }
## Set
## Empty
for
all
## X
## ∈
## N
## ∪
## T
## :
## First
## (
i
## )
## := {
i
## }
## First
## (
## +
## )
## := {
## +
## }
## First
## (
## *
## )
## := {
## *
## }
## First
## (
## (
## )
## := {
## (
## }
## First
## (
## )
## )
## := {
## )
## }
## Set
## First
for all
## X
## ∈
## N
## ∪
## T
## :
## First
## (
## E
## )
## := {
i
## ,
## (
## }
## First
## (
## E
## ’
## )
## := {
## +
## }
## First
## (
## T
## )
## := {
i
## ,
## (
## }
## First
## (
## T
## ’
## )
## := {
## *
## }
## First
## (
## F
## )
## := {
i
## ,
## (
## }
## Note:
for each
a
## ∈
## T
## :
## Empty
## (
a
## ) =
## ∅
## ,
## First
## (
a
## ) = {
a
## }

## •
## Input:
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
## First
## (
## X
## ) &
## Empty
## (
## X
) for
every
## X
## ∈
## N
## ∪
## T
## ;
x
## =
## X
## 1
## X
## 2
## ...
## X
n
, where
x
## ∈ (
## N
## ∪
## T
## )
## +
## •
## Output:
## First
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
## •
## Method:
## •
## First
## (
## X
## 1
## X
## 2
## ...
## X
n
## ) :=
## First
## (
## X
## 1
## )
## •
Apply the following rule until nothing can be added
to
## First
## (
## X
## 1
## X
## 2
## ...
## X
k
## -1
## X
k
## ...
## X
n
## ):
## •
if
## Empty
## (
## X
i
## ) = {
ε
} for all
i
## = 1,...,
k
-1, where
k
## ≤
n
then
add all symbols from
## First
## (
## X
k
) to
## First
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
## Algorithm
## :
## First
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
## Illustration:
## X
## 1
## X
## 2
## X
k
## -1
## ...
## X
n
## X
k
## ...
ε
a
## ∈
## First
## (
## X
k
## )
ε
ε
ε
## ...
## ...
a
a
## ∈
## First
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
## 24/57
## ! Note:
## First
## (
ε
## ) =
## ∅

## First
## (
## X
## 1
## X
## 2
## ...
## X
n
## ): Example
## 25/57
## Empty
## (
## E
## )
## :=
## ∅
## Empty
## (
## E
## ’
## )
## := {
ε
## }
## Empty
## (
## T
## )
## :=
## ∅
## Empty
## (
## T
## ’
## )
## := {
ε
## }
## Empty
## (
## F
## )
## :=
## ∅
## First
## (
## E
## )
## := {
i
## ,
## (
## }
## First
## (
## E
## ’
## )
## := {
## +
## }
## First
## (
## T
## )
## := {
i
## ,
## (
## }
## First
## (
## T
## ’
## )
## := {
## *
## }
## First
## (
## F
## )
## := {
i
## ,
## (
## }
## G
expr
## 3
## = (
## N
## ,
## T
## ,
## P
## ,
## E
), where:
## N
## = {
## E
## ,
## E
## ’
## ,
## T
## ,
## T
## ’
## ,
## F
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
## TE
## ’
## ,
## 2
## :
## E
## ’
## →
## +
## TE
## ’
## ,
## 3
## :
## E
## ’
## →
ε
## ,
## 4
## :
## T
## →
## FT
## ’
## 5
## :
## T
## ’
## →
## *
## FT
## ’
## ,
## 6
## :
## T
## ’
## →
ε
## ,
## 7
## :
## F
## →
## (
## E
## )
## ,
## 8
## :
## F
## →
i
## }
## Set
## Empty
## &
## First
for all
## X
## ∈
## N
## :
## Task:
## First
## (
## E
## ’
## T
## ’
## FET
## )
## 1)
## First
## (
## E
## ’
## T
## ’
## FET
## ) :=
## First
## (
## E
## ’
## ) = {
## +
## }
## 2)
## First
## (
## E
## ’
## T
## ’
## FET
## ):
add
## First
## (
## T
## ’
## ) = {
## *
## }
to
## First
## (
## E
## ’
## T
## ’
## FET
## )
## Empty
## (
## E
## ’
## )
## = {
ε
## }
## 3)
## First
## (
## E
## ’
## T
## ’
## F
## ET
## ):
add
## First
## (
## F
## ) =
## {
i
## ,
## (
## }
to
## First
## (
## E
## ’
## T
## ’
## FET
## )
## Empty
## (
## E
## ’
## )
## =
## Empty
## (
## T
## ’
## )
## = {
ε
## }
## Summary:
## First
## (
## E
## ’
## T
## ’
## FET
## ) =
## {
## +
## ,
## *
## ,
i
## ,
## (
## }

## •
## Input:
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
## Empty
## (
## X
) for every
## X
## ∈
## N
## ∪
## T
## ;
x
## =
## X
## 1
## X
## 2
## ...
## X
n
, where
x
## ∈ (
## N
## ∪
## T
## )
## +
## •
## Output:
## Empty
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
## •
## Method:
## •
if
## Empty
## (
## X
i
## ) = {
ε
} for all
i
## = 1,...,
n
then
## Empty
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
## := {
ε
## }
else
## Empty
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
## :=
## ∅
## Algorithm
## :
## Empty
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
## Illustration:
## X
## 1
## X
## 2
## ...
## X
n
## Empty
## (
## X
## 1
## X
## 2
## ...
## X
n
## ) = {
ε
## }
ε
ε
ε
## ...
ε
## ! Note:
## Empty
## (
ε
## ) = {
ε
## }
## 26/57

## Empty
## (
## X
## 1
## X
## 2
## ...
## X
n
## ): Example
## 27/57
## Empty
## (
## E
## )
## :=
## ∅
## Empty
## (
## E
## ’
## )
## := {
ε
## }
## Empty
## (
## T
## )
## :=
## ∅
## Empty
## (
## T
## ’
## )
## := {
ε
## }
## Empty
## (
## F
## )
## :=
## ∅
## G
expr
## 3
## = (
## N
## ,
## T
## ,
## P
## ,
## E
), where:
## N
## = {
## E
## ,
## E
## ’
## ,
## T
## ,
## T
## ’
## ,
## F
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
## TE
## ’
## ,
## 2
## :
## E
## ’
## →
## +
## TE
## ’
## ,
## 3
## :
## E
## ’
## →
ε
## ,
## 4
## :
## T
## →
## FT
## ’
## 5
## :
## T
## ’
## →
## *
## FT
## ’
## ,
## 6
## :
## T
## ’
## →
ε
## ,
## 7
## :
## F
## →
## (
## E
## )
## ,
## 8
## :
## F
## →
i
## }
## Set
## Empty
for all
## X
## ∈
## N
## :
## Task:
## Empty
## (
## E
## ’
## T
## ’
## )
## Empty
## (
## E
## ’
## )
## =
## Empty
## (
## T
## ’
## )
## = {
ε
}, so
## Empty
## (
## E
## ’
## T
## ’
## ) = {
ε
## }

## Set
## Follow
## Definition:
## Let
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
) be a CFG. For
every
## A
## ∈
## N
, we define the set
## Follow
## (
## A
) as
## Follow
## (
## A
## )
## = {
a
## :
a
## ∈
## T
## ,
## S
## ⇒
## *
x
## A
a
y
## ,
x
## ,
y
## ∈
## (
## N
## ∪
## T
## )
## *
## }
## ∪
## {
## $
## :
## S
## ⇒
## *
x
## A
## ,
x
## ∈
## (
## N
## ∪
## T
## )
## *
## }
## Gist:
## Follow
## (
## A
) is the set of all terminals that can
come right after
## A
in a sentential form of
## G
## Illustration:
## S
## ⇒
## *
x
## A
z
a
y
## S
## A
x
z
## ⇒
## *
x
## A
a
y
## S
## ⇒
## *
x
## A
a
## ∈
## Follow
## (
## A
## )
## $
## ∈
## Follow
## (
## A
## )
## ...
## $
## 28/57
## A
x
## S
## $
## $

## •
## Input:
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
## •
## Output:
## Follow
## (
## A
) for every
## A
## ∈
## N
## •
## Method:
## •
## Follow
## (
## S
## ) := {
## $
## };
## •
Apply the following rules until no
## Follow
set
can be changed:
## •
if
## A
## →
x
## B
y
## ∈
## P
then
## •
if
y
## ≠
ε
then
add all symbols from
## First
## (
y
) to
## Follow
## (
## B
## );
## •
if
## Empty
## (
y
## )
## =
## {
ε
## }
then
add all symbols from
## Follow
## (
## A
) to
## Follow
## (
## B
## );
## Algorithm
## :
## Follow
## (
## A
## )
## 29/57

## Previous Algorithm: Illustration
## 1)
## Follow
## (
## S
## ) := {
## $
## }
2) Apply the following rules until no
## Follow
set can be changed:
## •
if
## A
## →
x
## B
y
## ∈
## P
then
a
z
x
## S
## ...
## $
2a) if
y
## ≠
ε
then
add all symbols
from
## First
## (
y
) to
## Follow
## (
## B
## )
## 2a:
## A
x
y
## B
a
## ∈
## First
## (
y
## )
a
## ∈
## Follow
## (
## B
## )
a
z
x
## ’
2b) if
## Empty
## (
y
## ) =
## {
ε
## }
then
add all
symbols from
## Follow
## (
## A
) to
## Follow
## (
## B
## )
## A
x
y
## B
## 2b:
a
## ∈
## Follow
## (
## A
## )
ε
ε
ε
a
## ∈
## Follow
## (
## B
## )
## 30/57
## $

## Follow
## (
## X
) for
## G
expr
## 3
## : Example  1/3
## 2)
## E
## →
## T
## E
## ’
## ∈
## P
## :
ε
## :
## Empty
## (
ε
## ) =
## {
ε
## }
add
## Follow
## (
## E
## ) =
## {
## $
## ,
## )
} to
## Follow
## (
## E
## ’
## )
## Empty
## (
## E
## )
## :=
## ∅
## Empty
## (
## E
## ’
## )
## := {
ε
## }
## Empty
## (
## T
## )
## :=
## ∅
## Empty
## (
## T
## ’
## )
## := {
ε
## }
## Empty
## (
## F
## )
## :=
## ∅
## First
## (
## E
## )
## := {
i
## ,
## (
## }
## First
## (
## E
## ’
## )
## := {
## +
## }
## First
## (
## T
## )
## := {
i
## ,
## (
## }
## First
## (
## T
## ’
## )
## := {
## *
## }
## First
## (
## F
## )
## := {
i
## ,
## (
## }
## E
## →
## T
## E
## ’
## ∈
## P
## :
≠ ε
add
## First
## (
## E’
## )   =
## {
## +
}    to
## Follow
## (
## T
## )
## E
## →
## T
## E
## ’
## ∈
## P
## :
## Empty
## (
## E
## ’
## ) =
## {
ε
## }
add
## Follow
## (
## E
## ) =
## {
## $
## ,
## )
} to
## Follow
## (
## T
## )
## Summary:
## Follow
## (
## E
## ’
## )
## = {
## $
## ,
## )
## }
## ,
## Follow
## (
## T
## )
## = {
## +
## ,
## $
## ,
## )
## }
## Follow
## (
## E
## )
## :=
## ∅
## Follow
## (
## E
## ’
## )
## :=
## ∅
## Follow
## (
## T
## )
## :=
## ∅
## Follow
## (
## T
## ’
## )
## :=
## ∅
## Follow
## (
## F
## )
## :=
## ∅
## 0)
## Follow
## (
## E
## ) :
## = {
## $
## }
## 1)
## F
## →
## (
## E
## )
## ∈
## P
## :
add
## First
## (
## )
## ) =
## {
## )
## }
to
## Follow
## (
## E
## )
≠ ε
## Summary:
## Follow
## (
## E
## )
## = {
## $
## ,
## )
## }
## 31/57

## Follow
## (
## X
) for
## G
expr
## 3
## : Example  2/3
## Empty
## (
## E
## )
## :=
## ∅
## Empty
## (
## E
## ’
## )
## := {
ε
## }
## Empty
## (
## T
## )
## :=
## ∅
## Empty
## (
## T
## ’
## )
## := {
ε
## }
## Empty
## (
## F
## )
## :=
## ∅
## First
## (
## E
## )
## := {
i
## ,
## (
## }
## First
## (
## E
## ’
## )
## := {
## +
## }
## First
## (
## T
## )
## := {
i
## ,
## (
## }
## First
## (
## T
## ’
## )
## := {
## *
## }
## First
## (
## F
## )
## := {
i
## ,
## (
## }
## 4)
## T
## →
## F
## T
## ’
## ∈
## P
## :
ε
## :
## Empty
## (
ε
## ) =
## {
ε
## }
add
## Follow
## (
## T
## ) =
## {
## +
## ,
## $
## ,
## )
}  to
## Follow
## (
## T
## ’
## )
≠ ε
## T
## →
## F
## T
## ’
## ∈
## P
## :
add
## First
## (
## T’
## )   =
## {
## *
## }
to
## Follow
## (
## F
## )
## T
## →
## F
## T
## ’
## ∈
## P
## :
## Empty
## (
## T
## ’
## ) =
## {
ε
## }
add
## Follow
## (
## T
## ) =
## {
## +
## ,
## $
## ,
## )
}  to
## Follow
## (
## F
## )
## Summary:
## Follow
## (
## T
## ’
## )
## = {
## +
## ,
## $
## ,
## )
## }
## ,
## Follow
## (
## F
## )
## = {
## *
## ,
## +
## ,
## $
## ,
## )
## }
## Follow
## (
## E
## )
## := {
## $
## ,
## )
## }
## Follow
## (
## E
## ’
## )
## := {
## $
## ,
## )
## }
## Follow
## (
## T
## )
## := {
## +
## ,
## $
## ,
## )
## }
## Follow
## (
## T
## ’
## )
## :=
## ∅
## Follow
## (
## F
## )
## :=
## ∅
## 3)
## E
## ’
## →
## +
## T
## E
## ’
## ∈
## P
## :
ε
## :
## Empty
## (
ε
## ) =
## {
ε
## }
add
## Follow
## (
## E’
## ) =
## {
## $
## ,
## )
## }
to
## Follow
## (
## E
## ’
## )
≠ ε
## E
## ’
## →
## +
## T
## E
## ’
## ∈
## P
## :
add
## First
## (
## E’
## )    =
## {
## +
## }
to
## Follow
## (
## T
## )
## E
## ’
## →
## +
## T
## E
## ’
## ∈
## P
## :
## Empty
## (
## E
## ’
## ) =
## {
ε
## }
add
## Follow
## (
## E
## ’
## ) =
## {
## $
## ,
## )
## }
to
## Follow
## (
## T
## )
## Summary:
Nothing is changed
## 32/57

## Follow
## (
## X
) for
## G
expr
## 3
## : Example  3/3
## Empty
## (
## E
## )
## :=
## ∅
## Empty
## (
## E
## ’
## )
## := {
ε
## }
## Empty
## (
## T
## )
## :=
## ∅
## Empty
## (
## T
## ’
## )
## := {
ε
## }
## Empty
## (
## F
## )
## :=
## ∅
## First
## (
## E
## )
## := {
i
## ,
## (
## }
## First
## (
## E
## ’
## )
## := {
## +
## }
## First
## (
## T
## )
## := {
i
## ,
## (
## }
## First
## (
## T
## ’
## )
## := {
## *
## }
## First
## (
## F
## )
## := {
i
## ,
## (
## }
## Follow
## (
## E
## )
## := {
## $
## ,
## )
## }
## Follow
## (
## E
## ’
## )
## := {
## $
## ,
## )
## }
## Follow
## (
## T
## )
## := {
## +
## ,
## $
## ,
## )
## }
## Follow
## (
## T
## ’
## )
## := {
## +
## ,
## $
## ,
## )
## }
## Follow
## (
## F
## )
## := {
## *
## ,
## +
## ,
## $
## ,
## )
## }
add
## Follow
## (
## T’
## ) =
## {
## +
## ,
## $
## ,
## )
} to
## Follow
## (
## T
## ’
## )
add
## Follow
## (
## T
## ’
## ) =
## {
## +
## ,
## $
## ,
## )
## }to
## Follow
## (
## F
## )
## 5)
## T
## ’
## →
## *
## F
## T
## ’
## ∈
## P
## :
ε
## :
## Empty
## (
ε
## ) =
## {
ε
## }
≠ ε
## T
## ’
## →
## *
## F
## T
## ’
## ∈
## P
## :
add
## First
## (
## T’
## ) =
## {
## *
## }
to
## Follow
## (
## F
## )
## T
## ’
## →
## *
## F
## T
## ’
## ∈
## P
## :
## Empty
## (
## T
## ’
## ) =
## {
ε
## }
## End:
Nothing is changed.
## Summary:
## Follow
## (
## E
## )
## :=
## {
## $
## ,
## )
## }
## Follow
## (
## E
## ’
## )
## := {
## $
## ,
## )
## }
## Follow
## (
## T
## )
## := {
## +
## ,
## $
## ,
## )
## }
## Follow
## (
## T
## ’
## )
## := {
## +
## ,
## $
## ,
## )
## }
## Follow
## (
## F
## )
## :=
## {
## *
## ,
## +
## ,
## $
## ,
## )
## }
## 33/57

## Set
## Predict
## Definition:
## Let
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
) be a CFG. For
every
## A
## →
x
## ∈
## P
, we define
## Predict
## (
## A
## →
x
## )
so that •
if
## Empty
## (
x
## ) = {
ε
} then
## Predict
## (
## A
## →
x
## ) =
## First
## (
x
## )
## ∪
## Follow
## (
## A
## )
## •
if
## Empty
## (
x
## ) =
## ∅
then
## Predict
## (
## A
## →
x
## ) =
## First
## (
x
## )
## Gist:
## Predict
## (
## A
## →
x
) is the set of all terminals that
can begin a string obtained by a derivation started  by using
## A
## →
x
## .
## 34/57

## Set
## Predict
## (
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## ): Illustration
## X
## 1
## X
## 2
## X
n
## ...
a
y
## X
## 1
## X
## 2
## X
n
## ...
a
## ...
ε
ε
ε
## ...
## Empty
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
## =
## ∅
vs.
## Empty
## (
## X
## 1
## X
## 2
## ...
## X
n
## ) = {
ε
## }
a
## ∈
## First
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
a
## ∈
## Follow
## (
## A
## )
ε
## Summary:
if
## Empty
## (
## X
## 1
## X
## 2
## ...
## X
n
## ) = {
ε
} then
## Predict
## (
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## ) =
## First
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
## ∪
## Follow
## (
## A
## );
otherwise,
## Predict
## (
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## ) =
## First
## (
## X
## 1
## X
## 2
## ...
## X
n
## )
## A
## S
x
z
a
= the current input symbol
## S
x
## A
or
## 35/57

## Predict
## (
## A
## →
x
) for
## G
expr
## 3
## : Example 1/2
## 1
## :
## E
## →
## TE
## ’
## Empty
## (
## TE
## ’
## ) =
## ∅
because
## Empty
## (
## T
## ) =
## ∅
## Predict
## (
## 1
## ) :=
## First
## (
## TE
## ’
## ) =
## First
## (
## T
## ) =
## {
i
## ,
## (
## }
## Empty
## (
## E
## )
## :=
## ∅
## Empty
## (
## E
## ’
## )
## := {
ε
## }
## Empty
## (
## T
## )
## :=
## ∅
## Empty
## (
## T
## ’
## )
## := {
ε
## }
## Empty
## (
## F
## )
## :=
## ∅
## First
## (
## E
## )
## := {
i
## ,
## (
## }
## First
## (
## E
## ’
## )
## := {
## +
## }
## First
## (
## T
## )
## := {
i
## ,
## (
## }
## First
## (
## T
## ’
## )
## := {
## *
## }
## First
## (
## F
## )
## := {
i
## ,
## (
## }
## Follow
## (
## E
## )
## := {
## $
## ,
## )
## }
## Follow
## (
## E
## ’
## )
## := {
## $
## ,
## )
## }
## Follow
## (
## T
## )
## := {
## +
## ,
## $
## ,
## )
## }
## Follow
## (
## T
## ’
## )
## := {
## +
## ,
## $
## ,
## )
## }
## Follow
## (
## F
## )
## := {
## *
## ,
## +
## ,
## $
## ,
## )
## }
## 2
## :
## E
## ’
## →
## +
## TE
## ’
## Empty
## (
## +
## TE
## ’
## ) =
## ∅
because
## Empty
## (
## +
## ) =
## ∅
## Predict
## (
## 2
## ) :=
## First
## (
## +
## TE
## ’
## ) =
## First
## (
## +
## ) =
## {
## +
## }
## 3
## :
## E
## ’
→ ε
## Empty
## (
ε
## ) =
## {
ε
## }
## Predict
## (
## 3
## ) :=
## First
## (
ε
## )
## ∪
## Follow
## (
## E
## ’
## ) =
## ∅
## ∪
## {
## $
## ,
## )
## } = {
## $
## ,
## )
## }
## 4
## :
## T
## →
## FT
## ’
## Empty
## (
## FT
## ’
## ) =
## ∅
because
## Empty
## (
## F
## ) =
## ∅
## Predict
## (
## 4
## ) :=
## First
## (
## FT
## ’
## ) =
## First
## (
## F
## ) =
## {
i
## ,
## (
## }
## 36/57

## Predict
## (
## A
## →
x
) for
## G
expr
## 3
## : Example 2/2
## Empty
## (
## E
## )
## :=
## ∅
## Empty
## (
## E
## ’
## )
## := {
ε
## }
## Empty
## (
## T
## )
## :=
## ∅
## Empty
## (
## T
## ’
## )
## := {
ε
## }
## Empty
## (
## F
## )
## :=
## ∅
## First
## (
## E
## )
## := {
i
## ,
## (
## }
## First
## (
## E
## ’
## )
## := {
## +
## }
## First
## (
## T
## )
## := {
i
## ,
## (
## }
## First
## (
## T
## ’
## )
## := {
## *
## }
## First
## (
## F
## )
## := {
i
## ,
## (
## }
## Follow
## (
## E
## )
## := {
## $
## ,
## )
## }
## Follow
## (
## E
## ’
## )
## := {
## $
## ,
## )
## }
## Follow
## (
## T
## )
## := {
## +
## ,
## $
## ,
## )
## }
## Follow
## (
## T
## ’
## )
## := {
## +
## ,
## $
## ,
## )
## }
## Follow
## (
## F
## )
## := {
## *
## ,
## +
## ,
## $
## ,
## )
## }
## 5
## :
## T
## ’
## →
## *
## FT
## ’
## Empty
## (
## *
## FT
## ’
## ) =
## ∅
because
## Empty
## (
## *
## ) =
## ∅
## Predict
## (
## 5
## ) :=
## First
## (
## *
## FT
## ’
## ) =
## First
## (
## *
## ) =
## {
## *
## }
## 6
## :
## T
## ’
→ ε
## Empty
## (
ε
## ) =
## {
ε
## }
## Predict
## (
## 6
## ) :=
## First
## (
ε
## )
## ∪
## Follow
## (
## T
## ’
## )
## =
## ∅
## ∪
## {
## +
## ,
## $
## ,
## )
## } = {
## +
## ,
## $
## ,
## )
## }
## 7
## :
## F
## →
## (
## E
## )
## Empty
## (
## (
## E
## )
## ) =
## ∅
because
## Empty
## (
## (
## ) =
## ∅
## Predict
## (
## 7
## ) :=
## First
## (
## (
## E
## )
## ) =
## First
## (
## (
## ) =
## {
## (
## }
## 8
## :
## F
## →
i
## Empty
## (
i
## ) =
## ∅
## Predict
## (
## 8
## ) :=
## First
## (
i
## )
## = {
i
## }
## 37/57

Construction of LL Table
## ...
a
## ...
## ......
## A
t
## (
p
## ,
a
## )
α
## (
## A
## ,
a
## )
α
α
## (
## A
## ,
a
## ) =
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## ∈
## P
if
a
## ∈
## Predict
## (
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## );
otherwise,
α
## (
## A
## ,
a
) is blank.
i
## ∈
## Predict
## (
## 1
## )
## 1
i
## ∈
## Predict
## (
## 4
## )
## 4
i
## ∈
## Predict
## (
## 8
## )
## 8
Construct the rest
analogically.
## EE
## ’
## TT
## ’
## F
## Task:
LL table for
## G
expr
## 3
i
## +
## (
## *
## )
## $
## 1
## :
## E
## →
## TE
## ’
## 2
## :
## E
## ’
## →
## +
## TE
## ’
## 3
## :
## E
## ’
→ ε
## 4
## :
## T
## →
## FT
## ’
## 5
## :
## T
## ’
## →
## *
## FT
## ’
## 6
## :
## T
## ’
→ ε
## 7
## :
## F
## →
## (
## E
## )
## 8
## :
## F
## →
i
## {
i
## ,
## (
## }
## {
## +
## }
## {
## $
## ,
## )
## }
## {
i
## ,
## (
## }
## {
## *
## }
## {
## +
## ,
## $
## ,
## )
## }
## {
## (
## }
## {
i
## }
## Rule
r
## Predict
## (
r
## )
## 38/57

Parsing Based on LL Table: Example
## E
## Question:
i
## *
i
## ∈
## L
## (
## G
expr
## 3
## )
## ?
## EE
## ’
## TT
## ’
## F
i
## +
## (
## 148
## *
## )    $
## 1
## :
## E
## →
## TE
## ’
## 2
## :
## E
## ’
## →
## +
## TE
## ’
## 3
## :
## E
## ’
## →
ε
## 4
## :
## T
## →
## FT
## ’
## 5
## :
## T
## ’
## →
## *
## FT
## ’
## 6
## :
## T
## ’
## →
ε
## 7
## :
## F
## →
## (
## E
## )
## 8
## :
## F
## →
i
## 147
## 26
## 5
## 36
## 36
-   i
## $
## F   T’
## 4
## E’
## T
## 1
## F
## T’
## 5
i
## 8
## 8
ε
## 6
ε
## 3
## 39/57

LL Grammars
with
ε
## -rules
## : Definition
## Definition:
## Let
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
) be a CFG
## .
## G
is an
## LL
grammar
if for every
a
## ∈
## T
and every
## A
## ∈
## N
there is
no
more than
one
## A
## -rule
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## ∈
## P
such that
a
## ∈
## Predict
## (
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## )
## Illustration:
a
## ∈
## Predict
## (
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## )
Ruled out in an LL grammar
a
## ∈
## Predict
## (
## A
## →
## Y
## 1
## Y
## 2
## ...
## Y
m
## )
## Rule
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
## X
## 1
## X
## 2
## X
n
## ...
## Rule
r
## 2
## :
## A
## →
## Y
## 1
## Y
## 2
## ...
## Y
m
## Y
## 1
## Y
## 2
## Y
m
## ...
a
## A
x
## S
y
a
## A
x
## S
y
## 40/57

LL Analyzer Implementation
1) Recursive-Descent Parsing
## 2) Predictive Parsing
- Each nonterminal is represented by a procedure, which perform
its analysis:
## A
## X
## 1
## X
## 2
## X
n
## ...
## Rule
r
## 1
## :
Input string
function
## A
## :
boolean
## ;
begin
## {
## X
## 1
analysis}
## {
## X
## 2
analysis}
## ...
## {
## X
n
analysis}
end
- Table-driven syntax analyzer with pushdown
Input string
## S
These symbols are
in the pushdown.
## 41/57
## S
## A
## →
## X
## 1
## X
## 2
## ...
## X
n

## Recursive Descent: Example 1/4
## EE
## ’
## TT
## ’
## F
i
## +
## (
## 148
## *
## ) $
## 147
## 26  5
## 36
## 36
Procedure GetNextToken;begin{ this procedure get the next token to global variable “
token
## ”}
endfunction
## E
: boolean;
begin
## E
:= false;
if token in ['
i
## ', '
## (
'] then
{ simulation of rule
## 1
## :
## E
## →
## TE’
## }
## E
## :=
## T
and
## E1
## ;
end;function
## T
: boolean;
begin
## T
:= false;
if token in ['
i
## ', '
## (
'] then
{ simulation of rule
## 4
## :
## T
## →
## FT’
## }
## T
## :=
## F
and
## T1
## ;
end;• For
## E
## ∈
## N
## : Rule
## 1
## :
## E
## →
## TE
## ’
## • For
## T
## ∈
## N
## : Rule
## 4
## :
## T
## →
## FT
## ’
## EE
## ’
## TT
## ’
## F
i
## +
## (
## 148
## *
## ) $
## 147
## 26  5
## 36
## 36
## 42/57
## 1
## 4

## Recursive Descent: Example 2/4
function
## E1
: boolean;
begin
## E1
:= false;
if token = '
## +
' then begin
{ simulation of rule
## 2
## :
## E’
## →
## +
## TE’
## }
GetNextToken;
## E1
## :=
## T
and
## E1
## ;
endelseif token in ['
## )
## ', '
## $
'] then
{ simulation of rule
## 3
## :
## E’
## →
ε
## }
## E1
:= true;
end;
## • For
## E
## ’
## ∈
## N
## : Rules
## 2
## :
## E
## ’
## →
## +
## TE
## ’
## ,
## 3
## :
## E
## ’
## →
ε
## EE
## ’
## TT
## ’
## F
i
## +
## (
## 148
## *
## ) $
## 147
## 26  5
## 36
## 36
## 43/57
## 2
## 3

## Recursive Descent: Example 3/4
function
## T1
: boolean;
begin
## T1
:= false;
if token = '
## *
' then begin
{ simulation of rule
## 5
## :
## T’
## →
## *
## FT’
## }
GetNextToken;
## T1
## :=
## F
and
## T1
## ;
endelseif token in ['
## +
## ', '
## )
## ', '
## $
'] then
{ simulation of rule
## 6
## :
## T’
## →
ε
## }
## T1
:= true;
end;
## • For
## T
## ’
## ∈
## N
## : Rules
## 5
## :
## T
## ’
## →
## *
## FT
## ’
## ,
## 6
## :
## T
## ’
## →
ε
## EE
## ’
## TT
## ’
## F
i
## +
## (
## 148
## *
## ) $
## 147
## 26  5
## 36
## 36
## 44/57
## 5
## 6

## Recursive Descent: Example 4/4
function
## F
: boolean;
begin
## F
:= false;
if token = '
## (
' then begin
{ simulation of rule
## 7
## :
## F
## →
## (
## E
## )
## }
GetNextToken;if
## E
then begin
## F
## := (token = '
## )
## ');
GetNextToken;
end;
endelseif token = '
i
' then begin
{ simulation of rule
## 8
## :
## F
## →
i
## }
## F
:= true;
GetNextToken;
end;
end;
## • For
## F
## ∈
## N
## : Rules
## 7
## :
## F
## →
## (
## E
## )
## ,
## 8
## :
## F
## →
i
## EE
## ’
## TT
## ’
## F
i
## +
## (
## 148
## *
## ) $
## 147
## 26  5
## 36
## 36
Main body:begin
GetNextToken;if
## E
then
write('
## OK
## ')
else
write('
## ERROR
## ')
end.
## 45/57
## 7
## 8

Recursive Descent: Illustration for
i
## *
i
## $
Input string:
GetNextToken
## ;
## Call
## E
## ;
i *  i
## $
For token =
i
## :
## Call
## T
## ,
## Call
## E1
## E
## :
## Start:
## T
## :
For token =
i
## :
## Call
## F
## ,
## Call
## T1
For token =
i
## :
GetNextToken
## ;
## Return
## TRUE
## ;
## F
## :
## TRUE
For token =
## *
## :
GetNextToken
## ;
## Call
## F
## ,
## Call
## T1
## T1
## :
## F
## :
For token =
i
## :
GetNextToken
## ;
## Return
## TRUE
## ;
## TRUE
## TRUE
## TRUE
## TRUE
## TRUE
For token =
## $
## :
## Return
## TRUE
## ;
## T1
## :
## TRUE
For token =
## $
## :
## Return
## TRUE
## ;
## E1
## :
## 46/57

## Predictive Parsing
## •
Model of
table-driven syntax analyzer
## :
## Table-driven
syntax analyzer
## $
Input string:
LL Table
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
Left parse
= sequence of rules used in the leftmost
derivation of the input string.
## 47/57

## •
## Input:
## LL
-table for
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
Left parse of
x
if
x
## ∈
## L
## (
## G
); otherwise, error
## •
## Method:
- push(
## $
) & push(
## S
) onto the pushdown;
## •
while
the pushdown is not empty
do
- let
## X
= the pushdown top and
a
= the current token
## •
case
## X
of:
## •
## X
## =
## $
## :
if
a
## =
## $
then
success
else
error
## ;
## •
## X
## ∈
## T
## :
if
## X
## =
a
then
pop(
## X
## ) &
read next
a
from
input string
else
error
## ;
## •
## X
## ∈
## N
:    if
r
## :
## X
## →
x
## ∈
## LL
## -table[
## X
## ,
a
## ]
then
replace
## X
with reversal(
x
) on the
pushdown & write
r
to output
else
error
## ;
end
## Table
-Driven Parsing: Algorithm
## 48/57

## Table
-Driven Parsing: Example
## 1
## :
## E
## →
## TE
## ’
## 2
## :
## E
## ’
## →
## +
## TE
## ’
## 3
## :
## E
## ’
## →
ε
## 4
## :
## T
## →
## FT
## ’
## 5
## :
## T
## ’
## →
## *
## FT
## ’
## 6
## :
## T
## ’
## →
ε
## 7
## :
## F
## →
## (
## E
## )
## 8
## :
## F
## →
i
## EE
## ’
## TT
## ’
## F
i
## +
## (
## 148
## *
## ) $
## 147
## 26  5
## 36
## 36
Input string:
i
## *
i
## $
## Pushdown Input
## Rule
## Derivation
## $
## E
i
## *
i
## $
## 1
## :
## E
## →
## TE
## ’
## E
## ⇒
## TE
## ’
## $
## E
## ’
## T
i
## *
i
## $
## 4
## :
## T
## →
## FT
## ’
## ⇒
## FT
## ’
## E
## ’
## $
## E
## ’
## T
## ’
## F
i
## *
i
## $
## 8
## :
## F
## →
i
## ⇒
i
## T
## ’
## E
## ’
## $
## E
## ’
## T
## ’
i
i
## *
i
## $
## $
## E
## ’
## T
## ’
## *
i
## $
## 5
## :
## T
## ’
## →
## *
## FT
## ’
## ⇒
i
## *
## FT
## ’
## E
## ’
## $
## E
## ’
## T
## ’
## F
## *   *
i
## $
## $
## E
## ’
## T
## ’
## F
i
## $
## 8
## :
## F
## →
i
## ⇒
i
## *
i
## T
## ’
## E
## ’
## $
## E
## ’
## T
## ’
i
i
## $
## $
## E
## ’
## T
## ’
## $
## 6
## :
## T
## ’
## →
ε
## ⇒
i
## *
i
## E
## ’
## $
## E
## ’
## $
## 3
## :
## E
## ’
## →
ε
## ⇒
i
## *
i
## $
## $
## Success
Left parse:
## 1485863
## Rules:
## 49/57

y
## Handling Errors: Introduction
## S
## A
x
Basic idea
## :
## 50/57
A wrong token
Two kinds of errors:
- Unexpected token• No rule applicable
## B
a
skip to
key
## Key
## Note:
a
## ∈
## Follow
## (
## A
## )

## Panic
-Mode (Hartmann) Error Recovery
## 51/57
## S
## A
## 1
x
a wrong token
## ...
## X
## 1
## ...
## ...
## A
## 3
## X
## 3
## A
## 2
## X
## 2
## ...
## ...
## ...
## ...
## • Let
## Context
## (
## A
## 1
## ) =
## Follow
## (
## A
## 1
## )
## ∪
## Follow
## (
## A
## 2
## )
## ∪
## ...
## Follow
## (
## A
n
## )
## =
## A
n
repeat•
a
:= GetNextToken;
{These tokens are skipped}
until
a
in
## Context
## (
## A
## 1
## )
if
a
in
## Follow
## (
## A
i
## )
then
continue with parsing fromthe symbol
## X
i
## .

y
## Panic
-Mode Recovery: Illustration 1
## /2
## 52/57
## S
## A
## 1
x
a wrong token
## ...
## X
## 1
## ...
## ...
## A
## 3
## X
## 3
## A
## 2
## X
## 2
## ...
## ...
## ...
## ...
## Let
a
## ∈
## Follow
## (
## A
## 1
## ).
Then, continue from
## X
## 1
## =
## A
n
a
skip to
key
First token from
## Context
## (
## A
## 1
## )

y
## Panic
-Mode Recovery: Illustration 2
## /2
## 53/57
## S
## A
## 1
x
a wrong token
## ...
## X
## 1
## ...
## ...
## A
## 3
## X
## 3
## A
## 2
## X
## 2
## ...
## ...
## ...
## ...
## =
## A
n
## Let
a
## ∈
## Follow
## (
## A
## 3
## ).
Then, continue from
## X
## 3
a
skip to key
First token from
## Context
## (
## A
## 1
## )

## Context
## (
## X
) for Predictive Parser: Variant I
## 54/57
## For
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
## ),
## Context
## (
## A
## ) =
## Follow
## (
## A
) for every
## A
## ∈
## N
## •
## Method:
## • Let
## A
be push
down
top
& no rule is applicable:
## •
repeat
a
:= GetNextToken;
{These tokens are skipped}
until
a
in
## Context
## (
## A
## )
- pop
## A
from the pushdown
## ;

## <st-list>
## <stat>
## <st-list>
## ‘;’
## ∈
## Follow
## (
## <expr>
## )
## Key
## Variant I: Example
## 55/57
## <prog>
begin   id
## :=  *  *
id
## +
id
## ;
write   id
## ;
end
## <st-list>
## <stat>
## <assign>
## <expr>

## Context
## (
## X
) for Predictive Parser: Variant II
## 56/57
## For
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
## ),
## Context
## (
## A
## ) =
## First
## (
## A
## )
## ∪
## Follow
## (
## A
) for every
## A
## ∈
## N
## •
## Method:
## • Let
## A
be push
down
top
& no rule is applicable:
## •
repeat
a
:= GetNextToken;
{These tokens are skipped}
until
a
in
## Context
## (
## A
## )
## •
if
a
## ∈
## First
## (
## A
## )
then
resume according to
## A
else
pop
## A
from the pushdown
## //
a
## ∈
## Follow
## (
## A
## )

## <st-list>
## <expr>
## <expr>
## <stat>
## <st-list>
## ‘
id
## ’
## ∈
## First
## (
## <expr>
## )
## Key
Variant II: Example
## 57/57
## <prog>
begin   id
## :=  *  *
id
## +
id
## ;
write   id
## ;
end
## <st-list>
## <stat>
## <assign>
## <expr>