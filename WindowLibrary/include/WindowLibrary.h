#pragma once
#include <windows.h>
#include <unordered_set>
#include <string>
#include <sstream>


/// <summary>
/// Static Library definining interaction with and display onto the Console Window
/// </summary>
namespace WindowLibrary {

	class KeyboardInputData
	{

	public:
		KeyboardInputData() = default;

		void SetKeyStatus(char key, bool pressed);
		inline bool IsKeyHeld(const char key) const { return _heldKeys.contains(key); };
	private:
		std::unordered_set<char> _heldKeys{};

	};


	class ConsoleWindow
	{
	private:

		//screen info
		COORD _bufferSize;
		SMALL_RECT _bufferWriteRegion;

		//screen buffer
		CHAR_INFO* _buffer;

		//console handle
		HANDLE _consoleOutputHandle;
		HANDLE _consoleInputHandle;
		HWND _consoleWindowHandle;

		KeyboardInputData _inputs;

		DWORD _startInputMode;
	public:
		ConsoleWindow();
		~ConsoleWindow();

		void ResetInputMode();

		void Update();

		//display
		void Clear();
		void Blit(CHAR_INFO* background);
		void SetChar(int x, int y, CHAR_INFO caracterInfo);
		void EndFrame();

		inline bool ContainsPoint(int x, int y) const { return x >= 0 && y >= 0 && x < _bufferSize.X && y < _bufferSize.Y; }


		//getters
		inline const KeyboardInputData* const GetInputs() const { return &_inputs; }
		inline COORD GetBufferSize() const { return _bufferSize; }
	};

	/// <summary>
	/// An exception that gets thrown when a windows function fails.
	/// </summary>
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
}

