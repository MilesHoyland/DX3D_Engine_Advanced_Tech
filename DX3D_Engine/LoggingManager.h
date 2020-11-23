#pragma once
#include <Windows.h>						// standard Windows stuff

// c++ includes
#include <atomic>							// atomic objects (no data races) 
#include <thread>							// individual threats
#include <mutex>							// lockable objects
#include <iostream>							// input and output streams
#include <sstream>							// string streams
#include <fstream>							// file streams
#include <vector>							// vector containers
#include <map>								// map containers


// virtual abstract class - interface to open and close streams (and to write to them)
class LogPolicyInterface
{
public:
	virtual ~LogPolicyInterface() noexcept = default;

	virtual bool openOutputStream(const std::wstring& name) = 0;
	virtual void closeOutputStream() = 0;
	virtual void write(const std::string& msg) = 0;
};

// implementation of a policy to write to a file on the hard drive
class FileLogPolicy : public LogPolicyInterface
{
private:
	std::ofstream outputStream;

public:
	FileLogPolicy() : outputStream() {};
	~FileLogPolicy() { };

	bool openOutputStream(const std::wstring& filename) override;
	void closeOutputStream() override;
	void write(const std::string& msg) override;
};

enum SeverityType
{
	info = 0,
	debug,
	warning,
	error,
};

class LoggingManager
{
};


