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

#include "NeuralNetworkFileReader.h"

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



NeuralNetworkFileReader::NeuralNetworkFileReader()
{		
	m_currenttoken = nullptr;
	m_tokenizer = nullptr;
}

NeuralNetworkFileReader::~NeuralNetworkFileReader()
{	
	if (m_currenttoken) {
		delete m_currenttoken;
		m_currenttoken = nullptr;
	}
	if (m_tokenizer) {
		delete m_tokenizer;
		m_tokenizer = nullptr;
	}
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function readNeuralNetworkFile()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NeuralNetworkFileReader::readNeuralNetworkFile(NeuralNet& nn, std::string filename)
{
	std::ifstream file;

	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "Reading in map file: " + filename);
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");

	//does the file exist?
	if (std::filesystem::exists(filename))
	{
		//open the source file
		file.open(filename);

		//did the file open sucessfully?
		if (file.is_open()) 		{

			//get the file size, internet cant agree on whether this is legit or not, seems to be working so far
			file.seekg(0, std::ios::end);
			unsigned long filesize = (unsigned long)file.tellg();			
			file.seekg(0, std::ios::beg);

			//create a tokenizer
			m_tokenizer = new Tokenizer(file, filesize);	

			//prime the first token
			m_currenttoken = m_tokenizer->getNextToken();

			Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "****************************************");
			Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "* Reading in Neural Network Definition *");
			Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "****************************************");
			Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");

			//loop through all the tokens
			while (!isCurrentTokenType(Token::TokenType::TOKEN_EOF))
			{
				if (isCurrentTokenType(Token::TokenType::TOKEN_LBRACE))
				{                                                                      
					Logger::Append(Logger::LogLevel::LOGLEVEL_DEBUG, "Reading in Layer");
					Layer l;
					readLayer(l);
					nn.m_layers.push_back(l);                                    
					
				}
				else
				{
					//something's jacked up
					std::cout << "Unexpected token: " << m_currenttoken->m_contents << " , was expecting { indicating start of layer definition" << std::endl;
					system("pause");
					exit(1);
				}
			}

			Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "Read in " + std::to_string(nn.m_layers.size()) + " Layers");
			Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");
			Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");
			

			//cleanup
			if (m_currenttoken) {
				delete m_currenttoken;
				m_currenttoken = nullptr;
			}
			
			if (m_tokenizer) {
				delete m_tokenizer;
				m_tokenizer = nullptr;
			}
			

			//close the file
			file.close();

			return true;
		}
		//TODO: file didnt open error out
		Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "ERROR: Failed to open file");
		return false;
		
	}
	//TODO: file didnt exist error out
	Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "ERROR: File does not exist");
	return false;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function readLayer()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int NeuralNetworkFileReader::readLayer(Layer& layer) {

	eattoken(Token::TokenType::TOKEN_LBRACE);

	//keep going until the end of the layer
	while (!isCurrentTokenType(Token::TokenType::TOKEN_RBRACE))
	{
		//is this the start of a brush definition?
		if (isCurrentTokenType(Token::TokenType::TOKEN_LBRACE))
		{
			Neuron newneuron;
			Logger::Append(Logger::LogLevel::LOGLEVEL_DEBUG, "Reading in Neuron");
			readNeuron(newneuron);
			layer.m_neurons.push_back(newneuron);			
		}		
		else
		{
			if (isCurrentTokenType(Token::TokenType::TOKEN_EOF)) {                       //did we hit end of file?
				std::cout << "Unexpected token: End of File =(" << std::endl;            //yep
			}
			else {                                                                       //something is jacked
				std::cout << "Unexpected token: " << m_currenttoken->m_contents << " , was expecting {" << std::endl;
			}
			system("pause");
			exit(1);
		}
	}

	eattoken(Token::TokenType::TOKEN_RBRACE);

	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function readNeuron()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int NeuralNetworkFileReader::readNeuron(Neuron& neuron) {

	eattoken(Token::TokenType::TOKEN_LBRACE);
	//keep going until the end of the Neuron

	double weight;
	//keep going until the end of the layer
	while (!isCurrentTokenType(Token::TokenType::TOKEN_RBRACE)) {		
		readSignedDouble(weight);
		Logger::Append(Logger::LogLevel::LOGLEVEL_DEBUG, "Read in Signed Double: " + std::to_string(weight));
		neuron.m_weights.push_back(weight);
	}
	eattoken(Token::TokenType::TOKEN_RBRACE);
	return 0;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function readSignedInt()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int NeuralNetworkFileReader::readSignedInt(int& value) {

	bool negative = false;
	
	if (isCurrentTokenType(Token::TokenType::TOKEN_MINUS))        //does the number start with a negative sign?
	{		
		negative = true;
		eattoken(Token::TokenType::TOKEN_MINUS);
	}

	if (isCurrentTokenType(Token::TokenType::TOKEN_INT))             //is it a number next?
	{
		value = std::stoi(m_currenttoken->m_contents);            //get first point X value
		if (negative) {                                                         //if its negative flip the bit
			value *= -1;
		}
		eattoken(Token::TokenType::TOKEN_INT);
	}

	return true;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function readSignedFloat()
//
//  TODO: redo this to be more robust with 1.0 vs 1 vs 1.0f etc..
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int NeuralNetworkFileReader::readSignedFloat(float& value) {

	std::string intpart;
	std::string fracpart;

	bool negative = false;	
	
	if (isCurrentTokenType(Token::TokenType::TOKEN_MINUS))        //does the number start with a negative sign?
	{
		eattoken(Token::TokenType::TOKEN_MINUS);
		negative = true;                                          //later on well check to see if this flag is set because the number has a - sign in front of it
	}

	//handle first part of floating point number
	intpart = m_currenttoken->m_contents;
	eattoken(Token::TokenType::TOKEN_INT);	
	
	//handle the dot in the middle
	eattoken(Token::TokenType::TOKEN_PERIOD);
	
	//handle second part of floating point number
	fracpart = m_currenttoken->m_contents;
	eattoken(Token::TokenType::TOKEN_INT);

	//if the negative flag is set, then return the number negated, otherwise return just the number
	value = std::stof(intpart + "." + fracpart);

	//numerically negate the number
	if (negative)
		value *= -1;	

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function readSignedDouble()
//
//  TODO: redo this to be more robust with 1.0 vs 1 vs 1.0f etc..
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int NeuralNetworkFileReader::readSignedDouble(double& value) {

	std::string intpart;
	std::string fracpart;

	bool negative = false;

	if (isCurrentTokenType(Token::TokenType::TOKEN_MINUS))        //does the number start with a negative sign?
	{
		eattoken(Token::TokenType::TOKEN_MINUS);
		negative = true;                                          //later on well check to see if this flag is set because the number has a - sign in front of it
	}

	//handle first part of floating point number
	intpart = m_currenttoken->m_contents;
	eattoken(Token::TokenType::TOKEN_INT);

	//handle the dot in the middle
	eattoken(Token::TokenType::TOKEN_PERIOD);

	//handle second part of floating point number
	fracpart = m_currenttoken->m_contents;
	eattoken(Token::TokenType::TOKEN_INT);

	//if the negative flag is set, then return the number negated, otherwise return just the number
	value = std::stod(intpart + "." + fracpart);

	//numerically negate the number
	if (negative)
		value *= -1;

	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function readString()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int NeuralNetworkFileReader::readString(std::string& value) {	

	value = m_currenttoken->m_contents;	                                   //get the string out of the current token
	eattoken(Token::TokenType::TOKEN_STRING);                              //dont need anymore, so delete
	return true;                                                           //yay!

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function isCurrentTokenType()
//  
//  Checks if the current token is the same as the expected one we passed in 
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NeuralNetworkFileReader::isCurrentTokenType(Token::TokenType tokentype)
{
	if (m_currenttoken->m_type == tokentype)	
		return true;                          //yes	
	return false;                             //no
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function eattoken()
//
// Checks if the current token matches the one we want to eat. 
// If it doesn't, we've hit an unexpected token, print out the details and bail.
// If it does, delete the current token to free up the memory and get the next token.//  
// Passing in a NULL token skips the test and just eats the token no matter what
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NeuralNetworkFileReader::eattoken(Token::TokenType tokentype)
{
	//if we passed null, we just want to eat any token, so skip the error checking
	if (tokentype != Token::TokenType::TOKEN_NULL)
	{
		//is the token we think we're eating the one we are actually eating?
		if (m_currenttoken->m_type != tokentype)
		{   //no
			std::cout << "Unexpected token: " << Token::toString(m_currenttoken->m_type) << " , was expecting " << Token::toString(tokentype) << std::endl;
			system("pause");
			exit(1);
		}
	}

	//delete the token and advance to the next one
	delete m_currenttoken;
	m_currenttoken = m_tokenizer->getNextToken();

}


