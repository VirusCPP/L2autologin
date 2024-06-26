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
		void InitializeComponent();
		static void openAddAccountForm(mainWindow^ mainWin);
		addAccountForm(void)
		{
			InitializeComponent();
		}
		System::Windows::Forms::Label^ nameLable;
		System::Windows::Forms::TextBox^ nameTextBox;
		System::Windows::Forms::TextBox^ loginTextBox;
		System::Windows::Forms::TextBox^ passwordTextBox;
		System::Windows::Forms::Label^ loginLable;
		System::Windows::Forms::Label^ passwordLable;
		System::Windows::Forms::Button^ okButton;
		System::Windows::Forms::Button^ cancelButton;

	protected:
		~addAccountForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		   
#pragma endregion

	void okButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (nameTextBox->Text != "" && loginTextBox->Text != "" && passwordTextBox->Text != "") {
			mainWindow::addAccount(nameTextBox->Text, loginTextBox->Text, passwordTextBox->Text);
			Close();
		}
		else
			MessageBox::Show("Заполнены не все поля", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
}
	void cancelButton_Click(System::Object^ sender, System::EventArgs^ e) {
	Close();
}
};
}
