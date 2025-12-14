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
    std::string input;
    size_t position = 0;

    Token bufferedToken{};
    bool hasBufferedToken = false;

    void skipWhitespace() {
	while (position < input.size() && std::isspace(static_cast<unsigned char>(input[position]))) {
		position++;
	}
    }


    Token readNextToken(){
	skipWhitespace();

	if (position >= input.size()) {
	   return {TokenType::END, 0};
	}

	char currentChar = input[position];

	if (std::isdigit(static_cast<unsigned char>(currentChar))) {
	    long long number = 0;

 	    while (position < input.size() &&
		   std::isdigit(static_cast<unsigned char>(input[position]))) {
		int digit = input[position] - '0';

	 	if (number > (std::numerical_limits<long long>::max() - digit) / 10) {
			throw std::runtime_error("integer overflow");
		}
		
		number = number * 10 + digit;
		position++;
	}
	
	return {TokenType::INT, number};
    }

    position++;
    switch (currentChar){
	case '+': return {TokenType::PLUS, 0};
	case '-': return {TokenType::MINUS, 0};
	case '*': return {TokenType::MUL, 0};
	case '/': return {TokenType::DIV, 0};
	case '(': return {TokenType::LPAREN, 0};
	case ')': return {TokenType::RPAREN, 0};
	default: return {TokenType::BAD, 0};
    }
  }
};


