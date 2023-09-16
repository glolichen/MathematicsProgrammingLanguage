# Mathematics Programming Language

A really cursed language where you wrote code that looks like mathematical proofs. Inspired by Shakespeare Programming Language

## Variables

Variables must be definied with the syntax:
let variableName be ...

Python -> MPL:

`variable1 = 500`<br>
`let variable1 be 500.`

`variable2 = variable1 * 3`<br>
`let variable2 be variable1 * 3.`

The type of your variable is dynamic, must like python.

## Functions

Functions must be defined for a number of parameters.<br>
The input type and output type must be stated too.<br>
You must define this, even though MPL is weakly typed, because I want to annoy you.<br>
If your parameter is not of that type, you will get an exception.<br>
Functions must return a value and have no side effects. Therefore, MPL is a purely functional language.<br>
And your function must be one expression defined in one sentence, because Mathematics.

```
def add(num1: int, num2: int) -> int:
	return num1 + num2
```

```
let add be the function defined for (integer, integer) -> integer and defined by add(num1, num2) = num1 + num2.
```

## Data types

### Number types
There are three types: integer, rational, real. They are unlimited in size and will use as many bits as it takes.<br>
Oh, and integers can only go in integer, rational numbers can only go in rationals, and only irrational numbers can go in real.<br>
Again, just to make your life miserable because otherwise you'll just define everything as a real number.<br>

### Character types
Because MPL is designed to be inclusive of everyone's cultures, characters will be encoded in Unicode, so it's not just English letters.<br>
To define a character, use the single quotation mark ('c')

Python doesn't have chars, so I will use C to give an example.

`char c = 'a';`<br>
`let c be 'a'.`

### Strings
Doesn't exist, go write your own ~~array~~ list of chars.

### Lists


## Syntax

You know how Java, C, C++, etc require you to put a semicolon to mark the end of a line?<br>
In MPL, you have to use a period (.) to signify the end of your sentence.<br>
If you don't the sentence will continue and you'll probably get an error.<br>
So if you have a super long expression (because your function can only be one sentence), you can make it continue to the next line.