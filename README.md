# Mathematics Programming Language

A really cursed language where you wrote code that looks like mathematical proofs. Inspired by [Shakespeare Programming Language](https://en.wikipedia.org/wiki/Shakespeare_Programming_Language#Example_code), where programs appear like Shakespearean plays.

## Variables

Variables must be definied with the syntax:
let variableName be ...

Python -> MPL:

`variable1 = 500`<br>
`Let variable1 be 500.`

`variable2 = variable1 * 3`<br>
`Let variable2 be variable1 * 3.`

The type of your variable is dynamic, similar to python.

## Functions

Functions must be defined for a number of parameters, and the input type and output type must be stated as well. When you run the function, you must ensure the variable is of that type.

Functions must return a value and have no side effects, just like in mathematics. This makes MPL is a purely functional language, similar to Haskell.

```
def add(num1: int, num2: int) -> int:
	return num1 + num2
```

```
Let add be the function defined for (integer, integer) -> integer and defined by add(num1, num2) = num1 + num2.
```
We see that the function definition in MPL is pointlessly long and verbose. This is intentional, of course.

## Data types

### Number types
There are two number types: number and double precision floating point number. Hopefully they will not have limits like python.

### Character types
Because MPL is designed to be inclusive of everyone's cultures, characters will be encoded in Unicode, so it's not just English letters.<br>
To define a character, use the single quotation mark ('c')

Python doesn't have chars, so I will use C to give an example.

`char c = 'a';`<br>
`Let c be 'a'.`

### Strings
Doesn't exist, go write your own ~~array~~ list of chars.
Double quotation marks ("") is the same as an array of chars, so "abc" is equivalent to ['a','b','c'].

### Lists
Lists aren't really a thing in mathematics, so I'll just use the Computing definitio of Lists/Arrays in here.
A list is an ordered collection of items that supports duplicates. Elements can be modified or read by index number:
List indexes start at 1.

the ith element of list is set to x: `Let list[i] be x`
read the ith element of the list: `list[i]`

To create a list, either specify pre-define its elements or add the elements manually.

`Let list be [0,1,2,3]`<br>
`Let list be []. For each i in [0,1,2], add 0 to list.`

## For loop

For loops are also not a thing in math, but I supposed "for all" (∀) kind of works.
For now I will just have a for each loop. You can iterate over a list with the syntax:

`For each i in list, ...`

## I/O

To print a variable, use `Output variable.`

## Syntax

In MPL, you have to use a period (.) to signify the end of your sentence. This is very similar to the semicolon in C or Java. If you have a super long expression, you can make it continue to the next line by not inserting the period.

The first character of a sentence must be capitalized, and there must be either a space or new line after the period to distinguish it from a decimal point.

`Let m be 500. Let n be m - 50.` Valid<br>
`Let m be 500.Let n be m - 50.` Error

### Comments
To add a comment, start the line with `COMMENT:` and end it with a period as usual. The rest of the sentence will be ignored by the interpreter.

`Let m be 500. COMMENT: insert your comment here. Let n be m - 50.`
