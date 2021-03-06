#pragma once

#include "base.h"
#include <list>

class IInputListener
{
public:
	virtual ~IInputListener() {}

public:
	virtual void onMouseMessage(window_type hwnd, E_INPUT_MESSAGE message, int x, int y) = 0;
	virtual void onMouseWheel(window_type hwnd, int zDelta) = 0;
	virtual void onKeyMessage(window_type hwnd, E_INPUT_MESSAGE message, int key) = 0;
};

class CInputReader
{
public:
	CInputReader();
	~CInputReader();

public:
	bool acquire(E_INPUT_DEVICE device);
	bool unacquire(E_INPUT_DEVICE device);
	bool isKeyPressed(uint8_t keycode) const;
	bool isMousePressed(E_MOUSE_BUTTON button) const;

	void addListener(IInputListener* listener)
	{
		ListenerList.push_back(listener);
	}
	void removeListener(IInputListener* listener)
	{
		ListenerList.remove(listener);
	}

#ifdef A_PLATFORM_WIN_DESKTOP
public:
	void filterWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) const;
#endif

private:
	bool ProcessMouse;
	bool ProcessKeyboard;

	using T_ListenerList = std::list<IInputListener*>		;
	T_ListenerList	ListenerList;
};
