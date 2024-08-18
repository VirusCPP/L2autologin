#include "mainWindow.h"
#include "addAccountForm.h"

namespace L2autologin {
	void mainWindow::saveProfile() {
		if (!File::Exists(profileFileName)) {
			StreamWriter^ sw = gcnew StreamWriter(profileFileName, true);
			sw->Close();
		}
		if (accountNames->CheckedItems->Count != 0) {
			String^ profileText = profileComboBox->Text;

			if (profileText != "") {
				StreamReader^ sr = gcnew StreamReader(profileFileName);
				List<String^>^ fileLines = gcnew List<String^>();

				try {
					String^ line;
					bool profileFound = false;

					while ((line = sr->ReadLine()) != nullptr) {
						if (line->StartsWith(profileText)) {
							profileFound = true;

							// Adding a profile line
							fileLines->Add(profileText);

							// Create a row for indexes
							String^ indices = "";
							for (int i = 0; i < account::accArray->Count; i++) {
								if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
									indices += accountNames->Items[i]->ToString() + " ";
								}
							}
							fileLines->Add(indices->Trim());

							// Adding a value from DelayBox
							fileLines->Add(DelayBox->Text);

							// Skipping the old index line and DelayBox
							sr->ReadLine(); // Skipping the index line
							sr->ReadLine(); // Skipping the old DelayBox line

							// Move on to the next line so as not to add old information.
							continue;
						}
						else {
							fileLines->Add(line);
						}
					}

					if (!profileFound) {
						// Add a new profile if it was not found
						fileLines->Add(profileText);

						// Create a row for indexes
						String^ indices = "";
						for (int i = 0; i < account::accArray->Count; i++) {
							if (accountNames->GetItemCheckState(i) == CheckState::Checked) {
								indices += accountNames->Items[i]->ToString() + " ";
							}
						}
						fileLines->Add(indices->Trim());

						// Adding a value from DelayBox
						fileLines->Add(DelayBox->Text);
						// Add a blank line to start a new line
						fileLines->Add("");
					}
				}
				finally {
					sr->Close();
				}
				// Overwriting the file
				StreamWriter^ sw = gcnew StreamWriter(profileFileName, false);

				try {
					for each (String ^ fileLine in fileLines) {
						sw->WriteLine(fileLine);
					}
				}
				catch (Exception^ ex) {
					MessageBox::Show("Error: " + ex->Message + "\nStack Trace: " + ex->StackTrace, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				finally {
					sw->Close();
				}
			}
		}
	}

	void mainWindow::loadProfile() {
		if (!File::Exists(profileFileName)) {
			return;
		}
		if (accountNames->CheckedItems->Count != 0) {
			for (int i = 0; i < account::accArray->Count; i++) {
				accountNames->SetItemCheckState(i, CheckState::Unchecked);
			}
		}
		StreamReader^ sr = gcnew StreamReader(profileFileName);
		try {
			String^ line;
			while ((line = sr->ReadLine()) != nullptr) {
				if (line->StartsWith(profileComboBox->Text)) {
					String^ numbersLine = sr->ReadLine();
					if (numbersLine != nullptr) {
						array<String^>^ numberStrings =
							numbersLine->Split(gcnew array<wchar_t>{ ' ' }, StringSplitOptions::RemoveEmptyEntries);
						for each (String ^ numStr in numberStrings) {
							// Iterate over all elements in CheckedListBox
							for (int i = 0; i < accountNames->Items->Count; i++) {
								String^ itemName = accountNames->Items[i]->ToString();
								// Compare the element name with the current line from numbersLine
								if (itemName == numStr) {
									// If it matches, we mark this element
									accountNames->SetItemCheckState(i, CheckState::Checked);
									break; // Stopping the search because the element was found
								}
							}
						}
					}
					DelayBox->Text = sr->ReadLine();
				}
			}
		}
		catch (Exception^ ex) {
			if (MessageBox::Show("Ошибка загрузки профиля, удалить профиль?", "Ошибка", 
					MessageBoxButtons::YesNo, MessageBoxIcon::Error) == System::Windows::Forms::DialogResult::Yes) {
				profileComboBox->Items->Remove(profileComboBox->Text);
				profileComboBox->Text = "";
				saveData();
				saveProfile();
			}
		}
		finally {
			sr->Close();
		}
		moveSelectedItemsUp(accountNames);
	
	}

	void mainWindow::saveData() {
		StreamWriter^ sw = gcnew StreamWriter(dataFileName, false);
		sw->WriteLine(EncryptData("[Path] = " + Path, key, iv));
		try {
			for (int i = 0; i < account::accArray->Count; i++) {
				sw->WriteLine();
				sw->WriteLine(EncryptData("[Account Name] = " + account::accArray[i]->Name, key, iv));
				sw->WriteLine(EncryptData("[Account Login] = " + account::accArray[i]->Login, key, iv));
				sw->WriteLine(EncryptData("[Account Password] = " + account::accArray[i]->Password, key, iv));
			}
			sw->WriteLine();
			for (int i = 0; i < profileComboBox->Items->Count; i++) {
				sw->WriteLine(EncryptData("[Profile] = " + profileComboBox->Items[i]->ToString(), key, iv));
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show("Error: " + ex->Message + "\nStack Trace: " + ex->StackTrace, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		finally {
			sw->Close();
		}
	}


	void mainWindow::loadData() {
		if (!File::Exists(dataFileName)) {
			return;
		}

		StreamReader^ sr = gcnew StreamReader(dataFileName);

		try {
			String^ line;
			while ((line = sr->ReadLine()) != nullptr) {
				if (!String::IsNullOrEmpty(line)) {
					String^ decryptedLine = DecryptData(line, key, iv);

					if (decryptedLine->StartsWith("[Path] = ")) {
						String^ path = decryptedLine->Substring(9); // Extract the path by skipping "[Path] = "
						Path = path;
						PathBox->Text = Path;
					}
					else if (decryptedLine->StartsWith("[Account Name] = ")) {
						String^ name = decryptedLine->Substring(17); // Extracting the account name
						String^ encryptedLogin = sr->ReadLine();
						if (!String::IsNullOrEmpty(encryptedLogin)) {
							String^ decryptedLogin = DecryptData(encryptedLogin, key, iv);
							String^ login = decryptedLogin->Substring(18); // Extract the login, skipping "[Account Login] = "

							String^ encryptedPassword = sr->ReadLine();
							if (!String::IsNullOrEmpty(encryptedPassword)) {
								String^ decryptedPassword = DecryptData(encryptedPassword, key, iv);
								String^ password = decryptedPassword->Substring(21); // Extract the password, skipping "[Account Password] = "

								sr->ReadLine(); // Skip the blank line separating the account entries

								account^ newAccount = gcnew account(name, login, password);
								account::accArray->Add(newAccount);
								mainWindow::accountNames->Items->Add({ name });
							}
						}
					}
					else if (decryptedLine->StartsWith("[Profile] = ")) {
						String^ profile = decryptedLine->Substring(12); // Extract the profile, skipping "[Profile] = "
						profileComboBox->Items->Add({ profile });
					}
				}
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show("Error: " + ex->Message + "\nStack Trace: " + ex->StackTrace, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		finally {
			sr->Close();
		}
	}
}