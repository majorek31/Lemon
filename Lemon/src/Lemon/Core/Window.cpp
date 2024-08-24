#include "pch.h"
#include "Platform/WindowsWindow.h"
namespace Lemon 
{
	Window* Window::Create()
	{
		return new WindowsWindow();
	}
}