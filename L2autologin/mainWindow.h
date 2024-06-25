#pragma once
#include <msclr\marshal_cppstd.h>
namespace L2autologin {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Diagnostics;
	using namespace	System::Security::Cryptography;
	using namespace msclr::interop;

	
	public ref class mainWindow : public System::Windows::Forms::Form
	{

	public:
		mainWindow(void)
		{
			InitializeComponent();
			loadData();
			checkPathStatus();
		}
		static int delay;
		void removebutton_Click(System::Object^ sender, System::EventArgs^ e);
		void addbutton_Click(System::Object^ sender, System::EventArgs^ e);
		static void addAccount(String^ name, String^ login, String^ password);
		void addPathButton_Click(System::Object^ sender, System::EventArgs^ e);
		void startButton_Click(System::Object^ sender, System::EventArgs^ e);
		static bool isAccountUnique(String^ name, String^ login);
		static void launchApp();
		static void saveData();
		static void loadData();
		static void checkPathStatus();
		void InitializeComponent();
		static void chooseFolder();
		static void saveProfile();
		static void loadProfile();
		static System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
		static System::Windows::Forms::Button^ startButton;
		static System::Windows::Forms::TextBox^ PathBox;
		static System::Windows::Forms::TextBox^ DelayBox;
		static System::Windows::Forms::CheckedListBox^ accountNames;
		static System::Windows::Forms::ComboBox^ profileComboBox;
		static String^ tempFileName;
		static String^ pathFileName = "Data.ini";
		static String^ profileFileName = "Profile.ini";
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
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::Button^ saveProfileButton;
		System::Windows::Forms::Button^ loadProfileButton;
		System::Windows::Forms::Button^ addPathButton;

#pragma region Windows Form Designer generated code
	
#pragma endregion
	
	private: System::Void loadProfileButton_Click(System::Object^ sender, System::EventArgs^ e) {
		loadProfile();
	}
	private: System::Void saveProfileButton_Click(System::Object^ sender, System::EventArgs^ e) {
		saveProfile();
	}
	};
}
