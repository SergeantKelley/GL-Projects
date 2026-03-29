#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "includes\glad\glad.h"
#include "includes\GLFW\glfw3.h"

// window default settings
struct WindowStatus
{
	int windowedX = 150; // position X
	int windowedY = 150; // position Y
	int windowedW = 800; // size X
	int windowedH = 600; // size Y
};

// main window class that hadles with all modes and window settings
class Window
{
private:
    /* data */
public:
    Window(/* args */);
    ~Window();
    static Window& Instance();

public:
    void setWindowSize(int x, int y);
    void Init(bool fullscreenMode);
    void setWindowName(const char* windowName);
    void enableVertSyncronization(bool vSync);
    void setWindowContextVersion(int mainor, int major);
    int exec();
    void toggleFullscreenMode(GLFWwindow * win, bool fullscreen);
    inline bool isFullscreen() { return _fullscreen; };
    void setMouseCursorVisible(bool visibility);

private:
    void Display(GLFWwindow * win, double currTime);    // display loop function
    void initRenderingContext();                        // setup initial render settings or states
    void centerWindow();                                // set the main window centered

private:
    GLFWwindow * _win           = nullptr;  // GLFW window instance
    const char * _windowName    = "Unnamed Window"; // window title
    bool _vSync                 = false;    // vertical screen sync
    bool _fullscreen            = false;    // fullscree mode
    int _contextMajor           = 4;        // openGL context
    int _contextMinor           = 6;        // openGL context
    int _sizeX                  = 800;      // window size X
    int _sizeY                  = 600;      // window size Y
    int _monitorX               = 0;        // monitor size X
    int _monitorY               = 0;        // monitor size Y
    float _windowRatio;                     // w / h window ratio
    WindowStatus _winStatus;                // base window info (size and upper left corner position)
    const GLFWvidmode * _mode   = nullptr;  // video mode info
    GLFWmonitor * _monitor      = nullptr;  // monitor info
};

static Window Application = Window::Instance(); // The singleton window instance


