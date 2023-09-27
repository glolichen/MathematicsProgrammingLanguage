#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <gmpxx.h>
#include "lexer.hpp"

namespace parser {
	class Literal {};
	class Expression {};
	class Statement {};

	class StrLit : public Literal {
	public:
		std::string value;
		StrLit(std::string value) {
			this->value = value;
		}
	};

	class IntLit : public Literal {
	public:
		mpz_class value;
		IntLit(mpz_class value) {
			this->value = value;
		}
	};

	class RatLit : public Literal {
	public:
		mpq_class value;
		RatLit(mpq_class value) {
			this->value = value;
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

	class FuncCall : Expression {
	public:
		lexer::Token function;
		std::vector<lexer::Token> params;
		FuncCall(lexer::Token function, std::vector<lexer::Token> params) {
			this->function = function;
			this->params = params;
		}
	};

	class FuncDef : public Statement {
	public:
		lexer::Token name;
		std::vector<lexer::Token> paramTypes, params;
		lexer::Token returnType;
		Expression expr;
		FuncDef(lexer::Token name, std::vector<lexer::Token> paramTypes, 
				std::vector<lexer::Token> params, lexer::Token returnType, Expression expr) {
			this->name = name;
			this->paramTypes = paramTypes;
			this->params = params;
			this->returnType = returnType;
			this->expr = expr;
		}
	};

	class Goto : public Statement {
	public:
		int sentence;
		Goto(int sentence) {
			this->sentence = sentence;
		}
	};

	class GotoIf : public Statement {
	public:
		int sentence;
		Expression condition;
		GotoIf(int sentence, Expression condition) {
			this->sentence = sentence;
			this->condition = condition;
		}
	};

	void parse(std::vector<lexer::Token> &tokens);
}

#endif