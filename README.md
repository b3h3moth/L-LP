### bitwise Hacks

From bitwise operators to bitwise Hacks on integer and floating point data 
types. A journey among the bits:

* bit operators
* shifting
* extract, clear and setup a bit
* extract, clear and setup a bitfield
* bit hacks

### Libraries and API's

A lot of libraries for every day use; graphics, cryptography, serialization, 
database, I/O and so on.

### Representing information

How computer really works: 

* addressing 
* Byte ordering (Big-endian, Little-endian)
* integer representation
  * char, short, int, long (signed and unsigned);
  * casting and information loss
  * integer arithmetic

* floating point (IEEE 754 single and double precision)
  * float, double
  * to do, at the moment is empty

### The language

A lot of articles on C99 and C11 standards, the core of the language.

#### How to compile programs

The programs will be compiled with two standard:

- `iso9899:1999`, ``-std=c99``

- `iso9899:2011`, ``-std=c11`` (experimental and incomplete from GCC 4.7)

Architecture for testing code:

- `PPC 32 bit` (big endian)
- `x86 32 bit` (little endian)
- `x86 64 bit` (little endian)

Each program can be compiled both gcc and clang:

$ ``gcc   main.c -o main``

$ ``clang main.c -o main``

Or with more detail:

$ ``gcc   -o main main.c -g -Wall -pedantic -std=c99`` | oppure ``-std=c11``

$ ``clang -o main main.c -g -Wall -pedantic -std=c99`` | oppure ``-std=c11``

Nota: L'opzione `-ansi` e' equivalente a `-std=c90` per il C ed a `-std=c++98` per il
      C++. Inoltre `-std=c90` e' equivalente a `-std=c89`.

<hr />

<address>`*Luca Suriano a.k.a. Behemoth*: <behemoth _at_ autistici _dot_ org>`</address>

<url>`https://keybase.io/behemoth`</url>
