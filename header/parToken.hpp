#ifndef __PARTOKEN_HPP__
#define __PARTOKEN_HPP__

#include "Token.hpp"

class ParToken : public Token {
	public:
		ParToken(Token* l, Token* r);
		virtual int execute();
	private:
		Token* left;
		Token* right;
};

#endif
