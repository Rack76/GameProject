#pragma once

#include <vector>
class GLFWwindow;

class WindowManager {
public:
	void init();
	void selectWindow(int);
	GLFWwindow* getSelectedWindow();
	GLFWwindow* getWindow(int);
private:
	std::vector<GLFWwindow*> windows;
	int windowCount = 0;
	int selectedWindow = 0;
};