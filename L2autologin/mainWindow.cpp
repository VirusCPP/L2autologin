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
			MessageBox::Show("Аккаунт с такими данными уже существует", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	void mainWindow::removeAccount() {
		if (accountNames->CheckedItems->Count == 0) {
			return;
		}
		if (MessageBox::Show("Удалить выбранные аккаунты?", "Удаление аккаунтов", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
			for (int i = account::accArray->Count - 1; i >= 0 ; i--) {
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

							// Добавляем строку профиля
							fileLines->Add(profileText);

							// Создаем строку для индексов
							String^ indices = "";
							for (int i = 0; i < account::accArray->Count; i++) {
								if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
									indices += i.ToString() + " ";
								}
							}
							fileLines->Add(indices->Trim());

							// Добавляем значение из DelayBox
							fileLines->Add(DelayBox->Text);

							// Пропускаем старую строку индексов и DelayBox
							sr->ReadLine(); // Пропускаем строку индексов
							sr->ReadLine(); // Пропускаем старую строку DelayBox

							// Переходим к следующей строке, чтобы не добавлять старую информацию
							continue;
						}
						else {
							fileLines->Add(line);
						}
					}

					if (!profileFound) {
						// Добавляем новый профиль, если он не был найден
						fileLines->Add(profileText);

						// Создаем строку для индексов
						String^ indices = "";
						for (int i = 0; i < account::accArray->Count; i++) {
							if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
								indices += i.ToString() + " ";
							}
						}
						fileLines->Add(indices->Trim());

						// Добавляем значение из DelayBox
						fileLines->Add(DelayBox->Text);
						// Добавляем пустую строку для перехода на новую строку
						fileLines->Add(""); 
					}
				}
				finally {
					sr->Close();
				}
				// Перезаписываем файл
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

	String^ EncryptData(String^ plainText, array<Byte>^ key, array<Byte>^ iv) {
		Aes^ aes = Aes::Create();
		aes->Key = key;
		aes->IV = iv;

		MemoryStream^ memoryStream = gcnew MemoryStream();
		CryptoStream^ cryptoStream = gcnew CryptoStream(memoryStream, aes->CreateEncryptor(), CryptoStreamMode::Write);

		StreamWriter^ writer = gcnew StreamWriter(cryptoStream);
		writer->Write(plainText);
		writer->Flush();
		cryptoStream->FlushFinalBlock();

		array<Byte>^ encrypted = memoryStream->ToArray();
		return Convert::ToBase64String(encrypted);
	}

	String^ DecryptData(String^ encryptedText, array<Byte>^ key, array<Byte>^ iv) {
		array<Byte>^ buffer = Convert::FromBase64String(encryptedText);

		Aes^ aes = Aes::Create();
		aes->Key = key;
		aes->IV = iv;

		MemoryStream^ memoryStream = gcnew MemoryStream(buffer);
		CryptoStream^ cryptoStream = gcnew CryptoStream(memoryStream, aes->CreateDecryptor(), CryptoStreamMode::Read);

		StreamReader^ reader = gcnew StreamReader(cryptoStream);
		return reader->ReadToEnd();
	}

	void mainWindow::saveData() {
		array<Byte>^ key = Encoding::UTF8->GetBytes("1215241215241215"); // Замените на ваш ключ
		array<Byte>^ iv = Encoding::UTF8->GetBytes("8765432187654321"); // Замените на ваш IV

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

		array<Byte>^ key = Encoding::UTF8->GetBytes("1215241215241215"); // Используйте тот же ключ
		array<Byte>^ iv = Encoding::UTF8->GetBytes("8765432187654321"); // Используйте тот же IV

		StreamReader^ sr = gcnew StreamReader(_dataFileName);

		try {
			String^ line;
			while ((line = sr->ReadLine()) != nullptr) {
				if (!String::IsNullOrEmpty(line)) {
					String^ decryptedLine = DecryptData(line, key, iv);

					if (decryptedLine->StartsWith("[Path] = ")) {
						String^ path = decryptedLine->Substring(9); // Извлекаем путь, пропуская "[Path] = "
						Path = path;
						PathBox->Text = Path;
					}
					else if (decryptedLine->StartsWith("[Account Name] = ")) {
						String^ name = decryptedLine->Substring(17); // Извлекаем имя аккаунта
						String^ encryptedLogin = sr->ReadLine();
						String^ decryptedLogin = DecryptData(encryptedLogin, key, iv);
						String^ login = decryptedLogin->Substring(18); // Извлекаем логин, пропуская "[Account Login] = "

						String^ encryptedPassword = sr->ReadLine();
						String^ decryptedPassword = DecryptData(encryptedPassword, key, iv);
						String^ password = decryptedPassword->Substring(21); // Извлекаем пароль, пропуская "[Account Password] = "

						sr->ReadLine(); // Пропускаем пустую строку, разделяющую записи аккаунтов

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
			MessageBox::Show("Не найден файл L2.exe, проверьте путь до папки System", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}
