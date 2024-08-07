#include "mainWindow.h"
#include "addAccountForm.h"

namespace L2autologin {

	void mainWindow::addPathButton_Click(System::Object^ sender, System::EventArgs^ e) {
		chooseFolder();
	}

	void mainWindow::addAccButton_Click(System::Object^ sender, System::EventArgs^ e) {
		mainWindow^ addWin = dynamic_cast<mainWindow^>(Application::OpenForms[0]);
		addAccountForm::openAddAccountForm(addWin);
	}

	void mainWindow::removeAccButton_Click(System::Object^ sender, System::EventArgs^ e) {
		removeAccount();
	}

	void mainWindow::startButton_Click(System::Object^ sender, System::EventArgs^ e) {
		ThreadPool::QueueUserWorkItem(gcnew WaitCallback(&launchApp), nullptr);
	}

	void mainWindow::loadProfileButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (profileComboBox->Text != "") {
			loadProfile();
		}
	}

	void mainWindow::mainWindow_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == 'l'){
			showLoginPassword();
		}
	}

	void mainWindow::saveProfileButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (profileComboBox->Text != "" && accountNames->CheckedItems->Count != 0) {
			if (isProfileUnique(profileComboBox->Text)) {
				mainWindow::profileComboBox->Items->Add({ profileComboBox->Text });
			}
			saveProfile();
			saveData();
		}
		else
			MessageBox::Show("�� ������ �� ���� ������� ��� �� ������� �������� �������", "������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}

	void mainWindow::removeProfileButton_Click(System::Object^ sender, System::EventArgs^ e) {
		removeProfile();
	}
	void mainWindow::showProtocol_Click(System::Object^ sender, System::EventArgs^ e) {
		Process^ proc = gcnew Process();
		try {
			proc->StartInfo->FileName = Path + "\\L2.exe";
			proc->StartInfo->Arguments = "-L2ProtocolVersion";
			proc->Start();
		}
		catch(...)
		{
			MessageBox::Show("������ ������� ������� ����", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
}
}