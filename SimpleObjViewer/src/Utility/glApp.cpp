#include "glApp.h"

GLApp::GLApp()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool GLApp::CreateWindow(int width, int height, const char* windowName, GLFWmonitor* monitor, GLFWwindow* share)
{
	_width = width;
	_height = height;
	// Window
	_window = glfwCreateWindow(width, height, windowName, monitor, share);
	if (_window == NULL) {
		std::cout << "ERROR [GLApp]: Couldn't create a window!\n";
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(_window);

	// Set window resize event callback
	glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height)->void
	{
		glViewport(0, 0, width, height);
	});

	// Load OpenGL
	gladLoadGL();

	// Setting the viewport
	glViewport(0, 0, width, height);
	return true;
}

GLFWwindow* GLApp::GetWindow()
{
	return _window;
}

void GLApp::Destroy()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

bool GLApp::WindowShouldClose()
{
	return glfwWindowShouldClose(_window) == 1;
}

void GLApp::SwapBuffers()
{
	glfwSwapBuffers(_window);
}

int GLApp::GetWindowWidth()
{
	glfwGetWindowSize(_window, &_width, &_height);
	return _fullscreen ? _monitorWidth : _width;
}

int GLApp::GetWindowHeight()
{
	glfwGetWindowSize(_window, &_width, &_height);
	return _fullscreen ? _monitorHeight : _height;
}

bool GLApp::KeyPress(int key)
{
	if (glfwGetKey(_window, key) == GLFW_PRESS) {
		if (_activeKeys.count(key) < 1)
			_activeKeys.insert(std::pair<int, bool>(key, false));
		_activeKeys[key] = true;
		return true;
	}
	else {
		if (_activeKeys.count(key) < 1)
			_activeKeys.insert(std::pair<int, bool>(key, false));
		_activeKeys[key] = false;
		return false;
	}
}

bool GLApp::KeyPressOnce(int key)
{
	if (glfwGetKey(_window, key) == GLFW_PRESS) {
		if (_activeKeys.count(key) < 1)
			_activeKeys.insert(std::pair<int, bool>(key, false));

		if (!_activeKeys[key]) {
			_activeKeys[key] = true;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (_activeKeys.count(key) < 1)
			_activeKeys.insert(std::pair<int, bool>(key, false));
		_activeKeys[key] = false;
		return false;
	}
}

void GLApp::AllowFullscreen()
{
	_monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode * mode = glfwGetVideoMode(_monitor);
	_monitorWidth = mode->width;
	_monitorHeight = mode->height;
	_allowFullscreen = true;
}

void GLApp::ToggleFullscreen()
{
	if (_fullscreen) {
		glfwSetWindowMonitor(_window, NULL, 0, 0, _width, _height, 0);
		glViewport(0, 0, _width, _height);
	}
	if (!_fullscreen) {
		glfwSetWindowMonitor(_window, _monitor, 0, 0, _monitorWidth, _monitorHeight, 0);
		glViewport(0, 0, _monitorWidth, _monitorHeight);
	}
	_fullscreen = !_fullscreen;
}

void GLApp::PollEvents()
{
	if (KeyPress(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(_window, 1);
	}
	if (_allowFullscreen && KeyPressOnce(GLFW_KEY_F))
	{
		ToggleFullscreen();
	}

	glfwPollEvents();
}
