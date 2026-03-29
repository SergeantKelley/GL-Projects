#include "Application.h"

int main()
{
	Application.Init(false);
	Application.setWindowName("Hello Window");	
	Application.setMouseCursorVisible(false);
	Application.enableVertSyncronization(true);
	return Application.exec();
}
