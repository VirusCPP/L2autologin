#include "mainWindow.h"
#include "addAccountForm.h"

namespace L2autologin {

	void mainWindow::InitializeComponent() {
		this->accountNames = (gcnew System::Windows::Forms::CheckedListBox());
		this->removeButton = (gcnew System::Windows::Forms::Button());
		this->addButton = (gcnew System::Windows::Forms::Button());
		this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
		this->startButton = (gcnew System::Windows::Forms::Button());
		this->PathBox = (gcnew System::Windows::Forms::TextBox());
		this->addPathButton = (gcnew System::Windows::Forms::Button());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->DelayBox = (gcnew System::Windows::Forms::TextBox());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->profileComboBox = (gcnew System::Windows::Forms::ComboBox());
		this->saveProfileButton = (gcnew System::Windows::Forms::Button());
		this->loadProfileButton = (gcnew System::Windows::Forms::Button());
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
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(202, 79);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(58, 13);
		this->label1->TabIndex = 9;
		this->label1->Text = L"Задержка";
		// 
		// DelayBox
		// 
		this->DelayBox->Location = System::Drawing::Point(266, 76);
		this->DelayBox->Name = L"DelayBox";
		this->DelayBox->Size = System::Drawing::Size(52, 20);
		this->DelayBox->TabIndex = 10;
		this->DelayBox->Text = L"5000";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(324, 79);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(22, 13);
		this->label2->TabIndex = 11;
		this->label2->Text = L"Мс";
		// 
		// profileComboBox
		// 
		this->profileComboBox->FormattingEnabled = true;
		this->profileComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
			L"Профиль 1", L"Профиль 2", L"Профиль 3",
				L"Профиль 4", L"Профиль 5"
		});
		this->profileComboBox->Location = System::Drawing::Point(505, 13);
		this->profileComboBox->Name = L"profileComboBox";
		this->profileComboBox->Size = System::Drawing::Size(171, 21);
		this->profileComboBox->TabIndex = 12;
		// 
		// saveProfileButton
		// 
		this->saveProfileButton->Location = System::Drawing::Point(505, 74);
		this->saveProfileButton->Name = L"saveProfileButton";
		this->saveProfileButton->Size = System::Drawing::Size(171, 23);
		this->saveProfileButton->TabIndex = 13;
		this->saveProfileButton->Text = L"Сохранить профиль";
		this->saveProfileButton->UseVisualStyleBackColor = true;
		this->saveProfileButton->Click += gcnew System::EventHandler(this, &mainWindow::saveProfileButton_Click);
		// 
		// loadProfileButton
		// 
		this->loadProfileButton->Location = System::Drawing::Point(505, 41);
		this->loadProfileButton->Name = L"loadProfileButton";
		this->loadProfileButton->Size = System::Drawing::Size(171, 23);
		this->loadProfileButton->TabIndex = 14;
		this->loadProfileButton->Text = L"Загрузить профиль";
		this->loadProfileButton->UseVisualStyleBackColor = true;
		this->loadProfileButton->Click += gcnew System::EventHandler(this, &mainWindow::loadProfileButton_Click);
		// 
		// mainWindow
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(688, 169);
		this->Controls->Add(this->loadProfileButton);
		this->Controls->Add(this->saveProfileButton);
		this->Controls->Add(this->profileComboBox);
		this->Controls->Add(this->label2);
		this->Controls->Add(this->DelayBox);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->addPathButton);
		this->Controls->Add(this->PathBox);
		this->Controls->Add(this->startButton);
		this->Controls->Add(this->addButton);
		this->Controls->Add(this->removeButton);
		this->Controls->Add(this->accountNames);
		this->MaximumSize = System::Drawing::Size(704, 208);
		this->MinimumSize = System::Drawing::Size(704, 208);
		this->Name = L"mainWindow";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"L2 АвтоЛогин";
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
		this->nameTextBox->Location = System::Drawing::Point(13, 30);
		this->nameTextBox->Name = L"nameTextBox";
		this->nameTextBox->Size = System::Drawing::Size(100, 20);
		this->nameTextBox->TabIndex = 1;
		// 
		// loginTextBox
		// 
		this->loginTextBox->Location = System::Drawing::Point(119, 30);
		this->loginTextBox->Name = L"loginTextBox";
		this->loginTextBox->Size = System::Drawing::Size(100, 20);
		this->loginTextBox->TabIndex = 2;
		// 
		// passwordTextBox
		// 
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
		this->okButton->Location = System::Drawing::Point(13, 81);
		this->okButton->Name = L"okButton";
		this->okButton->Size = System::Drawing::Size(145, 23);
		this->okButton->TabIndex = 4;
		this->okButton->Text = L"OK";
		this->okButton->UseVisualStyleBackColor = true;
		this->okButton->Click += gcnew System::EventHandler(this, &addAccountForm::okButton_Click);
		// 
		// cancelButton
		// 
		this->cancelButton->Location = System::Drawing::Point(180, 81);
		this->cancelButton->Name = L"cancelButton";
		this->cancelButton->Size = System::Drawing::Size(145, 23);
		this->cancelButton->TabIndex = 5;
		this->cancelButton->Text = L"Cancel";
		this->cancelButton->UseVisualStyleBackColor = true;
		this->cancelButton->Click += gcnew System::EventHandler(this, &addAccountForm::cancelButton_Click);
		// 
		// addAccountForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(339, 116);
		this->Controls->Add(this->cancelButton);
		this->Controls->Add(this->okButton);
		this->Controls->Add(this->passwordTextBox);
		this->Controls->Add(this->loginTextBox);
		this->Controls->Add(this->nameTextBox);
		this->Controls->Add(this->passwordLable);
		this->Controls->Add(this->loginLable);
		this->Controls->Add(this->nameLable);
		this->MaximumSize = System::Drawing::Size(355, 155);
		this->MinimumSize = System::Drawing::Size(355, 155);
		this->Name = L"addAccountForm";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"Добавление аккаунта";
		this->ResumeLayout(false);
		this->PerformLayout();

	}

}