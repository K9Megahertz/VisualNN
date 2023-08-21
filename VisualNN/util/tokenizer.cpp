//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// 
// MIT License
// 
// Copyright(c) 2023 Gerald Filimonov
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Tokenizer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  CTORs/DTORs
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Tokenizer::Tokenizer(std::istream &s, const unsigned long filesize) : stream(s), streamlength(filesize)
{	
	char c;
	stream.get(c);                                        //get first character in the stream
	currentchar = std::string(1, c);	
	m_whitespaceenabled = false;


}

Tokenizer::~Tokenizer() {}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function get_next_token() 
//  Takes the current character index pointer and increments it by one
//  Updates currentchar with the character at the new location
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Token *Tokenizer::getNextToken()
{
	//never should have null in a text file, so keep going unless you find one
	while (currentchar[0] != '\0') {
		
		//skip whitespace if skipping is enabled, otherwise if its disabled return a token saying hey! we found whitespace!
		if (skip_whitespace() && m_whitespaceenabled) {
			return new Token(Token::TokenType::TOKEN_WHITESPACE, " ");
		}

		if (isalpha(currentchar[0]) || currentchar[0] == '_')                          //if character is [A-Z or a-z or 0-9 or '_']
			return parse_id();                                                         //this going to be an ID so grab it all

		if (currentchar[0] == '"')                                                     //if character is a quote
			return parse_string();                                                     //this is going to be a string so grab it all

		if (isdigit(currentchar[0]))                                                   //if character is [0-9 ]
			return parse_number();                                                     //this going to be an number so grab it all


		//otherwise we're looking for something else
		switch (currentchar[0])
		{
		case  '=': return advance_with_token(new Token(Token::TokenType::TOKEN_EQUALS, currentchar)); break;
		case  ';': return advance_with_token(new Token(Token::TokenType::TOKEN_SEMI, currentchar)); break;
		case  '(': return advance_with_token(new Token(Token::TokenType::TOKEN_LPAREN, currentchar)); break;
		case  ')': return advance_with_token(new Token(Token::TokenType::TOKEN_RPAREN, currentchar)); break;
		case  '{': return advance_with_token(new Token(Token::TokenType::TOKEN_LBRACE, currentchar)); break;
		case  '}': return advance_with_token(new Token(Token::TokenType::TOKEN_RBRACE, currentchar)); break;
		case  '[': return advance_with_token(new Token(Token::TokenType::TOKEN_LBRACKET, currentchar)); break;
		case  ']': return advance_with_token(new Token(Token::TokenType::TOKEN_RBRACKET, currentchar)); break;
		case  ':': return advance_with_token(new Token(Token::TokenType::TOKEN_COLON, currentchar)); break;
		case  ',': return advance_with_token(new Token(Token::TokenType::TOKEN_COMMA, currentchar)); break;		
		case '\\': return advance_with_token(new Token(Token::TokenType::TOKEN_BACKWARD_SLASH, currentchar)); break;		
		case  '<': return advance_with_token(new Token(Token::TokenType::TOKEN_LT, currentchar)); break;
		case  '>': return advance_with_token(new Token(Token::TokenType::TOKEN_GT, currentchar)); break;
		case  '/': return advance_with_token(new Token(Token::TokenType::TOKEN_FORWARD_SLASH, currentchar)); break;
		case  '*': return advance_with_token(new Token(Token::TokenType::TOKEN_ASTERISK, currentchar)); break;
		case  '-': return advance_with_token(new Token(Token::TokenType::TOKEN_MINUS, currentchar)); break;
		case  '+': return advance_with_token(new Token(Token::TokenType::TOKEN_PLUS, currentchar)); break;		
		case  '~': return advance_with_token(new Token(Token::TokenType::TOKEN_TILDE, currentchar)); break;
		case  '!': return advance_with_token(new Token(Token::TokenType::TOKEN_EXCLAMATION_MARK, currentchar)); break;
		case  '@': return advance_with_token(new Token(Token::TokenType::TOKEN_AT, currentchar)); break;
		case  '#': return advance_with_token(new Token(Token::TokenType::TOKEN_POUND, currentchar)); break;
		case  '$': return advance_with_token(new Token(Token::TokenType::TOKEN_DOLLAR, currentchar)); break;
		case  '%': return advance_with_token(new Token(Token::TokenType::TOKEN_PERCENT, currentchar)); break;
		case  '^': return advance_with_token(new Token(Token::TokenType::TOKEN_CARET, currentchar)); break;
		case  '&': return advance_with_token(new Token(Token::TokenType::TOKEN_AMPERSAND, currentchar)); break;
		case  '.': return advance_with_token(new Token(Token::TokenType::TOKEN_PERIOD, currentchar)); break;		
		case  '?': return advance_with_token(new Token(Token::TokenType::TOKEN_QUESTION_MARK, currentchar)); break;
		case  '`': return advance_with_token(new Token(Token::TokenType::TOKEN_BACKTICK, currentchar)); break;
		case '\'': return advance_with_token(new Token(Token::TokenType::TOKEN_SINGLE_QUOTE, currentchar)); break;
		case  '|': return advance_with_token(new Token(Token::TokenType::TOKEN_PIPE, currentchar)); break;
		case '\0': break;
		default: { printf("Unexpected character found %s\n", currentchar.c_str()); exit(1); }

		}
	}	

	return new Token(Token::TokenType::TOKEN_EOF, currentchar);                   // must have hit the end of the file, so return EOF Token

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function advance()
// 
// 
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Tokenizer::advance() {	

	if (currentchar[0] != '\0' && cursorpos < streamlength) {                   //make sure were not past the end of the file
		cursorpos++;                                                            //increment the index
		stream.get(currentchar[0]);                                             //get next character in the stream
	}
	else {
		currentchar = '\0';
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function skip_whitespace()
// 
// 
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Tokenizer::skip_whitespace() {

	bool skipped = false;
	while (currentchar[0] == ' ' || currentchar[0] == 10 || currentchar[0] == 13 || currentchar[0] == '\t') {   //skip any whitespace characters
		advance();                                                                     //advance to next character		
		skipped = true;
	}
	return skipped;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function advance_with_token()
//  Advance tokenizer and return token to make simple case code in get_next_token()
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Token* Tokenizer::advance_with_token(Token* token) {
	advance();                                                                         //advance to the next character
	return token;                                                                      //return the same token we passed in
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function parse_id()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Token* Tokenizer::parse_id() {


	std::string s;
	while (isalnum(currentchar[0]) || currentchar[0] == '_')                              // keep going so long as we have alphanumeric characters and/or underscores
	{
		s += currentchar;                                                                 //add character to string
		advance();                                                                        //advance to the next character
	}
	return new Token(Token::TokenType::TOKEN_ID, s);                                      //return the token

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function parse_string()
//  
//  
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Token* Tokenizer::parse_string() {

	advance();                                                                            //advance one character past the first quote
	std::string s;
	while (currentchar[0] != '"')                                                         //keep going till we find another quote
	{
		s += currentchar[0];		                                                      //add character to string
		advance();                                                                        //advance to next character
	}
	advance();                                                                            //advance one character past the end of the final quote

	return new Token(Token::TokenType::TOKEN_STRING, s.c_str());                          //return the token

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function parse_number()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Token* Tokenizer::parse_number() {

	std::string s;
	while (isdigit(currentchar[0]))                                                  // keep going so long as we have a digit
	{
		s += currentchar[0];                                                            //add character to string
		advance();                                                                        //advance to the next character
	}

	return new Token(Token::TokenType::TOKEN_INT, s);                                     //return the token

}


void Tokenizer::EnableWhitespace()
{
	m_whitespaceenabled = true;

}

void Tokenizer::DisableWhitespace()
{
	m_whitespaceenabled = false;

}
