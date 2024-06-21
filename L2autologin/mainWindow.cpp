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
		L2autologin::mainWindow^ mainWindowInstance = gcnew L2autologin::mainWindow();
		Application::Run(mainWindowInstance);
	}

	void addAccountForm::openAddAccountForm(mainWindow^ mainWin) {
		addAccountForm^ AddAccountForm = gcnew addAccountForm();
		AddAccountForm->ShowDialog();
	}

	void mainWindow::addbutton_Click(System::Object^ sender, System::EventArgs^ e) {
		mainWindow^ mainWin = dynamic_cast<mainWindow^>(Application::OpenForms[0]);
		addAccountForm::openAddAccountForm(mainWin);
	}

	void mainWindow::removebutton_Click(System::Object^ sender, System::EventArgs^ e) {
		for (int i = accountNames->Items->Count - 1; i >= 0; i--) {
			if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
				accountNames->Items->RemoveAt(i); 
				account::accArray->RemoveAt(i);   
				accountCount--;
			}
		}
		saveAcc();
	}
	void mainWindow::addAccount(String^ name, String^ login, String^ password) {
		if (isAccountUnique(name, login)) {
			account^ newAccount = gcnew account(name, login, password);
			account::accArray->Add(newAccount);
			mainWindow::accountNames->Items->Add({ name });
			saveAcc();
			mainWindow::accountCount++;
		}
	}
	void mainWindow::ChooseFolder() {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			Path = folderBrowserDialog1->SelectedPath;
			PathBox->Text = Path;
			savePath();
			checkPathStatus();
		}
	}
	void mainWindow::checkPathStatus() {
		if (Path == nullptr)
			startButton->Enabled = false;
		else
			startButton->Enabled = true;
	}

	void mainWindow::addPathButton_Click(System::Object^ sender, System::EventArgs^ e) {
		ChooseFolder();
	}

	bool mainWindow::isAccountUnique(String^ name, String^ login) {
		for (int i = 0; i < accountCount; i++) {
			if (account::accArray[i]->Name == name || account::accArray[i]->Login == login) {
				return false; 
			}
		}
		return true; 
	}
	void mainWindow::Encrypt(String^ fileName) {
		// Генерируем ключ и IV
		array<Byte>^ key = GenerateKey();
		array<Byte>^ iv = GenerateIV();

		// Сохраняем ключ и IV для последующей дешифрации
		SaveKeyAndIV("l2al.key", key, iv);

		// Создаем файловый поток для чтения исходного файла
		FileStream^ originalFileStream = gcnew FileStream(fileName, FileMode::Open, FileAccess::Read);

		// Создаем файловый поток для записи зашифрованных данных
		String^ encryptedFileName = fileName + ".encrypted";
		FileStream^ encryptedFileStream = gcnew FileStream(encryptedFileName, FileMode::Create, FileAccess::Write);

		// Создаем объект RijndaelManaged
		RijndaelManaged^ rijndael = gcnew RijndaelManaged();

		// Создаем криптографический поток для шифрования данных
		CryptoStream^ cryptoStream = gcnew CryptoStream(encryptedFileStream, rijndael->CreateEncryptor(key, iv), CryptoStreamMode::Write);

		try {
			// Читаем исходный файл и шифруем его
			array<Byte>^ buffer = gcnew array<Byte>(4096);
			int bytesRead;
			while ((bytesRead = originalFileStream->Read(buffer, 0, buffer->Length)) > 0) {
				cryptoStream->Write(buffer, 0, bytesRead);
			}

			// Завершаем запись в криптографический поток
			cryptoStream->FlushFinalBlock();
		}
		finally {
			// Закрываем все потоки в блоке finally, чтобы гарантированно освободить ресурсы
			if (cryptoStream) cryptoStream->Close();
			if (originalFileStream) originalFileStream->Close();
			if (encryptedFileStream) encryptedFileStream->Close();

			// Заменяем исходный файл зашифрованным файлом
			File::Delete(fileName);
			File::Move(encryptedFileName, fileName);
		}
	}
	void mainWindow::Decrypt(String^ fileName) {
		// Путь к файлу с ключом и IV
		String^ keyIVFileName = "l2al.key";

		// Загружаем ключ и IV для дешифрации
		array<Byte>^ key;
		array<Byte>^ iv;
		LoadKeyAndIV(keyIVFileName, key, iv);

		// Создаем файловый поток для чтения зашифрованного файла
		FileStream^ encryptedFileStream = gcnew FileStream(fileName, FileMode::Open, FileAccess::Read);

		// Создаем файловый поток для записи дешифрованных данных
		String^ decryptedFileName = fileName->Substring(0, fileName->LastIndexOf('.'));
		FileStream^ decryptedFileStream = gcnew FileStream(decryptedFileName, FileMode::Create, FileAccess::Write);

		// Создаем объект RijndaelManaged
		RijndaelManaged^ rijndael = gcnew RijndaelManaged();

		// Создаем криптографический поток для дешифрования
		CryptoStream^ cryptoStream = gcnew CryptoStream(encryptedFileStream, rijndael->CreateDecryptor(key, iv), CryptoStreamMode::Read);

		try {
			// Читаем зашифрованные данные и дешифруем их
			array<Byte>^ buffer = gcnew array<Byte>(4096);
			int bytesRead;
			while ((bytesRead = cryptoStream->Read(buffer, 0, buffer->Length)) > 0) {
				decryptedFileStream->Write(buffer, 0, bytesRead);
			}
		}
		finally {
			// Закрываем все потоки в блоке finally, чтобы гарантированно освободить ресурсы
			if (cryptoStream) cryptoStream->Close();
			if (encryptedFileStream) encryptedFileStream->Close();
			if (decryptedFileStream) decryptedFileStream->Close();

			// Удаляем исходный зашифрованный файл и переименовываем расшифрованный файл
			File::Delete(fileName);
			File::Move(decryptedFileName, fileName);
		}
	}



	void mainWindow::SaveKeyAndIV(String^ fileName, array<Byte>^ key, array<Byte>^ iv) {
		FileStream^ fs = nullptr;
		try {
			fs = gcnew FileStream(fileName, FileMode::Create, FileAccess::Write);
			BinaryWriter^ bw = gcnew BinaryWriter(fs);
			bw->Write(key);
			bw->Write(iv);
		}
		finally {
			if (fs) fs->Close();
		}
	}
	array<Byte>^ mainWindow::GenerateKey() {
		RijndaelManaged^ rijndael = gcnew RijndaelManaged();
		rijndael->GenerateKey();
		return rijndael->Key;
	}

	array<Byte>^ mainWindow::GenerateIV() {
		RijndaelManaged^ rijndael = gcnew RijndaelManaged();
		rijndael->GenerateIV();
		return rijndael->IV;
	}

	void mainWindow::LoadKeyAndIV(String^ fileName, array<Byte>^% key, array<Byte>^% iv) {
		FileStream^ fs = nullptr;
		try {
			fs = gcnew FileStream(fileName, FileMode::Open, FileAccess::Read);
			BinaryReader^ br = gcnew BinaryReader(fs);
			key = br->ReadBytes(32); // 256 бит для ключа
			iv = br->ReadBytes(16);  // 128 бит для IV
		}
		finally {
			if (fs) fs->Close();
		}
	}

	
	void mainWindow::savePath() {
		File::WriteAllText(pathFileName, Path);
		Encrypt(pathFileName);
	}

	void mainWindow::saveAcc() {
		if (File::Exists(accFileName)) {
			Decrypt(accFileName);
		}
		StreamWriter^ sw = gcnew StreamWriter(accFileName, false);

		try {
			for (int i = 0; i < account::accArray->Count; i++) {
				sw->WriteLine(account::accArray[i]->Name);
				sw->WriteLine(account::accArray[i]->Login);
				sw->WriteLine(account::accArray[i]->Password);
				sw->WriteLine();
			}
		}
		finally {
			sw->Close();
		}
		Encrypt(accFileName);
	}
	void mainWindow::loadPath() {
		if (File::Exists(pathFileName)) {
			Decrypt(pathFileName);
			StreamReader^ sr = gcnew StreamReader(pathFileName);
			try {
				String^ line;
				while ((line = sr->ReadLine()) != nullptr) {
					String^ path = line;
					Path = path;
					PathBox->Text = Path;
				}
			}
		
			finally {
				sr->Close();
			}
			Encrypt(pathFileName);
		}
	}
	void mainWindow::loadAcc() {
		if (File::Exists(accFileName)) {
			Decrypt(accFileName);
			StreamReader^ sr = gcnew StreamReader(accFileName);

			try {
				String^ line;
				account::accArray->Clear();
				while ((line = sr->ReadLine()) != nullptr) {
					String^ name = line;
					String^ login = sr->ReadLine();
					String^ password = sr->ReadLine();
					sr->ReadLine();
					account^ newAccount = gcnew account(name, login, password);
					account::accArray->Add(newAccount);
					mainWindow::accountNames->Items->Add({ name });
					accountCount++;
				}
			}
			finally {
				sr->Close();
			}
			Encrypt(accFileName);
		}
	}

	void mainWindow::startButton_Click(System::Object^ sender, System::EventArgs^ e) {
		Process^ proc = gcnew Process();
		proc->StartInfo->WorkingDirectory = Path;
		proc->StartInfo->FileName = Path + "\\L2.exe";
		for (int i = accountNames->Items->Count - 1; i >= 0; i--) {
			if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
				String^ parm1 = account::accArray[i]->Login;
				String^ parm2 = account::accArray[i]->Password;
				proc->StartInfo->Arguments = "account=" + parm1 + " " + "password" + parm2;
				proc->Start();
			}
		}
	}

	void mainWindow::InitializeComponent(){
		this->accountNames = (gcnew System::Windows::Forms::CheckedListBox());
		this->removeButton = (gcnew System::Windows::Forms::Button());
		this->addButton = (gcnew System::Windows::Forms::Button());
		this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
		this->startButton = (gcnew System::Windows::Forms::Button());
		this->PathBox = (gcnew System::Windows::Forms::TextBox());
		this->addPathButton = (gcnew System::Windows::Forms::Button());
		this->SuspendLayout();
		// 
		// accountNames
		// 
		this->accountNames->FormattingEnabled = true;
		this->accountNames->HorizontalScrollbar = true;
		this->accountNames->Location = System::Drawing::Point(13, 13);
		this->accountNames->Name = L"accountNames";
		this->accountNames->Size = System::Drawing::Size(176, 139);
		this->accountNames->TabIndex = 3;
		// 
		// removeButton
		// 
		this->removeButton->Location = System::Drawing::Point(205, 131);
		this->removeButton->Name = L"removeButton";
		this->removeButton->Size = System::Drawing::Size(116, 23);
		this->removeButton->TabIndex = 4;
		this->removeButton->Text = L"Удалить аккаунт";
		this->removeButton->UseVisualStyleBackColor = true;
		this->removeButton->Click += gcnew System::EventHandler(this, &mainWindow::removebutton_Click);
		// 
		// addButton
		// 
		this->addButton->Location = System::Drawing::Point(205, 102);
		this->addButton->Name = L"addButton";
		this->addButton->Size = System::Drawing::Size(116, 23);
		this->addButton->TabIndex = 5;
		this->addButton->Text = L"Добавить аккаунт";
		this->addButton->UseVisualStyleBackColor = true;
		this->addButton->Click += gcnew System::EventHandler(this, &mainWindow::addbutton_Click);
		// 
		// startButton
		// 
		this->startButton->ImageKey = L"(отсутствует)";
		this->startButton->Location = System::Drawing::Point(327, 102);
		this->startButton->Name = L"startButton";
		this->startButton->Size = System::Drawing::Size(136, 52);
		this->startButton->TabIndex = 6;
		this->startButton->Text = L"СТАРТ";
		this->startButton->UseVisualStyleBackColor = true;
		this->startButton->Click += gcnew System::EventHandler(this, &mainWindow::startButton_Click);
		// 
		// PathBox
		// 
		this->PathBox->Enabled = false;
		this->PathBox->Location = System::Drawing::Point(205, 13);
		this->PathBox->Name = L"PathBox";
		this->PathBox->Size = System::Drawing::Size(258, 20);
		this->PathBox->TabIndex = 7;
		// 
		// addPathButton
		// 
		this->addPathButton->Location = System::Drawing::Point(205, 41);
		this->addPathButton->Name = L"addPathButton";
		this->addPathButton->Size = System::Drawing::Size(258, 23);
		this->addPathButton->TabIndex = 8;
		this->addPathButton->Text = L"Выбрать папку System";
		this->addPathButton->UseVisualStyleBackColor = true;
		this->addPathButton->Click += gcnew System::EventHandler(this, &mainWindow::addPathButton_Click);
		// 
		// mainWindow
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(483, 169);
		this->Controls->Add(this->addPathButton);
		this->Controls->Add(this->PathBox);
		this->Controls->Add(this->startButton);
		this->Controls->Add(this->addButton);
		this->Controls->Add(this->removeButton);
		this->Controls->Add(this->accountNames);
		this->MaximumSize = System::Drawing::Size(499, 208);
		this->MinimumSize = System::Drawing::Size(499, 208);
		this->Name = L"mainWindow";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"L2 АвтоЛогин";
		this->ResumeLayout(false);
		this->PerformLayout();
	}
}
