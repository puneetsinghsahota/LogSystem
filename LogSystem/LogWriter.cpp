#include <ctime>
#include <chrono>
#include <iostream>
#include <Windows.h>
#include <strsafe.h>
#include <sstream>
#include "LogWriter.h"

void LogWriter::Write(std::string msg)
{
	_logger.logger_Write(msg);
}

void LogWriter::DebuggerOutput(std::string msg)
{
	msg = AddTimeStamp(msg);
	_logger.logger_DebuggerOutput(msg);
}

void LogWriter::ConsoleOutput(std::string msg)
{
	msg = AddTimeStamp(msg);
	_logger.logger_ConsoleOutput(msg);
}

void LogWriter::InstantiateLogger(std::string path)
{

	_lockThis.lock(); /// To restrict Number of Instance to only one 
	if (!_logger._isLogger_instantiated)
	{
		_logger.logger_SetLogPath(path);
		_logger._isLogger_instantiated = true;
	}
	_lockThis.unlock();

}

void LogWriter::FileOutput(std::string msg)
{
	msg = AddTimeStamp(msg);
	_logger.logger_FileOutput(msg);
}


LogWriter::LogWriter()
{
	_isLogger_instantiated = false;
	_logger_name = "Log";
}

LogWriter::~LogWriter()
{
}

void LogWriter::logger_SetLogPath(std::string path)
{
	_logPath = path;
	_logger_file.open(_logPath, std::ios_base::app);
}

void LogWriter::logger_Write(std::string msg)
{
	msg = AddTimeStamp(msg);
	_logger.logger_DebuggerOutput(msg);
	_logger.logger_FileOutput(msg);
	_logger.logger_ConsoleOutput(msg);
}

void LogWriter::logger_FileOutput(std::string msg)
{
	_logger_file << msg;
}

void LogWriter::logger_DebuggerOutput(std::string msg)
{
	msg = msg + "\n";
	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, msg.c_str(), -1, NULL, 0);
	wchar_t* log_msg = new wchar_t[wchars_num];
	MultiByteToWideChar(CP_UTF8, 0, msg.c_str(), -1, log_msg, wchars_num);
	OutputDebugString(log_msg);
}

void LogWriter::logger_ConsoleOutput(std::string msg)
{
	std::cout << msg;
}

std::string LogWriter::AddTimeStamp(std::string msg)
{
	//counts milli seconds
	auto now_ms = std::chrono::system_clock::now();
	auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now_ms);
	auto fraction = now_ms - seconds;
	std::time_t cnow = std::chrono::system_clock::to_time_t(now_ms);
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(fraction);

	//counts rest of the time stamp
	std::time_t t = std::time(0);  
	std::tm* now = std::localtime(&t);
	int year = (now->tm_year + 1990);
	int month = (now->tm_mon + 1);
	int date = now->tm_mday;
	int hour = now->tm_hour;
	int minute = now->tm_min;
	int second = now->tm_sec;
	long long milliseconds = ms.count();

	//forms final message
	std::string time_stamp ="\n " + std::to_string(date) + "/" + std::to_string(month) + "/" + std::to_string(year) + ","
		+ std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second) + ":" 
		+ "\"" + std::to_string(milliseconds) + "\"" + ", ";
	
	msg = time_stamp + msg;

	return msg;
}
