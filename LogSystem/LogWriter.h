#pragma once
#include <string>
#include <fstream>
#include <mutex>


/**
	Written by © puneetsinghsahota@gmail.com FOR General Use in Logging or Profiling A System

	LogWriter
	--------

	A log Writer Class is a SingleTon Class --  Which is used to write Logs in below given forms : 
	The Console Screen, Debug Output Screen, File
*/
class LogWriter
{
private:
	bool _isLogger_instantiated;

	static std::mutex _lockThis;

	/**
		Singleton Instance of A Logger
	*/
	static LogWriter _logger;

	/**
		MEMBER FUNCTIONS
	*/
	void logger_SetLogPath(std::string path);
	void logger_Write(std::string msg);
	void logger_FileOutput(std::string msg);
	void logger_DebuggerOutput(std::string msg);
	void logger_ConsoleOutput(std::string msg);

	std::ofstream _logger_file;
	std::string _logPath;
	std::string _logger_name;
	/**
		Adds Time Stamp in front of the given Msg
	*/
	static std::string AddTimeStamp(std::string msg);

public:

	/**
		Used to write a Message to Logger 
		It takes in 1 Parameter :- 
			- @param message - msg - std::string - The output which needs to be printed to the Log
	*/
	static void Write(std::string msg);

	/**
		Writes Output on A Debug Output Screen
			- @param message - msg - std::string - The output which needs to be printed to the Log
	*/
	static void DebuggerOutput(std::string msg);

	/**
		Writes an Output on Console Screen
			- @param message - msg - std::string - The output which needs to be printed to the Log
	*/
	static void ConsoleOutput(std::string msg);

	/**
		Instantiates a Logger for the System and Sets Path of the Logger System
			-@param path - std::string - Path to the Log File
	*/
	static void InstantiateLogger(std::string path);

	/**
		Writes an Output To LOGGER FILE ".txt"
			- @param message - msg - std::string - The output which needs to be printed to the Log
	*/
	static void FileOutput(std::string msg);

	LogWriter();
	~LogWriter();
	
};

