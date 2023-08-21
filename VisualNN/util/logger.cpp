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

#include "Logger.h"

std::ofstream Logger::file;
Logger::LogLevel Logger::m_currentloglevel = Logger::LogLevel::LOGLEVEL_DEBUG;



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

Logger::Logger()
{	

}

Logger::~Logger()
{
	file.close();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Append()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logger::Append(Logger::LogLevel ll, std::string message)
{
	
	if (m_currentloglevel >= ll) {
		time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		file << "[" << std::put_time(localtime(&now), "%F %T : ") << LogLevelAsString(ll) << "] " << message.c_str() << std::endl;
		std::cout << "[" << std::put_time(localtime(&now), "%F %T : ") << LogLevelAsString(ll) << "] " << message.c_str() << std::endl;
	}


}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Start()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Logger::Start(std::string filename)
{
	//TODO: Error handling
	file.open(filename);

	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "*********************************");
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "*        Logging Sarted         *");
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "*********************************");
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function SetLogLevel()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logger::SetLogLevel(Logger::LogLevel ll)
{
	m_currentloglevel = ll;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function LogLevelAsString()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string Logger::LogLevelAsString(Logger::LogLevel ll)
{

	switch (ll) {

	case Logger::LogLevel::LOGLEVEL_INFO:
		return "INFO";
		break;
	case Logger::LogLevel::LOGLEVEL_DEBUG:
		return "DEBUG";
		break;
	case Logger::LogLevel::LOGLEVEL_ERROR:
		return "ERROR";
		break;
	case Logger::LogLevel::LOGLEVEL_WARNING:
		return "WARNING";
		break;
	default:
		return "UNKNOWN";
		break;

	}
}

