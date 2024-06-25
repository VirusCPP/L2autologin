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
	    static System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	    static System::Windows::Forms::Button^ startButton;
		static System::Windows::Forms::TextBox^ PathBox;
	
	public:
		static String^ tempFileName;
		static String^ pathFileName = "Data.ini";
		static String^ Path;
		static System::Windows::Forms::TextBox^ DelayBox;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ addPathButton;
	public:	   
		mainWindow(void)
		{
			InitializeComponent();
			loadData();
			checkPathStatus();
		}

	protected:
		~mainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	public: static System::Windows::Forms::CheckedListBox^ accountNames;
	public: System::Windows::Forms::Button^ removeButton;
	public: System::Windows::Forms::Button^ addButton;
	public: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
	
#pragma endregion
	
	};
}
