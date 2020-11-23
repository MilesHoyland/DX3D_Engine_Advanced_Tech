#include <Shlobj.h>
#include <Shlwapi.h>
#include <Pathcch.h>
#include "Logger.h"
#include "ServiceLocator.h"

// DLLs /////////////////////////////////////////////////////////////////////////////////
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Pathcch.lib")
namespace util
{

	// FUNCTIONS ////////////////////////////////////////////////////////////////////////
	// the openOutputStream function opens a file on the hard drive and sets the output precision
	bool FileLogPolicy::openOutputStream(const std::wstring& filename)
	{
		PWSTR docPath = NULL;
		HRESULT hr = SHGetKnownFolderPath(FOLDERID_Desktop, NULL, NULL, &docPath);

		// debug mode only: make sure the operation succeeded
#ifndef NDEBUG
		if (FAILED(hr))
			return false;
#endif

		// append custom folder to path
		std::wstringstream path;
		path << docPath << L"\\DX3D_Engine\\logs\\";

		// delete the wstring pointer to avoid memory leak
		::CoTaskMemFree(static_cast<void*>(docPath));

		// create directory (if it does not exist)
		hr = SHCreateDirectory(NULL, path.str().c_str());

		// debug mode only: make sure the operator succeeded
#ifndef NDEBUG
		if (FAILED(hr))
			return false;
#endif

		// append file name to path
		path << filename.c_str();

		// try to open the file
		outputStream.open(path.str().c_str(), std::ios_base::binary | std::ios_base::out);

		// debug mode only: make sure the file is opened
#ifndef NDEBUG
		if (!outputStream.is_open())
			return false;
#endif
		// set output precision
		outputStream.precision(20);

		// return success
		return true;
	}

	// the closeOutputStream function closes the file on the hard drive
	void FileLogPolicy::closeOutputStream()
	{
		outputStream.close();
	}

	// the write functions writes a message :)
	void FileLogPolicy::write(const std::string& msg)
	{
		// add the message to the stream
		outputStream << msg << std::endl;
	}
}