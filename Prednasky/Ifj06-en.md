

Part VI.
Models for Context
-Free
## Languages
## 1/50

Context-Free Grammar (CFG)
## Gist:
## A
grammar
is based on a finite set of
grammatical rules, by which it generates strings of its language.
## Illustration
## :
## Grammar
## G
## :
Start nonterminal
## Terminals:
a
## ,
b
## ,
c
## ,
d
## Nonterminals:
## A
## ,
## B
## ,
## S
## S
## Rules:
## S
## →
## AB
## ,
## A
## →
a
## A
b
## ,
## A
## →
ab
## ,
## B
## →
b
## B
a
## ,
## B
## →
ba
## AB
ab
## B
abb
## B
a
abbbaa
## Rule:
## S
## →
## AB
## Rule:
## A
## →
ab
## Rule:
## B
## →
b
## B
a
## Rule:
## B
## →
ba
## ∈
## L
## (
## G
## )
## 2/50

Context-Free Grammar: Definition
## Definition:
A context-free grammar
(CFG) is a
quadruple
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
), where
## •
## N
is an alphabet of
nonterminals
## •
## T
is an alphabet of
terminals
## ,
## N
## ∩
## T
## =
## ∅
## •
## P
is a finite set of
rules
of the form
## A
## →
x
## ,
where
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
## •
## S
## ∈
## N
is the
start nonterminal
- Strictly mathematically,
## P
is a relation from
## N
to (
## N
## ∪
## T
## )
## *
- Instead of (
## A
## ,
x
## )
## ∈
## P
, we write
## A
## →
x
## ∈
## P
## •
## A
## →
x
means that
## A
can be replaced with
x
## •
## A
## →
ε
is called
ε
## -rule
Mathematical Note on Rules:
## 3/50

## Convention
## •
## A
## , ... ,
## F
## ,
## S
: nonterminals
## •
## S
: the start nonterminal
## •
a
## , ... ,
d
: terminals
## •
## U
## , ... ,
## Z
: members of (
## N
## ∪
## T
## )
## •
u
## , ... ,
z
: members of (
## N
## ∪
## T
## )
## *
## •
π
: sequence of productions
## 4/50
A subset of rules of the form:
## A
## →
x
## 1
## ,
## A
## →
x
## 2
## , ...,
## A
## →
x
n
can be simply written as:
## A
## →
x
## 1
## |
x
## 2
## |
## ...
## |
x
n

## A
## Derivation Step
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
) be a CFG. Let
u
## ,
v
## ∈
## (
## N
## ∪
## T
## )
## *
and
p
## =
## A
## →
x
## ∈
## P.
## Then,
u
## A
v
directly derives
u
x
v
according to
p
in
## G
, written
as
u
## A
v
## ⇒
u
x
v
## [
p
] or, simply,
u
## A
v
## ⇒
u
x
v.
## Note:
## If
u
## A
v
## ⇒
u
x
v
in
## G
, we also say that
## G
makes a
derivation step
from
u
## A
v
to
u
x
v
## .
Gist: A change of a string by a rule.
v
u
## Rule:
## A
## →
x
x
## ...
u
v
## ...
## 5/50

## Definition:
## Let
u
## ∈
## (
## N
## ∪
## T
## )
## *
## .
## G
makes a
zero
## -step
derivation
from
u
to
u
; in symbols,
u
## ⇒
## 0
u
## [
ε
] or, simply,
u
## ⇒
## 0
u
## Definition:
## Let
u
## 0
## ,...,
u
n
## ∈
## (
## N
## ∪
## T
## )
## *
## ,
n
## ≥
1, and
u
i
## -1
## ⇒
u
i
## [
p
i
## ],
p
i
## ∈
## P
, for all
i
## = 1,...,
n
; that is
u
## 0
## ⇒
u
## 1
## [
p
## 1
## ]
## ⇒
u
## 2
## [
p
## 2
## ] ...
## ⇒
u
n
## [
p
n
## ]
## Then,
## G
makes
n derivation steps
from
u
## 0
to
u
n
## ,
u
## 0
## ⇒
n
u
n
## [
p
## 1
## ...
p
n
] or, simply,
u
## 0
## ⇒
n
u
n
Sequence of Derivation Steps 1/2
Gist: Several consecutive derivation steps.
## 6/50

## If
u
## 0
## ⇒
n
u
n
## [
π
] for some
n
## ≥
1, then
u
## 0
properly
derives u
n
in
## G
, written as
u
## 0
## ⇒
## +
u
n
## [
π
## ].
## If
u
## 0
## ⇒
n
u
n
## [
π
] for some
n
## ≥
0, then
u
## 0
derives
u
n
in
## G
, written as
u
## 0
## ⇒
## *
u
n
## [
π
## ].
## Example:
## Consider
a
## A
b
## ⇒
a
aBb
b
## [
## 1
## :
## A
## →
aBb
], and
aa
## B
bb
## ⇒
aa
c
bb
## [
## 2
## :
## B
## →
c
## ].
## Then,
a
## A
b
## ⇒
## 2
aa
c
bb
## [
## 1 2
## ],
a
## A
b
## ⇒
## +
aa
c
bb
## [
## 1 2
## ],
a
## A
b
## ⇒
## *
aa
c
bb
## [
## 1 2
## ]
Sequence of Derivation Steps 2/2
## 7/50

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
) be a CFG. The
language generated
by G
## ,
## L
## (
## G
), is defined as
## L
## (
## G
## ) = {
w
## :
w
## ∈
## T
## *
## ,
## S
## ⇒
## *
w
## }
## Generated Language
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
), let
w
## =
a
## 1
a
## 2
## ...
a
n
## ;
a
i
## ∈
## T
for
i
## = 1..
n
## S
## ⇒
## ...
## ⇒
## ...
## ⇒
a
## 1
a
## 2
## ...
a
n
w
G generates
a terminal string
w
by a
sequence of derivation steps from
## S
to
w
Gist: if
then
w
## ∈
## L
## (
## G
## );
otherwise,
w
## ∉
## L
## (
## G
## )
## Illustration:
## 8/50

## Definition:
## Let
## L
be a language.
## L
is a
context-
free language
## (CFL
) if there exists a context-free
grammar that generates
## L
## .
## Example:
## L
## =
## {
a
n
b
n
## :
n
## ≥
## 0}
is a CFL.
Context-Free Language
## (CFL
## )
Gist: A language  generated
by a CFG.
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
), where
## N
## = {
## S
## },
## T
## = {
a
## ,
b
## },
## P
## = {
## 1
## :
## S
## →
a
## S
b
## ,
## 2
## :
## S
## →
ε
## }
## S
## ⇒
ε
## [
## 2
## ]
## S
## ⇒
a
## S
b
## [
## 1
## ]
## ⇒
ab
## [
## 2
## ]
## S
## ⇒
a
## S
b
## [
## 1
## ]
## ⇒
aa
## S
bb
## [
## 1
## ]
## ⇒
aabb
## [
## 2
## ]
## ...
## L
## (
## G
## )
## = {
a
n
b
n
## :
n
## ≥
## 0}
## 9/50

## Rule Tree
## •
Rule tree graphically represents a rule
## 1)
## A
## →
ε
## :
## 2)
## A
## →
## X
## 1
## X
## 2
## ...
## X
n
## :
## A
ε
## A
## X
## 1
## X
## 2
## ...
## X
n
## •
Derivation tree corresponding to a derivation
## S
## ⇒
## ...
## ⇒
## U
## 1
## U
## 2
## ...
## U
m
## A
## V
## 1
## V
## 2
## ...
## V
n
## S
## U
## 1
## U
## 2
## ...
## U
m
## V
## 1
## V
## 2
## ...
## V
n
## ...
## ...
## ...
## ...
## ...
## ...
Rule tree
corresponding
to
## A
## →
x
x
## A
## 10/50
## ⇒
## U
## 1
## U
## 2
## ...
## U
m
x
## V
## 1
## V
## 2
## ...
## V
n

## Derivation
## Tree
## : Example
## G
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
## 1
## :
## E
## →
## E
## +
## T
## ,
## 2
## :
## E
## →
## T
## ,
## 3
## :
## T
## →
## T
## *
## F
## ,
## 4
## :
## T
## →
## F
## ,
## 5
## :
## F
## →
## (
## E
## )
## ,
## 6
## :
## F
## →
i
## }
## Derivation:
Derivation tree:
## E
## ⇒
## E
## +
## T
## [
## 1
## ]
## E
## E
## T
## +
## ⇒
## T
+  i *
## F
## [
## 2
## ]
## T
## ⇒
## F
+  i *  i
## [
## 4
## ]
## F
## ⇒
i  +  i *  i
## [
## 6
## ]
i
## ⇒
## E
## +
## F
## *
## F
## [
## 4
## ]
## F
## ⇒
## E
+  i *
## F
## [
## 6
## ]
i
## ⇒
## T
+  i *  i
## [
## 6
## ]
i
## ⇒
## E
## +
## T
## *
## F
## [
## 3
## ]
## T
## F
## *
## 11/50

## Leftmost Derivation
During a
leftmost derivation step
, the
leftmost nonterminal is rewritten.
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
, let
u
## ∈
## T
## *
## ,
v
## ∈
## (
## N
## ∪
## T
## )
## *
## . Let
p
## =
## A
## →
x
## ∈
## P
be a
rule
## .
## Then,
uAv
directly derives
uxv
in the
leftmost way
according to
p
in
## G
, written as
uAv
## ⇒
lm
uxv
## [
p
## ]
## Note:
We define
## ⇒
lm
## +
and
## ⇒
lm
## *
by analogy with
## ⇒
## +
and
## ⇒
## *
, respectively.
## Gist:
## 12/50

## Leftmost Derivation
## : Example
## G
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
## 1
## :
## E
## →
## E
## +
## T
## ,
## 2
## :
## E
## →
## T
## ,
## 3
## :
## T
## →
## T
## *
## F
## ,
## 4
## :
## T
## →
## F
## ,
## 5
## :
## F
## →
## (
## E
## )
## ,
## 6
## :
## F
## →
i
## }
Leftmost derivation:
Derivation tree:
## E
## ⇒
lm
## E
## +
## T
## [
## 1
## ]
## E
## E
## T
## +
## F
## ⇒
lm
## F
## +
## T
## [
## 4
## ]
## T
## ⇒
lm
## T
## +
## T
## [
## 2
## ]
i
## ⇒
lm
i  +
## T
## [
## 6
## ]
## T
## F
## *
## ⇒
lm
i  +
## T
## *
## F
## [
## 3
## ]
## F
## ⇒
lm
i  +
## F
## *
## F
## [
## 4
## ]
i
## ⇒
lm
i  +  i *
## F
## [
## 6
## ]
i
## ⇒
lm
i  +  i *  i
## [
## 6
## ]
## 13/50

## Rightmost Derivation
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
, let
u
## ∈
## (
## N
## ∪
## T
## )
## *
## ,
v
## ∈
## T
## *
## .
## Let
p
## =
## A
## →
x
## ∈
## P
be a
rule
## .
## Then,
uAv
directly derives
uxv
in the
rightmost way
according to
p
in
## G
, written as
uAv
## ⇒
rm
uxv
## [
p
## ]
## Note:
We define
## ⇒
rm
## +
and
## ⇒
rm
## *
by analogy with
## ⇒
## +
and
## ⇒
## *
, respectively.
During a
rightmost derivation step
, the
rightmost nonterminal is rewritten.
## Gist:
## 14/50

## Rightmost Derivation
## : Example
## G
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
## 1
## :
## E
## →
## E
## +
## T
## ,
## 2
## :
## E
## →
## T
## ,
## 3
## :
## T
## →
## T
## *
## F
## ,
## 4
## :
## T
## →
## F
## ,
## 5
## :
## F
## →
## (
## E
## )
## ,
## 6
## :
## F
## →
i
## }
Rightmost derivation:
Derivation tree:
## E
## ⇒
rm
## E
## +
## T
## [
## 1
## ]
## E
## E
## T
## +
## ⇒
rm
## E
## +
## T
## *
## F
## [
## 3
## ]
## T
## F
## *
## ⇒
rm
## E
## +
## F
-  i
## [
## 4
## ]
## F
## T
## ⇒
rm
## T
+  i *  i
## [
## 2
## ]
## ⇒
rm
## E
+  i *  i
## [
## 6
## ]
i
## F
## ⇒
rm
## F
+  i *  i
## [
## 4
## ]
## ⇒
rm
## E
## +
## T
-  i
## [
## 6
## ]
i
i
## ⇒
rm
i  +  i *  i
## [
## 6
## ]
## 15/50

## Derivations: Summary
## •   Let
## A
## →
x
## ∈
## P
be a rule.
## 1) Derivation:
## Let
u
## ,
v
## ∈
## (
## N
## ∪
## T
## )
## *
## :
u
## A
v
## ⇒
u
x
v
## Note:
Any nonterminal is rewritten
2) Leftmost derivation:
## Let
u
## ∈
## T
## *
## ,
v
## ∈
## (
## N
## ∪
## T
## )
## *
## :
u
## A
v
## ⇒
lm
u
x
v
## Note:
Leftmost nonterminal is rewritten
3) Rightmost derivation:
## Let
u
## ∈
## (
## N
## ∪
## T
## )
## *
## ,
v
## ∈
## T
## *
## :
u
## A
v
## ⇒
rm
u
x
v
## Note:
Rightmost nonterminal is rewritten
## 16/50

Reduction of the Number of Derivations
## Theorem
## :
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
The next three languages coincide(1) {
w
## :
w
## ∈
## T
## *
## ,
## S
## ⇒
lm
## *
w
## }
## (2) {
w
## :
w
## ∈
## T
## *
## ,
## S
## ⇒
rm
## *
w
## }
## (3) {
w
## :
w
## ∈
## T
## *
## ,
## S
## ⇒
## *
w
## } =
## L
## (
## G
## )
Gist: Without any loss of generality, we can
consider only leftmost or rightmost derivations.
## 17/50

Introduction to Ambiguity
## Theory:
## ☺
## ×
## Practice:
## 
## Theory:
## 
## ×
## Practice:
## ☺
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
## 1
## :
## E
## →
## E
## +
## T
## ,
## 2
## :
## E
## →
## T
## ,
## 3
## :
## T
## →
## T
## *
## F
## ,
## 4
## :
## T
## →
## F
## ,
## 5
## :
## F
## →
## (
## E
## )
## ,
## 6
## :
## F
## →
i
## }
## E
## E
## T
## +
## T
## F
## *
## F
## T
i
## F
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
## E   E
Improper during compilation
## E
## E
## E
## +
## *
i
i
i
## E   E
## Note:
## L
## (
## G
expr
## 1
## ) =
## L
## (
## G
expr
## 2
## )
## 18/50

## Grammatical Ambiguity
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
If there exists
x
## ∈
## L
## (
## G
) with more than one
derivation tree, then
## G
is
ambiguous
## ;
otherwise,
## G
is
unambiguous
## .
## Definition:
## A CFL,
## L
## ,
is
inherently ambiguous
if
## L
is generated by no unambiguous grammar.
## Example:
## •
## G
expr
## 1
is
unambiguous
, because for every
x
## ∈
## L
## (
## G
expr
## 1
## )
there exists
only one derivation tree
## •
## G
expr
## 2
is
ambiguous
, because for
i+i*i
## ∈
## L
## (
## G
expr
## 2
## )
there exist
two derivation trees
## •
## L
expr
## = L
## (
## G
expr
## 1
## )
## = L
## (
## G
expr
## 2
) is
not inherently ambiguous
because
## G
expr
## 1
is unambiguous
## 19/50

Pushdown Automata (PDA)
## A
m
## A
## 1
## A
## 2
## ...
a
i
a
n
## ...
a
## 1
a
## 2
## ...
Read-write head
Read head
## Finite
## State
## Control
## Pushdown:
Input tape:
top
Gist: An FA extended by a pushdown store.
move of head
## 20/50

## Pushdown Automata: Definition
## Definition:
A pushdown automaton
(PDA) is
a 7
## -tuple
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## S
## ,
## F
), where
## •
## Q
is a
finite set of states
## •
## Σ
is an
input alphabet
## •
## Γ
is a
pushdown alphabet
## •
## R
is a
finite set of rules
of the form:
## Apa
## →
wq
where
## A
## ∈ Γ
## ,
p
## ,
q
## ∈
## Q
## ,
a
## ∈ Σ ∪
## {
ε
## },
w
## ∈ Γ
## *
## •
s
## ∈
## Q
is the
start state
## •
## S
## ∈ Γ
is the
start pushdown symbol
## •
## F
## ⊆
## Q
is a set of
final states
## 21/50

Notes on PDA Rules
## •
Interpretation of
## A
p
a
## →
w
q
: if the current state
is
p
, current input symbol is
a
, and the topmost
symbol on the pushdown is
## A
, then
## M
can read
a
, replace
## A
with
w
and change state
p
to
q
## .
## •
## Note
: if
a
## =
ε
, no symbol is read
- Strictly mathematically,
## R
is a finite relation
from
## Γ ×
## Q
## ×
## (
## Σ ∪
## {
ε
}) to
## Γ
## *
## ×
## Q
- Instead of (
## A
p
a
## ,
w
q
## )
## ∈
## R
, however, we write
## A
p
a
## →
w
q
## ∈
## R
Mathematical note on rules:
## 22/50

represents
q
## ∈
## Q
represents the initial state
s
## ∈
## Q
represents a final state
f
## ∈
## F
denotes
## Apa
## →
wq
## ∈
## R
q
s
f
p
q
## A
## /
w
## ,
a
## Graphical Representation
## 23/50

## Graphical Representation
## : Example
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## S
## ,
## F
## )
## •
## Σ
## = {
a
## ,
b
## };
where:
## •
## Γ
## = {
a
## ,
## S
## };
a
p
a
## →
aa
p
## ,
a
## /
aa
## ,
a
pq
s
## •
## Q
## = {
s
## ,
p
## ,
q
## ,
f
## };
f
## •
## R
## = {
## S
s
a
## →
## Sa
p
## ,
## S
## /
## Sa
## ,
a
a
p
b
## →
q
## ,
a
## /
ε
## ,
b
## S
q
## →
f
## }
## S
## /
ε
## ,
ε
## •
## F =
## {
f
## }
a
q
b
## →
q
## ,
a
## /
ε
## ,
b
## 24/50

PDA Configuration
## Definition:
## Let
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## S
## ,
## F
) be a PD
## A.
A configuration
of
## M
is a string
χ ∈ Γ
## *
## Q
## Σ
## *
## Gist: Instan
taneous description of PD
## A
## Configuration
## A
m
## A
## 1
## A
## 2
## ...
a
i
a
n
## ...
a
## 1
a
## 2
## ...
Read-write head
Read head
## Finite State
## Control
## Pushdown:
Input tape:
p
= current state
p
## 25/50

## Move
## Definition:
## Let
x
## Apa
y
and
x
wq
y
be two configurations
of a PDA,
## M
, where
x
## ,
w
## ∈ Γ
## *
## ,
## A
## ∈ Γ
## ,
p
## ,
q
## ∈
## Q
## ,
a
## ∈ Σ ∪
## {
ε
}, and
y
## ∈ Σ
## *
## .
## Let
r
## =
## Apa
## →
wq
## ∈
## R
be a rule
## .
## Then,
## M
makes
a
move
from
x
## Apa
y
to
x
wq
y
according to
r
, written as
x
## Apa
y |– x
wq
y
## [
r
] or, simply,
x
## Apa
y |– x
wq
y
## .
## Note:
if
a
## =
ε
, no input symbol is read
## Rule:
## Apa
## →
wq
Gist: A computational step made by a
## PD
## A
## Configuration:
a
p
## A
y
x
New configuration:
q
## ...
w
## ...
y
x
## 26/50

## Definition:
## Let
χ
be a configuration.
## M
makes
zero moves
from
χ
to
χ
; in symbols,
χ
## |–
## 0
χ
## [
ε
] or, simply,
χ
## |–
## 0
χ
## Definition:
## Let
χ
## 0
## ,
χ
## 1
## , ...,
χ
n
be a sequence of
configurations,
n
## ≥
1, and
χ
i
## -1
## |–
χ
i
## [
r
i
## ],
r
i
## ∈
## R
## ,
for all
i
## = 1, ...,
n
; that is,
χ
## 0
## |–
χ
## 1
## [
r
## 1
## ]
## |–
χ
## 2
## [
r
## 2
## ] ...
## |–
χ
n
## [
r
n
## ]
## Then
## M
makes
n moves
from
χ
## 0
to
χ
n
## ,
χ
## 0
## |–
n
χ
n
## [
r
## 1
## ...
r
n
] or, simply,
χ
## 0
## |–
n
χ
n
Sequence of Moves 1/2
Gist: Several consecutive computational steps
## 27/50

## If
χ
## 0
## |–
n
χ
n
## [
ρ
] for some
n
## ≥
1, then
χ
## 0
## |–
## +
χ
n
## [
ρ
] or, simply,
χ
## 0
## |–
## +
χ
n
## If
χ
## 0
## |–
n
χ
n
## [
ρ
] for some
n
## ≥
0, then
χ
## 0
## |–
## *
χ
n
## [
ρ
] or, simply,
χ
## 0
## |–
## *
χ
n
## Example:
## Consider
## A
## Apa
bc
## |–
## A
## Bq
bc
## [
## 1
## :
## Apa
## →
## Bq
], and
## A
## Bqb
c
## |–
## A
BCr
c
## [
## 2
## :
## Bqb
## →
BCr
## ].
## Then,
## A
## Apa
bc
## |–
## 2
## A
BCr
c
## [
## 1 2
## ],
## A
## Apa
bc
## |–
## +
## A
BCr
c
## [
## 1 2
## ],
## A
## Apa
bc
## |–
## *
## A
BCr
c
## [
## 1 2
## ]
Sequence of Moves 2/2
## 28/50

## Definition:
## Let
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## S
## ,
## F
) be a PDA
## .
## 1)
## The
language that M accepts
by final state
## ,
denoted by
## L
## (
## M
## )
f
, is defined as
## L
## (
## M
## )
f
## = {
w
## :
w
## ∈ Σ
## *
## ,
## Ssw
## |–
## *
zf
## ,
z
## ∈
## Γ
## *
## ,
f
## ∈
## F
## }
## 2)
## The
language that M accepts
by empty pushdown
## ,
denoted by
## L
## (
## M
## )
ε
, is defined as
## L
## (
## M
## )
ε
## = {
w
## :
w
## ∈ Σ
## *
## ,
## Ssw
## |–
## *
zf
## ,
z
## =
ε
## ,
f
## ∈
## Q
## }
## 3)
## The
language that M accepts
by final state and
empty pushdown
, denoted by
## L
## (
## M
## )
f
ε
, is defined as
## L
## (
## M
## )
f
ε
## = {
w
## :
w
## ∈ Σ
## *
## ,
## Ssw
## |–
## *
zf
## ,
z
## =
ε
## ,
f
## ∈
## F
## }
## Accepted Language: Three Types
## 29/50

PDA: Example
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## S
## ,
## F
## )
## •
## Σ
## = {
a
## ,
b
## };
where:
## •
## Γ
## = {
a
## ,
## S
## };
a
p
a
## →
aa
p
## ,
## •
## Q
## = {
s
## ,
p
## ,
q
## ,
f
## };
## •
## R
## = {
## S
s
a
## →
## Sa
p
## ,
a
p
b
## →
q
## ,
## S
q
## →
f
## }
## •
## F =
## {
f
## }
a
q
b
## →
q
## ,
## Question
## :
aabb
## ∈
## L
## (
## M
## )
f
ε
## ?
## S
s
aabb
## |–
## Sa
p
abb
## |–
## Saa
p
bb
## |–
## Sa
q
b
## |–
## S
q
## |–
f
## Rule:
## S
s
a
## →
## Sa
p
## S
s
b
a
a
b
p
a
## S
a
b
b
q
## S
a
b
p
## S
a
a
b
b
## Rule:
a
p
a
## →
aa
p
## Rule:
a
p
b
## →
q
## Rule:
a
q
b
## →
q
## Rule:
## S
q
## →
f
## S
q
f
## Answer:
## YES
## Empty
pushdown
Final state
## Note:
## L
## (
## M
## )
f
## =
## L
## (
## M
## )
ε
## =
## L
## (
## M
## )
f
ε
## = {
a
n
b
n
## :
n
## ≥
## 1}
## 30/50

Three Types of Acceptance: Equivalence
## Theorem:•
## L = L
## (
## M
f
## )
f
for a PDA
## M
f
## ⇔
## L = L
## (
## M
f
ε
## )
f
ε
for a PDA
## M
f
ε
## •
## L = L
## (
## M
ε
## )
ε
for a PDA
## M
ε
## ⇔
## L = L
## (
## M
f
ε
## )
f
ε
for a PDA
## M
f
ε
## •
## L = L
## (
## M
f
## )
f
for a PDA
## M
f
## ⇔
## L = L
## (
## M
ε
## )
ε
for a PDA
## M
ε
## Note:
There exist these conversions:
## PDA
## M
f
ε
that accept
## L
by final state and
empty pushdown
## PDA
## M
f
that accept
## L
by final state
## PDA
## M
ε
that accept
## L
by empty pushdown
## 31/50

Deterministic PDA (DPDA)
## Gist:
Deterministic PDA makes no more tha
n
one move from any
configuration.
## Definition:
## Let
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## S
## ,
## F
) be a
## PDA
## .
## M
is a
deterministic PDA
if for each rule
## Apa
## →
wq
## ∈
## R
, it holds that
## R
## – {
## Apa
## →
wq
## }
contains no rule with the left-hand side equal to
## Apa
or
## Ap
## .
## Illustration:
## Configuration:
a
p
## A
y
x
## Ap
## →
w
## 1
q
## 1
## Apa
## →
w
## 2
q
## 2
No more that one rule of the forms
## 32/50

PDAs are Stronger than
## DPDA
s
## Theorem:
There exists no DPDA
## M
f
ε
that accepts
## L =
## {
xy
## :
x
## ,
y
## ∈ Σ
## *
## ,
y = reversal
## (
x
## )}
Illustration:Proof:
See page 431 in [Meduna: Automata and Languages]
## 33/50
The family of
languages accepted
by
## PDA
s
The family of
deterministic
CFLs
## 
the languages
accepted by
## DPDA
s
## ⊂
## L =
## {
xy
## :
x
## ,
y
## ∈ Σ
## *
## ,
y = reversal
## (
x
## )}

Extended PDA (EPDA)
## Gist:
The pushdown top of an EPDA represents a string rather than a single symbol.
## Definition:
An Extended Pushdown automaton
(EPDA) is a 7
## -tuple
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## S
## ,
## F
## ),
where
## Q
## ,
## Σ
## ,
## Γ
## ,
s, S, F
are defined
as in
an
## PDA
and
## R
is a
finite set of rules
of the form:
v
pa
## →
wq
## ,
where
v
## ,
w
## ∈
## Γ
## *
## ,
p
## ,
q
## ∈
## Q
## ,
a
## ∈ Σ ∪
## {
ε
## }
Illustration:Pushdown of PDA:
Pushdown of EPDA:
## A
x
x
v
PDA has a
single symbols
as the
pushdown top
EPDA has
a string
as the
pushdown top
## 34/50

Move in EPDA
## Definition:
## Let
x
v
pay
and
xwqy
be two configurations
of an EPDA,
## M
, where
x
## ,
v
## ,
w
## ∈ Γ
## *
## ,
p
## ,
q
## ∈
## Q
## ,
a
## ∈ Σ
## ∪
## {
ε
}, and
y
## ∈ Σ
## *
## . Let
r
## =
v
pa
## →
wq
## ∈
## R
be a rule
## .
## Then,
## M
makes a
move
from
x
v
pay
to
xwqy
according
to
r
, written as
x
v
pay |– xwqy
## [
r
] or
x
v
pay |– xwqy
## .
## Rule:
vpa
## →
wq
## Configuration:
New configuration:
q
## ...
w
## ...
y
x
## Note: |–
n
## ,
## |–
## +
## ,
## |–
## *,
## L
## (
## M
## )
f
## ,
## L
## (
## M
## )
ε
, and
## L
## (
## M
## )
f
ε
are defined
analogically to the corresponding definitions for P
## DA.
a
p
y
x
v
## 35/50

EPDA: Example
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## S
## ,
## F
## )
## •
## Σ
## = {
a
## ,
b
## };
where:
## •
## Γ
## = {
a
## ,
b
## ,
## S
## ,
## C
## };
s
## •
## Q
## = {
s
## ,
f
## };
f
## •
## F =
## {
f
## }
s
## →
## C
s
## ,
ε
## /
## C
## ,
ε
## SC
## /
ε
## ,
ε
## SC
s
## →
f
## }
aC
s
a
## →
## C
s
## ,
aC
## /
## C
## ,
a
## •
## R
## = {
s
a
## →
a
s
## ,
ε
## /
a
## ,
a
s
b
## →
b
s
## ,
ε
## /
b
## ,
b
bC
s
b
## →
## C
s
## ,
bC
## /
## C
## ,
b
## S
s
abba
## |–
## Sa
s
bba
## |–
## Sab
s
ba
## |–
SabC
s
ba
## |–
SaC
s
a
## |–
f
## |–
## SC
s
## Question
## :
abba
## ∈
## L
f
ε
## (
## M
## )
## ?
## Answer:
## YES
## Note:
## L
## (
## M
## )
f
## =
## L
## (
## M
## )
ε
## =
## L
## (
## M
## )
f
ε
## = {
xy
## :
x
## ,
y
## ∈ Σ
## *
## ,
y
= reversal(
x
## )}
## 36/50

Three Types of Acceptance: Equivalence
## Theorem:•
## L = L
## (
## M
f
## )
f
for an EPDA
## M
f
## ⇔
## L = L
## (
## M
f
ε
## )
f
ε
for an EPDA
## M
f
ε
## •
## L = L
## (
## M
ε
## )
ε
for an EPDA
## M
ε
## ⇔
## L = L
## (
## M
f
ε
## )
f
ε
for an EPDA
## M
f
ε
## •
## L = L
## (
## M
f
## )
f
for an EPDA
## M
f
## ⇔
## L = L
## (
## M
ε
## )
ε
for an EPDA
## M
ε
## Note:
There exist these conversion:
## EPDA
## M
f
ε
that accept
## L
by final state and
empty pushdown
## EPDA
## M
f
that accept
## L
by final state
## EPDA
## M
ε
that accept
## L
by empty pushdown
## 37/50

EPDAs and PDAs are Equivalent
## Theorem:
For every EPDA
## M
, there is a PDA
## M
## ’,
and
## L
## (
## M
## )
f
## =
## L
## (
## M
## ’)
f
## .
## Illustration:
## =
The family of
languages accepted
by
## EPDA
s
The family of
languages accepted
by
## PDA
s
## Proof:
See page 419 in [Meduna: Automata and Languages]
## 38/50

## EPDA
s and PDA
s as Parsing Models for CFG
s
## Gist:
An EPDA or a PDA can simulate the construction of a derivation tree for a CFG
## •
Two basic approaches:
## 1) Top
-Down Parsing
## 2) Bottom
-Up Parsing
## From
## S
towards
the input string
From the input string towards
## S
## S
Input string
## S
Input string
## 39/50

EPDAs as Models of Bottom
-Up Parsers 1/2
## Gist: An
## EPDA
## M
underlies a bottom
## -up
parser
## 1)
## M
contains
shift
rules that copy the input symbols
onto the pushdown:
a
s
y
x
for every
a
## ∈ Σ
## :
add
s
a
## →
a
s
to
## R
## ;
for every
## A
## →
x
## ∈
## P
in
## G
## :
add
x
s
## →
## A
s
to
## R
## ;
a
s
y
x
## 2)
## M
contains
reduction
rules that simulate the
application of a grammatical rule in reverse:
s
y
x
## A
s
y
## 3)
## M
also contains the rule
## #
## S
s
## →
f
that takes
## M
to a
final state
f
## 40/50

Derivation tree:
## S
EPDAs as Models of Bottom
-Up Parsers 2/2
## #
## S
s
## →
f
## ∈
## R
x
y
z
start pushdown symbol
## B
## C
## #
s
x
y
z
## #
s
x
y
z
## #
s
x
y
z
## B
## #
s
x
z
f
## Rule:
## B
## →
y
## Rule:
## C
## →
z
## Rule:
## S
## →
x
## BC
## C
## B
## #
s
x
## B
## #
s
x
z
## S
## #
s
## Bottom
-up construction of a derivation tree:
## 41/50

## •
## Input:
## CFG
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
## EPDA
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## #
## ,
## F
## );
## L
## (
## G
## ) =
## L
## (
## M
## )
f
## •
## Method:
## •
## Q
## := {
s
## ,
f
## };
## •
## Σ
## :=
## T
## ;
## •
## Γ
## :=
## N
## ∪
## T
## ∪
## {
## #
## };
- Construction of
## R
## :
- for every
a
## ∈ Σ
, add
s
a
## →
a
s
to
## R
## ;
- for every
## A
## →
x
## ∈
## P
, add
x
s
## →
## A
s
to
## R
## ;
- add
## #
## S
s
## →
f
to
## R
## ;
## •
## F
## := {
f
## };
Algorithm: From CFG to
## EPDA
## 42/50

From CFG to EPDA
## : Example 1
## /2
## •
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
), where:
## N
## = {
## S
## },
## T
## = {
## (
## ,
## )
## },
## P
## = {
## S
## →
## (
## S
## )
## ,
## S
## →
## ( )
## }
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## #
## ,
## F
) where:
## Objective:
An EPDA
## M
such that
## L
## (
## G
## ) =
## L
## (
## M
## )
f
## S
## →
## (
## S
## )
## ∈
## P
## Q =
## {
s
## ,
f
## };
## Σ
## =
## T
## = {
## (
## ,
## )
## };
## Γ
## =
## N
## ∪
## T
## ∪
## {
## #
## } = {
## S
## ,
## (
## ,
## )
## ,
## #
## }
## R
## = {
## “(”
## ∈
## T
s
## (
## →
## (
s
## ,
s
## )
## →
## )
s
## ,
## (
## S
## )
s
## →
## S
s
## ,
## ( )
s
## →
## S
s
## ,
## #
## S
s
## →
f
## }
## S
## →
## ( )
## ∈
## P
## “)”
## ∈
## T
shift rules
reduction rules
## F
## = {
f
## }
## 43/50

From CFG to
EPDA: Example 2/2
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## #
## ,
## F
), where:
## Q =
## {
s
## ,
f
## },
## Σ
## =
## T
## = {
## (
## ,
## )
## },
## Γ
## = {
## (
## ,
## )
## ,
## S
## ,
## #
## },
## F =
## {
f
## }
## R
## = {
s
## (
## →
## (
s
## ,
s
## )
## →
## )
s
## ,
## (
## S
## )
s
## →
## S
s
## ,
## ( )
s
## →
## S
s
## ,
## #
## S
s
## →
f
## }
## Question
## :
## (( ))
## ∈
## L
## (
## M
## )
f
## ?
## Rule:
s
## (
## →
## (
s
## #
s
## )
## (
## (
## )
f
## Answer:
## YES
## (  (
## )
## )
## S
## S
## #
s
## )
## (
## (
## )
## #
s
## )
## (
## (
## )
## Rule:
s
## (
## →
## (
s
## Rule:
s
## )
## →
## )
s
## #
s
## )
## (
## (
## )
## Rule:
s
## )
## →
## )
s
## #
s
## )
## (
## S
## Rule:
## (
## S
## )
## →
## S
## Rule:
## #
## S
s
## →
f
## Rule:
## ( )
s
## →
## S
## #
s
## )
## (
## S
## #
s
## S
## (  (
## )
## )
## S
## (  (  )
## S
## (  (  )(  ((
Final state
## 44/50

PDAs as Models of Top
-Down Parsers 1/2
## 1)
## M
contains
popping
rules that pops the top symbol from the
pushdown and reads the input symbol if both coincide:
for every
a
## ∈ Σ
## :
add
a
s
a
## →
s
to
## R
## ;
x
y
s
## 2)
## M
contains
expansion
rules that simulate the
application of a grammatical rule:
## A
s
y
s
y
a
n
...  a
## 1
a
s
y
x
a
for every
## A
## →
a
## 1
## ...a
n
## ∈
## P
in
## G
## ,
add
## A
s
## →
a
n
## ...a
## 1
s
to
## R
## ;
= reversal(
a
## 1
## ...a
n
## )
## Gist: An
## PDA
## M
underlies a top
## -down
parser
## 45/50

Derivation tree:
PDAs as Models of Top
-Down Parsers 2/2
## Top
-down construction of a derivation tree:
start pushdown symbol
## S
a
## 1
## ..a
k
## B
## C
b
## 1
## ..b
l
c
## 1
## ..c
m
## S
s
a
## 1
## ...
a
k
b
## 1
## ...
b
l
c
## 1
## ...
c
m
## C
## B
s
a
k
## ...
a
## 1
a
## 1
## ...
a
k
b
## 1
## ...
b
l
c
## 1
## ...
c
m
## C
## B
s
b
## 1
## ...
b
l
c
## 1
## ...
c
m
## C
s
b
## 1
## ...
b
l
c
## 1
## ...
c
m
b
l
## ...
b
## 1
## C
s
c
## 1
## ...
c
m
s
c
## 1
## ...
c
m
c
m
## ...
c
## 1
s
## OK
## OK
## OK
## S
## →
a
## 1
## ..a
k
## BC
## B
## →
b
## 1
## ..b
l
## C
## →
c
## 1
## ..c
m
## Empty
pushdown
## 46/50

## •
## Input:
## CFG
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
## PDA
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## S
## ,
## F
## );
## L
## (
## G
## ) =
## L
## (
## M
## )
ε
## •
## Method:
## •
## Q
## := {
s
## };
## •
## Σ
## :=
## T
## ;
## •
## Γ
## :=
## N
## ∪
## T
## ;
- Construction of
## R
## :
- for every
a
## ∈ Σ
, add
a
s
a
## →
s
to
## R
## ;
- for every
## A
## →
x
## ∈
## P
, add
## A
s
## →
y
s
to
## R
## ,
where
y
= reversal(
x
## );
## •
## F
## :=
## ∅
## ;
Algorithm: From CFG to
## PDA
## 47/50

From CFG to
PDA: Example 1
## /2
## •
## G
## = (
## N
## ,
## T
## ,
## P
## ,
## S
), where:
## N
## = {
## S
## },
## T
## = {
## (
## ,
## )
## },
## P
## = {
## S
## →
## (
## S
## )
## ,
## S
## →
## ( )
## }
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## S
## ,
## F
) where:
## Objective:
An PDA
## M
such that
## L
## (
## G
## ) =
## L
## (
## M
## )
ε
## S
## →
## (
## S
## )
## ∈
## P
## Q =
## {
s
## };
## Σ
## =
## T
## = {
## (
## ,
## )
## };
## Γ
## =
## N
## ∪
## T
## = {
## S
## ,
## (
## ,
## )
## }
## R
## = {
## “(”
## ∈
## T
## (
s
## (
## →
s
## ,
## )
s
## )
## →
s
## ,
## S
s
## →
## )
## S
## (
s
## ,
## S
s
## →
## )(
s
## }
## S
## →
## ( )
## ∈
## P
## “)”
## ∈
## T
## F
## =
## ∅
rev
rev
## 48/50
popping rules
expansion rules

From CFG to
PDA: Example 2/2
## M
## = (
## Q
## ,
## Σ
## ,
## Γ
## ,
## R
## ,
s
## ,
## S
## ,
## F
), where:
## Q =
## {
s
## },
## Σ
## =
## T
## = {
## (
## ,
## )
## },
## Γ
## = {
## (
## ,
## )
## ,
## S
## },
## F =
## ∅
## P
## = {
## (
s
## (
## →
s
## ,
## )
s
## )
## →
s
## ,
## S
s
## →
## )
## S
## (
s
## ,
## S
s
## →
## )(
s
## }
## Question
## :
## (( ))
## ∈
## L
## (
## M
## )
ε
## ?
## Rule:
## S
s
## →
## )
## S
## (
s
## Answer:
## YES
## (  (
## )
## )
## S
## S
## Rule:
## (
s
## (
## →
s
## Rule:
## S
s
## →
## )(
s
## Rule:
## )
s
## )
## →
s
## Rule:
## )
s
## )
## →
s
## Rule:
## (
s
## (
## →
s
## Empty
pushdown
## S
s
## )
## (
## (
## )
## )
## (
## S
s
## )
## (
## )
## )
s
## )
## (
## )
## )
## )
## (
s
## )
## )
## )
## )
s
## )
## )
s
## (
## )
## S
## SS
## (
## )
## S
## S
## (  (
## )
## )
## S
## S
## (  (
## )
## )
## S
## S
## (  (
## )
## )
## S
## S
## S
s
## )
## (
## (
## )
## 49/50

Models for Context-free
## Languages
## Proof
: See the previous algorithm.
## Theorem:
For every CFG
## G
, there is an PDA
## M
such that
## L
## (
## G
## ) =
## L
## (
## M
## )
ε
## .
## Proof:
See page 486 in [Meduna: Automata and Languages]
## Theorem:
For every PDA
## M
, there is a CFG
## G
such that
## L
## (
## M
## )
ε
## =
## L
## (
## G
## ).
## Conclusion:
The fundamental models for
context-free languages are
## 1)
Context-free grammars
## 2)
Pushdown automata
## 50/50