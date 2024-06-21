#pragma once
#include "mainWindow.h"
#include "account.h"
namespace L2autologin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	
	public ref class addAccountForm : public System::Windows::Forms::Form
	{
	public:
		static void openAddAccountForm(mainWindow^ mainWin);
		addAccountForm(void)
		{
			InitializeComponent();
		}

	protected:
		
		~addAccountForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::Label^ nameLable;
	public: System::Windows::Forms::TextBox^ nameTextBox;
	public: System::Windows::Forms::TextBox^ loginTextBox;
	public: System::Windows::Forms::TextBox^ passwordTextBox;
	public: System::Windows::Forms::Label^ loginLable;
	public: System::Windows::Forms::Label^ passwordLable;
	public: System::Windows::Forms::Button^ okButton;
	public: System::Windows::Forms::Button^ cancelButton;
	private:System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(){
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
#pragma endregion

	void okButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (nameTextBox->Text != "" && loginTextBox->Text != "" && passwordTextBox->Text != "") {
			mainWindow::addAccount(nameTextBox->Text, loginTextBox->Text, passwordTextBox->Text);
			Close();
		}
		else
			MessageBox::Show("Заполнены не все поля", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
}
private: System::Void cancelButton_Click(System::Object^ sender, System::EventArgs^ e) {
	Close();
}
};
}
