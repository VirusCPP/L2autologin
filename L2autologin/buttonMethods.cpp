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

	void mainWindow::saveProfileButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (profileComboBox->Text != "") {
			if (isProfileUnique(profileComboBox->Text)) {
				mainWindow::profileComboBox->Items->Add({ profileComboBox->Text });
			}
			saveProfile();
			saveData();
		}
	}

	void mainWindow::removeProfileButton_Click(System::Object^ sender, System::EventArgs^ e) {
		removeProfile();
	}
}