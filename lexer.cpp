#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <map>
#include <regex>

#include "lexer.hpp"

using lexer::TokenType;

const std::string LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string NUMBERS = "0123456789";

std::map<std::vector<std::string>, int> lexer::multiWordKeywords;

void lexer::init() {
	for (std::pair<std::string, int> kwd : lexer::KEYWORDS) {
		std::vector<std::string> split;
		std::string cur = "";
		for (char c : kwd.first) {
			if (c == ' ') {
				split.push_back(cur);
				cur = "";
				continue;
			}
			cur += c;
		}
		if (cur != "")
			split.push_back(cur);
		if (split.size() > 1)
			lexer::multiWordKeywords.insert({ split, kwd.second });
	}
}

bool is_letter(char c) {
	for (char letter : LETTERS) {
		if (c == letter)
			return true;
	}
	return false;
}
bool is_number(char c) {
	for (char number : NUMBERS) {
		if (c == number)
			return true;
	}
	return false;
}

int get_keyword(std::string token) {
	auto out = lexer::KEYWORDS.find(token);
	if (out == lexer::KEYWORDS.end())
		return -1;
	return out->second;
}

std::string scan(std::string file, int *index, std::function<bool(std::string, int)> valid) {
	std::string ret(1, file[(*index)++]);
	for (; (*index) < file.size(); (*index)++) {
		if (!valid(file, *index)) {
			(*index)--;
			return ret;
		}
		ret += file[*index];
	}
	(*index)--;
	return ret;
}

std::string lexer::type_to_string(int type) {
	return lexer::TOKEN_NAME[type];
}
void lexer::lex(std::string text, std::vector<lexer::Token> &output) {
	int curSentence = 1;
	bool isComment = false;
	for (int i = 0; i < text.size(); i++) {
		if (text.substr(i, 8) == "COMMENT:")
			isComment = true;

		char c = text[i];
		std::string token = "";

		if (c == '.' && (i == text.size() - 1 || text[i + 1] == ' ' || text[i + 1] == '\n')) {
			if (!isComment) {
				output.push_back({ PERIOD, curSentence, "." });
				curSentence++;
			}
			isComment = false;
		}
		else if (!isComment) {
			if (is_letter(c)) {
				std::string token = scan(text, &i, [](std::string string, int index) {
					return is_letter(string[index]) || is_number(string[index]);
				});
				int keyword = get_keyword(token);
				if (keyword == -1)
					output.push_back({ IDENTIFIER, curSentence, token });
				else
					output.push_back({ keyword, curSentence, token });
			}
			else if (is_number(c)) {
				std::string token = scan(text, &i, [](std::string string, int index) {
					return is_number(string[index]) || (string[index] == '.' && index < string.size() && is_number(string[index + 1]));
				});
				bool isFloat = false;
				for (char ch : token) {
					if (ch == '.') {
						isFloat = true;
						break;
					}
				}
				if (isFloat)
					output.push_back({ FLOAT_LIT, curSentence, token });
				else
					output.push_back({ INT_LIT, curSentence, token });
			}
			else if (c == '"') {
				bool isClosed = false;
				std::string ret = "\"";
				i++;
				for (; i < text.size(); i++) {
					ret += text[i];
					if (text[i] == '"' && (i == 0 || text[i - 1] != '\\')) {
						isClosed = true;
						break;
					}
				}
				if (!isClosed)
					throw std::invalid_argument("unclosed string literal");
				output.push_back({ STR_LIT, curSentence, ret });
			}
			else if (c == '\'') {
				if (text[i + 2] == '\'') {
					std::string ret(1, text[++i]);
					ret = "'" + ret + "'";
					output.push_back({ CHAR_LIT, curSentence, ret });
					i++;
				}
				else if (text[i + 1] == '\\' && text[i + 3] == '\'') {
					std::string ret = "'\\";
					// copied from https://stackoverflow.com/a/22185359
					switch (text[i + 2]) {
						case '\\': ret += "\\"; break;
						case '\"': ret += "\""; break;
						case '\'': ret += "'"; break;
						case '?': ret += "?"; break;
						case 'a': ret += "a"; break;
						case 'b': ret += "b"; break;
						case 'f': ret += "f"; break;
						case 'n': ret += "n"; break;
						case 'r': ret += "r"; break;
						case 't': ret += "t"; break;
						case 'v': ret += "v"; break;
						case '0': ret += "0"; break;
					}
					ret += "'";
					output.push_back({ CHAR_LIT, curSentence, ret });
					i += 3;
				}
				else
					throw std::invalid_argument("unclosed character");
			}
			else {
				std::string ret(1, c);
				if (c == ',')
					output.push_back({ COMMA, curSentence, ret });
				else if (c == '(')
					output.push_back({ LPAR, curSentence, ret });
				else if (c == ')')
					output.push_back({ RPAR, curSentence, ret });
				else if (c == '+')
					output.push_back({ ADD, curSentence, ret });
				else if (c == '-') {
					if (i < text.size() - 1 && text[i + 1] == '>') {
						output.push_back({ ARROW, curSentence, ret + ">" });
					}
					else
						output.push_back({ SUBTRACT, curSentence, ret });
				}
				else if (c == '*')
					output.push_back({ MULTIPLY, curSentence, ret });
				else if (c == '/')
					output.push_back({ DIVIDE, curSentence, ret });
				else if (c == '=')
					output.push_back({ EQUAL, curSentence, ret });
			}
		}
	}

	// for (int i = 0; i < output.size(); i++) {
	// 	if (i < output.size() - 1 && output[i].token == "For" && output[i + 1].token == "each") {
	// 		output[i] = { KEYWD, output[i].sentence, "For each" };
	// 		output.erase(std::next(output.begin(), i + 1));
	// 		i--;
	// 	}
	// 	if (i < output.size() - 4 && output[i].token == "be" && output[i + 1].token == "the"
	// 		&& output[i + 2].token == "function" && output[i + 3].token == "defined" && output[i + 4].token == "for") {

	// 		output[i] = { BTFDF, output[i].sentence, "be the function defined for" };
	// 		output.erase(std::next(output.begin(), i + 1), std::next(output.begin(), i + 5));
	// 		i -= 4;
	// 	}
	// 	if (i < output.size() - 2 && output[i].token == "and" && output[i + 1].token == "defined" && output[i + 2].token == "by") {
	// 		output[i] = { ADB, output[i].sentence, "and defined by" };
	// 		output.erase(std::next(output.begin(), i + 1), std::next(output.begin(), i + 3));
	// 		i -= 2;
	// 	}
	// }
}