# Mathematics Programming Language

A really cursed language where you wrote code that looks like mathematical proofs. Inspired by [Shakespeare Programming Language](https://en.wikipedia.org/wiki/Shakespeare_Programming_Language#Example_code), where programs appear like Shakespearean plays.

My goal with MPL is to create a language that is both pointlessly verbose and unreadable and low level, hopefully lower than C. Below is a specification for MPL syntax and features.

## Variables

Variables must be definied with the syntax:
let variableName be ...

Python
```
variable1 = 500
variable2 = variable1 * 3
```

MPL
```
Let variable1 be 500.`
Let variable2 be variable1 * 3.
```

The type of your variable is dynamic, similar to python.

## Functions

Functions must be defined for a number of parameters, and the input type and output type must be stated as well. When you run the function, you must ensure the variable is of that type.

Functions must return a value and have no side effects, just like in mathematics.

Python
```
def add(num1: int, num2: int) -> int:
	return num1 + num2
```

MPL
```
Let add be the function defined for (integer, integer) -> integer and defined by add(num1, num2) = num1 + num2.
```

## Comparison operators

### Equal to
Python: `a == b`<br>
MPL: `a = b`

### Not equal to
Python: `a != b`<br>
MPL: `a =/= b`

### Greater than
Python: `a > b`<br>
MPL: `a > b`

### Greater than or equal to
Python: `a >= b`<br>
MPL: `a >= b`

### Less than
Python: `a < b`<br>
MPL: `a < b`

### Less than or equal to
Python: `a <= b`<br>
MPL: `a <= b`

## Logical operators

### Negation
Python: `not a`<br>
C/C++/Java: `!a`<br>
MPL: `~a` ([source](https://en.wikipedia.org/wiki/Negation))

### And
Python: `a and b`<br>
C/C++/Java: `a && b`<br>
MPL: `a ^ b` ([source](https://en.wikipedia.org/wiki/Logical_conjunction))

### Or
Python: `a or b`<br>
C/C++/Java: `a || b`<br>
MPL: `a + b` ([source](https://en.wikipedia.org/wiki/Logical_disjunction))

## Bitwise operators

Who needs those?

## Assignment operators

### Direct assignment
Python: `a = b`<br>
MPL: `Let a be b`

## Data types

### Number types
There are two number types: number and double precision floating point number. They are variable bit, like python.

### Character types
Because MPL is designed to be inclusive of everyone's cultures, characters will be encoded in Unicode, so it's not just English letters. To define a character, use the single quotation mark ('c')

C/C++/Java: `char c = 'a';`

MPL: `Let c be 'a'.`

### Strings
Doesn't exist, go write your own ~~array~~ list of chars.
Double quotation marks ("") is the same as an array of chars, so "abc" is equivalent to ['a','b','c'].

### Lists
Lists aren't really a thing in mathematics (at least to my knowledge), so I'll just use the Computing definition of Lists/Arrays in here.

A list is an ordered collection of items that supports duplicates. Elements can be modified or read by index number, and indices  start at 1 (lol).

the ith element of list is set to x: `Let list_i be x`
read the ith element of the list: `list_i`

MPL has this ~~bizarre~~ unique underscore extraction operator because I've seen people use subscript as indices in math. 

To create a list, specify the length of the list. This can be a variable or a constant. The list is not initialized with 0 so it could be filled with garbage.

```
Let list be 4 long.

Let list2Length be 500.
Let list2 be list2Length long.
```

You must free the list when it is no longer in use. Otherwise, you will create a memory leak.
```
Forget list. Forget list2.
```

## For loop

Doesn't exist, use goto.

## Goto

Because everyone with a valid opinion (apart from Linus Torvalds) seems to hate goto, they're the only method of looping in MPL. Use `refer to sentence [sentence number]` to go to a certain sentence. Comments do not count as sentences.

## If statement

If statements are too complicated and high level for MPL. The only branching statement is `refer to sentence [sentence number] if [condition]`, which is basically a goto if statement.

## I/O

To print a variable, use `output variable`.

## Syntax

In MPL, you have to use a period (.) to signify the end of your sentence. This is like the semicolon in C or Java.

The first character of a sentence must be capitalized, and there must be either a space or new line after the period to distinguish it from a decimal point.

`Let m be 500. Let n be m - 50.` Valid<br>
`Let m be 500.Let n be m - 50.` Error

### Comments
To add a comment, start the line with `COMMENT:` and end it with a period as usual. The rest of the sentence will be ignored by the interpreter.

`Let m be 500. COMMENT: insert your comment here. Let n be m - 50.`
