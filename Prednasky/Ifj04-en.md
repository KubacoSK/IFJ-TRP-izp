

Part IV.
## Vari
ants
of
## Finite
## Automat
a
## 1/36

a)
## Configuration:
p
ax
p
q
## 1
q
## 3
a
a
q
## 2
ε
Next Configuration: q
## 1
x
or
q
## 2
x
or
q
## 3
ax
## ?
## ...
## ...
## ......
Theory vs. Practice
## Theory:
## ☺
## ×
## Practice:
## 
## 2/36
p
b)
## Configuration:
p
ax
q
## 1
q
## 3
a
b
q
## 2
c
## Next Configuration:
## Theory:
## 
## ×
## Practice:
## ☺
only
q
## 1
x
## ...
## ...
## ......

## Answer:
## YES
## ,
ab
## ∈
## L
## (
## M
## )
because
f
## ∈
## F
## .
Simulation of all possible moves from every configura
tion.
s
a
b
## Example:
## |–
q
## 1
a
b
## |–
q
## 2
a
b
## |–
s
b
q
## 1
s
b
f
ε
c
ε
c
a
q
## 2
a
b
## Question
## :
ab
## ∈
## L
## (
## M
## )
## ?
## |–
q
## 1
## |–
f
## |–
q
## 2
b
## |–
q
## 1
b
## FA
## M
is defined as:
No next
configuration
Use of FA in General
## 3/36

Preference in practice:
Determinictic FA
(DFA) that
makes no more than one move from every configuration.
## Definition:
## Let
## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
) be a FA
## .
## M
is an
ε
-free finite automaton
if for all
rules
pa
## →
q
## ∈
## R
, where
p
## ,
q
## ∈
## Q,
holds
a
## ∈ Σ
## (
a
≠ ε
## )
From FA to DFA in Essence 1/2
s
p
q
f
a
a
## 1)
Gist: Removal of
ε
## -moves
ε
ε
## 4/36
a

## Definition:
## Let
## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
) be an
ε
## -free
## FA
## .
## M
is a
deterministic finite automaton
(DFA) if for each rule
pa
## →
q
## ∈
## R
it holds that
## R
## – {
pa
## →
q
} contains no rule with the left-
hand side equal to
pa
## .
From FA to DFA in Essence 2/2
## 2)
Gist: Removal of nodeterminism
a
## ...
## ......
p
q
## 1
q
## 2
a
p
a
## {
q
## 1
## ,
q
## 2
## }
## ...
## ...
## New State
## 5/36

- For every FA
## M
, there is an equivalent DFA
## M
d
## .
## Proof
is based on these conversions:
## Finite Automaton
## M
ε
## -free Finite Automaton
## M'
## DFA
## M
d
## L
## (
## M
## ) =
## L
## (
## M'
## )
## L
## (
## M'
## ) =
## L
## (
## M
d
## )
## Theorem
## 6/36

ε
## -closure(
s
## )
ε
## -closure(
p
## )
ε
## -closure(
q
## )
ε
## -closure(
f
## )
## Definition:
For every
states
p
## ∈
## Q
, we define a set
ε
## -closure
## (
p
) as
ε
## -closure(
p
## ) = {
q
## :
q
## ∈
## Q
## ,
p
## |–
## *
q
## }
## Example:
s
p
ε
q
ε
f
a
ε
## -closure
## Gist:
q
is in
ε
## -closure(
p
) if FA can reach
q
from
p
without reading.
## 7/36

## •
## Input:
## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
## );
p
## ∈
## Q
## •
## Output:
ε
## -closure(
p
## )
## •
## Method:
## •
i
## := 0;
## Q
## 0
## := {
p
## };
## •
repeat
i
## :=
i
## + 1
## ;
## Q
i
## :=
## Q
i
## -1
## ∪
## {
p'
## :
p'
## ∈
## Q
## ,
q
## →
p'
## ∈
## R
## ,
q
## ∈
## Q
i
## -1
## };
until
## Q
i
## =
## Q
i
## -1
## ;
## •
ε
## -closure(
p
## ) :=
## Q
i
## .
## Algorithm:
ε
## -closure
## 8/36

## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
), where:
## Q
## = {
s
## ,
p
## ,
q
## ,
f
## },
## Σ
## = {
a
## },
## R
## = {
s
## →
p
## ,
p
## →
q
## ,
qa
## →
f
## },
## F
## = {
f
## }
## Task:
ε
## -closure(
s
## )
ε
## -closure: Example
## Q
## 0
## = {
s
## }
## 1)
s
## →
p'
## ;
p'
## ∈
## Q
## :
s
## →
p
## Q
## 1
## = {
s
## }
## ∪
## {
p
## } = {
s
## ,
p
## }
## 2)
s
## →
p'
## ;
p'
## ∈
## Q
## :
s
## →
p
p
## →
p'
## ;
p'
## ∈
## Q
## :
p
## →
q
## Q
## 2
## = {
s
## ,
p
## }
## ∪
## {
p
## ,
q
## } = {
s
## ,
p
## ,
q
## }
## 3)
s
## →
p'
## ;
p'
## ∈
## Q
## :
s
## →
p
p
## →
p'
## ;
p'
## ∈
## Q
## :
p
## →
q
q
## →
p'
## ;
p'
## ∈
## Q
## :
none
## Q
## 3
## = {
s
## ,
p
## ,
q
## }
## ∪
## {
p
## ,
q
## } = {
s
## ,
p
## ,
q
## } =
## Q
## 2
## =
ε
## -closure(
s
## )
## 9/36

## •
## Input:
## FA
## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
## )
## •
## Output:
ε
-free FA
## M'
## = (
## Q
## ,
## Σ
## ,
## R'
## ,
s
## ,
## F'
## )
## •
## Method:
## •
## R'
## :=
## ∅
## ;
## •
for all
p
## ∈
## Q
do
## R'
## :=
## R'
## ∪
## {
pa
## →
q
## :
p'a
## →
q
## ∈
## R
## ,
a
## ∈ Σ
## ,
p'
∈ ε
## -closure(
p
## ),
q
## ∈
## Q
## };
## •
## F'
## := {
p
## :
p
## ∈
## Q
## ,
ε
## -closure(
p
## )
## ∩
## F
## ≠
## ∅
## }.
Algorithm: FA to
ε
-free FA
Gist: Skip all
ε
## -moves
p
p'
q
a
ε
## ...
## ...
## ...
ε
ε
ε
ε
ε
ε
## -closure(
p
## )
a
## 10/36

## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
), where:
## Q
## = {
s
## ,
q
## 1
## ,
q
## 2
, f
## };
## Σ
## = {
a
## ,
b, c
## };
## R
## = {
sa
## →
s
## ,
s
## →
q
## 1
## ,
q
## 1
b
## →
q
## 1
## ,
q
## 1
b
## →
f
## ,
s
## →
q
## 2
## ,
q
## 2
c
## →
q
## 2
## ,
q
## 2
c
## →
f
## ,
fa
## →
f
## };
## F =
## {
f
## }
1) for
p
## =
s
## :
ε
## -closure(
s
## ) = {
s
## ,
q
## 1
## ,
q
## 2
## }
## A.
s
d
## →
q'
## ,
d
## ∈ Σ
## ,
q'
## ∈
## Q
## :
s
a
## →
s
## B.
q
## 1
d
## →
q'
## ,
d
## ∈ Σ
## ,
q'
## ∈
## Q
## :
q
## 1
b
## →
q
## 1
## ,
q
## 1
b
## →
f
## C.
q
## 2
d
## →
q'
## ,
d
## ∈ Σ
## ,
q'
## ∈
## Q
## :
q
## 2
c
## →
q
## 2
## ,
q
## 2
c
## →
f
## R'
## =
## ∅
## ∪
## {
s
a
## →
s
## ,
s
b
## →
q
## 1
## ,
s
b
## →
f
## ,
s
c
## →
q
## 2
## ,
s
c
## →
f
## }
FA to
ε
-free FA
## : Example 1/3
## 11/36

2) for
p
## =
q
## 1
## :
ε
## -closure(
q
## 1
## ) = {
q
## 1
## }
## A.
q
## 1
d
## →
q'
## ;
d
## ∈ Σ
## ;
q'
## ∈
## Q
## :
q
## 1
b
## →
q
## 1
## ,
q
## 1
b
## →
f
## R'
## =
## R'
## ∪
## {
q
## 1
b
## →
q
## 1
## ,
q
## 1
b
## →
f
## }
3) for
p
## =
q
## 2
## :
ε
## -closure(
q
## 2
## ) = {
q
## 2
## }
## A.
q
## 2
d
## →
q'
## ;
d
## ∈ Σ
## ;
q'
## ∈
## Q
## :
q
## 2
c
## →
q
## 2
## ,
q
## 2
c
## →
f
## R'
## =
## R'
## ∪
## {
q
## 2
c
## →
q
## 2
## ,
q
## 2
c
## →
f
## }
4) for
p
## =
f
## :
ε
## -closure(
f
## ) = {
f
## }
## A.
f
d
## →
q'
## ;
d
## ∈ Σ
## ;
q'
## ∈
## Q
## :
f
a
## →
f
## R'
## =
## R'
## ∪
## {
f
a
## →
f
## }
## R' =
## {
s
a
## →
s
## ,
s
b
## →
q
## 1
## ,
s
b
## →
f
## ,
s
c
## →
q
## 2
## ,
s
c
## →
f
## ,
q
## 1
b
## →
q
## 1
## ,
q
## 1
b
## →
f
## ,
q
## 2
c
## →
q
## 2
## ,
q
## 2
c
## →
f
## ,
f
a
## →
f
## }
FA to
ε
-free FA
## : Example 2/3
## 12/36

ε
## -closure(
s
## )
## ∩
## F
## = {
s
## ,
q
## 1
## ,
q
## 2
## }
## ∩
## {
f
## } =
## ∅
ε
## -closure(
q
## 1
## )
## ∩
## F
## = {
q
## 1
## }
## ∩
## {
f
## }
## =
## ∅
ε
## -closure(
q
## 2
## )
## ∩
## F
## = {
q
## 2
## }
## ∩
## {
f
## }
## =
## ∅
ε
## -closure(
f
## )
## ∩
## F
## = {
f
## }
## ∩
## {
f
## } = {
f
## }
## ≠
## ∅
## F'
## = {
f
## }
q
## 1
s
b
f
ε
c
ε
c
a
q
## 2
a
b
q
## 1
s
b
f
b
c
c
a
q
## 2
a
b
b
c
c
FA to
ε
-free FA
## : Example 3/3
## 13/36

## Algorithm
## :
ε
-free FA to
## DFA
## 1/2
## Gist:
In DFA, make states from all subsets of states in
ε
-free FA
and move between
them so that all possible states of
ε
-free FA
are simultaneously
simulated.
q
## 1
s
b
f
b
c
c
a
q
## 2
a
b
b
c
c
## Illustration:
## Q
## DFA
## = {
## {
s
## }, {
q
## 1
## }, {
q
## 2
## }, {
f
## }, {
s
## ,
q
## 1
## },
## {
s
## ,
q
## 2
## }, {
s
## ,
f
## }, {
q
## 1
## ,
q
## 2
## }, {
q
## 1
## ,
f
## }, {
q
## 2
## ,
f
## },
## {
s
## ,
q
## 1
## ,
q
## 2
## }, {
s
## ,
q
## 1
## ,
f
## }, {
s
## ,
q
## 2
## ,
f
## }, {
q
## 1
## ,
q
## 2
## ,
f
## },
## {
s
## ,
q
## 1
## ,
q
## 2
## ,
f
## }
## }
a
c
## {
q
## 2
## ,
f
## }
## ...
## {
q
## 1
## ,
f
## }
b
## ...
For state {
s
## ,
f
## }:
## {
s
## ,
f
## }
For state {
s
## }: ...
## ......
For state {
s
## ,
q
## 1
## ,
q
## 2
## ,
f
## }: ...
## 14/36

## •
## Input:
ε
-free FA:
## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
## )
## •
## Output:
## DFA:
## M
d
## = (
## Q
d
## ,
## Σ
## ,
## R
d
## ,
s
d
## ,
## F
d
## )
## •
## Method:
## •
## Q
d
## := {
## Q'
## :
## Q'
## ⊆
## Q
## ,
## Q'
## ≠ ∅
## };
## R
d
## :=
## ∅
## ;
## •
for each
## Q
## '
## ∈
## Q
d
## ,
and
a
## ∈ Σ
do
begin
## Q''
## :
## =
## {
q
## :
p
## ∈
## Q'
## ,
pa
## →
q
## ∈
## R
## };
if
## Q''
## ≠
## ∅
then
## R
d
## :
## = R
d
## ∪
## {
## Q'a
## →
## Q''
## };
end
## •
s
d
## :
## =
## {
s
## };
## •
## F
d
## :
## =
## {
## F'
## :
## F'
## ∈
## Q
d
## ,
## F'
## ∩
## F
## ≠ ∅
## }.
## Algorithm
## :
ε
-free FA to
## DFA
## 2/2
## 15/36

## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
), where:
## Q
## = {
s
## ,
q
## 1
## ,
q
## 2
, f
## };
## Σ
## = {
a
## ,
b, c
## };
## F =
## {
f
## }
## R =
## {
sa
## →
s
## ,
sb
## →
q
## 1
## ,
sb
## →
f
## ,
sc
## →
q
## 2
## ,
sc
## →
f
## ,
q
## 1
b
## →
q
## 1
## ,
q
## 1
b
## →
f
## ,
q
## 2
c
## →
q
## 2
## ,
q
## 2
c
## →
f
## ,
fa
## →
f
## };
## Q
d
## =
## {
## {
s
## }, {
s
## ,
q
## 1
## }, {
s
## ,
q
## 1
## ,
q
## 2
## }, {
s
## ,
q
## 1
## ,
f
## }, {
s
## ,
q
## 1
## ,
q
## 2
## ,
f
## }, {
s
## ,
q
## 2
## }, {
s
## ,
q
## 2
## ,
f
## },
## {
s
## ,
f
## }, {
q
## 1
## }, {
q
## 1
## ,
q
## 2
## }, {
q
## 1
## ,
f
## }, {
q
## 1
## ,
q
## 2
## ,
f
## }, {
q
## 2
## }, {
q
## 2
## ,
f
## }, {
f
## }
## }
for
## Q'
## = {
s
## }:
s
a
q
## 1
f
b
b
## ,
c
q
## 2
c
## ...
## ...
## ...
## {
s
## }
## ...
a
## {
q
## 1
## ,
f
## }
b
## ...
b
b
c
## {
q
## 2
## ,
f
## }
## ...
c
c
## R
d
## =
## ∅
## ∪
## {
## {
s
## }
a
## →
## {
s
## }, {
s
## }
b
## →
## {
q
## 1
## ,
f
## }, {
s
## }
c
## →
## {
q
## 2
## ,
f
## }
## }
ε
-free FA to
DFA: Example 1/5
## 16/36

for
## Q'
## = {
s
## ,
q
## 1
## }:
b
q
## 1
f
## ...
## ...
b
## ...
## {
s
## ,
q
## 1
## }
## {
s
## }
## ...
a
## {
q
## 1
## ,
f
## }
b
b
b
b
b
## ...
## {
q
## 2
## ,
f
## }
c
c
c
## R
d
## = R
d
## ∪
## {
## {
s
## ,
q
## 1
## }
a
## →
## {
s
## }, {
s
## ,
q
## 1
## }
b
## →
## {
q
## 1
## ,
f
## }, {
s
## ,
q
## 1
## }
c
## →
## {
q
## 2
## ,
f
## }
## }
s
a
q
## 1
f
b
## ,
c
q
## 2
c
## ...
b
## ...
## ...
ε
-free FA to
DFA: Example 2/5
## 17/36

## ...
a
## {
s
## ,
f
## }
a
## {
q
## 1
## ,
f
## }
b
b
b
b
b
## {
q
## 2
## ,
f
## }
c
## ...
c
c
c
c
## R
d
## = R
d
## ∪
## {
## {
s
## ,
q
## 1
## ,
q
## 2
## ,
f
## }
a
## →
## {
s
## ,
f
## }, {
s
## ,
q
## 1
## ,
q
## 2
## ,
f
## }
b
## →
## {
q
## 1
## ,
f
## },
## {
s
## ,
q
## 1
## ,
q
## 2
## ,
f
## }
c
## →
## {
q
## 2
## ,
f
## }
## }
Construct the
other states
analogically...
## ...
for
## Q'
## = {
s
## ,
q
## 1
## ,
q
## 2
## ,
f
## }:
b
q
## 1
f
## ...
## ...
b
s
a
q
## 1
f
b
## ,
c
q
## 2
c
b
## ...
c
q
## 2
f
## ...
## ...
c
f
## ...
## ...
a
## ...
## {
s
## ,
q
## 1
## ,
q
## 2
## ,
f
## }
## ...
ε
-free FA to
DFA: Example 3/5
## 18/36

Final states:
## F
d
## :
## =
## {
## F'
## :
## F'
## ∈
## Q
d
## ,
## F'
## ∩
## F
## ≠ ∅
## }
## {
s
## }
## ∩
## {
f
## }
## =
## ∅
## ⇒
## {
s
## }
## ∉
## F
d
## {
s
## ,
q
## 1
## ,
q
## 2
## ,
f
## }
## ∩
## {
f
## }
## =
## {
f
## }
## ≠
## ∅
## ⇒
## {
s
## ,
q
## 1
## ,
q
## 2
## ,
f
## }
## ∈
## F
d
for
## F
## = {
f
## }:
## {
s
## ,
q
## 1
## }
## ∩
## {
f
## }
## =
## ∅
## ⇒
## {
s
## ,
q
## 1
## }
## ∉
## F
d
## {
s
## ,
q
## 1
## ,
q
## 2
## }
## ∩
## {
f
## }
## =
## ∅
## ⇒
## {
s
## ,
q
## 1
## ,
q
## 2
## }
## ∉
## F
d
## {
s
## ,
q
## 1
## ,
f
## }
## ∩
## {
f
## }
## =
## {
f
## }
## ≠
## ∅
## ⇒
## {
s
## ,
q
## 1
## ,
f
## }
## ∈
## F
d
## ...
## F
d
## =
## {
## {
s
## ,
q
## 1
## ,
f
## }, {
s
## ,
q
## 1
## ,
q
## 2
## ,
f
## }, {
s
## ,
q
## 2
## ,
f
## }, {
s
## ,
f
## },
## {
q
## 1
## ,
f
## }, {
q
## 1
## ,
q
## 2
## ,
f
## }, {
q
## 2
## ,
f
## }, {
f
## }
## }
ε
-free FA to
DFA: Example 4/5
## 19/36

## {
q
## 1
## ,
f
## }
## {
q
## 2
## ,
f
## }
## {
s
## ,
q
## 1
## ,
q
## 2
## }
## {
s
## }
## {
s
## ,
q
## 1
## }
## {
s
## ,
q
## 2
## }
## {
q
## 1
## ,
q
## 2
## }
## {
q
## 1
## }
## {
q
## 2
## }
## {
s
## ,
f
## }
## {
q
## 1
## ,
q
## 2
## ,
f
## }
## {
s
## ,
q
## 1
## ,
f
## }
## {
s
## ,
q
## 2
## ,
f
## }
## {
s,q
## 1
## ,
q
## 2
## ,
f
## }
## {
f
## }
## Question:
Can we make DFA smaller?
a
b
c
b
b
a
a
c
a
c
a
b
c
a
b
c
a
b
c
b
c
a
b
c
a
b
c
a
a
b
b
c
c
a
b
c
ε
-free FA to
DFA: Example 5/5
## Answer:
## YES
## 20/36

## Definition:
## Let
## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
) be an FA
## .
A state
q
## ∈
## Q
is
accessible
if there exists
w
## ∈ Σ
## *
such that
sw
## |–
## *
q
; otherwise,
q
is
inaccessible.
s
q
## 1
a
f
## Example:
q
## 2
a
b
b
## Note:
Each inaccesible state can be removed from FA
## Accessible States
## Gist:
## State
q
is
accessible
if a string takes DFA
from
s
(the start state) to
q
## .
## State
s
- accesible:
w
## =
ε
## :
s
## |–
## 0
s
## State
q
## 1
- accesible:
w
## =
a
## :
s
a
## |–
q
## 1
## State
f
- accesible:
w
## =
a
b
## :
s
a
b
## |–
q
## 1
b
## |–
f
## State
q
## 2
## -
inaccessible
(there is no
w
## ∈ Σ
## *
such that
s
w
## |–
## *
q
## 2
## )
## 21/36

## {
s
## ,
q
## 1
## ,
q
## 2
## }
## {
s
## ,
q
## 1
## }
## {
s
## ,
q
## 2
## }
## {
q
## 1
## ,
q
## 2
## }
## {
q
## 1
## }
## {
s
## ,
f
## }
## {
q
## 1
## ,
q
## 2
## ,
f
## }
## {
s
## ,
q
## 1
## ,
f
## }
## {
s
## ,
q
## 2
## ,
f
## }
## {
s,q
## 1
## ,
q
## 2
## ,
f
## }
b
c
a
b
c
a
b
c
a
b
c
b
c
a
b
c
a
b
c
a
a
b
b
c
c
a
b
c
## {
q
## 2
## }
## Many
inaccessible states
## Previous Example
## {
q
## 1
## ,
f
## }
## {
q
## 2
## ,
f
## }
## {
s
## }
## {
f
## }
a
b
c
b
a
a
c
a
## 22/36

Algorithm II:
ε
-free FA to DFA
## 1/2
## Gist:
Analogy to the previous algorithm except that only sets of accessible states are introduced.
b
a
a
q
## 1
s
f
b
c
c
q
## 2
b
b
c
c
## Illustration:
## Q
## DFA
## = {
## {
s
## }
## }
a
## {
s
## }
For state {
s
## }:
Add new states
## {
q
## 1
## ,
f
## }
## ,
## {
q
## 2
## ,
f
## }
to
## Q
## DFA
For state
## {
q
## 1
## ,
f
## }
## : ...
## ...
For state
## {
q
## 2
## ,
f
## }
## : ...
Add new states ...
## {
q
## 1
## ,
f
## }
b
## ...
c
## {
q
## 2
## ,
f
## }
## ...
## 23/36

## •
## Input:
ε
## -
free
## FA:
## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
## )
## •
## Output:
## DFA:
## M
d
## = (
## Q
d
## ,
## Σ
## ,
## R
d
## ,
s
d
## ,
## F
d
## )
without any inaccessible states
## •
## Method:
## •
s
d
## :
## =
## {
s
## };
## Q
new
## :
## =
## {
s
d
## };
## R
d
## :=
## ∅
## ;
## Q
d
## :=
## ∅
## ;
## F
d
## :=
## ∅
## ;
## •
repeat
let
## Q'
## ∈
## Q
new
## ;
## Q
new
## :
## = Q
new
## –
## {
## Q'
## };
## Q
d
## :
## = Q
d
## ∪
## {
## Q'
## };
for each
a
## ∈ Σ
do begin
## Q''
## :
## =
## {
q
## :
p
## ∈
## Q'
## ,
pa
## →
q
## ∈
## R
## };
if
## Q''
## ≠
## ∅
then
## R
d
## :
## = R
d
## ∪
## {
## Q'a
## →
## Q''
## };
if
## Q''
## ∉
## Q
d
## ∪
## {
## ∅
## }
then
## Q
new
## :
## = Q
new
## ∪
## {
## Q''
## }
end;
if
## Q'
## ∩
## F
## ≠
## ∅
then
## F
d
## :
## = F
d
## ∪
## {
## Q'
## }
until
## Q
new
## =
## ∅
## .
Algorithm II:
ε
-free FA to DFA
## 2/2
## 24/36

## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
), where:
## Q
## = {
s
## ,
q
## 1
## ,
q
## 2
, f
## };
## Σ
## = {
a
## ,
b, c
## };
## F =
## {
f
## }
## R =
## {
sa
## →
s
## ,
sb
## →
q
## 1
## ,
sb
## →
f
## ,
sc
## →
q
## 2
## ,
sc
## →
f
## ,
q
## 1
b
## →
q
## 1
## ,
q
## 1
b
## →
f
## ,
q
## 2
c
## →
q
## 2
## ,
q
## 2
c
## →
f
## ,
fa
## →
f
## };
## Q
new
## =
## {
## {
s
## }
## }
## ;
## R
d
## =
## ∅
## ;
## Q
d
## =
## ∅
## ;
## F
d
## =
## ∅
for
## Q
## ' = {
s
## }:
s
a
q
## 1
f
b
b
## ,
c
q
## 2
c
## ...
## ...
## ...
## {
s
## }
a
## {
q
## 1
## ,
f
## }
b
b
b
c
## {
q
## 2
## ,
f
## }
c
c
## R
d
## :
## =
## ∅
## ∪
## {
## {
s
## }
a
## →
## {
s
## }, {
s
## }
b
## →
## {
q
## 1
## ,
f
## }, {
s
## }
c
## →
## {
q
## 2
## ,
f
## }
## }
## Q
new
## =
## {
## {
q
## 1
## ,
f
## }, {
q
## 2
## ,
f
## }
## }
## ,
## Q
d
## =
## ∅
## ∪
## {
## {
s
## }
## }
## ,
## F
d
## =
## ∅
ε
-free FA to DFA:
## Example 1/3
## 25/36

a
## {
f
## }
a
b
for
## Q'
## = {
q
## 1
## ,
f
## }:
## {
s
## }
a
b
c
b
b
b
## {
q
## 1
## ,
f
## }
## {
q
## 2
## ,
f
## }
b
q
## 1
f
## ...
## ...
f
## ...
## ...
a
## F
d
## :=
## ∅
## ∪
## {
## {
q
## 1
## ,
f
## }
## }
b
for
## Q'
## = {
q
## 2
## ,
f
## }:
c
q
## 2
f
## ...
## ...
c
f
## ...
## ...
a
## {
f
## }
a
## {
s
## }
a
b
c
## {
q
## 1
## ,
f
## }
## {
q
## 2
## ,
f
## }
## R
d
## :
## = R
d
## ∪
## {
## {
q
## 1
## ,
f
## }
a
## →
## {
f
## }, {
q
## 1
## ,
f
## }
b
## →
## {
q
## 1
## ,
f
## }
## }
## Q
new
## =
## {
## {
q
## 2
## ,
f
## }, {
f
## }
## }
## ,
## Q
d
## =
## Q
d
## ∪
## {
## {
q
## 1
## ,
f
## }
## }
## ,
a
a
c
c
c
## F
d
## :=
## F
d
## ∪
## {
## {
q
## 2
## ,
f
## }
## }
## R
d
## :
## = R
d
## ∪
## {
## {
q
## 2
## ,
f
## }
a
## →
## {
f
## }, {
q
## 2
## ,
f
## }
c
## →
## {
q
## 2
## ,
f
## }
## }
## Q
new
## =
## {
## {
f
## }
## }
## ,
## Q
d
## =
## Q
d
## ∪
## {
## {
q
## 2
## ,
f
## }
## }
## ,
ε
-free FA to DFA:
## Example 2/3
## 26/36

f
## ...
## ...
a
for
## Q'
## = {
f
## }:
b
## {
f
## }
a
## {
s
## }
a
b
c
## {
q
## 1
## ,
f
## }
## {
q
## 2
## ,
f
## }
a
c
a
a
## F
d
## :=
## F
d
## ∪
## {
## {
f
## }
## }
## R
d
## :
## = R
d
## ∪
## {
## {
f
## }
a
## →
## {
f
## }
## }
## Q
new
## =
## ∅
## ,
## Q
d
## =
## Q
d
## ∪
## {
## {
f
## }
## }
## ,
b
a
a
q
## 1
s
f
b
c
c
q
## 2
b
b
c
c
b
## {
f
## }
a
## {
s
## }
a
b
c
## {
q
## 1
## ,
f
## }
## {
q
## 2
## ,
f
## }
a
c
a
## Summary:
ε
-free FA to DFA:
## Example 3/3
## 27/36

## Definition:
## Let
## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
) be a DFA. A state
q
## ∈
## Q
is
terminating
if there exists
w
## ∈ Σ
## *
such that
qw
## |–
## *
f
with
f
## ∈
## F
; otherwise,
q
is
nonterminating.
s
q
## 1
a
f
## Example:
q
## 2
b
## State
s
- terminating:
w
## =
a
b
## :
s
a
b
## |–
q
## 1
b
## |–
f
## State
q
## 1
- terminating:
w
## =
b
## :
q
## 1
b
## |–
f
## State
f
- terminating:
w
## =
ε
## :
f
## |–
## 0
f
## State
q
## 2
## -
nonterminating
(there is no
w
## ∈ Σ
## *
such that
q
## 2
w
## |–
## *
q
## ,
q
## ∈
## F
## )
## Note:
Each nonterminating state can be removed from DFA
## Terminating States
## Gist:
## State
q
is
terminating
if a string takes DFA
from
q
to a final state.
b
a
## 28/36

## •
## Input:
## DFA:
## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
## )
## •
## Output:
## DFA:
## M
t
## = (
## Q
t
## ,
## Σ
## ,
## R
t
## ,
s
## ,
## F
## )
## •
## Method:
## •
## Q
## 0
## :=
## F
## ;
i
## := 0
## ;
## •
repeat
i
## :=
i
## + 1
## ;
## Q
i
## :=
## Q
i
## -1
## ∪
## {
q
## :
qa
## →
p
## ∈
## R
## ,
a
## ∈ Σ
## ,
p
## ∈
## Q
i
## -1
## };
until
## Q
i
## =
## Q
i
## -1
## ;
## •
## Q
t
## :=
## Q
i
## ;
## •
## R
t
## := {
qa
## →
p
## :
qa
## →
p
## ∈
## R
## ,
p
## ,
q
## ∈
## Q
t
## ,
a
## ∈ Σ
## }.
Algorithm: Removal of nont. states
## 29/36

## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
), where:
## Q
## = {
s
## ,
q
## 1
## ,
q
## 2
## ,
f
## },
## Σ
## = {
a
## ,
b
## },
## R
## = {
sa
## →
q
## 1
## ,
sb
## →
q
## 2
## ,
q
## 1
a
## →
q
## 2
## ,
q
## 1
b
## →
f
## },
## F
## = {
f
## }
## R
t
## = {
s
a
## →
q
## 1
## ,
s
b
## →
q
## 2
## ,
q
## 1
a
## →
q
## 2
## ,
q
## 1
b
## →
f
## }
## Nonterminating
## States
## : Example
## Q
## 0
## = {
f
## }
## 1)
qd
## →
f
## ;
q
## ∈
## Q
## ;
d
## ∈ Σ
## :
q
## 1
b
## →
f
## Q
## 1
## = {
f
## }
## ∪
## {
q
## 1
## } = {
f
## ,
q
## 1
## }
## 2)
qd
## →
f
## ;
q
## ∈
## Q
## ;
d
## ∈ Σ
## :
q
## 1
b
## →
f
qd
## →
q
## 1
## ;
q
## ∈
## Q
## ;
d
## ∈ Σ
## :
s
a
## →
q
## 1
## Q
## 2
## = {
f
## ,
q
## 1
## }
## ∪
## {
q
## 1
## ,
s
## } = {
f
## ,
q
## 1
## ,
s
## }
## 3)
qd
## →
f
## ;
q
## ∈
## Q
## ;
d
## ∈ Σ
## :
q
## 1
b
## →
f
qd
## →
q
## 1
## ;
q
## ∈
## Q
## ;
d
## ∈ Σ
## :
s
a
## →
q
## 1
qd
## →
s
## ;
q
## ∈
## Q
## ;
d
## ∈ Σ
## :
none
## Q
## 3
## = {
f
## ,
q
## 1
## ,
s
## }
## ∪
## {
q
## 1
## ,
s
## } = {
f
## ,
q
## 1
## ,
s
## } =
## Q
## 2
## =
## Q
t
## 30/36

s
q
## 1
f
1) Inaccessible state (
q
## 2
## ):
q
## 2
a
There exists no computation
from the start state to this
inaccessible state.
a
b
s
q
## 1
f
2) Nonterminating state (
q
## 2
## ):
q
## 2
a
a
b
There exists no computation
from this nonterminating
state to a final state.
Summary: States to Remove
## 31/36

## Definition:
## Let
## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
) be a
## DFA
## .
## M
is
complete
, if for any
p
## ∈
## Q
## ,
a
## ∈ Σ
there
is exactly one rule of the form
pa
## →
q
## ∈
## R
for some
q
## ∈
## Q
; otherwise,
## M
is
in complete
## Σ
## = {
a
## ,
b
## ,
c
## }
a
s
f
b
c
## Conversion:
Incomplete DFA
## ?
ab
c
## ??
c
a
## ,
b
q
false
a
## ,
b
## ,
c
to Complete DFA
b
a
s
f
c
Complete DFA
## 32/36
Gist: Complete DFA cannot get stuck.

## •
## Input:
Incomplete DFA
## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
## )
## •
## Output:
Complete DFA
## M
c
## = (
## Q
c
## ,
## Σ
## ,
## R
c
## ,
s
## ,
## F
## )
## •
## Method:
## •
## Q
c
## :=
## Q
## ∪
## {
q
false
## };
## •
## R
c
## :=
## R
## ∪
## {
qa
## →
q
false
## :
a
## ∈ Σ
## ,
q
## ∈
## Q
c
## ,
qa
## →
p
## ∉
## R
## ,
p
## ∈
## Q
## }.
Algorithm: DFA to Complete DFA
Gist: Add a “trap” state
## 33/36

## Definition:
## Let
## M
## = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
) be a
complete
## DFA
## . Then,
## M
is
well-specified
## FA
(WSFA) if:
## 1)
## Q
has no inaccessible state
## 2)
## Q
has no more than one nonterminating state
## Note:
If well-specified FA has one nonterminating
state, then it is
q
false
from the previous algorithm.
## Theorem:
For every FA
## M
, there is an
equivalent WS
## FA
## M
ws
## .
## Proof:
Use the next algorithm.
Well-Specified FA
## 34/36

## •
## Input:
## FA
## M
## •
## Output:
## WS
## FA
## M
ws
## •
## Method:
- convert a FA
## M
to
an equivalent
ε
-free FA
## M'
- convert a
## M'
to
an equivalent DFA
## M
d
without
any
inaccessible state
- convert
## M
d
to
an equivalent DFA
## M
t
without any
nonterminating state
- convert
## M
t
to
an equivalent complete DFA
## M
c
## •
## M
ws
## :=
## M
c
## Note:
No more than one nonterminating state in
## M
ws
## —
q
false
## Algorithm
## : FA
to
## WSFA
## 35/36

Variants of FA: Summary
## 36/36
Number of rules of the form
p
## →
q
## ,
where
p
## ,
q
## ∈
## Q
Number of rules of the form
pa
## →
q
## ,
for any
p
## ∈
Q, a
## ∈
## ∑
Number of inaccessible statesNumber of nonterminating statesNumber of this FAs for any regular language.
## FA
ε-free FA
## DFA
Complete FA
## WSFA
## 0-
n
## 0-
n
## 0-
n
## 0-
n
## ∞
## 0
## 0-
n
## 0-
n
## 0-
n
## ∞
## 0
## 0-10-
n
## 0-
n
## ∞
## 01
## 0-
n
## 0-
n
## ∞
## 010
## 0-1
## ∞