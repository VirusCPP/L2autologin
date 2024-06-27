#include "mainWindow.h"
#include "addAccountForm.h"

namespace L2autologin {
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
						// ��������� ������ ������ ��� �������� �� ����� ������
						fileLines->Add("");
					}
				}
				finally {
					sr->Close();
				}
				// �������������� ����
				StreamWriter^ sw = gcnew StreamWriter(_profileFileName, false);

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
		sw->WriteLine(EncryptData("[Path] = " + Path, key, iv));
		try {
			for (int i = 0; i < account::accArray->Count; i++) {
				sw->WriteLine();
				sw->WriteLine(EncryptData("[Account Name] = " + account::accArray[i]->Name, key, iv));
				sw->WriteLine(EncryptData("[Account Login] = " + account::accArray[i]->Login, key, iv));
				sw->WriteLine(EncryptData("[Account Password] = " + account::accArray[i]->Password, key, iv));
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
			while ((line = sr->ReadLine()) != nullptr) {
				if (!String::IsNullOrEmpty(line)) {
					String^ decryptedLine = DecryptData(line, key, iv);

					if (decryptedLine->StartsWith("[Path] = ")) {
						String^ path = decryptedLine->Substring(9); // ��������� ����, ��������� "[Path] = "
						Path = path;
						PathBox->Text = Path;
					}
					else if (decryptedLine->StartsWith("[Account Name] = ")) {
						String^ name = decryptedLine->Substring(17); // ��������� ��� ��������
						String^ encryptedLogin = sr->ReadLine();
						String^ decryptedLogin = DecryptData(encryptedLogin, key, iv);
						String^ login = decryptedLogin->Substring(18); // ��������� �����, ��������� "[Account Login] = "

						String^ encryptedPassword = sr->ReadLine();
						String^ decryptedPassword = DecryptData(encryptedPassword, key, iv);
						String^ password = decryptedPassword->Substring(21); // ��������� ������, ��������� "[Account Password] = "

						sr->ReadLine(); // ���������� ������ ������, ����������� ������ ���������

						account^ newAccount = gcnew account(name, login, password);
						account::accArray->Add(newAccount);
						mainWindow::accountNames->Items->Add({ name });
					}
				}
			}
		}
		finally {
			sr->Close();
		}
	}
}