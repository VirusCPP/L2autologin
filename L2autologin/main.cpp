#include "mainWindow.h"
#include "addAccountForm.h"

namespace L2autologin {
	[STAThread]
		void main(array<String^>^ args)
	{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		mainWindow^ mainWindowInstance = gcnew mainWindow(); // создаем экземпляр mainWindow
		Application::Run(mainWindowInstance);
	}
}