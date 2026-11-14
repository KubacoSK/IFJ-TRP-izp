

Formal Languages and
## Compilers
## Alexander Meduna
## &
## Roman Lukáš

••These lecture notes are based onThese lecture notes are based on
Automata and LanguagesAutomata and Languages  byby
Alexander Meduna, Springer, 2000Alexander Meduna, Springer, 2000
## References

Part I.Part I.
AlphabetsAlphabets, , Strings,Strings,  and and
LanguagesLanguages
## 1/20

Alphabets and symbols
Definition: An alphabet is a finite, nonempty
set of elements, which are called symbols.
a
b
## 0
## 1
## Alphabet
## Symbols
## Example:
If we denote this alphabet as , then  = {a, b, 0, 1}
## 2/20

Definition: Let  be an alphabet.
1)  is a string over 
2) if x is a string over  and a   then xa is  a
string over 
## Example: Consider  = {0, 1}:
Is string over .
## :
## :
## ...
## 
## 0
## 1
## =  0
## =  1 1
Note:  denotes the empty string that contains no symbols.
## 
##  0
## 0
## 1
## 1
## 0
## 0
## 1
## 1
## 10
## 10
## 0
## 
## String
Gist: x = a
## 1
a
## 2
## ...a
n
## 3/20

n = 4, thus |x| = 4
Definition: Let x be a string over .
The length of x, |x|, is defined as follows:
1) if x = , then |x| = 0
2) if x = a
## 1
## ...a
n
, then |x| = n
for some n  1, and a
i
  for all i = 1,...,n
Note: The length of x is the number of all symbols in x.
Example: Consider x =1010
## Task: |x|
x = 1 0 1 0
a
## 1
a
## 2
a
## 3
a
## 4
Length of String
## Gist: |a
## 1
a
## 2
## ...a
n
| = n

## 4/20

Definition: Let x and y be two strings over .
The concatenation of x and y is xy.
Note: x = x = x
## Examples:
Concatenation of 101 and 001 is 101001
Concatenation of  and 001 is 001 = 001
Concatenation of Strings
Gist: xy

## 5/20

Definition: Let x be a string over .
For i  0, the i-th power of x, x
i
, is defined as
1) x
## 0
=     2) if i  1 then x
i
= xx
i-1
Note: x
i
x
j
= x
j
x
i
= x
i+j
, where i, j  0
Example: Consider x =10
Task: x
## 3

x
## 3
= xx
## 2
## = 10x
## 2
x
## 0
## = 
x
## 2
= xx
## 1
## = 10x
## 1
x
## 1
= xx
## 0
## = 10x
## 0
x
## 1
## = 10 = 10
x
## 2
## = 1010

x
## 3
## = 101010

Power of String
Gist: x
i
= xx...x

i-times
## 6/20

Definition: Let x be a string over .
The reversal of x, reversal(x), is defined as:
1) if x =  then reversal() = 
2) if x = a
## 1
## ...a
n
then reversal(a
## 1
## ...a
n
) = a
n
## ...a
## 1
for some n  1, and a
i
  for all i = 1,...,n
Example: Consider x =1010
Task: reversal(x)
reversal(           ) =             , so
a
## 1
a
## 1
a
## 2
a
## 2
a
## 3
a
## 3
a
## 4
a
## 4
reversal(           ) =
## 1

## 1

## 0

## 0

## 1

## 1

## 0

## 0

Reversal of String
Gist: reversal(a
## 1
## ...a
n
) = a
n
## ...a
## 1
## 7/20

Definition: Let x and y be two strings over ;
x is prefix of y if there is a string z over  so
xz = y
Note: if x  {, y} then x is proper prefix of y.
## Example: Consider 1010
Task: All prefixes of 1010
Prefixes of 1010
Proper prefixes
of 1010
## 
## 1
## 10
## 101
## 1010
Prefix of String
Gist: x is a prefix of xz

## 8/20

Definition: Let x and y be two strings over ;
x is suffix of y if there is a string z over  so
zx = y
Note: if x  {, y} then x is proper suffix of y.
## Example: Consider 1010
Task: All suffixes of 1010
Suffixes of 1010
Proper suffixes
of 1010
## 
## 0
## 10
## 010
## 1010
Suffix of String
Gist: x is a suffix of zx

## 9/20

## Substrings
of 1010
Proper substrings
of 1010
Definition: Let x and y be two strings over ;
x is substring of y if there are two string z, z’
over  so zxz’ = y.
Note: if x  {, y} then x is proper substring of y.
## Example: Consider 1010
Task: All substrings of 1 0 1 0
## 
## 1 , 0
## 10 , 01
## 101 , 010
## 1010
## Substring
Gist: x is a substring of zxz’

## 10/20

## Definition: Let 
## *
denote the set of all strings
over . Every subset L  
## *
is a language over .
## Note: 
## +
denote the set 
## *
## – {}.
## Set 
## *

## L
## 1
## , L
## 2
## , L
## 3
## , L
## 4
are languages over 
## L
## 1
## = 
## L
## 2
## = {}
## L
## 4
= {x: 10 is substring of x}
## ...
## L
## 3
## = {x: |x| = 1}
## Example: Consider  = {0, 1}:
## 000
## 
## 01
## 00
## 10
## 11
## 001
## 010
## 100
## ...
## 011
## 111 0 1
## Languages
## Gist: L  
## *
## 11/20

Definition: A language, L, is finite if L contains a
finite number of strings; otherwise, L is infinite.
Note: Let S be a set; card(S) is the number of its members.
## Examples:
## • L
## 1
=  is finite because card(L
## 1
## ) = 0
## • L
## 2
= { } is finite because card(L
## 2
## ) = 1
## • L
## 3
= {x: |x| = 1} = {0, 1} is finite because
card(L
## 3
## ) = 2
## • L
## 4
= {x: 10 is substring of x} = {10, 010, 100, ... }
is infinite
Finite and Infinite Languages
Gist: finite language contains a finite number
of strings

## 12/20

## Definition: Let L
## 1
and L
## 2
be two languages over .
The union of L
## 1
and L
## 2
## , L
## 1
##  L
## 2
, is defined as
## L
## 1
##  L
## 2
= {x: x  L
## 1
or x  L
## 2
## }
Example: Consider languages L
## 1
## = {0, 1, 00, 01},
## L
## 2
## = {00, 01, 10, 11}
## Task:  L
## 1
##  L
## 2

## L
## 1
## L
## 2
## 0
## 1
## 00
## 01
## 10
## 11
Union of Languages
Gist: Union of L
## 1
and L
## 2
is L
## 1
##  L
## 2
## L
## 1
##  L
## 2
## = {0, 1, 00, 01, 10, 11}
## 0
## 1
## 00
## 01
## 10
## 11
## 13/20

Example: Consider languages L
## 1
## = {0, 1, 00, 01},
## L
## 2
## = {00, 01, 10, 11}.
## Task: L
## 1
##  L
## 2

## L
## 1
## L
## 2
## 0
## 1
## 00
## 01
## 10
## 11
Intersection of Languages
## L
## 1
##  L
## 2
## = {00, 01}
## 00
## 01
Gist: Intersection of L
## 1
and L
## 2
is L
## 1
##  L
## 2
## Definition: Let L
## 1
and L
## 2
be two languages over .
The intersection of L
## 1
and L
## 2
## , L
## 1
##  L
## 2
, is defined as:
## L
## 1
##  L
## 2
= {x: x  L
## 1
and x  L
## 2
## }
## 14/20

## Definition: Let L
## 1
and L
## 2
be two languages over .
The difference of L
## 1
and L
## 2
## , L
## 1
## – L
## 2
, is defined as
## L
## 1
## – L
## 2
= {x: x  L
## 1
and x  L
## 2
## }
Example: Consider languages L
## 1
## = {0, 1, 00, 01},
## L
## 2
## = {00, 01, 10, 11}
## Task: L
## 1
## – L
## 2

## L
## 1
## L
## 2
## 0
## 1
## 00
## 01
## 10
## 11
Difference of Languages
Gist: Difference of L
## 1
and L
## 2
is L
## 1
## – L
## 2
## L
## 1
## – L
## 2
## = {0, 1}
## 0
## 1
## 00
## 01
## 15/20

Definition: Let L be a languages over .
The complement of L, L, is defined as
## L = 
## *
## – L
Example: Consider language L = {0, 1, 01, 10}
## Task:  L
## 
## *
## ...
## 000
## 
## 00
## 10
## 01
## 11
## 001
## 010 100
## 011
## 0
## 1
Complement of Language
## Gist: L = 
## *
## – L
## L
## ...
## 000
## 
## 00
## 11
## 001
## 010 100
## 011
## L
## 10
## 01
## 0
## 1
## 16/20

## L
## 1
## L
## 2
## Definition: Let L
## 1
and L
## 2
be two languages over .
The concatenation of L
## 1
and L
## 2
## , L
## 1
## L
## 2
, is defined as
## L
## 1
## L
## 2
= {xy: x  L
## 1
and y  L
## 2
## }
Note: 1) L{}= {}L = L  2) L = L = 
## 00
## 0
## 01
## 0
## 00
## 1
## 01
## 1
## L
## 1
## 0
## 1
## L
## 2
## 00
## 01
Example: Consider languages L
## 1
## = {0, 1}, L
## 2
## = {00, 01}
## Task:  L
## 1
## L
## 2

Concatenation of Languages
## Gist: L
## 1
## L
## 2
= {xy: x  L
## 1
and y  L
## 2
## }
## 17/20

reversal(L)
Definition: Let L be a language over .
The reversal of L, reversal(L), is defined as
reversal(L) = {reversal(x): x  L}
## L

## 01
## 011
## Example: Consider L= {01, 011}
Task:  reversal(L)
reversal(      ) = 10 01 10
reversal(      ) = 110 011 110
Reversal of Language
Gist: reversal(L) = {reversal(x): x  L}
## 18/20

Definition: Let L be a language over .
For i  0, the i-th power of L, L
i
, is defined as:
## 1) L
## 0
= {}         2) if i  1 then L
i
## = LL
i-1
## L
## 2
## = LL
## 1
## 0
## 0
## 0
## 01
## 01
## 0
## 01
## 01
## L

## 0
## 01
## L
## 1
## = LL
## 0
## 0
## 01
## 
## 
## 0
## 01
## L
## 0

## 
Power of Language
## Gist: L
i
## = LL...L

i-times
## 19/20
## Example: Consider L= {0, 01}
## Task:  L
## 2


Definition: Let L be a language over . The
iteration of L, L
## *
, and the positive iteration of L,
## L
## +
, are defined as L
## *
## =  L
i
## , L
## +
## =  L
i
## 
i = 0
## 
i = 1
## Note: 1) L
## +
## = LL
## *
## = L
## *
## L  2) L
## *
## = L
## +
##  {}
## Example:
## Task:  L
## *
and L
## +

Consider language L= {0, 01} over  = {0, 1}.
## L
## 0
## = {},

## L
## 1
## = {0, 01},

## L
## 2
## = {00, 001, 010, 0101}, ...
## L
## *
## = L
## 0
##  L
## 1
##  L
## 2
## 

## ...= {, 0, 01, 00, 001, 010, 0101, ... }
## L
## +
## =         L
## 1
##  L
## 2
## 

## ...=     {0, 01, 00, 001, 010, 0101, ... }
Iteration of Language
## 20/20
## Gist: L
## *
## = L
## 0
##  L
## 1
##  L
## 2
##  ...  L
i
##  ...
## L
## +
## = L
## 1
##  L
## 2
##  ...  L
i
##  ...