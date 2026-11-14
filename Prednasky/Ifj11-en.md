

Part XI.
Properties of Regular
## Languages
## 1/35

## • Let
## L
be a RL
## .
Then, there is
k
## ≥
1 such that
if
z
## ∈
## L
and
## |
z
## |
## ≥
k
## ,
then
there exist
u
## ,
v
## ,
w
## :
z = uvw
## ,
## 1)
v
≠ ε
## 2) |
uv
## |
## ≤
k
## 3)
for each
m
## ≥
## 0,
uv
m
w
## ∈
## L
Pumping Lemma for RLs
## Example:
for RE
r
## =
a
b
## *
c
## ,
## L
## (
r
) is
regular.
- for
z
## =
a
b
c
## :
z
## ∈
## L
## (
r
## ) &
## |
z
## |
## ≥
## 3
## :
u v w
uv
## 0
w =
a
b
## 0
c
## =
a
c
## ∈
## L
## (
r
## )
uv
## 1
w =
a
b
## 1
c
## =
a
b
c
## ∈
## L
## (
r
## )
uv
## 2
w =
a
b
## 2
c
## =
a
bb
c
## ∈
## L
## (
r
## )
## ...
v
## ≠
ε
## ,
## |
uv
## | = 2
## ≤
## 3
- for
z
## =
a
b
bc
## :
z
## ∈
## L
## (
r
## ) &
## |
z
## |
## ≥
## 3
## :
u v w
uv
## 0
w =
a
b
## 0
bc
## =
a
bc
## ∈
## L
## (
r
## )
uv
## 1
w =
a
b
## 1
bc
## =
a
b
bc
## ∈
## L
## (
r
## )
uv
## 2
w =
a
b
## 2
bc
## =
a
bb
bc
## ∈
## L
## (
r
## )
## ...
## ...
v
## ≠
ε
## ,
## |
uv
## | = 2
## ≤
## 3
## Gist:
Pumping lemma demonstrates an infinite iteration of some substring in RLs.
There is
k
## = 3
such that
## 1)
## ,
## 2)
and
## 3)
holds.
## 2/35

## Pumping Lemma
## : Illustration
## 3/35
## •
## L
= any regular language:
k
## ∈
## L
z
k
z
## ∈
## L
nothing interesting
w
u
v
k
## =
z
w
u
## ∈
## L
## 3)
v
w
v
u
w
v
u
## ∈
## L
## ∈
## L
## ...
## ≤
k
## 2)
## ≠
ε
## 1)

Proof of Pumping Lemma 1/3
## •
## Let
## L
be a regular language. Then, there exists
## DFA
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
), and
## L
## =
## L
## (
## M
## ).
## •
## For
z
## ∈
## L
## (
## M
## ),
## M
makes |
z
| moves and
## M
visits
## |
z
## |
## +
1 states:
s
a
## 1
a
## 2
## ...
a
n
## |–
q
## 1
a
## 2
## ...
a
n
## |– ... |–
q
n
## -1
a
n
## |–
q
n
## |
z
## |
## |
z
## |
## +
1 states
q
## 1
s
q
n
a
## 1
a
## 2
## ...
q
n
## -1
a
n
- for
z
## =
a
## 1
a
## 2
## ...
a
n
## :
a
n
## -1
## 4/35

Proof of Pumping Lemma 2/3
## • Let
k
= card
## (
## Q
)  (the number of states).
For each
z
## ∈
## L
and
## |
z
## |
## ≥
k
## ,
## M
visits
k +
1 or
more states. As
k +
## 1
## >
card
## (
## Q
), there exists a
state
q
that
## M
visits at least twice.
s
z
## =
s
u
v
w
## |–
i
q
v
w
## |–
j
q
w
## |–
## *
f
## ,
f
## ∈
## F
## Summary:
## • For
z
exist
u
## ,
v
## ,
w
such that
z
## =
u
v
w
## :
s
reads
v
q
reads
u
f
reads
w
s
u
## |–
i
q
q
w
## |–
## *
f
q
v
## |–
j
q
## ;
j
## ≥
## 1
## ,
i + j
## ≤
k
## 5/35

Proof of Pumping Lemma 3/3
-  There exist moves:
- for
m
## = 0
## ,
u
v
m
w
## =
u
v
## 0
w
## =
u
w
## ,
## 1.
## 2.
## 3.
s
u
w
## |–
i
q
w
## |–
## *
f
## ,
f
## ∈
## F
## 1.
## 3.
- for each
m
## > 0,
s
u
v
m
w
## |–
i
q
v
m
w
## |–
## *
f
## ,
f
## ∈
## F
## 1.
## 3.
## |–
j
q
v
m-
## 1
w
## 2.
## |–
j
q
w
## |–
j
## ...
## 2.
## 2.
## Summary:
## 1)
q
v
## |–
j
q
## ,
j
## ≥
## 1
; therefore,
## |
v
## |
## ≥
## 1
, so
v
≠ ε
## 2)
s
u
v
## |–
i
q
v
## |–
j
q
## ,
i + j
## ≤
k
; therefore,
## |
u
v
## |
## ≤
k
## 3)
For each
m
## ≥
## 0:
s
u
v
m
w
## |–
## *
f
## ,
f
## ∈
## F
, therefore
u
v
m
w
## ∈
## L
## QED
s
u
## |–
i
q
## ;
q
v
## |–
j
q
## ;
q
w
## |–
## *
f
## ,
f
## ∈
## F
, so
## 6/35

## Pumping Lemma: Application I
## •
Based on the pumping lemma, we often make a proof b
y
contradiction to demonstrate that a language is
not
regular
Assume that
## L
is regular
Consider the PL constant
k
and select
z
## ∈
## L
, whose
length depends on
k
so
## |z|
## ≥
k
is surely true.
For all decompositions of
z
into
uvw
## ,
v
≠ ε
## ,
## |
uv
## |
## ≤
k
, show
## :
there exists
m
## ≥
0 such that
uv
m
w
## ∉
## L
from the pumping lemma,
uv
m
w
## ∈
## L
contradiction
false assumption
## Therefore,
## L
is not regular
## 7/35

## Pumping Lemma: Example
Prove that
## L
## = {
a
n
b
n
## :
n
## ≥
0} is not regular:
## 1)
Assume that
## L
is regular. Let
k
## ≥
## 1
be the
pumping lemma constant for
## L
## .
## 2)
## Let
z
## =
a
k
b
k
## :
a
k
b
k
## ∈
## L
## ,
## |
z
## | = |
a
k
b
k
## |
## = 2
k
## ≥
k
## 3)
All decompositions of
z
into
uvw
## ,
v
≠ ε
## ,
## |
uv
## |
## ≤
k
## :
## 8/35
u
v
w
a a
## ...
a a
bb
## ...
bb
k
k
## |
uv
## |
## ≤
k
- pumping lemma:
uv
## 0
w
## ∈
## L
k
## -
i
## <
k
a a
bb
## ...
bb
## ∉
## L
u
w
## •
uv
## 0
w
## =
uw
## =
## Contradiction!
## 4)
## Therefore,
## L
is not regular

Note on Use of Pumping Lemma
## •
Pumping lemma:
## L
is regular
if
exist
k
## ≥
1 and ...
then
## L
is regular
exist
k
## ≥
1 and ...
if
then
## •
However, the next implication is
incorrect
## :
## •
## We
cannot
use the pumping lemma to
prove that
## L
is regular.
Main application of the pumping lemma:•
proof by contradiction that
## L
is
not
regular.
## 9/35

Pumping Lemma: Application II. 1/3
## •
We can use the pumping lemma to prove
some other theorems.
## Illustration:
## • Let
## M
be a DFA and
k
be the pumping lemma
constant (
k
is the number of states in
## M
## ). Then
## ,
## L
## (
## M
) is infinite
## ⇔
there exists
z
## ∈
## L
## (
## M
## ),
k
## ≤
## |
z
## | <
## 2
k
## Proof:
## 1)
there exists
z
## ∈
## L
## (
## M
## )
## ,
k
## ≤
## |
z
## |
## < 2
k
## ⇒
## L
## (
## M
) is infinite
## :
if
z
## ∈
## L
## (
## M
## )
## ,
k
## ≤
## |
z
## |
, then by PL:
z = uvw
## ,
v
## ≠
ε
, and for each
m
## ≥
## 0:
uv
m
w
## ∈
## L
## (
## M
## )
## L
## (
## M
) is infinite
## 10/35

Pumping Lemma: Application II. 2/3
## 2)
## L
## (
## M
) is infinite
## ⇒
there exists
z
## ∈
## L
## (
## M
## ),
k
## ≤
## |
z
## | < 2
k
## :
Assume that
## L
## (
## M
) is infinite
and there exists no
z
## ∈
## L
## (
## M
## )
## ,
## |
z
## |
## ≥
k
a)
Prove by contradiction that
## •
## L
## (
## M
) is infinite
## ⇒
there exists
z
## ∈
## L
## (
## M
## ), |
z
## |
## ≥
k
- We prove by contradiction, that
## L
## (
## M
) is infinite
there exists
z
## ∈
## L
## (
## M
## ), |
z
## |
## ≥
k
there exists
z
## ∈
## L
## (
## M
## ),
k
## ≤
## |
z
## | <
## 2
k
a)
b)
for all
z
## ∈
## L
## (
## M
) holds  |
z
## | <
k
## L
## (
## M
) is finite
## Contradiction !
## 11/35

## Pumping Lemma:
## Application
## II. 3/3
## If
z
## 0
## ∈
## L
## (
## M
## )
and
## |
z
## 0
## |
## ≥
k
, the PL implies:
z
## 0
## =
uvw
## ,
## |
uv
## |
## ≤
k
, and for each
m
## ≥
## 0,
uv
m
w
## ∈
## L
## (
## M
## )
b)
Prove by contradiction
## Contradiction !
Assume that
there is
z
## ∈
## L
## (
## M
## ), |
z
## |
## ≥
k
k
## 2
k
## |
uw
## |
## =
## |
z
## 0
## |
## –
## |
v
## |
for
m
## = 0
## :
uv
m
w =
uw
## ∈
## L
## (
## M
## )
## Summary:
uw
## ∈
## L
## (
## M
## ),
## |
uw
## |
## ≥
k
and
## |
uw
## | < |
z
## 0
## |!
z
## 0
is not the shortest string
satisfying
z
## 0
## ∈
## L
## (
## M
## ),
## |
z
## 0
## |
## ≥
k
## ≥
## 2
k
## ≤
k
## Let
z
## 0
be
the shortest string
satisfying
z
## 0
## ∈
## L
## (
## M
## )
## ,
## |
z
## 0
## |
## ≥
k
Because there exists no
z
## ∈
## L
## (
## M
## ),
k
## ≤
## |
z
## | < 2
k
, so
## |
z
## 0
## |
## ≥
## 2
k
and
there is no
z
## ∈
## L
## (
## M
## ),
k
## ≤
## |
z
## | < 2
k
## ≥
k
there exists
z
## ∈
## L
## (
## M
## ),
k
## ≤
## |
z
## | < 2
k
## •
there exists
z
## ∈
## L
## (
## M
## ), |
z
## |
## ≥
k
## ⇒
## 12/35

The family of
regular languages
## Illustration:•
The family of regular languages is closed under
union
## .
It means:
## Definition:
The family of regular languages
is closed under an operation
o
if the language
resulting from the application of
o
to
any
regular languages is also regular.
Closure properties 1/2
## L
## 1
## L
## 2
## ∪
## =
## L
## 3
## 13/35

## Proof:
## Theorem:
The family of regular languages is
closed under
union
## ,
concatenation
## ,
iteration
## .
Closure properties 2/2
## • Let
## L
## 1
## ,
## L
## 2
be two
regular languages
- Then, there exist two REs
r
## 1
## ,
r
## 2
## :
## L
## (
r
## 1
## ) =
## L
## 1
## ,
## L
## (
r
## 2
## ) =
## L
## 2
## ;
- By the definition of regular expressions:
## •
r
## 1
## .
r
## 2
is a RE denoting
## L
## 1
## L
## 2
## •
r
## 1
## +
r
## 2
is a RE denoting
## L
## 1
## ∪
## L
## 2
## •
r
## 1
## *
is a RE denoting
## L
## 1
## *
- Every RE denotes regular language, so
## L
## 1
## L
## 2
## ,
## L
## 1
## ∪
## L
## 2
## ,
## L
## 1
## *
are a
regular languages
## 14/35

## •
## Input:
Complete FA:
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
## Complete F
## A:
## M
## ’ = (
## Q
## ,
## Σ
## ,
## R
## ,
s
## ,
## F
## ’),
## •
## Method:
## •
## F
## ’ :=
## Q
## –
## F
## Algorithm
: FA for Complement
## L
## (
## M
## ’) =
## L
## (
## M
## )
## Example:
a
a
## ,
b
q
s
f
b
b
a
## Q
## –
## F
## F
## M
## :
## F
## ’ =
## Q
## –
## F
## L
## (
## M
## ) = {
x
## :
a
b
is a
substring
of
x
## };
## L
## (
## M
## ’) = {
x
## :
a
b
is no
substring
of
x
## }
a
a
## ,
b
f
b
b
a
## M
## ’:
s
q
## 15/35

FA for Complement: Problem
- Previous algorithm requires a
complete
## FA
## • If
## M
is incomplete FA
, then
## M
must be converted to
a complete FA before we use the previous algorithm
a
s
f
b
c
Incomplete DFA:
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
Complete DFA:
b
a
s
f
c
## M
## :
## Example:
c
a
## ,
b
a
## ,
b
## ,
c
a
c
f
s
b
q
false
## M
## 2
## ’:
## L
## (
## M
## 2
## ’)
## =
## L
## (
## M
## )
## L
## (
## M
## 1
## ’)
## ≠
## L
## (
## M
## )
## !
## -
c
## ∉
## L
## (
## M
## ),
c
## ∉
## L
## (
## M
## 1
## ’)
s
c
a
f
b
## M
## 1
## ’:
## 16/35

## Proof:
## Theorem:
The family of regular languages is
closed under
complement
## .
Closure properties: Complement
## •
## Let
## L
be a
regular language
- Then, there exists a complete DFA
## M
## :
## L
## (
## M
## ) =
## L
- We can construct a complete DFA
## M
## ’
## :
## L
## (
## M
## ’) =
## L
by using the previous algorithm
- Every FA defines a regular language, so
## L
is a
regular language
## 17/35

## Proof:
Closure properties: Intersection
## • Let
## L
## 1
## ,
## L
## 2
be two
regular languages
## •
## L
## 1
## ,
## L
## 2
are
regular languages
(the family of regular languages is closed under complement)•
## L
## 1
## ∪
## L
## 2
is a
regular language
(the family of regular languages is closed under union)•
## L
## 1
## ∪
## L
## 2
is a
regular language
(the family of regular languages is closed under complement)•
## L
## 1
## ∩
## L
## 2
## =
## L
## 1
## ∪
## L
## 2
is a
regular language
(DeMorgan’s law)
## Theorem:
The family of regular languages is
closed under
intersection
## .
## 18/35

## Definition:
Let a family of languages be
closed under union, intersection, and complement. Then, this family represents a Boolean algebra of languages
## .
Boolean Algebra of Languages
## Theorem:
The family of regular languages is
a Boolean algebra of languages.
- The family of regular languages is closed under union, intersection, and complement. Proof:
## 19/35

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
) be a WSFA,
and let
p
## ,
q
## ∈
## Q
## ,
p
## ≠
q.
## States
p
and
q
are
distinguishable
if there exists
w
## ∈ Σ
## *
such
that:
pw
## |–
## *
p'
and
qw
## |–
## *
q'
, where
p'
## ,
q'
## ∈
## Q
and
## ((
p'
## ∈
## F
and
q'
## ∉
## F
) or (
p'
## ∉
## F
and
q'
## ∈
## F
## ));
otherwise, states
p
and
q
are
indistinguishable
## Minimization: Distinguishable States
## Gist:
## String
w distinguishes
states
p
and
q
if
WSFA reaches a final state from precisely
one of configuration
s
pw
and
qw
## .
## 20/35

b
a
q
## 2
a
q
## 3
a
## ,
b
q
## 1
s
b
## Distinguishable States: Example
## •
s
and
q
## 1
are
distinguishable
, because for
w
## =
a
## :
s
a
## |–
s
## ,
s
## ∉
## F
q
## 1
a
## |–
q
## 2
## ,
q
## 2
## ∈
## F
a
## ,
b
## •
q
## 2
and
q
## 3
are
indistinguishable
, because for each
w
## ∈ Σ
## *
## :
q
## 2
w
## |–
## *
q
## 2
## ,
q
## 2
## ∈
## F
q
## 3
w
## |–
## *
q
## 3
## ,
q
## 3
## ∈
## F
## •
Other pairs of states are trivially
distinguishable
for
w
## =
ε
## .
## 21/35

## Definition:
## Let
## M
be a
## WS
## FA
## . Then,
## M
is
minimum
-state FA
if
## M
contains only
distinguishable states.
## Theorem:
For every WSFA
## M
, there is an
equivalent minimum
-state FA
## M
m
## Minimum
-State FA
## Proof:
Use the next algorithm.
## 22/35

## •
## Input:
## WS
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
## Minimum
-State FA
## M
m
## = (
## Q
m
## ,
## Σ
## ,
## R
m
## ,
s
m
## ,
## F
m
## )
## •
## Method:
## •
## Q
m
## =
## {
## {
p
## :
p
## ∈
## F
## }, {
q
## :
q
## ∈
## Q – F
## }
## }
## ;
## •
repeat
if there exist
## X
## ∈
## Q
m
## ,
d
## ∈
## Σ
## ,
## X
## 1
## ,
## X
## 2
## ⊂
## X
such that
## X
## =
## X
## 1
## ∪
## X
## 2
## ,
## X
## 1
## ∩
## X
## 2
## =
## ∅
and
## {
q
## 1
## :
p
## 1
## ∈
## X
## 1
## ,
p
## 1
d
## →
q
## 1
## ∈
## R
## }
## ⊆
## Q
## 1
## ,
## Q
## 1
## ∈
## Q
m
## ,
## {
q
## 2
## :
p
## 2
## ∈
## X
## 2
## ,
p
## 2
d
## →
q
## 2
## ∈
## R
## }
## ∩
## Q
## 1
## =
## ∅
then
divide
## X
into
## X
## 1
and
## X
## 2
in
## Q
m
until
no division is possible;
## •
## R
m
## =
## {
## Xa
## →
## Y
## :
## X
## ,
## Y
## ∈
## Q
m
## ,
pa
## →
q
## ∈
## R
## ,
p
## ∈
## X
## ,
q
## ∈
## Y
## ,
a
## ∈
## Σ
## }
## ;
## •
s
m
## =
## X
with
s
## ∈
## X
## ;
## F
m
## :
## =
## {
## X
## :
## X
## ∈
## Q
m
## ,
## X
## ∩
## F
## ≠ ∅
## }
## .
Algorithm: WSFA to Min
-State FA
## 23/35

a
s
a
b
a
q
## 1
q
## 3
f
q
## 2
q
## 4
a
a
a
b
b
b
b
b
## Q
m
## =
## {
## {
s
## ,
f
## }, {
q
## 1
## ,
q
## 2
## ,
q
## 3
## ,
q
## 4
## }
## }
## Final
## States
## Other
## States
## 1)
## X
## =
## {
s
## ,
f
## }
## :
s
a
## →
f
f
a
## →
s
d
## =
a
## :
## Division:
## {
q
## 1
## ,
q
## 2
## ,
q
## 3
## ,
q
## 4
## }
## ⇒
## Minimization: Example 1/4
## ⊆
## Q
## 1
## = {
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
## }
## ∩
## Q
## 1
## =
## ∅
From one set
From one set
q
## 1
a
## →
q
## 1
## 2)
## X
## =
## {
q
## 1
## ,
q
## 2
## ,
q
## 3
## ,
q
## 4
## }
## :
q
## 2
a
## →
q
## 2
q
## 3
a
## →
q
## 4
q
## 4
a
## →
q
## 3
d
## =
a
## :
q
## 2
b
## →
f
q
## 3
b
## →
q
## 1
q
## 4
b
## →
q
## 2
q
## 1
b
## →
s
d
## =
b
## :
s
b
## →
q
## 3
f
b
## →
q
## 4
d
## =
b
## :
From one set
## {
q
## 1
## ,
q
## 2
## },
## X
## 1
## {
q
## 3
## ,
q
## 4
## }
## X
## 2
## 24/35

## 1)
## X
## =
## {
s
## ,
f
## }
## :
s
a
## →
f
f
a
## →
s
d
## =
a
## :
## Q
m
## =
## {
## {
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
## 3
## ,
q
## 4
## }
## }
s
b
## →
q
## 3
f
b
## →
q
## 4
d
## =
b
## :
## 2)
## X
## =
## {
q
## 1
## ,
q
## 2
## }
## :
q
## 1
a
## →
q
## 1
q
## 2
a
## →
q
## 2
d
## =
a
## :
q
## 1
b
## →
s
q
## 2
b
## →
f
d
## =
b
## :
## 3)
## X
## =
## {
q
## 3
## ,
q
## 4
## }
## :
q
## 3
a
## →
q
## 3
q
## 4
a
## →
q
## 4
d
## =
a
## :
q
## 3
b
## →
q
## 1
q
## 4
b
## →
q
## 2
d
## =
b
## :
No next divisions !!!
## Minimization: Example 2/4
From one set
From one set
From one set
From one set
From one set
From one set
## 25/35

## Q
m
## =
## {
## {
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
## 3
## ,
q
## 4
## }
## }
s
a
## →
f
## ∈
## R
## :
## {
s
## ,
f
## }
a
## →
## {
s
## ,
f
## }
## ∈
## R
m
f
a
## →
s
## ∈
## R
## :
s
b
## →
q
## 3
## ∈
## R
## :
f
b
## →
q
## 4
## ∈
## R
## :
q
## 1
a
## →
q
## 1
## ∈
## R
## :
## {
q
## 1
## ,
q
## 2
## }
a
## →
## {
q
## 1
## ,
q
## 2
## }
## ∈
## R
m
q
## 2
a
## →
q
## 2
## ∈
## R
## :
## {
s
## ,
f
## }
b
## →
## {
q
## 3
## ,
q
## 4
## }
## ∈
## R
m
q
## 1
b
## →
s
## ∈
## R
## :
## {
q
## 1
## ,
q
## 2
## }
b
## →
## {
s
## ,
f
## }
## ∈
## R
m
q
## 2
b
## →
f
## ∈
## R
## :
q
## 3
a
## →
q
## 3
## ∈
## R
## :
q
## 4
a
## →
q
## 4
## ∈
## R
## :
q
## 3
b
## →
q
## 1
## ∈
## R
## :
## {
q
## 3
## ,
q
## 4
## }
b
## →
## {
q
## 1
## ,
q
## 2
## }
## ∈
## R
m
q
## 4
b
## →
q
## 2
## ∈
## R
## :
## {
q
## 3
## ,
q
## 4
## }
a
## →
## {
q
## 3
## ,
q
## 4
## }
## ∈
## R
m
## Minimization: Example 3/4
## 26/35

s
## ∈
## {
s
## ,
f
## }
s
m
## :
## =
## {
s
## ,
f
## }
## M
m
## = (
## Q
m
## ,
## Σ
## ,
## R
m
## ,
s
m
## ,
## F
m
), where:
## Σ
## = {
a
## ,
b
## },
s
m
## =
## {
s
## ,
f
## }
## Q
m
## =
## {
## {
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
## 3
## ,
q
## 4
## }
## }
## ,
## F
m
## = {
## {
s
## ,
f
## }
## }
## R
m
## =
## {
## {
s
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
f
## }
b
## →
## {
q
## 3
## ,
q
## 4
## }, {
q
## 1
## ,
q
## 2
## }
a
## →
## {
q
## 1
## ,
q
## 2
## },
## {
q
## 1
## ,
q
## 2
## }
b
## →
## {
s
## ,
f
## }, {
q
## 3
## ,
q
## 4
## }
a
## →
## {
q
## 3
## ,
q
## 4
## }, {
q
## 3
## ,
q
## 4
## }
b
## →
## {
q
## 1
## ,
q
## 2
## }
## }
## Minimization: Example 4/4
## 27/35
s
## ∈
## F
## :
## {
s
## ,
f
## }
## ∈
## F
m
f
## ∈
## F
## :
a
s
a
b
a
q
## 1
q
## 3
f
q
## 2
q
## 4
a
a
a
b
b
b
b
b
## {
q
## 1
## ,
q
## 2
## }
## Summary:
## {
q
## 3
## ,
q
## 4
## }
## {
s
## ,
f
## }
a
a
b
b
b
a

Variants of FA: Summary
## 28/35
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
Min-State FA
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
## 010
## 0-1
## 1

## Main Decidable Problems
- Membership problem:•
## Instance:
## FA
## M
## ,
w
## ∈ Σ
## *
## ;
## Question:
w
## ∈
## L
## (
## M
## )
## ?
- Emptiness problem:•
## Instance:
## FA
## M
## ;
## Question:
## L
## (
## M
## ) =
## ∅
## ?
- Finiteness problem:•
## Instance:
## FA
## M
## ;
## Question:
## Is
## L
## (
## M
) finite
## ?
- Equivalence problem:•
## Instance:
## FA
## M
## 1
## ,
## M
## 2
## ;
## Question:
## L
## (
## M
## 1
## ) =
## L
## (
## M
## 2
## )
## ?
## 29/35

## Algorithm: Membership Problem
## •
## Input:
## DFA
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
w
## ∈ Σ
## *
## •
## Output:
## YES
if
w
## ∈
## L
## (
## M
## )
## NO
if
w
## ∉
## L
## (
## M
## )
## •
## Method:
## •
if
sw
## |–
## *
f
## ,
f
## ∈
## F
then
write (’
## YES
## ’)
else
write (’
## NO
## ’)
The membership problem for FA
s is decidable
## Summary:
## 30/35

## Algorithm: Emptiness Problem
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
## );
## •
## Output:
## YES
if
## L
## (
## M
## )
## =
## ∅
## NO
if
## L
## (
## M
## )
## ≠
## ∅
## •
## Method:
## •
if
s
is nonterminating
then
write (’
## YES
## ’)
else
write (’
## NO
## ’)
The emptiness problem for FA
s is decidable
## Summary:
## 31/35

## Algorithm: Finiteness Problem
## •
## Input:
## DFA
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
## •
## Output:
## YES
if
## L
## (
## M
) is finite
## NO
if
## L
## (
## M
) is infinite
## •
## Method:
## • Let
k
= card(
## Q
## )
## •
if
there exist
z
## ∈
## L
## (
## M
## ),
k
## ≤
## |
z
## | <
## 2
k
then
write (’
## NO
## ’)
else
write (’
## YES
## ’)
The finiteness problem for FA
s is decidable
## Summary:
## Note:
This algorithm is based on
## L
## (
## M
) is infinite
## ⇔
there exists
z
## :
z
## ∈
## L
## (
## M
## ),
k
## ≤
## |
z
## | <
## 2
k
## 32/35

## M
## :
a
b
b
f
a
s
## Question
## :
a
b
## ∈
## L
## (
## M
## )
## ?
s
a
b
## Question
## :
## L
## (
## M
## )
## =
## ∅
## ?
## Answer:
## NO
because
s
is terminating
## Answer:
## YES
because
s
a
b
## |–
## *
f
## ,
f
## ∈
## F
## Q
## 0
## = {
f
## }
## 1.
qa
## ’
## →
f
## ;
q
## ∈
## Q
## ;
a
## ’
## ∈ Σ
## :
s
b
## →
f
## ,
f
a
## →
f
## Q
## 1
## = {
f
## }
## ∪
## {
s
## ,
f
## } = {
f
## ,
s
## }
## ...
s
is terminating
## |–
s
b
## |–
f
## ,
f
## ∈
## F
## ,
## ...
## Decidable Problems: Example
## Question
## :
## Is
## L
## (
## M
) finite
## ?
## Answer:
## NO
because there exist
z
## ∈
## L
## (
## M
## ),
k
## ≤
## |
z
## | <
## 2
k
## ∈
## L
## (
## M
## )
## ,
## ...
k
= card(
## Q
## ) = 2
All strings
z
## ∈ Σ
## *
## : 2
## ≤
## |
z
## | < 4
## :
aa
## ,
bb
## ,
a
b
## 33/35

## Algorithm: Equivalence Problem
## •
## Input:
Two minimum state FA
## ,
## M
## 1
and
## M
## 2
## •
## Output:
## YES
if
## L
## (
## M
## 1
## )
## =
## L
## (
## M
## 2
## )
## NO
if
## L
## (
## M
## 1
## )
## ≠
## L
## (
## M
## 2
## )
## •
## Method:
## •
if
## M
## 1
coincides with
## M
## 2
except for the name of states
then
write (’
## YES
## ’)
else
write (’
## NO
## ’)
The equivalence problem for FA is decidable
## Summary:
## 34/35

## Equivalence Problem: Example
## Question:
## L
## (
## M
## 1
## )
## =
## L
## (
## M
## 2
## )
## ?
a
f
s
q
b
a
a
b
## M
## 1
## :
a
q
b
a
a
p
s
bb
## M
## 2
## :
A minimum state FA
b
a
b
b
## {
f
## }
a
## {
s
## ,
q
## }
## M
min
## 1
## :
a
b
b
## {
p
## ,
q
## }
a
## {
s
## }
## M
min
## 2
## :
## Answer:
## YES
because
## M
min
## 1
coincides with
## M
min
## 2
## 35/35