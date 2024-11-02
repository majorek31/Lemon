#include "pch.h"
#include "Platform/Windows/WindowsWindow.h"
namespace Lemon 
{
	Window* Window::Create()
	{
		return new WindowsWindow();
	}
}