

Part III.Part III.
## 1/29
Part III.Part III.
Models for Regular Models for Regular
LanguagesLanguagesLanguagesLanguages

Regular Expressions (RE): Definition
## 2/29
## Gist:
Expressions with operators ., +, and * thatdenote concatenation, union, and iteration, respectively.iteration, respectively.
## Definition:
## Let
## Σ
be an alphabet. The
regular
expressions
over
## Σ
and the
languages they denote
are defined as follows:•
## ∅
is a RE denoting the empty set
## •
ε
is a RE denoting {
ε
## }
## •
a
, where
a
## ∈
## Σ
, is a RE denoting {
a
## }
## •
a
, where
a
## ∈
## Σ
, is a RE denoting {
a
## }
## • Let
r
and
s
be regular expressions denoting the
languages
## L
r
and
## L
s
, respectively; then
## • (
r
## .
s
) is a RE denoting
## L
## =
## L
r
## L
s
## •  (
r
## +
s
) is a RE denoting
## L
## =
## L
r
## ∪
## L
s
## •  (
r
## *
) is a RE denoting
## L
## =
## L
r
## *

## Regular Expressions: Example
## Question:
## Is (
ε
## + (
a.
## (
b
## *
))) the regular expression
over
## Σ
## = {
a
## ,
b
## }
## ?
## 3/29
a
b
ε
εεε
Is a RE over
## Σ
## ΣΣΣ
## .
## (
b
## *
## )
## (
a
## .
## (
b
## *
## )
## )
## (
ε
εεε
## +
## (
a
## .
## (
b
## *
## )
## )
## )
## Answer:(
ε
## + (
a.
## (
b
## *
))) is
the RE over
## Σ
## .

## Precedence
s
## :
## *
## > . > +
1) Reduction of the number of parentheses by
## Simplification
## 4/29
## Precedence
s
## :
## > . > +
## Example:(
## (
a
## .
## (
a
## *
## )
## )
## +
## (
## (
b
## *
## )
## .
b
## )
## )
can be written as
a
## .
a
## *
## +
b
## *
## .
b
## ,
## 3) Expression
rr
## *
or
r
## *
r
is simplified to
r
## +
## 2) Expression
r
## .
s
is simplified to
rs
and
a
## .
a
## *
## +
b
## *
## .
b
can be written as
a
## +
## +
b
## +

## Definition:
## Let
## L
be a language.
## L
is a
regular
language
(RL) if there exists a regular expression
## Regular Language
## (RL)
Gist: Every RE denotes a regular language
## 5/29
language
(RL) if there exists a regular expression
r
that denotes
## L
## .
## Examples:
r
## 1
## =
ab + ba
denotes
## L
## 1
## = {
ab
## ,
ba
## }
## +
## *
n
m
## ≥
## ≥
## Denotation
## :
## L
## (
r
) means the language denoted by
r
## .
r
## 2
## =
a
## +
b
## *
denotes
## L
## 2
## = {
a
n
b
m
## :
n
## ≥
## 1,
m
## ≥
## 0}
r
## 3
## =
ab
## (
a + b
## )
## *
denotes
## L
## 3
## = {
x
## :
ab
is prefix of
x
## }
## L
## 1
## ,
## L
## 2
## ,
## L
## 3
## ,
## L
## 4
are regular languages over
## Σ
## ΣΣΣ
r
## 4
## = (
a + b
## )
## *
ab
## (
a + b
## )
## *
denotes
## L
## 4
## = {
x
## :
ab
is substring of
x
## }

Finite Automata (FA)
Gist:  The simplest model of computation
based on a finite set of states and
computational rules.
## 6/29
Final states
s
q
## 1
q
## 2
q
i
q
n
Current state
computational rules.
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
Read head
Input tape:
## Finite State Control
Start state
move of head

## Definition:
A finite automaton
(FA) is a 5
## -tuple:
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
), where
## •
## Q
is a
finite set of states
## Finite Automata
## : Definition
## 7/29
## •
## Q
is a
finite set of states
## •
## Σ
is an
input alphabet
## •
## R
is a
finite set of rules
of the form:
pa
## →
q
## ,
where
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
## •
s
## ∈
## Q
is the
start state
## •
## F
## ⊆
## Q
is a
set of
final states
## •
## F
## ⊆
## Q
is a
set of
final states
- Strictly mathematically,
## R
is a relation from
## Q
## ×
## (
## Σ ∪
## {
ε
}) to
## Q
- Instead of (
p
a
## ,
q
), however, we write the rule as
p
a
## →
## →→→
q
## •
p
a
## →
## →→→
q
means that with
a
## ,
## M
can move from
p
to
q
- if
a
## =
ε
, no symbol is read
Mathematical note on rules:

denotes a state
q
## ∈
## Q
denotes the start state
s
## ∈
## Q
q
s
## Graphical  Representation
## 8/29
denotes the start state
s
## ∈
## Q
denotes a final state
f
## ∈
## F
denotes
pa
## →
q
## ∈
## R
s
f
p
q
a

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
## ),
b
a
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
a
where:
## Graphical Representation
## : Example
## 9/29
p
b
## →
p
## ,
p
b
## →
f
## ,
b
ε
εεε
s
## →
p
## ,
s
## →
q
## ,
ε
εεε
c
pq
s
f
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
## Σ
## = {
a
## ,
b
## ,
c
## };
## •
## R
## = {
s
a
## →
s
## ,
s
## →
q
## ,
q
c
## →
f
## ,
f
a
## →
f
## };
q
c
## →
q
## ,
c
q
## •
## F =
## {
f
## }

## •
## Columns:
Member of
## Σ ∪
## {
ε
## }
## •
## Rows
## :
States of
## Q
## Tabular Representation
## 10/29
## •
## Rows
## :
States of
## Q
## •
First row:
The start state
## •
## Underscored:
Final states
## ...
a
## ...
ε
εεε
s
## ......
p
f
t
## (
p
## ,
a
## )
t
## (
p
## ,
a
## )
t
## (
p
## ,
a
## ) = {
q
## :
pa
## →
q
## ∈
## R
## }

ε
εεε
a
b
c
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
## ),
where:
## Tabular Representation
## : Example
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
## 11/29
ε
εεε
a
b
c
## •
## Σ
## = {
a
## ,
b
## ,
c
## };
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
## ∅
## ∅∅∅
s
f
pq
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
s
a
## →
s
## ,
## {
s
## }
p
b
## →
p
## ,
## {
p
## }
## {
f
## }
s
## →
p
## ,
## {
p
## }
p
b
## →
f
## ,
## {
p
## ,
f
## }
## {
q
## }
## {
q
## ,
f
## }
s
## →
q
## ,
## {
p
## ,
q
## }
f
a
## →
f
## };
q
c
## →
q
## ,
q
c
## →
f
## ,
s
## →
q
## ,
## •
## F =
## {
f
## }

## Configuration
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
) be a FA.
A configuration
of
## M
is a string
χ
## ∈
## Q
## Σ
## *
Gist: Instance description of FA
## 12/29
s
q
## 1
q
## 2
q
i
q
n
## Finite State Control
Current state
A configuration
of
## M
is a string
χ
## ∈
## Q
## Σ
## *
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
Read head
Input tape:
## Finite State Control
## Configuration
q
i

## Move
## Definition:
## Let
p
a
x
and
q
x
be two
configurations
of
## M
, where
p
## ,
q
## ∈
## Q
## ,
a
## ∈
## Σ
## ∪
## {
ε
}, and
x
## ∈
## Σ
## *
## .
Gist: Computational step of FA
## 13/29
of
## M
, where
p
## ,
q
## ∈
## Q
## ,
a
## ∈
## Σ
## ∪
## {
ε
}, and
x
## ∈
## Σ
## *
## .
## Let
r
## =
p
a
## →
q
## ∈
## R
be a rule
## .
## Then
## M
makes a
move
from
p
a
x
to
q
x
according to
r
, written as
p
a
x
## |–
q
x
## [
r
] or, simply,
p
a
x
## |–
q
x
## Note:
if
a
## =
ε
, no input symbol is read
## Rule:
p
a
## →
q
## Configuration:
a
p
x
New configuration:
q
## ...
x

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
## ;
in symbols,
Sequence of Moves 1/2
Gist: Several consecutive computational steps
## 14/29
zero moves
from
χ
to
χ
## ;
in symbols,
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
## :
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
## ].
Sequence of Moves 2/2
## 15/29
## 0
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
## ].
## Example:
## Consider
p
a
bc
## |
## –
q
bc
## [
## 1
## :
p
a
## →
q
], and
q
b
c
## |
## –
r
c
## [
## 2
## :
q
b
## →
r
## ].
p
a
bc
## |
## –
q
bc
## [
## 1
## :
p
a
## →
q
], and
q
b
c
## |
## –
r
c
## [
## 2
## :
q
b
## →
r
## ].
## Then,
p
a
b
c
## |–
## 2
r
c
## [
## 1 2
## ],
p
a
b
c
## |–
## +
r
c
## [
## 1 2
## ],
p
a
b
c
## |–
## *
r
c
## [
## 1 2
## ]

## Accepted Language
## M
accepts
w
if it can completely read
w
by a sequence of moves from
s
to a
final state
## Gist:
## 16/29
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
## The
language accepted by M
## ,
## L
## (
## M
), is defined
as:
## L
## (
## M
## ) = {
w
## :
w
## ∈ Σ
## *
## ,
sw
## |–
## *
f
## ,
f
## ∈
## F
## }
final state
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
## ):
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
w
if
q
n
## ∈
## F
then
w
## ∈
## L
## (
## M
## );
otherwise,
w
## ∉
## L
## (
## M
## )

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
q, qb
## →
s
## },
## F
## = {
s
## }
## Question
## :
ab
## ∈
## L
## (
## M
## )
## ?
FA: Example 1/3
## 17/29
s
## Finite State Control:
q
ab
s
ab
## Finite Automaton
## M
## Question
## :
ab
## ∈
## L
## (
## M
## )
## ?
## Current Configuration:
a
b
Read head
Input tape:
a
s
ab

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
q, qb
## →
s
## },
## F
## = {
s
## }
FA: Example 2/3
## Question
## :
ab
## ∈
## L
## (
## M
## )
## ?
## 18/29
s
## Finite State Control:
q
b
a
q
b
## Finite Automaton
## M
## Current Configuration:
## Question
## :
ab
## ∈
## L
## (
## M
## )
## ?
a
b
Read head
Input tape:
s
ab
## |–
q
b

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
q, qb
## →
s
## },
## F
## = {
s
## }
FA: Example 3/3
## Question
## :
ab
## ∈
## L
## (
## M
## )
## ?
## 19/29
s
## Finite State Control:
q
ab
## Current Configuration:
s
## Finite Automaton
## M
## Answer:
## Question
## :
ab
## ∈
## L
## (
## M
## )
## ?
a
b
Input tape:
Read head
## Answer:
## YES
## ,
ab
## ∈
## L
## (
## M
## ),
because
s
## ∈
## F
s
ab
## |–
q
b
## |–
s

## Equivalent Models
## Definition:
Two models for languages, such
as FAs, are equivalent if they both specify the
same language.
## 20/29
same language.
## Example:
## M
## 1
## :
## M
## 2
## :
a
s
s
f
a
a
## Question
## :
## Is
## M
## 1
equivalent to
## M
## 2
## ?
## Answer:
## M
## 1
and
## M
## 2
are equivalent
because
## L
## (
## M
## 1
## ) =
## L
## (
## M
## 2
## ) = {
a
n
## :
n
## ≥
## ≥≥≥
## 0}

## •
## For
a
## RE
r
## =
## ∅
, there
is
a
n equivalent
## FA
## M
## .
Conversion of RE to FA: Basics 1/5
Algorithm that converts any RE to an equivalent FA (lex in UNIX).
## Gist:
## 21/29
## •
## For
a
## RE
r
## =
## ∅
, there
is
a
n equivalent
## FA
## M
## ∅
## ∅∅∅
## .
## •
For a RE
r
## =
ε
, there is an equivalent FA
## M
ε
εε
ε
## .
## Proof:
## M
## ∅
## ∅∅∅
## :
## Proof:
## M
ε
εε
ε
## :
s
ε
εεε
s
f
- For a RE
r
## =
a
## ,
a
## ∈ Σ
, there is an equivalent FA
## M
a
## .
a
## Proof:
## M
ε
εε
ε
## :
s
f
## Proof:
## M
a
## :
s
f

RE to FA: Concatenation 2/5
## •
## Let
r
be a RE over
## Σ
and
## M
r
## = (
## Q
r
## ,
## Σ
## ,
## R
r
## ,
s
r
## , {
f
r
}) be
an FA  such that
## L
## (
## M
r
## ) =
## L
## (
r
## ).
## •
## Let
t
be
a
RE over
## Σ
and
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
t
## , {
f
t
## })
be
## 22/29
## •
## Let
t
be
a
RE over
## Σ
and
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
t
## , {
f
t
## })
be
an FA  such that
## L
## (
## M
t
## ) =
## L
## (
t
## ).
- Then, for the RE
r
## .
t
, there exists an equivalent FA
## M
r.t
## Proof:
## Let
## Q
r
## ∩
## ∩∩∩
## Q
t
## =
## ∅
## ∅∅∅
## .
## M
r.t
## = (
## Q
r
## ∪
## Q
t
## ,
## Σ
## ,
## R
r
## ∪
## R
t
s
r
## ,
## ∪
## {
f
r
## →
s
t
## },
## {
f
t
## })
## Construction:
## M
r.t
## :
r.t
r
t
r
t
f
r
f
t
## ...
## M
r
## :
s
r
## ...
## M
t
## :
s
t
f
r
f
t
r
r
t
ε
εεε
t

## •
## Let
r
be a RE over
## Σ
and
## M
r
## = (
## Q
r
## ,
## Σ
## ,
## R
r
## ,
s
r
## , {
f
r
}) be
an FA such that
## L
## (
## M
r
## ) =
## L
## (
r
## ).
## •
## Let
t
be RE over
## Σ
and
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
t
## , {
f
t
## })
be
RE to FA: Union 3/5
## 23/29
## •
## Let
t
be RE over
## Σ
and
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
t
## , {
f
t
## })
be
an FA
such that
## L
## (
## M
t
## ) =
## L
## (
t
## ).
- For a RE
r
## +
t
, there exists an equivalent FA
## M
r+t
## Proof:
## Let
## Q
r
## ∩
## ∩∩∩
## Q
t
## =
## ∅
## ∅∅∅
## ,
s
## ,
f
## ∉
## Q
r
## ∪
## Q
t
## .
s
## ,
## M
r+t
## = (
## Q
r
## ∪
## Q
t
## ∪
## {
s
## ,
f
## }
## ,
## Σ
## ,
## R
r
## ∪
## R
t
## {
f
## })
## ∪
## {
s
## →
s
r
## ,
s
## →
s
t
## ,
f
t
## →
f
## },
f
r
## →
f
## ,
## Construction:
## M
r+t
## :
s
## ,
f
r
f
t
## ...
## M
r
## :
s
r
## ...
## M
t
## :
s
t
s
f
f
r
f
t
## {
f
## })
ε
εεε
s
## →
s
t
## ,
ε
εεε
f
t
## →
f
## },
ε
εεε
f
r
## →
f
## ,
ε
εεε

## •
## Let
r
be a RE over
## Σ
and
## M
r
## = (
## Q
r
## ,
## Σ
## ,
## R
r
## ,
s
r
## , {
f
r
}) be
an FA such that
## L
## (
## M
r
## ) =
## L
## (
r
## ).
## •
For the RE
r
## *
, t
here exists a
n equivalent
## FA
## M
RE to FA: Iteration 4/5
## 24/29
## •
For the RE
r
## *
, t
here exists a
n equivalent
## FA
## M
r*
## Proof:
## Let
s
## ,
f
## ∉
## Q
r
## .
## M
r*
## = (
## Q
r
## ∪
## {
s
## ,
f
## },
## Σ
## ,
## R
r
## {
f
## })
f
r
## →
f
## ,
f
r
## →
s
r
## ,
s
## →
f
## },
s
## ,
## ∪
## {
s
## →
s
r
## ,
## Construction:
## M
r*
## :
f
r
## ...
## M
r
## :
s
r
s
f
ε
εεε
ε
εεε
ε
εεε
f
r
ε
εεε

RE to FA: Completion 5/5
## •
## Input:
## RE
r
over
## Σ
## •
## Output:
## FA
## M
such that
## L
## (
r
## ) =
## L
## (
## M
## )
## •
## Method:
## 25/29
## •
## Method:
## •
From “inside” of
r
, repeatedly use the next
rules to construct
## M
## :
- for RE
## ∅
## ∅∅∅
## ,
construct FA
## M
## ∅
## ∅∅∅
- for RE
ε
εεε
## ,
construct FA
## M
ε
εε
ε
## •
for RE
a
## ∈
## Σ
, construct FA
## M
a
## (see 1/5)
## •
for RE
a
## ∈
## Σ
, construct FA
## M
a
## •
let
for REs
r
and
t
, there already exist FAs
## M
r
and
## M
t
, respectively;
then
## ,
- for RE
r.t
, construct FA
## M
r.t
## (see 2/5)
- for RE
r + t
, construct FA
## M
r + t
## (see 3/5)
- for RE
r
## *
construct FA
## M
r*
## (see 4/5)

RE to FA: Example 1/3
Transform RE
r
## = ((
ab
## ) + (
cd
## ))
## *
to an equivalent FA
## M
For RE
a
## :
a
s
f
## M
a
## :
For RE
b
## :
b
s
f
## M
b
## :
## 26/29
For RE
a
## :
s
f
For RE
b
## :
s
f
For RE
c
## :
c
s
f
For RE
d
## :
d
s
f
## M
a
b
## :
a
s
a
f
a
b
s
b
f
b
## M
a
## :
## M
b
## :
For RE
a
b
## :
ε
εεε
For RE
c
## :
c
s
f
For RE
d
## :
d
s
f
## M
c
d
## :
d
s
d
f
d
## M
d
## :
c
s
c
f
c
## M
c
## :
For RE
c
d
## :
ε
εεε

For RE
a
b
## :
a
s
a
f
a
b
s
b
f
b
ε
εεε
## M
a
b
## :
RE to FA: Example 2/3
## 27/29
## M
a
b
## +
c
d
## :
ε
εεε
ε
εεε
For RE
a
s
a
f
a
b
s
b
f
b
ε
εεε
## M
a
b
## :
For RE
c
d
## :
c
s
c
f
c
d
s
d
f
d
ε
εεε
## M
c
d
## :
f
## +
s
## +
ε
εεε
ε
εεε
ε
εεε
For RE
a
b
## +
c
d
## :
s
a
f
a
s
b
f
b
c
s
c
f
c
d
s
d
f
d
ε
εεε
## M
c
d
## :

a
s
a
f
a
b
s
b
f
b
ε
εεε
f
s
ε
εεε
## M
a
b
## +
c
d
## :
For RE
a
b
## +
c
d
## :
ε
εεε
RE to FA: Example 3/3
## 28/29
f
## +
s
## +
a
b
## +
c
d
## :
c
s
c
f
c
d
s
d
f
d
ε
εεε
ε
εεε
ε
εεε
## M
## (
a
b
## +
c
d
## )*
## :
a
s
f
b
s
f
ε
εεε
ε
εεε
## M
a
b
## +
c
d
## :
ε
εεε
ε
εεε
For a final RE
## (
a
b
## +
c
d
## )
## *
## :
a
s
a
f
a
b
s
b
f
b
ε
εεε
f
## +
s
## +
ε
εεε
c
s
c
f
c
d
s
d
f
d
ε
εεε
ε
εεε
ε
εεε
f
s
ε
εεε
ε
εεε
ε
εεε
ε
εεε

Models for Regular Languages
## Proof
is based on
the
previous algorithm.
## Theorem:
For every RE
r
, there is an FA
## M
such that
## L
## (
r
## ) =
## L
## (
## M
## ).
## 29/29
## Proof
is based on
the
previous algorithm.
## Proof:
See page 210 in [Meduna: Automata and Languages]
## Theorem:
For every FA
## M
, there is an RE
r
such that
## L
## (
## M
## ) =
## L
## (
r
## ).
## Conclusion:
The fundamental models for
regular languages are
## 1)
Regular expressions
## 2)
## Finite Automata