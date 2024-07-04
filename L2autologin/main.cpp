#include "mainWindow.h"
#include "addAccountForm.h"

namespace L2autologin {
	
	[STAThread]
		void main(array<String^>^ args)
	{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		mainWindow::mainWindowInstance = gcnew mainWindow(); // создаем экземпляр mainWindow
		mainWindow::mainWindowInstance->TopMost = mainWindow::_onTop;
		Application::Run(mainWindow::mainWindowInstance);
	}
	
}