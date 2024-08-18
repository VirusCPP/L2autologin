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
		void okButton_Click(System::Object^ sender, System::EventArgs^ e);
		void cancelButton_Click(System::Object^ sender, System::EventArgs^ e);
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
		System::ComponentModel::Container^ components;
	protected:
		~addAccountForm()
		{
			if (components)
			{
				delete components;
			}
		}
	};
}
