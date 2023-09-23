#ifndef PARSER_H
#define PARSER_H

#include "lexer.hpp"

/*
expression: literal, unary (not), binary (all the other operators), grouping (?)
literal: int, float, char, string
grouping: "(" + expression + ")"


*/

class Expression {};

class Binary : Expression {
public:
	Expression left, right;
	lexer::Token operation;
	Binary(Expression left, lexer::Token operation, Expression right) {
		this->left = left;
		this->operation = operation;
		this->right = right;
	}
};

class Assign : Expression {
public:
	lexer::Token name;
	Expression value;
	Assign(lexer::Token name, Expression value) {
		this->name = name;
		this->value = value;
	}
};

class Group : Expression {
public:
	Expression expr;
	Group(Expression expr) {
		this->expr = expr;
	}
};

class Unary : Expression {
public:
	lexer::Token operation;
	Expression operand;
	Unary(lexer::Token operation, Expression operand) {
		this->operation = operation;
		this->operand = operand;
	}
};

class Assign : Expression {
public:
	lexer::Token name;
	Expression value;
	Assign(lexer::Token name, Expression value) {
		this->name = name;
		this->value = value;
	}
};

class Assign : Expression {
public:
	lexer::Token name;
	Expression value;
	Assign(lexer::Token name, Expression value) {
		this->name = name;
		this->value = value;
	}
};




#endif