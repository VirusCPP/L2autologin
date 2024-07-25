#include "mainWindow.h"
#include "addAccountForm.h"

namespace L2autologin {

	void mainWindow::InitializeComponent() {
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(mainWindow::typeid));
		this->accountNames = (gcnew System::Windows::Forms::CheckedListBox());
		this->removeButton = (gcnew System::Windows::Forms::Button());
		this->addButton = (gcnew System::Windows::Forms::Button());
		this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
		this->startButton = (gcnew System::Windows::Forms::Button());
		this->PathBox = (gcnew System::Windows::Forms::TextBox());
		this->addPathButton = (gcnew System::Windows::Forms::Button());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->DelayBox = (gcnew System::Windows::Forms::TextBox());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->profileComboBox = (gcnew System::Windows::Forms::ComboBox());
		this->saveProfileButton = (gcnew System::Windows::Forms::Button());
		this->removeProfileButton = (gcnew System::Windows::Forms::Button());
		this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
		this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
		this->protocolButton = (gcnew System::Windows::Forms::Button());
		this->showLoginPassworButton = (gcnew System::Windows::Forms::Button());
		this->SuspendLayout();
		// 
		// accountNames
		// 
		this->accountNames->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->accountNames->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->accountNames->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->accountNames->FormattingEnabled = true;
		this->accountNames->HorizontalScrollbar = true;
		this->accountNames->Location = System::Drawing::Point(12, 12);
		this->accountNames->Name = L"accountNames";
		this->accountNames->Size = System::Drawing::Size(176, 137);
		this->accountNames->TabIndex = 3;
		// 
		// removeButton
		// 
		this->removeButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->removeButton->FlatAppearance->BorderSize = 0;
		this->removeButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->removeButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->removeButton->Location = System::Drawing::Point(204, 130);
		this->removeButton->Name = L"removeButton";
		this->removeButton->Size = System::Drawing::Size(116, 23);
		this->removeButton->TabIndex = 4;
		this->removeButton->Text = L"Удалить аккаунт";
		this->removeButton->UseVisualStyleBackColor = false;
		this->removeButton->Click += gcnew System::EventHandler(this, &mainWindow::removeAccButton_Click);
		// 
		// addButton
		// 
		this->addButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->addButton->FlatAppearance->BorderSize = 0;
		this->addButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->addButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->addButton->Location = System::Drawing::Point(204, 101);
		this->addButton->Name = L"addButton";
		this->addButton->Size = System::Drawing::Size(116, 23);
		this->addButton->TabIndex = 5;
		this->addButton->Text = L"Добавить аккаунт";
		this->addButton->UseVisualStyleBackColor = false;
		this->addButton->Click += gcnew System::EventHandler(this, &mainWindow::addAccButton_Click);
		// 
		// startButton
		// 
		this->startButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->startButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->startButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->startButton->ImageKey = L"(отсутствует)";
		this->startButton->Location = System::Drawing::Point(326, 130);
		this->startButton->Name = L"startButton";
		this->startButton->Size = System::Drawing::Size(150, 23);
		this->startButton->TabIndex = 6;
		this->startButton->Text = L"СТАРТ";
		this->startButton->UseVisualStyleBackColor = false;
		this->startButton->Click += gcnew System::EventHandler(this, &mainWindow::startButton_Click);
		// 
		// PathBox
		// 
		this->PathBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->PathBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->PathBox->Enabled = false;
		this->PathBox->ForeColor = System::Drawing::SystemColors::ControlLightLight;
		this->PathBox->Location = System::Drawing::Point(204, 12);
		this->PathBox->Name = L"PathBox";
		this->PathBox->Size = System::Drawing::Size(272, 20);
		this->PathBox->TabIndex = 7;
		// 
		// addPathButton
		// 
		this->addPathButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->addPathButton->FlatAppearance->BorderSize = 0;
		this->addPathButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->addPathButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->addPathButton->Location = System::Drawing::Point(204, 40);
		this->addPathButton->Name = L"addPathButton";
		this->addPathButton->Size = System::Drawing::Size(140, 23);
		this->addPathButton->TabIndex = 8;
		this->addPathButton->Text = L"Выбрать папку System";
		this->addPathButton->UseVisualStyleBackColor = false;
		this->addPathButton->Click += gcnew System::EventHandler(this, &mainWindow::addPathButton_Click);
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->label1->Location = System::Drawing::Point(201, 78);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(173, 13);
		this->label1->TabIndex = 9;
		this->label1->Text = L"Задержка между запуском окон";
		// 
		// DelayBox
		// 
		this->DelayBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->DelayBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->DelayBox->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->DelayBox->Location = System::Drawing::Point(382, 75);
		this->DelayBox->Name = L"DelayBox";
		this->DelayBox->Size = System::Drawing::Size(52, 20);
		this->DelayBox->TabIndex = 10;
		this->DelayBox->Text = L"5000";
		this->DelayBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainWindow::textBox_KeyPress);
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->label2->Location = System::Drawing::Point(440, 78);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(22, 13);
		this->label2->TabIndex = 11;
		this->label2->Text = L"Мс";
		// 
		// profileComboBox
		// 
		this->profileComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->profileComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->profileComboBox->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->profileComboBox->FormattingEnabled = true;
		this->profileComboBox->Location = System::Drawing::Point(482, 13);
		this->profileComboBox->Name = L"profileComboBox";
		this->profileComboBox->Size = System::Drawing::Size(171, 21);
		this->profileComboBox->TabIndex = 12;
		this->profileComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &mainWindow::loadProfileButton_Click);
		// 
		// saveProfileButton
		// 
		this->saveProfileButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->saveProfileButton->FlatAppearance->BorderSize = 0;
		this->saveProfileButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->saveProfileButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->saveProfileButton->Location = System::Drawing::Point(482, 40);
		this->saveProfileButton->Name = L"saveProfileButton";
		this->saveProfileButton->Size = System::Drawing::Size(171, 23);
		this->saveProfileButton->TabIndex = 13;
		this->saveProfileButton->Text = L"Сохранить профиль";
		this->saveProfileButton->UseVisualStyleBackColor = false;
		this->saveProfileButton->Click += gcnew System::EventHandler(this, &mainWindow::saveProfileButton_Click);
		// 
		// removeProfileButton
		// 
		this->removeProfileButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->removeProfileButton->FlatAppearance->BorderSize = 0;
		this->removeProfileButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->removeProfileButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->removeProfileButton->Location = System::Drawing::Point(482, 73);
		this->removeProfileButton->Name = L"removeProfileButton";
		this->removeProfileButton->Size = System::Drawing::Size(171, 23);
		this->removeProfileButton->TabIndex = 13;
		this->removeProfileButton->Text = L"Удалить профиль";
		this->removeProfileButton->UseVisualStyleBackColor = false;
		this->removeProfileButton->Click += gcnew System::EventHandler(this, &mainWindow::removeProfileButton_Click);
		// 
		// progressBar1
		// 
		this->progressBar1->Location = System::Drawing::Point(482, 130);
		this->progressBar1->Name = L"progressBar1";
		this->progressBar1->Size = System::Drawing::Size(168, 23);
		this->progressBar1->TabIndex = 14;
		// 
		// checkBox1
		// 
		this->checkBox1->AutoSize = true;
		this->checkBox1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->checkBox1->Location = System::Drawing::Point(482, 106);
		this->checkBox1->Name = L"checkBox1";
		this->checkBox1->Size = System::Drawing::Size(116, 17);
		this->checkBox1->TabIndex = 15;
		this->checkBox1->Text = L"Поверх всех окон";
		this->checkBox1->UseVisualStyleBackColor = true;
		this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &mainWindow::checkBox1_CheckedChanged);
		// 
		// protocolButton
		// 
		this->protocolButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->protocolButton->FlatAppearance->BorderSize = 0;
		this->protocolButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->protocolButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->protocolButton->Location = System::Drawing::Point(350, 40);
		this->protocolButton->Name = L"protocolButton";
		this->protocolButton->Size = System::Drawing::Size(126, 23);
		this->protocolButton->TabIndex = 8;
		this->protocolButton->Text = L"Версия протокола";
		this->protocolButton->UseVisualStyleBackColor = false;
		this->protocolButton->Click += gcnew System::EventHandler(this, &mainWindow::showLoginPasswordButton_Click);
		// 
		// showLoginPassworButton
		// 
		this->showLoginPassworButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->showLoginPassworButton->FlatAppearance->BorderSize = 0;
		this->showLoginPassworButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->showLoginPassworButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->showLoginPassworButton->Location = System::Drawing::Point(326, 100);
		this->showLoginPassworButton->Name = L"showLoginPassworButton";
		this->showLoginPassworButton->Size = System::Drawing::Size(150, 23);
		this->showLoginPassworButton->TabIndex = 5;
		this->showLoginPassworButton->Text = L"Показать логин и пароль";
		this->showLoginPassworButton->UseVisualStyleBackColor = false;
		this->showLoginPassworButton->Click += gcnew System::EventHandler(this, &mainWindow::showLoginPasswordButton_Click);
		// 
		// mainWindow
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
			static_cast<System::Int32>(static_cast<System::Byte>(31)));
		this->ClientSize = System::Drawing::Size(662, 169);
		this->Controls->Add(this->checkBox1);
		this->Controls->Add(this->progressBar1);
		this->Controls->Add(this->removeProfileButton);
		this->Controls->Add(this->saveProfileButton);
		this->Controls->Add(this->profileComboBox);
		this->Controls->Add(this->label2);
		this->Controls->Add(this->DelayBox);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->protocolButton);
		this->Controls->Add(this->addPathButton);
		this->Controls->Add(this->PathBox);
		this->Controls->Add(this->startButton);
		this->Controls->Add(this->showLoginPassworButton);
		this->Controls->Add(this->addButton);
		this->Controls->Add(this->removeButton);
		this->Controls->Add(this->accountNames);
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
		this->ImeMode = System::Windows::Forms::ImeMode::On;
		this->MaximumSize = System::Drawing::Size(678, 208);
		this->MinimumSize = System::Drawing::Size(678, 208);
		this->Name = L"mainWindow";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"L2 AutoLogin by VirusCPP";
		this->ResumeLayout(false);
		this->PerformLayout();

	}

	void addAccountForm::InitializeComponent() {
		this->nameLable = (gcnew System::Windows::Forms::Label());
		this->nameTextBox = (gcnew System::Windows::Forms::TextBox());
		this->loginTextBox = (gcnew System::Windows::Forms::TextBox());
		this->passwordTextBox = (gcnew System::Windows::Forms::TextBox());
		this->loginLable = (gcnew System::Windows::Forms::Label());
		this->passwordLable = (gcnew System::Windows::Forms::Label());
		this->okButton = (gcnew System::Windows::Forms::Button());
		this->cancelButton = (gcnew System::Windows::Forms::Button());
		this->SuspendLayout();
		// 
		// nameLable
		// 
		this->nameLable->Location = System::Drawing::Point(12, 4);
		this->nameLable->Name = L"nameLable";
		this->nameLable->Size = System::Drawing::Size(101, 23);
		this->nameLable->TabIndex = 0;
		this->nameLable->Text = L"Name";
		this->nameLable->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// nameTextBox
		// 
		this->nameTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->nameTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->nameTextBox->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->nameTextBox->ImeMode = System::Windows::Forms::ImeMode::On;
		this->nameTextBox->Location = System::Drawing::Point(13, 30);
		this->nameTextBox->Name = L"nameTextBox";
		this->nameTextBox->Size = System::Drawing::Size(100, 20);
		this->nameTextBox->TabIndex = 1;
		// 
		// loginTextBox
		// 
		this->loginTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->loginTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->loginTextBox->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->loginTextBox->ImeMode = System::Windows::Forms::ImeMode::On;
		this->loginTextBox->Location = System::Drawing::Point(119, 30);
		this->loginTextBox->Name = L"loginTextBox";
		this->loginTextBox->Size = System::Drawing::Size(100, 20);
		this->loginTextBox->TabIndex = 2;
		// 
		// passwordTextBox
		// 
		this->passwordTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->passwordTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->passwordTextBox->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->passwordTextBox->ImeMode = System::Windows::Forms::ImeMode::On;
		this->passwordTextBox->Location = System::Drawing::Point(225, 30);
		this->passwordTextBox->Name = L"passwordTextBox";
		this->passwordTextBox->Size = System::Drawing::Size(100, 20);
		this->passwordTextBox->TabIndex = 3;
		// 
		// loginLable
		// 
		this->loginLable->Location = System::Drawing::Point(119, 4);
		this->loginLable->Name = L"loginLable";
		this->loginLable->Size = System::Drawing::Size(100, 23);
		this->loginLable->TabIndex = 0;
		this->loginLable->Text = L"Login";
		this->loginLable->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// passwordLable
		// 
		this->passwordLable->Location = System::Drawing::Point(225, 6);
		this->passwordLable->Name = L"passwordLable";
		this->passwordLable->Size = System::Drawing::Size(100, 18);
		this->passwordLable->TabIndex = 0;
		this->passwordLable->Text = L"Password";
		this->passwordLable->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// okButton
		// 
		this->okButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->okButton->FlatAppearance->BorderSize = 0;
		this->okButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->okButton->Location = System::Drawing::Point(13, 81);
		this->okButton->Name = L"okButton";
		this->okButton->Size = System::Drawing::Size(145, 23);
		this->okButton->TabIndex = 4;
		this->okButton->Text = L"OK";
		this->okButton->UseVisualStyleBackColor = false;
		this->okButton->Click += gcnew System::EventHandler(this, &addAccountForm::okButton_Click);
		// 
		// cancelButton
		// 
		this->cancelButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->cancelButton->FlatAppearance->BorderSize = 0;
		this->cancelButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->cancelButton->Location = System::Drawing::Point(180, 81);
		this->cancelButton->Name = L"cancelButton";
		this->cancelButton->Size = System::Drawing::Size(145, 23);
		this->cancelButton->TabIndex = 5;
		this->cancelButton->Text = L"Cancel";
		this->cancelButton->UseVisualStyleBackColor = false;
		this->cancelButton->Click += gcnew System::EventHandler(this, &addAccountForm::cancelButton_Click);
		// 
		// addAccountForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
			static_cast<System::Int32>(static_cast<System::Byte>(32)));
		this->ClientSize = System::Drawing::Size(339, 116);
		this->Controls->Add(this->cancelButton);
		this->Controls->Add(this->okButton);
		this->Controls->Add(this->passwordTextBox);
		this->Controls->Add(this->loginTextBox);
		this->Controls->Add(this->nameTextBox);
		this->Controls->Add(this->passwordLable);
		this->Controls->Add(this->loginLable);
		this->Controls->Add(this->nameLable);
		this->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
		this->MaximumSize = System::Drawing::Size(355, 155);
		this->MinimumSize = System::Drawing::Size(355, 155);
		this->Name = L"addAccountForm";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"Добавление аккаунта";
		this->ResumeLayout(false);
		this->PerformLayout();

	}
}