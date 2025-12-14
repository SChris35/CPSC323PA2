//Chris Saran
//Main.cpp file

#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <limits>


enum class TokenType{
	INT, PLUS, MINUS, MUL, DIV, LPAREN, RPAREN, END, BAD
};

  struct Token {
	TokenType type = TokenType::BAD;
	long long value = 0; 
  };

// LEXER

  class Lexer {
  public:
	explicit Lexer(std::string inputString)
	  : input(std::move(inputString)) {}

	Token peekToken(){
	   if (!hasBufferedToken){
	      bufferedToken = readNextToken();
	      hasBufferedToken = true;
	   }
	   return bufferedToken;
	}
	
	Token getToken() {
	   Token x = peekToken();
	   hasBufferedToken = false;
	   return x;
	}

private:
