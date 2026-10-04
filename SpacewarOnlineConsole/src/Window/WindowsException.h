#pragma once
#include <exception>
#include <string>
#include <sstream>
#include <windows.h>

// Define a new exception class that
// inherits from std::exception
class WindowsException : public std::exception {

private:
    std::string _errorMessage;
    DWORD _errorCode;

public:

    WindowsException(const char* msg)
    {
        //retrieve windows error message from last error code
        LPVOID pWindowsErrorMessage;
        _errorCode = GetLastError();
        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            _errorCode,
            MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
            (LPSTR)&pWindowsErrorMessage,
            0, NULL);

        //set error message to both exception message and windows error message
        std::stringstream ss{};
        ss << msg << " - " << (LPSTR)pWindowsErrorMessage;
        _errorMessage = std::string(std::istreambuf_iterator<char>(ss), {});
        LocalFree(pWindowsErrorMessage);
    }

    inline const char* what() const noexcept {
        return _errorMessage.c_str();
    }

    inline const DWORD GetErrorCode() {
        return _errorCode;
    }
};

#define WINDOWS_THROW_IF_FAILED(X, msg)  if (X==FALSE) throw WindowsException(#msg)