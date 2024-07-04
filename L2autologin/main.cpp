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
	void mainWindow::checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (checkBox1->Checked) {
			_onTop = true;
			mainWindowInstance->TopMost = true; // Update the TopMost property
		}
		else {
			_onTop = false;
			mainWindowInstance->TopMost = false; // Update the TopMost property
		}
	}
}