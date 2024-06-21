#pragma once
#include <fstream>
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

	
	public ref class mainWindow : public System::Windows::Forms::Form
	{
	public:
		void removebutton_Click(System::Object^ sender, System::EventArgs^ e);
		void addbutton_Click(System::Object^ sender, System::EventArgs^ e);
		static void addAccount(String^ name, String^ login, String^ password);
		void addPathButton_Click(System::Object^ sender, System::EventArgs^ e);
		void startButton_Click(System::Object^ sender, System::EventArgs^ e);
		static bool isAccountUnique(String^ name, String^ login);
		static void savePath();
		static void saveAcc();
		static void loadAcc();
		static void loadPath();
		void checkPathStatus();
		void InitializeComponent();
		void ChooseFolder();
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::Button^ startButton;
	public: static System::Windows::Forms::TextBox^ PathBox;
	private:

	private:

	private: System::Windows::Forms::Button^ addPathButton;


	public:
		static String^ pathFileName = "path.dat";
		static String^ accFileName = "acc.dat";
		static String^ Path;
		static int accountCount = 0;
		mainWindow(void)
		{
			InitializeComponent();
			
			loadAcc();
			loadPath();
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
	protected:

	protected:

	protected:

	public: System::Windows::Forms::Button^ removeButton;
	public: System::Windows::Forms::Button^ addButton;
	public: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
	
#pragma endregion
	
	};
}
