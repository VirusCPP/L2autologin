#include "mainWindow.h"
#include "addAccountForm.h"

namespace L2autologin {
	void mainWindow::addPathButton_Click(System::Object^ sender, System::EventArgs^ e) {
		chooseFolder();
	}
	
	void mainWindow::addbutton_Click(System::Object^ sender, System::EventArgs^ e) {
		mainWindow^ addWin = dynamic_cast<mainWindow^>(Application::OpenForms[0]);
		addAccountForm::openAddAccountForm(addWin);
	}

	void mainWindow::removebutton_Click(System::Object^ sender, System::EventArgs^ e) {
		for (int i = accountNames->Items->Count - 1; i >= 0; i--) {
			if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
				accountNames->Items->RemoveAt(i);
				account::accArray->RemoveAt(i);
				accountCount--;
			}
		}
		saveData();
	}

	void mainWindow::startButton_Click(System::Object^ sender, System::EventArgs^ e) {
		launchApp();
	}

	void addAccountForm::openAddAccountForm(mainWindow^ mainWin) {
		addAccountForm^ AddAccountForm = gcnew addAccountForm();
		AddAccountForm->ShowDialog();
	}

	void mainWindow::addAccount(String^ name, String^ login, String^ password) {
		if (isAccountUnique(name, login)) {
			account^ newAccount = gcnew account(name, login, password);
			account::accArray->Add(newAccount);
			mainWindow::accountNames->Items->Add({ name });
			saveData();
			mainWindow::accountCount++;
		}
		else
			MessageBox::Show("Аккаунт с такими данными уже существует", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	void mainWindow::chooseFolder() {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			Path = folderBrowserDialog1->SelectedPath;
			PathBox->Text = Path;
			saveData();
			checkPathStatus();
		}
	}

	void mainWindow::checkPathStatus() {
		if (Path == nullptr)
			startButton->Enabled = false;
		else
			startButton->Enabled = true;
	}

	bool mainWindow::isAccountUnique(String^ name, String^ login) {
		for (int i = 0; i < accountCount; i++) {
			if (account::accArray[i]->Name == name || account::accArray[i]->Login == login) {
				return false;
			}
		}
		return true;
	}

	void mainWindow::saveData() {
		StreamWriter^ sw = gcnew StreamWriter(pathFileName, false);
		sw->WriteLine("[Path] = " + Path);
		try {
			for (int i = 0; i <= mainWindow::accountCount; i++) {
				
				sw->WriteLine();
				sw->WriteLine("[Account Name] = " + account::accArray[i]->Name);
				sw->WriteLine("[Account Login] = " + account::accArray[i]->Login);
				sw->WriteLine("[Account Password] = " + account::accArray[i]->Password);
				sw->WriteLine();
			}
		}
		finally {
			sw->Close();
		}
	}
	
	void mainWindow::loadData() {
		if (File::Exists(pathFileName)) {
			StreamReader^ sr = gcnew StreamReader(pathFileName);

			try {
				String^ line;
				while ((line = sr->ReadLine()) != nullptr) {
					if (line->StartsWith("[Path] = ")) {
						String^ path = line->Substring(9);
						Path = path;
						PathBox->Text = Path;
					}
					else if (line->StartsWith("[Account Name] = ")) {
						String^ name = line->Substring(17);
						String^ login = sr->ReadLine();
						if (login != nullptr && login->StartsWith("[Account Login] = ")) {
							login = login->Substring(18);
						}
						else {
		
							continue;
						}			
						String^ password = sr->ReadLine();
						if (password != nullptr && password->StartsWith("[Account Password] = ")) {
							password = password->Substring(21); 
						}
						else {
							
							continue;
						}

						sr->ReadLine();

						account^ newAccount = gcnew account(name, login, password);
						account::accArray->Add(newAccount);
						mainWindow::accountNames->Items->Add({ name });
						accountCount++;
					}
				}
			}
			finally {
				sr->Close();
			}
		}
	}

	void mainWindow::launchApp() {
		Process^ proc = gcnew Process();
		int delay;
		Int32::TryParse(DelayBox->Text, delay);
		proc->StartInfo->FileName = Path + "\\L2.exe";
		if (accountNames->CheckedItems->Count != 0) {
			for (int i = 0; i < accountCount; i++) {
				if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
					accountNames->SetItemCheckState(i, CheckState::Unchecked);
					String^ parm1 = account::accArray[i]->Login;
					String^ parm2 = account::accArray[i]->Password;
					proc->StartInfo->Arguments = "account=" + parm1 + " " + "password=" + parm2;
					proc->Start();
					System::Threading::Thread::Sleep(delay);
				}
			}
		}
		else {
			proc->Start();
		}
	}
}
