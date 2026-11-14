

Part X.Part X.
## 1/43
Part X.Part X.
OptimizationOptimization
andand
Code GenerationCode GenerationCode GenerationCode Generation

## Basic Blocks
## 2/43
## • A
basic block
is a sequence of statements
executed sequentially from beginning to end
## •
## A
leader
is the first statement of a basic block
## •
## A
leader
is the first statement of a basic block
Determine the set of leaders as follows:•   The
first statement
is a
leader
-   Any statement that is the
label
of a goto
statement is a
leader
statement is a
leader
-   Any statement that follows
a
goto
statement is a
leader

## Block 1
## Basic Blocks: Example
## 3/43
## LEADER
(first statement)
sum := 0
## ;
i := 0;
Block 2Block 3
## LEADER
## (label)
## LEADER
(follows a goto
statement)
## L1
## :
if i >= n
goto L2
## ;
sum := sum + a[i];i := i + 1;
goto L1
## ;
## Block 4
## LEADER
## (label &
follows a goto
statement)
goto L1
## ;
## L2
## :
result := sum

## B1
Flow Graph over Blocks
## 4/43
sum := 0
## ;
i := 0;
## B1
Program with basic blocks:
Flow control
graph:
## B1B2B3
i := 0;L1
## :
if i >= n
goto L2
## ;
sum := sum + a[i];i := i + 1;goto L1
## ;
## B1
## B2
## B3
## B4
goto L1
## ;
## L2
## :
result := sum
## B3
## B4
## Note:
Isolated blocks in a flow graph =
dead code

## Optimization: Introduction
## 5/43
## Gist:
## Optimizer
makes a more efficient version
of the intermediate or target code
Variants of optimizations:1)
Local optimization
## ×
## ×××
Global optimization
## •
Local optimization
– within a basic block
## •
Global optimization
– span several basic blocks
Variants of optimizations:2)
## O
ptimization
for speed
## ×
## ×××
## O
ptimization
for size
## 2)
## O
ptimization
for speed
## ×
## ×××
## O
ptimization
for size
## 1)
Constant folding
## 2)
Constant propagation
## 3)
Copy propagation
Optimization methods:
## 4)
Loop invariant expressions
## 5)
Loop unrolling
## 6)
Dead code elimination

## Optimization Methods 1/3
1) Constant folding
a := 1;b := 2;
c := 3;
## 6/43
b := 2;c := a + b;
c := 3;
2) Constant propagation
a := 3;b := a;c := b;
c := 3;
3) Copy propagation
a := x;b := a;c := b;
c := x;

## Optimization Methods 2/3
4) Loop invariant expressions
for i := 1 to 100 do
x := p*q/rfor i := 1 to 100 do
## 7/43
for i := 1 to 100 do
a[i] := p*q/r + i
for i := 1 to 100 do
a[i] := x + i
5) Loop unrolling
for i := 1 to 100 dobegin
write(x[i, 1]);
for i := 1 to 100 dobegin
for j := 1 to 2 do
write(x[i, 2]);
end;
write(x[i, j]);
end;

## Optimization Methods 3/3
6) Dead code elimination
## 8/43
## •
Dead code:
a)
Never executed
b)
Does nothing useful
trace := false;if trace then begin
writeln(...);...
end;
nothing
b)
Does nothing useful
ad
a)
x := x;
nothing
ad
b)

## Optimization For Size
## 9/43
- This optimization only makes a shorter
program
## Example:
case p of
1: u :=
a*b
- c;
2: v :=
a*b
+ c;
3: x := d -
a*b
## ;
4: y :=
a*b
/ d;
5: z := 2 *
a*b
## ;
## T
## :=
a*b
## ;
case p of
1: u :=
## T
- c;
2: v :=
## T
+ c;
3: x := d -
## T
## ;
4: y :=
## T
## /
d;
5: z := 2 *
a*b
## ;
end;•
## Note:
## (a*b)
is very busy.
4: y :=
## T
## /
d;
5: z := 2 *
## T
## ;
end;

## Code Generation
## : Introduction
## 10/43
## •
Blind generation
vs.
Context-sensitive generation
Variants of code genarations:1)
## B
lind generation
## 1)
## B
lind generation
- For every 3AC instruction, there is a procedure
that generates the corresponding target code
Main disadvantage:• As each 3AC instruction is out of the basic block
context, a lot of  redundant loading and storing oc
cur
## 2)
Context-sensitive generation
- Reduction of loading and storing between
registers and memory.
context, a lot of  redundant loading and storing oc
cur

## Blind Generation: Example
l
oad
r
i
## ,
a
add
r
## ,
b
## 11/43
## (
## +
## ,
a
## ,
b
## ,
r
## )
## 3AC:
Generated code:
l
oad
r
i
## ,
a
add
r
i
## ,
b
st ore
r
i
## ,
r
## (
## +
## ,
a
## ,
b
## ,
r
## )
load
r
i
## ,
a
mul
r
i
## ,
b
st ore
r
i
## ,
r
## (
## *
## ,
a
## ,
b
## ,
r
## )
load
r
i
## ,
a
st ore
r
i
## ,
r
## (
## :=
## ,
a
## ,   ,
r
## )

## Blind Generation
## 12/43
Example:3AC:
Generated target code:
load
r1 ,
a
add
r1 ,
b
st ore
r1 ,
c
l
oad
r1
## ,
c
## (
## +
## ,
a
## ,
b
## ,
c
## )
## (
## *
## ,
c
## ,
d
## ,
e
## )
A redundant
l
oad
r1
## ,
c
mul
r1 ,
d
st ore
r1 ,
e
## (
## *
## ,
c
## ,
d
## ,
e
## )
A redundantinstruction

Context-Sensitive Generation (CSG)
## 13/43
- Minimization of loading and storing between
registers and memory:
## •
General rule:
If a value is in a register and
## •
General rule:
If a value is in a register and
will be used “
soon
”, keep it in the register
Information needed :
## 1)
## Question:
Which variables are needed later in the
block and where?
## Answer
is in the
Basic block table
## (
## BBT
## )
## 2)
## Q:
Which registers are in use and what they hold?
## 2)
## Q:
Which registers are in use and what they hold?
## A
is in the
Register association table
## (
## RAT
## )
## 3)
## Q:
Where the current value of a variable is to be
found?A
is in the
Address table
## (
## AT
## )

CSG: Analysis within a Basic Block
## 14/43
- A variable is
live
if it is used later in the block
live
## Example:
live
next use
## ...
No occurrence of  variable “
a
## ”
## ...
## (i)
a
:= b + c
(j) d :=
a
+ b
## Question:
How to detect live variables effectively?
## Answer:
## Apply
backward
finding
## 
that is, read
the instructions from the block end towards its beg
in

Symbol Table (ST)
## 15/43
variable    status
next use
a
live
## (10)
Extetion of a ST:
## Status
## :
livedead
a
b
pos
livelive
dead
## (10)(20)
none
## ...
## ...
## ...
Next use
## :
none(
i
## )
## •
i
= number of a line
Initial assumption:• All programmer variables:• All temporary variables:• All variables:
## Status
## :
live
## Status
## :
dead
Next use
## :
none

Basic Block Table (BBT)
## 16/43
line    instruction
status
next use
Structure of a
## BBT:
## ...
## ...
## (
i
## )
a
## :=
b
## +
c
## ......
## ......
backward
Suppose that (
i
) is the current instruction:
## 1)
## Move
status
and
next use
of
a
## ,
b
## ,
c
from
## ST
to
## BBT
## •
## Method:
## 1)
## Move
status
and
next use
of
a
## ,
b
## ,
c
from
## ST
to
## BBT
## 2)
## In
## ST
make these changes:
For variable
a
## :
## Status
## :
dead
Next use
## :
none
For variables
b
## ,
c
## :
## Status
## :
live
Next use
## :
## (
i
## )

Changes in a ST: Illustration
## 17/43
var
status
next use
a
dead
none
## ...
## ST:
a
b
c
dead
livelive
none
## (
i
## )
## (
i
## )
## ......
## ...
## ...
## ...
a
is dead because
a
## :=
b
## +
c
kills
any
previous
definition of
a
## (
i
## )
a
## :=
b
## +
c
backward
previous
definition of
a
b
## ,
c
are alive and used in (
i
); this
information reflects the situation earlier
in the block

Filling BBT: Example 1/8
## 18/43
d := (a
## -b) + (c
## -a)    - (d+b) * (c+1)
u
v       x       y
w
z
## BBT:
w
z
line   instruction
status
next use
## (1)(2)(3)
u:=a   -bv:=c   -aw:=u+v
## BBT:
## (3)(4)(5)(6)(7)
w:=u+vx:=d+by:=c+1z:=x*yd:=w   -z

Filling BBT: Example 2/8
## 19/43
var    status   next use
a
## L
## N
ST - line (7):
a
b
c
du
v
w
## LLLL
## DD
## D
## NNNNNNN
## [1]
## [2]
## [3]
## [3]
programvariables
w
xy
z
## DDDD
## NNNN
L – liveD – deadN – none
## [2] [2]
## [3] [3]
temporary variables

Filling BBT: Example 3/8
## 20/43
line
instruction
status
next use
## BBT:
line
instruction
status
next use
## (1)(2)(3)(4)(5)
u:=a   -b
v:=c   -aw:=u+vx:=d+b
y:=c+1
## (5)(6)(7)
y:=c+1z:=x*yd:=w   -z
d:L  ; w,z:D
d,w,z:N
## [1]
## [2]
## [3]

Filling BBT: Example 4/8
## 21/43
var    status   next use
a
## L
## N
ST - line (6):
a
b
c
du
v
## LLL
## DDD
## NNNNNN
v
w
xy
z
## D
## L
## DD
## L
## N
## (7)
## NN
## (7)
## [1] [1] [2]
## [3]
## [3] [4]

Filling BBT: Example 5/8
## 22/43
## BBT:
line   instruction
status
next use
## (1)(2)(3)
## (4)
u:=a   -bv:=c   -aw:=u+vx:=d+b
## (4)(5)(6)(7)
x:=d+by:=c+1z:=x*yd:=w   -z
z:L  ; x,y:Dd:L; w,z:D
z:7   ; x,y:Nd,w,z:N
## [2]
## [1]
## [3]
## [4]

Filling BBT: Example 6/8
## 23/43
var    status   next use
a
## L
## N
ST - line (5):
a
b
c
du
v
## LLL
## DD
## D
## NNNNNN
## [1]
## [2]
v
w
xy
z
## D
## LLL
## D
## N
## (7)(6)(6)
## N
## [1]
## [3]

Filling BBT: Example 7/8
## 24/43
## BBT:
line   instruction
status
next use
## (1)(2)(3)
## (4)
u:=a   -b
v:=c   -aw:=u+v
x:=d+b
## (4)(5)(6)(7)
x:=d+by:=c+1z:=x*yd:=w   -z
y,c:Lz:L; x,y:Dd:L; w,z:D
y:6   ; c:Nz:7; x,y:Nd,w,z:N
## [1]
## [3]
## [2]
## •
Fill the rest analogically.

Filling BBT: Example 8/8
## 25/43
Final BBT:
line   instruction
status
next use
## (1)(2)(3)
## (4)
u:=a   -b
v:=c   -aw:=u+v
x:=d+b
u,a,b:Lv,c,a:Lw:L; u,v:Dx,b:L; d:D
u:3; a:2; b:4v:3; c:5; a:Nw:7; u,v:Nx:6; d,b:N
## (4)(5)(6)(7)
x:=d+by:=c+1z:=x*yd:=w   -z
x,b:L; d:Dy,c:Lz:L; x,y:Dd:L; w,z:D
x:6; d,b:Ny:6; c:Nz:7; x,y:Nd,w,z:N

## Register Association Table
## 26/43
reg.
contents
## 0
reserved
Structure of a RAT:
## Contents
## :
reservedfree
## 012345
reservedreserved
free
a
free
b
## Contents
## :
freevar
i
## •
reversed
for some operation
system purposes
## •
var
i
## =
name of variable
## 5
b
## ...
## ...
## •
var
i
## =
name of variable
- Every use of a register updates RAT.• RAT indicates the current contents of each
register

variable
address
a
in
memory
Address Table (AT)
## 27/43
Structure of an AT:
## Address
## :
in memoryreg.
i
a
b
c
in
memory
reg. 5
nowhere
## ...
## ...
## Address
## :
reg.
i
nowhere
## •
i
= number of register
## •
Address table shows where the current value
## •
Address table shows where the current value
of every variable can be found.

GetReg
## 28/43
GetReg
## :
## •
GetReg
returns an optimal register
for
b
in
a :=
b
+ c
GetReg
## :
begin
if
b
is in register
## R
and
b
is dead
and
b
has no next use
then
return
## R
elseif
there is any free register
## R
then
return
## R
else begin
## •
select an occupied register
else begin
## •
select an occupied register
## R
- save
## R
’s current contents
- update RAT & AT• return
## R
end;
end;

GenCode
## 29/43
## •
GenCode
generate an optimal code for
command
a
## :=
b
## +
c
GenCode
## :
GenCode
## :
begin•   Ask
GetReg
for a register
## R
for
b
## •
if
b
is not in
## R
then
generate
load R,b
## •
if
c
is in reg.
## S
then
generate
add  R,S
else
generate
add  R,c
{= c is in memory}{= c is in memory}
-   Update RAT & AT to indicate that current
value of
a
is in
## R
## •
if
c
is in
## S
and
c
is dead
and
has no next
use
then
mark
## S
as free in RAT
end;

GetReg
and
GenCode
## : Example 1/10
## 30/43
line   instruction
status
next use
## (1)
## (2)
u:=a   -bv:=c
## -
a
u,a,b:Lv,c,a:L
u:3; a:2; b:4v:3; c:5; a:N
## BBT:
## (2)(3)(4)(5)(6)(7)
v:=c
## -
a
w:=u+vx:=d+by:=c+1z:=x*yd:=w   -z
v,c,a:Lw:L; u,v:Dx,b:L; d:Dy,c:Lz:L; x,y:Dd:L; w,z:D
v:3; c:5; a:Nw:7; u,v:Nx:6; d,b:Ny:6; c:Nz:7; x,y:Nd,w,z:N
reg.
contents
## 0,1
## 2-11
## 12-15
reservedfreereserved
var.
address
a-du-z
in memorynowhere
## RAT:
## AT:

GetReg
and
GenCode
## : Example 2/10
GetReg
## :
## R2
## Instruction:
(1) u:=a
## -b
## Properties:
u, a, b: live
## 31/43
reg.
contents
## 0,1
reserved
var.
address
a
## -
d
in memory
## RAT:
## AT:
GetReg
## :
## R2
GenCode
## :
load R2,asub  R2,b
## 0,1
## 2-11
## 12-15
reservedfreereserved
a
## -
d
u-z
in memorynowhere

GetReg
and
GenCode
## : Example 3/10
GetReg
## :
## R3
## Instruction:
(2) v:=c
## -a
## Properties:
v, c, a: live
## 32/43
reg.
contents
## 0,1
reserved
var.
address
a
## -
d
in memory
## RAT:
## AT:
GetReg
## :
## R3
GenCode
## :
load R3,csub  R3,a
## 0,1
## 2
## 3-11
## 12-15
reservedufreereserved
a
## -
d
u
v-z
in memory2nowhere

GetReg
and
GenCode
## : Example 4/10
GetReg
## :
## R2
## Instruction:
(3) w:=u+v
## Properties:
w: live; u, v: dead
## 33/43
reg.
contents
## 0,1
reserved
var.
address
a
## -
d
in memory
## RAT:
## AT:
GetReg
## :
## R2
GenCode
## :
add R2,R3
## 0,1
## 23
## 4-11
## 12-15
reserveduvfreereserved
a
## -
d
uv
w-z
in memory23nowhere

GetReg
and
GenCode
## : Example 5/10
GetReg
## :
## R3
## Instruction:
(4) x:=d+b
## Properties:
x, b: live; d: dead
## 34/43
reg.
contents
## 0,1
reserved
var.
address
a
## -
d
in memory
## RAT:
## AT:
GetReg
## :
## R3
GenCode
## :
load R3,dadd  R3,b
## 0,1
## 2
## 3-11
## 12-15
reservedwfreereserved
a
## -
d
u, v
w
x-z
in memorynowhere2nowhere

GetReg
and
GenCode
## : Example 6/10
GetReg
## :
## R4
## Instruction:
(5) y:=c+1
## Properties:
y, c: live
## 35/43
reg.
contents
## 0,1
reserved
var.
address
a
## -
d
in memory
## RAT:
## AT:
GetReg
## :
## R4
GenCode
## :
load R4,cadd  R4,#1
## 0,1
## 23
## 4-11
## 12-15
reservedwxfreereserved
a
## -
d
u, v
w
x
y, z
in memorynowhere23nowhere

GetReg
and
GenCode
## : Example 7/10
GetReg
## :
## R3
## Instruction:
(6) z:=x*y
## Properties:
z: live; x, y: dead
## 36/43
reg.
contents
## 0,1
reserved
var.
address
a
## -
d
in memory
## RAT:
## AT:
GetReg
## :
## R3
GenCode
## :
mul R3,R4
## 0,1
## 234
## 5-11
## 12-15
reservedwxyfreereserved
a
## -
d
u, v
w
xy
z
in memorynowhere234nowhere

GetReg
and
GenCode
## : Example 8/10
GetReg
## :
## R2
## Instruction:
(7) d:=w
## -z
## Properties:
d: live; w, z: dead
## 37/43
reg.
contents
## 0,1
reserved
var.
address
a
## -
d
in memory
## RAT:
## AT:
GetReg
## :
## R2
GenCode
## :
sub R2,R3
## 0,1
## 23
## 4-11
## 12-15
reservedwzfreereserved
a
## -
d
u, v
w
x, y
z
in memorynowhere2nowhere3

GetReg
and
GenCode
## : Example 9/10
GetReg
## :
## -
## Instruction:
end of block
## Properties:
d: live;
## 38/43
reg.
contents
## 0,1
reserved
var.
address
a
## -
c
in memory
## RAT:
## AT:
GetReg
## :
## -
GenCode
## :
store
## R2,d
(save all live variables!)
## 0,1
## 2
## 3-11
## 12-15
reserveddfreereserved
a
## -
c
d
u-z
in memory2nowhere

GetReg
and
GenCode
## : Example 10/10
## 39/43
## Line
## 3AC
generated code
## •
Resulting Code: 12 instructions instead of 21
## (1)(2)(3)(4)
u:=a-bv:=c-aw:=u+vx:=d+b
load  R2,  asub   R2,  bload  R3,  csub   R3,  aadd   R2, R3load  R3,  d
add
## R3,
b
## (5)(6)(7)
y:=c+1z:=x*yd:=w-z
add
## R3,
b
load  R4,  cadd   R4, #1mul   R3, R4sub   R2, R3store R2,  d

## Parallel Compilers: Introduction
## 40/43
## •
Lexical analyzer
translates a
complete
source
program into tokens
## •
Preparation of the syntax analysis in parallel:
- A separation of some substrings of tokens.
These substrings and the rest, called the
program
skeleton
, are parsed in parallel.
## •
In the skeleton, the removed substrings
## •
In the skeleton, the removed substrings
are replaced with
pseudotokens
## .

Parallel Compilers: Separation of Conditions
## 41/43
## ...
if
cond
## 1
then ...
## ...
## ...
if
## [
cond
## ,
## 1
## ]
then ...
## ...
while
cond
## 2
do ...
repeat ... until
cond
## 3
## ......   ...
while
## [
cond
## ,
## 2
## ]
do ...
repeat ... until
## [
cond
## ,
## 3
## ]
## ......   ...
## •
Table of condition:
## •
Table of condition:
## 1
cond
## 1
## 2
cond
## 2
## 3
cond
## 3

Parallel Compilers: Multi-Level Separation
## 42/43
## ...
if
a + b   >   c * d
and
a – b   =   c + d
then ...
## .........
if
## [
cond
## ,
## 1
## ]
then ...
## ...
## •
Table of expressions:
## 1
a + b
## 2
c * d
## 3
a
## -
b
## ...
## •
Table of condition:
## 1
## [
expr
## ,
## 1
## ] > [
expr
## ,
## 2
] and [
expr
## ,
## 3
## ] = [
expr
## ,
## 4
## ]
## 2
## ...
## 3
a
## -
b
## 4
c + d

## Parallel Compilers: Parsing
## 43/43
## Processor 1
## Processor 2
## Processor
k
## ...
## Skeleton
## Table
## 1
## Table
k
## -1
## ...
## •
different methods 1
## –
k
## Tables
Parallel parsing
## •
different methods 1
## –
k
## •
different intermediate codes