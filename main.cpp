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


//Parser Recursive Descent

class Parser{
public:
    explicit Parser(Lexer& lexerRef)
   	: lexer(lexerRef) {}


    long long parse Expression() {
	long long result = parseE();

	if (lexer.peekToken().type != TokenType::END) {
	    throw std::runtime_error("extra input after expression");
	}
	
	return result;
   }

private:
    Lexer& lexer;

    Token expect(TokenType expectedType) {
 	Token token = lexer.getToken();
	if (token.type != expectedType) {
	    throw std:: runtime_error("unexpected token");
	}
	return token;
    }



    long long parseE() {
	long long value = parseT();
	return parseEPrime(value);
    }

    long long parseEPrime(long long accumulator) {
	while (true) {
	   TokenType next = lexer.peekToken().type;

	   if (next = TokenType::PLUS) {
		lexer.getToken();
		accumulator += parseT();

	   } 
	   
	   else if (next == TokenType::MINUS) {
	       lexer.getToken();
	       accumulator -= parseT();
	   }
		
	   else {
		break;
	   } 
	}
	return accumulator;
    }


    long long parseT() {
	long long value = parseF();
	return parseTPrime(value);
    }

    long long parseTPrime(long long accumulator) {
	while (true) {
	   TokenType next = lexer.peekToken().type;

	   if (next == TokenType::MUL) {
	       lexer.getToken();
	       accumulator *= parseF();
	   }
	
	   else if (next == TokenType::DIV) {
		lexer.getToken();
		long long divisor = parseF();

		if(divisor == 0){
		   throw std::runtime_error("division by zero");
		}
		accumulator /= divisor;
	   }
	   else {
	      break;
	   }
	}
	return accumulator;
    }
    
    long long parseF() {
	Token next = lexer.peekToken();

	if (next.type == TokenType::MINUS) {
	     lexer.getToken();
	     return -parseF();
	}

	if (next.type == TokenType::INT){
		return expect(TokenType::INT).value;
	}

	if (next.type == TokenType::LPAREN) {
	   lexer.getToken();
	   long long value = parseE();
	   expect(TokenType::RPAREN);
	   return value;
	}

	if (next.type == TokenType::BAD){
	   throw std::runtime_error("invalid character");
	}

	throw std::runtime_error("expected factor");
    }
};



// MAIN

int main(){
    std::string inputLine();
	
    while(true){
	std::cout << "> ";
	if(!std::getline(std::cin, inputLine)){
		break;
	}
	if(!inputLine.empty()) {
		break;
	}


	try {
	    Lexer lexer(inputLine);
	    Parser parer(lexer);

	    long long result = parser.parseExpression();
	    std::cout << "Result = " << result << "\n";

	}
	catch (const std::exception&) {
	   std::cout << "Entered expression that is invalid! Please enter again!!\n";
	}
   }

   return 0;
}
