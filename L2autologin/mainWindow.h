#pragma once
#include <msclr\marshal_cppstd.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace L2autologin {

	using namespace System;
	using namespace System::IO;
	using namespace System::Text;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Diagnostics;
	using namespace System::Threading;

	
	public ref class mainWindow : public System::Windows::Forms::Form
	{

	public:
		mainWindow(void)
		{
			InitializeComponent();
			loadData();
			checkPathStatus();
		}
		static int _delay;
		static String^ _version = L"0.9";
		void removeAccButton_Click(System::Object^ sender, System::EventArgs^ e);
		void addAccButton_Click(System::Object^ sender, System::EventArgs^ e);
		static void addAccount(String^ name, String^ login, String^ password);
		static void removeAccount();
		static void removeProfile();
		void addPathButton_Click(System::Object^ sender, System::EventArgs^ e);
		void startButton_Click(System::Object^ sender, System::EventArgs^ e);
		static bool isAccountUnique(String^ name, String^ login);
		static bool isProfileUnique(String^ profileName);
		void removeProfileButton_Click(System::Object^ sender, System::EventArgs^ e);
		void saveProfileButton_Click(System::Object^ sender, System::EventArgs^ e);
		void loadProfileButton_Click(System::Object^ sender, System::EventArgs^ e);
		static void launchApp(Object^ state);
		static void saveData();
		static void loadData();
		static void checkPathStatus();
		void InitializeComponent();
		static void chooseFolder();
		static void saveProfile();
		static void loadProfile();
		void textBox_KeyPress(Object^ sender, KeyPressEventArgs^ e);
		static String^ EncryptData(String^ plainText, array<Byte>^ key, array<Byte>^ iv);
		static String^ DecryptData(String^ encryptedText, array<Byte>^ key, array<Byte>^ iv);
		static System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
		static System::Windows::Forms::Button^ startButton;
		static System::Windows::Forms::TextBox^ PathBox;
		static System::Windows::Forms::TextBox^ DelayBox;
		static System::Windows::Forms::CheckedListBox^ accountNames;
		static System::Windows::Forms::ComboBox^ profileComboBox;
		static String^ _dataFileName = "Data.bin";
		static String^ _profileFileName = "Profile.ini";
		static String^ Path;
		System::Windows::Forms::Button^ removeButton;
		System::Windows::Forms::Button^ addButton;
		System::ComponentModel::Container^ components;

	protected:
		~mainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: 
		String^ connString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\\source\\SiteCore65\\Individual-Data.xls;Extended Properties=Excel 8.0;";
		static array<Byte>^ key = Encoding::UTF8->GetBytes("1215241215241215"); // Замените на ваш ключ
		static array<Byte>^ iv = Encoding::UTF8->GetBytes("8765432187654321"); // Замените на ваш IV
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::Button^ saveProfileButton;
		System::Windows::Forms::Button^ addPathButton;
		System::Windows::Forms::Button^ removeProfileButton;
	};
}
