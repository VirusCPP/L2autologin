#pragma once
#include "mainWindow.h"
namespace L2autologin {
	ref class account
	{
	public:
		String^ Name;
		String^ Login;
		String^ Password;

		account(String^ name, String^ login, String^ password) {
			Name = name;
			Login = login;
			Password = password;
		}

		static List<account^>^ accArray = gcnew List<account^>(999);
	};
}
