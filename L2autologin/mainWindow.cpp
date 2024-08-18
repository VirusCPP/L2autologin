#include "mainWindow.h"
#include "addAccountForm.h"

namespace L2autologin {

	void mainWindow::moveSelectedItemsUp(CheckedListBox^ listBox) {
		// List for storing selected items
		cliext::vector<Object^> selectedItems;
		cliext::vector<account^> selectedAccounts;
		cliext::vector<bool> checkedStates;

		// Go through all the elements and collect the selected elements
		for (int i = 0; i < listBox->Items->Count; i++) {
			if (listBox->GetItemChecked(i)) {
				selectedItems.push_back(listBox->Items[i]);
				selectedAccounts.push_back(account::accArray[i]);
				checkedStates.push_back(true); // Save the checked state
			}
		}

		// Remove the selected elements from the original list and from accArray
		for (int i = selectedItems.size() - 1; i >= 0; i--) {
			int index = listBox->Items->IndexOf(selectedItems[i]);
			listBox->Items->RemoveAt(index);
			account::accArray->RemoveAt(index);
		}

		// Insert the selected elements to the beginning of the list
		for (int i = 0; i < selectedItems.size(); i++) {
			listBox->Items->Insert(i, selectedItems[i]);
			listBox->SetItemChecked(i, checkedStates[i]); // Restoring the checked state
			account::accArray->Insert(i, selectedAccounts[i]);
		}
	}

	void mainWindow::moveItem(CheckedListBox^ listBox, int direction) {
		// Get the index of the selected element
		int index = listBox->SelectedIndex;

		// If there is no selected element or the index is invalid
		if (index < 0 || index >= listBox->Items->Count)
			return;

		// New index after move
		int newIndex = index + direction;

		// Checking for list out of bounds
		if (newIndex < 0 || newIndex >= listBox->Items->Count)
			return;

		// Save current element
		Object^ selectedItem = listBox->Items[index];
		bool isChecked = listBox->GetItemChecked(index);

		// Save the corresponding account^ object from accArray
		account^ selectedAccount = account::accArray[index];

		// Remove current element from list and accArray
		listBox->Items->RemoveAt(index);
		account::accArray->RemoveAt(index);

		// Insert an element and the corresponding account^ object at a new position
		listBox->Items->Insert(newIndex, selectedItem);
		listBox->SetItemChecked(newIndex, isChecked);
		account::accArray->Insert(newIndex, selectedAccount);

		// Setting a new selected item
		listBox->SelectedIndex = newIndex;
		saveData();
	}

	void mainWindow::textBox_KeyPress(Object^ sender, KeyPressEventArgs^ e)
	{
		if (!Char::IsDigit(e->KeyChar) && e->KeyChar != '\b')
		{
			e->Handled = true;
		}
	}

	void addAccountForm::openAddAccountForm(mainWindow^ mainWin) {
		addAccountForm^ AddAccountForm = gcnew addAccountForm();
		AddAccountForm->ShowDialog();
	}

	void mainWindow::addAccount(String^ name, String^ login, String^ password) {
		if (isAccountUnique(name, login)) {
			account^ newAccount = gcnew account(name, login, password);
			account::accArray->Add(newAccount);
			mainWindow::accountNames->Items->Add({ name });
			saveData();
		}
		else
			MessageBox::Show("Аккаунт с такими данными уже существует", "Ошибка", 
				MessageBoxButtons::OK, MessageBoxIcon::Information);
	}


	void mainWindow::removeAccount() {
		if (accountNames->CheckedItems->Count == 0) {
			return;
		}
		if (MessageBox::Show("Удалить выбранные аккаунты?", "Удаление аккаунтов", 
				MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
			for (int i = account::accArray->Count - 1; i >= 0 ; i--) {
				if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
					accountNames->Items->RemoveAt(i);
					account::accArray->RemoveAt(i);
				}
			}
			saveData();
		}
	}

	void mainWindow::removeProfile() {
		if (profileComboBox->Text == "") {
			return;
		}
		if (MessageBox::Show("Удалить выбранный профиль?", "Удаление профиля", 
				MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
			profileComboBox->Items->Remove(profileComboBox->Text);
			profileComboBox->Text = "";
			saveData();
			saveProfile();
		}
	}

	void mainWindow::chooseFolder() {
		if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			Path = folderBrowserDialog->SelectedPath;
			PathBox->Text = Path;
			if (!System::IO::File::Exists(Path + "\\L2.exe")) {
				MessageBox::Show("Файл L2.exe не найден", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			else {
				MessageBox::Show("Файл L2.exe найден", "L2AutoLogin", MessageBoxButtons::OK, MessageBoxIcon::Information);
				saveData();
			}
			checkPathStatus();
		}
	}

	void mainWindow::checkPathStatus() {
		if (!System::IO::File::Exists(Path + "\\L2.exe")) {
			startButton->Enabled = false;
			protocolButton->Enabled = false;
		}
		else {
			startButton->Enabled = true;
			protocolButton->Enabled = true;
		}
	}

	void mainWindow::showLoginPassword() {
		String^ Result = "Используйте \"CTRL + C\" чтобы скопировать текст \n\n";
		try{
			if (accountNames->CheckedItems->Count != 0) {
				for (int i = 0; i < account::accArray->Count; i++) {
					if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
						String^ parm0 = account::accArray[i]->Name;
						String^ parm1 = account::accArray[i]->Login;
						String^ parm2 = account::accArray[i]->Password;
						Result += parm0 + "\n" + "Login = " + parm1 + "\n"
							+ "Password = " + parm2 + "\n\n";
					}
				}
				MessageBox::Show(Result, "Show Login and Password", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else
				MessageBox::Show("Выберите хотя бы один аккаунт", "Show Login and Password", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		catch (Exception^ ex) {
			ex;
		}
	}

	bool mainWindow::isAccountUnique(String^ name, String^ login) {
		for (int i = 0; i < account::accArray->Count; i++) {
			if (account::accArray[i]->Name == name || account::accArray[i]->Login == login) {
				return false;
			}
		}
		return true;
	}

	bool mainWindow::isProfileUnique(String^ profileName) {
		for (int i = 0; i < profileComboBox->Items->Count; i++) {
			if (profileComboBox->Items[i]->ToString() == profileName) {
				return false;
			}
		}
		return true;
	}

	void mainWindow::checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (checkBox1->Checked) {
			mainWindowInstance->TopMost = true;
		}
		else {
			mainWindowInstance->TopMost = false;
		}
	}

	void mainWindow::launchApp(Object^ state) {
		progressBar1->Value = 0;
		Process^ proc = gcnew Process();
		Int32::TryParse(DelayBox->Text, delay);
		proc->StartInfo->FileName = Path + "\\L2.exe";
		try {
			int progress = accountNames->CheckedItems->Count;
			if (accountNames->CheckedItems->Count != 0) {
				for (int i = 0; i < account::accArray->Count; i++) {
					if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
						accountNames->SetItemCheckState(i, CheckState::Unchecked);
						String^ parm1 = account::accArray[i]->Login;
						String^ parm2 = account::accArray[i]->Password;
						proc->StartInfo->Arguments = "account=" + parm1 + " " + "password=" + parm2;
						proc->Start();
						System::Threading::Thread::Sleep(delay);
						progressBar1->Increment(100 / progress);
					}
				}
			}
			else {
				proc->Start();
			}
		}
		catch (...) {
			MessageBox::Show("Не найден файл L2.exe, проверьте путь до папки System", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		finally {
			progressBar1->Value = 100;
		}
	}
}
