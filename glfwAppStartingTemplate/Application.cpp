#include "Application.h"


// Keyboard Handler
void onKeyboardCallback(GLFWwindow * win, int key, int scancode, int action, int mods)
{
     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)   glfwSetWindowShouldClose(win, true);
	 if (key == GLFW_KEY_F5 && action == GLFW_PRESS)  Application.toggleFullscreenMode(win, (Application.isFullscreen())? false: true);
}
// Mouse Handler
void onMouseCallback(GLFWwindow *win, int button, int action, int mods)
{

}

// Window reshape handler
void onReshapeCallback(GLFWwindow * win, int newWidth, int newHeight)
{
   	glViewport(0, 0, newWidth, newHeight);
	
}
// Get single instance on Window
Window& Window::Instance()
{
	static Window app;
	return app;
}
// glfw3 initialization
Window::Window(/* args */)
{
    if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
}

Window::~Window()
{
	_windowName = NULL;
}
// Window Size
void Window::setWindowSize(int x, int y)
{
    _sizeX = x;
    _sizeY = y;
	glfwSetWindowSize(_win, _sizeX, _sizeY);
	glViewport(0, 0, _sizeX, _sizeY);
}

// getting all primary information, creating window, setting event handlers
void Window::Init(bool fullscreenMode)
{
	_monitor = glfwGetPrimaryMonitor();	
	_mode = glfwGetVideoMode(_monitor);
	_win = glfwCreateWindow((fullscreenMode)? _mode->width :_sizeX, (fullscreenMode)? _mode->height :_sizeY, _windowName,  (fullscreenMode)? _monitor : NULL, NULL);
	_fullscreen = fullscreenMode;
    glfwMakeContextCurrent(_win);
	centerWindow();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
    	printf("Oh my, failed to initialize GLAD!");
	}
	initRenderingContext(); // setup defalut states
	// setup event handlers
	glfwSetKeyCallback(_win, onKeyboardCallback);
	glfwSetMouseButtonCallback(_win, onMouseCallback);
	glfwSetWindowSizeCallback(_win, onReshapeCallback);
}
// Main window title
void Window::setWindowName(const char* windowName)
{
    _windowName = windowName;
	glfwSetWindowTitle(_win, _windowName);
}
// Vertical syncronization
void Window::enableVertSyncronization(bool vSync)
{
     glfwSwapInterval(vSync ? 1 : 0);  
	 _vSync = vSync;
}
// Ajusting openGL context
void Window::setWindowContextVersion(int mainor, int major)
{
    _contextMajor = major;
    _contextMinor = mainor;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _contextMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _contextMinor);
}
// Display loop
void Window::Display(GLFWwindow * win, double currTime)
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

}
// The main event loop
int Window::exec()
{
    int returnCode = 0;
  	while (!glfwWindowShouldClose(_win))
	{
		Display(_win, glfwGetTime());
		glfwSwapBuffers(_win);
		glfwPollEvents();
	}
    glfwDestroyWindow(_win);
 	glfwTerminate();

	return glfwWindowShouldClose(_win);
}

void Window::initRenderingContext()
{
    glfwGetFramebufferSize(_win, &_sizeX, &_sizeY);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0);
}
// fullscreen mode
void Window::toggleFullscreenMode(GLFWwindow * win, bool fullscreen)
{
	_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if(fullscreen) glfwSetWindowMonitor(win, glfwGetPrimaryMonitor(), 0, 0, _mode->width, _mode->height, _mode->refreshRate);
	else 
	{		
		_winStatus.windowedX = _monitorX + (_mode->width - _sizeX) / 2;
		_winStatus.windowedY = _monitorY + (_mode->height - _sizeY) / 2;
		glfwSetWindowMonitor(win, nullptr, _winStatus.windowedX, _winStatus.windowedY, _winStatus.windowedW, _winStatus.windowedH, 0);
	}
	_fullscreen = fullscreen;
}
// Cursor visibility over the main window
void Window::setMouseCursorVisible(bool visibility)
{
	glfwSetInputMode(_win, GLFW_CURSOR, visibility? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}
// The Main Window Position Centering 
void Window::centerWindow()
{
    if (!_mode) 
	{
		printf("Oh no, problem getting video mode info!");
		return;
	}
    glfwGetMonitorPos(_monitor, &_monitorX, &_monitorY);
    glfwGetWindowSize(_win, &_sizeX, &_sizeY);
    glfwSetWindowPos(_win, _monitorX + (_mode->width - _sizeX) / 2, _monitorY + (_mode->height - _sizeY) / 2);
}
