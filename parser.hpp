#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "lexer.hpp"

namespace Parser {
	class Literal {};
	class Expression {};

	class String : public Literal {
	public:
		std::string literal;
		String(std::string literal) {
			this->literal = literal;
		}
	};

	class Binary : public Expression {
	public:
		Expression left, right;
		lexer::Token operation;
		Binary(Expression left, lexer::Token operation, Expression right) {
			this->left = left;
			this->operation = operation;
			this->right = right;
		}
	};

	class Assign : public Expression {
	public:
		lexer::Token name;
		Expression value;
		Assign(lexer::Token name, Expression value) {
			this->name = name;
			this->value = value;
		}
	};

	class Group : public Expression {
	public:
		Expression expr;
		Group(Expression expr) {
			this->expr = expr;
		}
	};

	class Unary : public Expression {
	public:
		lexer::Token operation;
		Expression operand;
		Unary(lexer::Token operation, Expression operand) {
			this->operation = operation;
			this->operand = operand;
		}
	};

	class LiteralExpr : public Expression {
	public:
		Literal value;
		LiteralExpr(Literal value) {
			this->value = value;
		}
	};

	class Goto : Expression {
	public:
		int sentence;
		Goto(int sentence) {
			this->sentence = sentence;
		}
	};

	class GotoIf : Expression {
	public:
		int sentence;
		Expression condition;
		GotoIf(int sentence, Expression condition) {
			this->sentence = sentence;
			this->condition = condition;
		}
	};
}

#endif