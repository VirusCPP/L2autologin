#pragma once
#include <msclr\marshal_cppstd.h>
#include <tlhelp32.h>
#include <windows.h>

#if defined _WIN64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

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
	using namespace System::Windows;

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
		static mainWindow^ mainWindowInstance;
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
		void showProtocol_Click(System::Object^ sender, System::EventArgs^ e);
		void mainWindow_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
		static void launchApp(Object^ state);
		static void saveData();
		static void loadData();
		static void checkPathStatus();
		void InitializeComponent();
		static void chooseFolder();
		static void saveProfile();
		static void loadProfile();
		static void showLoginPassword();
		void textBox_KeyPress(Object^ sender, KeyPressEventArgs^ e);
		static String^ EncryptData(String^ plainText, array<Byte>^ key, array<Byte>^ iv);
		static String^ DecryptData(String^ encryptedText, array<Byte>^ key, array<Byte>^ iv);
		static System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog;
		static System::Windows::Forms::Button^ startButton;
		static System::Windows::Forms::Button^ protocolButton;
		static System::Windows::Forms::TextBox^ PathBox;
		static System::Windows::Forms::TextBox^ DelayBox;
		static System::Windows::Forms::CheckedListBox^ accountNames;
		static System::Windows::Forms::ComboBox^ profileComboBox;
		static System::Windows::Forms::ProgressBar^ progressBar1;
		void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		static String^ _dataFileName = "Data.bin";
		static String^ _profileFileName = "Profile.ini";
		static String^ Path;
		
	protected:
		~mainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: 
		static array<Byte>^ key = Encoding::UTF8->GetBytes("1215241215241215"); // Замените на ваш ключ
		static array<Byte>^ iv = Encoding::UTF8->GetBytes("8765432187654321"); // Замените на ваш IV
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::Button^ saveProfileButton;
		System::Windows::Forms::Button^ addPathButton;
		System::Windows::Forms::Button^ removeProfileButton;
		System::Windows::Forms::CheckBox^ checkBox1;
		System::Windows::Forms::Button^ removeButton;
		System::Windows::Forms::Button^ addButton;
		System::ComponentModel::Container^ components;
	};
}
