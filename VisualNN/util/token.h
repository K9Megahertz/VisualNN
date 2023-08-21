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

#pragma once
#include <string>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Token
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Token
{

public:

	enum class TokenType {
		TOKEN_NULL,		
		TOKEN_WHITESPACE,
		TOKEN_ID,
		TOKEN_EQUALS,
		TOKEN_STRING,
		TOKEN_SEMI,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_LBRACE,
		TOKEN_RBRACE,
		TOKEN_LBRACKET,
		TOKEN_RBRACKET,
		TOKEN_COLON,
		TOKEN_COMMA,		
		TOKEN_FORWARD_SLASH,
		TOKEN_BACKWARD_SLASH,
		TOKEN_POUND,
		TOKEN_LT,
		TOKEN_GT,
		TOKEN_ASTERISK,
		TOKEN_MINUS,
		TOKEN_PLUS,
		TOKEN_EXCLAMATION_MARK,
		TOKEN_PERIOD,
		TOKEN_QUESTION_MARK,
		TOKEN_CARET,
		TOKEN_AT,
		TOKEN_PERCENT,
		TOKEN_AMPERSAND,
		TOKEN_PIPE,
		TOKEN_CHAR,
		TOKEN_INT,
		TOKEN_DOLLAR,		
		TOKEN_TILDE,
		TOKEN_BACKTICK,
		TOKEN_SINGLE_QUOTE,
		TOKEN_EOF
	};

	Token(Token::TokenType type, std::string currentchar);
	Token();
	~Token();

	
	TokenType m_type;
	std::string m_contents;

	static std::string toString(Token::TokenType tt);


};

