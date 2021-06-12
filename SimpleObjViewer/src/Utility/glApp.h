#ifndef GL_APP_H
#define GL_APP_H

#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <map>

class GLApp {
protected:
	int _width, _height;
	int _monitorWidth, _monitorHeight;
	bool _fullscreen = false, _allowFullscreen = false;
	GLFWwindow* _window;
	GLFWmonitor* _monitor;
	std::map<int, bool> _activeKeys;
public:
	GLApp();
	bool CreateWindow(int width, int height, const char* windowName, GLFWmonitor* monitor, GLFWwindow* share);
	GLFWwindow* GetWindow();
	void Destroy();
	bool WindowShouldClose();
	void SwapBuffers();
	int GetWindowWidth();
	int GetWindowHeight();
	bool KeyPress(int);
	bool KeyPressOnce(int);
	void AllowFullscreen();
	void ToggleFullscreen();
	void PollEvents();
};

#endif