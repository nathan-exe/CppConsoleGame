#pragma once
class Window
{
public :
	void Update();

	//inputs
	inline bool IsKeyHeld();

	//display
	void BeginFrame();
	void SetChar(int x, int y);
	void EndFrame();
};

