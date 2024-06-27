#include "mainWindow.h"
#include "addAccountForm.h"

namespace L2autologin {

	void mainWindow::textBox_KeyPress(Object^ sender, KeyPressEventArgs^ e)
	{
		if (!Char::IsDigit(e->KeyChar) && e->KeyChar != '\b')
		{
			e->Handled = true;
		}
	}

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
		}
		else
			MessageBox::Show("������� � ������ ������� ��� ����������", "������", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	void mainWindow::removeAccount() {
		if (accountNames->CheckedItems->Count == 0) {
			return;
		}
		if (MessageBox::Show("������� ��������� ��������?", "�������� ���������", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
			for (int i = 0; i < account::accArray->Count; i++) {
				if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
					accountNames->Items->RemoveAt(i);
					account::accArray->RemoveAt(i);
				}
			}
			saveData();
		}
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
		if (PathBox->Text == "")
			startButton->Enabled = false;
		else
			startButton->Enabled = true;
	}

	bool mainWindow::isAccountUnique(String^ name, String^ login) {
		for (int i = 0; i < account::accArray->Count; i++) {
			if (account::accArray[i]->Name == name || account::accArray[i]->Login == login) {
				return false;
			}
		}
		return true;
	}

	void mainWindow::saveProfile() {
		if (!File::Exists(_profileFileName)) {
			StreamWriter^ sw = gcnew StreamWriter(_profileFileName, true);
			sw->Close();
		}
		if (accountNames->CheckedItems->Count != 0) {
			String^ profileText = profileComboBox->Text;

			if (profileText != "") {
				StreamReader^ sr = gcnew StreamReader(_profileFileName);
				List<String^>^ fileLines = gcnew List<String^>();

				try {
					String^ line;
					bool profileFound = false;

					while ((line = sr->ReadLine()) != nullptr) {
						if (line->StartsWith(profileText)) {
							profileFound = true;

							// ��������� ������ �������
							fileLines->Add(profileText);

							// ������� ������ ��� ��������
							String^ indices = "";
							for (int i = 0; i < account::accArray->Count; i++) {
								if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
									indices += i.ToString() + " ";
								}
							}
							fileLines->Add(indices->Trim());

							// ��������� �������� �� DelayBox
							fileLines->Add(DelayBox->Text);

							// ���������� ������ ������ �������� � DelayBox
							sr->ReadLine(); // ���������� ������ ��������
							sr->ReadLine(); // ���������� ������ ������ DelayBox

							// ��������� � ��������� ������, ����� �� ��������� ������ ����������
							continue;
						}
						else {
							fileLines->Add(line);
						}
					}

					if (!profileFound) {
						// ��������� ����� �������, ���� �� �� ��� ������
						fileLines->Add(profileText);

						// ������� ������ ��� ��������
						String^ indices = "";
						for (int i = 0; i < account::accArray->Count; i++) {
							if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
								indices += i.ToString() + " ";
							}
						}
						fileLines->Add(indices->Trim());

						// ��������� �������� �� DelayBox
						fileLines->Add(DelayBox->Text);

						fileLines->Add(""); // ��������� ������ ������ ��� �������� �� ����� ������
					}
				}
				finally {
					sr->Close();
				}

				StreamWriter^ sw = gcnew StreamWriter(_profileFileName, false); // �������������� ����

				try {
					for each (String ^ fileLine in fileLines) {
						sw->WriteLine(fileLine);
					}
				}
				finally {
					sw->Close();
				}
			}
		}
	}

	void mainWindow::loadProfile() {
		if (!File::Exists(_dataFileName)) {
			return;
		}
		if (accountNames->CheckedItems->Count != 0) {
			for (int i = 0; i < account::accArray->Count; i++) {
				accountNames->SetItemCheckState(i, CheckState::Unchecked);
			}
		}
		StreamReader^ sr = gcnew StreamReader(_profileFileName);
		try {
			String^ line;
			while ((line = sr->ReadLine()) != nullptr) {
				if (line->StartsWith(profileComboBox->Text)) {
					String^ numbersLine = sr->ReadLine();
					if (numbersLine != nullptr) {
						array<String^>^ numberStrings =
							numbersLine->Split(gcnew array<wchar_t>{ ' ' }, StringSplitOptions::RemoveEmptyEntries);
						for each (String ^ numStr in numberStrings) {
							int number;
							if (Int32::TryParse(numStr, number)) {
								accountNames->SetItemCheckState(number, CheckState::Checked);
							}
						}
					}
					DelayBox->Text = sr->ReadLine();
				}
			}
		}
		finally {
			sr->Close();
		}
	}

	void mainWindow::saveData() {
		StreamWriter^ sw = gcnew StreamWriter(_dataFileName, false);
		sw->WriteLine("[Path] = " + Path);													// ��������� ���� � ����� System
		try {
			for (int i = 0; i < account::accArray->Count; i++) {
				
				sw->WriteLine();															//
				sw->WriteLine("[Account Name] = " + account::accArray[i]->Name);			//
				sw->WriteLine("[Account Login] = " + account::accArray[i]->Login);			// ��������� ������ ���������
				sw->WriteLine("[Account Password] = " + account::accArray[i]->Password);	//
			}
		}
		finally {
			sw->Close();
		}
	}
	
	void mainWindow::loadData() {
		if (!File::Exists(_dataFileName)) {
			return;
		}
		StreamReader^ sr = gcnew StreamReader(_dataFileName);

		try {
			String^ line;
			while ((line = sr->ReadLine()) != nullptr) {								//
				if (line->StartsWith("[Path] = ")) {									//
					String^ path = line->Substring(9);									// ��������� ���� � ����� System
					Path = path;														//
					PathBox->Text = Path;												//
				}
				// ��������� ������ ���������
				else if (line->StartsWith("[Account Name] = ")) {						
					String^ name = line->Substring(17);									
					String^ login = sr->ReadLine();										
					login = login->Substring(18);									
					String^ password = sr->ReadLine();
					password = password->Substring(21); 
					
					sr->ReadLine();
					
					account^ newAccount = gcnew account(name, login, password);
					account::accArray->Add(newAccount);
					mainWindow::accountNames->Items->Add({ name });
				}
			}
		}
		finally {
			sr->Close();
		}
	}

	void mainWindow::launchApp(Object^ state) {
		Process^ proc = gcnew Process();
		Int32::TryParse(DelayBox->Text, _delay);
		proc->StartInfo->FileName = Path + "\\L2.exe";
		try {
			if (accountNames->CheckedItems->Count != 0) {
				for (int i = 0; i < account::accArray->Count; i++) {
					if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
						accountNames->SetItemCheckState(i, CheckState::Unchecked);
						String^ parm1 = account::accArray[i]->Login;
						String^ parm2 = account::accArray[i]->Password;
						proc->StartInfo->Arguments = "account=" + parm1 + " " + "password=" + parm2;
						proc->Start();
						System::Threading::Thread::Sleep(_delay);
					}
				}
			}

			else {
				proc->Start();
			}
		}
		catch (...) {
			MessageBox::Show("�� ������ ���� L2.exe, ��������� ���� �� ����� System", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}
