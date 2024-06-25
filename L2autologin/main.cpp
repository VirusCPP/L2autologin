#include "mainWindow.h"
#include "addAccountForm.h"

namespace L2autologin {
	using namespace System;
	using namespace System::Windows::Forms;
	[STAThread]
		void main(array<String^>^ args)
	{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		mainWindow^ mainWindowInstance = gcnew mainWindow(); // создаем экземпляр mainWindow
		Application::Run(mainWindowInstance);
	}
}