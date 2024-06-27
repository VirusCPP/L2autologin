#include "mainWindow.h"
#include "addAccountForm.h"

namespace L2autologin {
	String^ mainWindow::EncryptData(String^ plainText, array<Byte>^ key, array<Byte>^ iv) {
		Aes^ aes = Aes::Create();
		aes->Key = key;
		aes->IV = iv;

		MemoryStream^ memoryStream = gcnew MemoryStream();
		CryptoStream^ cryptoStream = gcnew CryptoStream(memoryStream, aes->CreateEncryptor(), CryptoStreamMode::Write);

		StreamWriter^ writer = gcnew StreamWriter(cryptoStream);
		writer->Write(plainText);
		writer->Flush();
		cryptoStream->FlushFinalBlock();

		array<Byte>^ encrypted = memoryStream->ToArray();
		return Convert::ToBase64String(encrypted);
	}

	String^ mainWindow::DecryptData(String^ encryptedText, array<Byte>^ key, array<Byte>^ iv) {
		array<Byte>^ buffer = Convert::FromBase64String(encryptedText);

		Aes^ aes = Aes::Create();
		aes->Key = key;
		aes->IV = iv;

		MemoryStream^ memoryStream = gcnew MemoryStream(buffer);
		CryptoStream^ cryptoStream = gcnew CryptoStream(memoryStream, aes->CreateDecryptor(), CryptoStreamMode::Read);

		StreamReader^ reader = gcnew StreamReader(cryptoStream);
		return reader->ReadToEnd();
	}
}