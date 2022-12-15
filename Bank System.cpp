
#pragma warning(disable : 4996)
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<fstream>
#include<ctime>
#include<iomanip>
using namespace std;


string FileName = "Client_Record.txt";
void ShowMainMenuScreen();
void TransactionMenu();
enum enMenu { ShowClientList = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5,Transaction=6, Exit = 7 };
enum enTransaction{Deopsit=1,Withdrow=2,TotalBalance=3,MainMenu=4};

//void PrintEachWordInString(string S1)
//{
//	string delim = " ";
//	cout << "\nYour String Words are: \n\n";
//	short pos = 0;
//	string sWord;
//	while ((pos = S1.find(delim)) != std::string::npos)
//	{
//		sWord = S1.substr(0, pos);
//		if (sWord != "")
//		{
//			cout << sWord << endl;
//		}
//		S1.erase(0, pos + delim.length());
//	}
//	if (S1 != "")
//	{
//		cout << S1 << endl;
//	}
//}
//int CountStringWords(string S1)
//{
//	string delim = " ";
//	short pos = 0;
//	string sWord;
//	short counter = 0;
//	while ((pos = S1.find(delim)) != std::string::npos)
//	{
//		sWord = S1.substr(0, pos);
//		if (sWord != "")
//		{
//			counter++;
//		}
//		S1.erase(0, pos + delim.length());
//	}
//	if (S1 != "")
//	{
//		counter++;
//	}
//	return counter;
//}
vector <string> SplitString(string S1, string delim)
{
	vector <string> vString;

	short pos = 0;
	string sWord;

	while ((pos = S1.find(delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}
//string TrimLeft(string S2)
//{
//	for (short i = 0;i < S2.length();i++)
//	{
//		if (S2[i] != ' ')
//		{
//			return S2.substr(i, S2.length() - i);
//		}
//	}
//	return "";
//}
//string TrimRight(string S2)
//{
//	for (short i = S2.length()-1;i >=0 ;i--)
//	{
//		if (S2[i] != ' ')
//		{
//			return S2.substr(0, i + 1);
//		}
//	}
//	return "";
//
//}
//string Trim(string S2)
//{
//	return TrimLeft(TrimRight(S2));
//}
string JoinString(vector <string>& vString, string delim)
{
	string S1 = "";

	for (string& item : vString)
	{
		S1 = S1 + item + delim;
	}
	return S1.substr(0, S1.length() - delim.length());
}
//string JoinString(string Arr[],int Length,string delim)
//{
//	string S1 = "";
//	for (short i = 0;i < Length;i++)
//	{
//		S1 = S1 + Arr[i] + delim;
//	}
//	return S1.substr(0,S1.length()-delim.length());
//}
//string ReverseWordsInString(string S1)
//{
//	vector <string> vString;
//	string S2 = "";
//	vString = SplitString(S1, " ");
//	vector<string>::iterator iter = vString.end();
//	while(iter != vString.begin())
//	{
//		--iter;
//		S2 += *iter + " ";
//	}
//	S2 = S2.substr(0, S2.length() - 1);
//	return S2;
//}
//string ReplaceWordInString(string S1,string StringToReplace,string sReplaceTo)
//{
//	short pos = S1.find(StringToReplace);
//
//	while ((pos != std::string::npos))
//	{
//		S1 = S1.replace(pos, StringToReplace.length(), sReplaceTo);
//		pos = S1.find(StringToReplace);
//	}
//	return S1;
//}
//string ReplaceWordInStringUsingSplitFunction(string S1, string StringToReplace, string sReplaceTo,bool MatchCase = true)
//{
//
//	vector<string>vString = SplitString(S1, " ");
//	for (string& s : vString)
//	{
//		if (MatchCase)
//		{
//			if (s == StringToReplace)
//			{
//				s = sReplaceTo;
//			}
//		}
//		else
//		{
//			if (LowerAllLettersInString(s) == LowerAllLettersInString(StringToReplace))
//			{
//				s = sReplaceTo;
//			}
//		}
//	}
//	return JoinString(vString," ");
//
//}
//string RemovePunct(string S1)
//{
//	string S2 = "";
//	for (short i = 0;i < S1.length();i++)
//	{
//		if (!ispunct(S1[i]))
//		{
//			S2 += S1[i];
//		}
//	}
//	return S2;
//}
struct stClientData
{
	string Account_Number;
	string Pin_Code;
	string Name;
	string Phone;
	double Account_Balance;
	bool Mark_For_Delete = false;

};
stClientData ConvertLineToRecord(string Line, string seprator = "#//#")
{
	stClientData Client;
	vector<string>vRecord = SplitString(Line, seprator);


	Client.Account_Number = vRecord[0];
	Client.Pin_Code = vRecord[1];
	Client.Name = vRecord[2];
	Client.Phone = vRecord[3];
	Client.Account_Balance = stod(vRecord[4]);

	return Client;

}
bool ClientExistByAccuntNumber(string AccountNumber, string FileName)
{
	vector<stClientData>vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		stClientData Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.Account_Number == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return false;

}
stClientData Read_ClientData()
{

	stClientData ClientData;
	cout << "\nEnter Account Number ? " << setw(10);
	getline(cin >> ws, ClientData.Account_Number);
	while (ClientExistByAccuntNumber(ClientData.Account_Number, FileName))
	{
		cout << "Client with account number [" << ClientData.Account_Number << "] already exists , enter another account number ?";
		getline(cin >> ws, ClientData.Account_Number);
	}
	cout << "\nEnter PinCode ? " << setw(10);
	getline(cin, ClientData.Pin_Code);
	cout << "\nEnter Name ? " << setw(10);
	getline(cin, ClientData.Name);
	cout << "\nEnter Phone ? " << setw(10);
	getline(cin, ClientData.Phone);
	cout << "\nEnter Account Balance ? " << setw(10);
	cin >> ClientData.Account_Balance;

	return ClientData;

}
string ConvertRecordToLine(stClientData ClientData, string seprator = "#//#")
{
	string ClientRecord = "";
	ClientRecord += ClientData.Account_Number + seprator;
	ClientRecord += ClientData.Pin_Code + seprator;
	ClientRecord += ClientData.Name + seprator;
	ClientRecord += ClientData.Phone + seprator;
	ClientRecord += to_string(ClientData.Account_Balance);
	return ClientRecord;
}

//void SplitEachClientData(stClientData Client, vector <string> vClient)
//{
//
//
//	for (short i = 0;i < vClient.size();++i)
//	{
//		Client = ConvertLineToRecord(vClient[i]);
//		PrintRecordCard(Client);
//	}
//
//
//}
void PrintRecordCard(stClientData Client)
{
	cout << "\n\nThe Following are the Client details: \n\n";
	cout << "------------------------------------------------\n";
	cout << "Account_Number  :" << Client.Account_Number;
	cout << "\nPin_Code        :" << Client.Pin_Code;
	cout << "\nName            :" << Client.Name;
	cout << "\nPhone           :" << Client.Phone;
	cout << "\nAccount_Balance :" << Client.Account_Balance;
	cout << "\n------------------------------------------------\n";
	//cout << Client.Account_Number <<setw(10) << "|" << Client.Pin_Code <<setw(5) << "|" << Client.Name <<setw(18) << "|" << Client.Phone <<setw(10) << "|" << Client.Account_Balance << endl;

}
void LoadClientToFile(string FileName, string ClientRecord)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << ClientRecord << endl;
		MyFile.close();

	}
}
vector<stClientData> LoadClientsDataFromFile(string FileName)
{
	vector <stClientData> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stClientData Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}
void PrintClientRecord(stClientData Client)
{
	cout << "| " << setw(15) << left << Client.Account_Number;
	cout << "| " << setw(10) << left << Client.Pin_Code;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.Account_Balance << "|";
}
void ShowClientsData()
{


	/*char ask = 'Y';
	cout << "\n\n\tDo You Want To Show Client Data ? ";
	cin >> ask;
	if (ask == 'Y' || ask == 'y')
	{*/
	vector<stClientData>vClients;
	vClients = LoadClientsDataFromFile(FileName);
	cout << "\n\t\t\t\t\tClient List(" << vClients.size() << ")Client(s).";
	cout << "\n___________________________________________________________________________________________________\n";
	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(10) << left << "Pin Code";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(12) << left << "Balance     |";
	cout << "\n___________________________________________________________________________________________________\n";
	for (stClientData Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout << "____________________________________________________________________________________________________\n";

	//}
}
string ReadAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter Account Number You Want To Search For? ";
	cin >> AccountNumber;
	return AccountNumber;
}
bool FindClientByAccountNumber(string AccountNumber, vector<stClientData> vClients, stClientData& Client)
{

	for (stClientData C : vClients)
	{
		if (C.Account_Number == AccountNumber)
		{
			Client = C;
			return true;
		}

	}
	return false;
}
void LoadDataFromFileToVector(string FileName, vector <string>& vClient)
{
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		while (getline(MyFile, Line))
		{
			vClient.push_back(Line);
		}
		MyFile.close();
	}

}

vector<stClientData> SaveClientDataToFile(string FileName, vector <stClientData>& vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (stClientData C : vClients)
		{
			if (C.Mark_For_Delete == false)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}

		MyFile.close();
	}
	return vClients;
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClientData>& vClients)
{
	for (stClientData& C : vClients)
	{
		if (C.Account_Number == AccountNumber)
		{
			C.Mark_For_Delete = true;
			return true;
		}
	}
	return false;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<stClientData>& vClients)
{
	stClientData Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintRecordCard(Client);
		cout << "\n\nAre You Sure You Want To Delete it ? y/n ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientDataToFile(FileName, vClients);
			//Refresh Clients
			vClients = LoadClientsDataFromFile(FileName);
			cout << "\n\nClient Succssfully Deleted.\n\n";
			return true;
		}

	}
	else
	{
		cout << "\n\nClient with Account Number (" << AccountNumber << ") not Found!";
		return false;
	}

}
void AddNewClient()
{
	stClientData Client;
	Client = Read_ClientData();
	LoadClientToFile(FileName, ConvertRecordToLine(Client));
}
void AddClients()
{
	char AddMore = 'Y';
	do
	{
		cout << "Adding New Client:\n\n";
		AddNewClient();
		cout << "\n\nClient Record saving succesfully , Do You Want To Add More Clients? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
stClientData ChangeClientRecord(string AccountNumber)
{

	stClientData ClientData;
	ClientData.Account_Number = AccountNumber;
	cout << "\nEnter PinCode ? " << setw(10);
	getline(cin >> ws, ClientData.Pin_Code);
	cout << "\nEnter Name ? " << setw(10);
	getline(cin, ClientData.Name);
	cout << "\nEnter Phone ? " << setw(10);
	getline(cin, ClientData.Phone);
	cout << "\nEnter Account Balance ? " << setw(10);
	cin >> ClientData.Account_Balance;

	return ClientData;

}
bool UpdateClientByAccountNumber(string AccountNumber, vector<stClientData>& vClients)
{
	stClientData Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintRecordCard(Client);
		cout << "\n\nAre You Sure You Want To Update it ? y/n ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			for (stClientData& C : vClients)
			{
				if (C.Account_Number == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveClientDataToFile(FileName, vClients);
			cout << "\n\nClient Succssfully Updated.\n\n";

			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") not Found!";

		return false;

	}

}
void ShowUpdateClientsScreen()
{
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	cout << "           Update Clients Screen              \n";
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	vector<stClientData>vClients;
	vClients = LoadClientsDataFromFile(FileName);
	string AccountNumber;
	cout << "\nPlease enter Account Number you want to Update ?" << endl;
	cin >> AccountNumber;
	UpdateClientByAccountNumber(AccountNumber, vClients);
}
void ShowAddNewClientsScreen()
{
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	cout << "           Add New Clients Screen            \n";
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	AddClients();

}
void ShowDeleteClientScreen()
{
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	cout << "           Delete Clients Screen              \n";
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	vector<stClientData>vClients;
	vClients = LoadClientsDataFromFile(FileName);
	string AccountNumber;
	cout << "\nenter Client's account number you want to delete ?";
	cin >> AccountNumber;
	DeleteClientByAccountNumber(AccountNumber, vClients);
}
void ShowFindClientScreen()
{
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	cout << "           Find Clients Screen                \n";
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	vector<stClientData>vClients;
	vClients = LoadClientsDataFromFile(FileName);
	stClientData Client;
	string AccountNumber = ReadAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintRecordCard(Client);
	else
		cout << "Client With Account Number [" << AccountNumber << "] is not Found!";
}
void ShowEndScreen()
{
	system("cls");
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	cout << "             Program ends :-)                 \n";
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	
}
void GoBackToMainMenu()
{
	cout << "\n\nPress any key to go back to main menu...";
	system("pause>0");
	ShowMainMenuScreen();
}
void PrintClientsBalance(stClientData Client)
{
	cout << "| " << setw(15) << left << Client.Account_Number;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Account_Balance << "|";
}
short ReadMainMenuOption()
{
	cout << "Choose what do you want to do? [1 To 6]? ";
	short Option = 0;
	cin >> Option;
	return Option;
}
short ReadTransactionOption()
{
	cout << "\nChoose What You Want To Do ? [1 to 4] ?";
	short Option;
	cin >> Option;
	return Option;
}
void ShowTotalBalance()
{
	vector<stClientData>vClients;
	vClients = LoadClientsDataFromFile(FileName);
	cout << "\n\t\t\t\t\tClient List(" << vClients.size() << ")Client(s).";
	cout << "\n__________________________________________________________________________\n";
	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Balance     |";
	cout << "\n__________________________________________________________________________\n";
	double TotalBalances = 0;
	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available in the system!";
	else
		for (stClientData Client : vClients)
		{
			PrintClientsBalance(Client);
			TotalBalances += Client.Account_Balance;
			cout << endl;
		}
	cout << "__________________________________________________________________________\n";
	cout << "\t\t\t\tTotal Balances = " << TotalBalances;
}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<stClientData> vClients)
{
	char Anwser = 'Y';
	cout << "Are you sure you want to preform this transaction ? y/n?";
	cin >> Anwser;
	if (toupper(Anwser) == 'Y')
	{
		for (stClientData& C : vClients)
		{
			if (C.Account_Number == AccountNumber)
			{
				C.Account_Balance += Amount;
				SaveClientDataToFile(FileName, vClients);
				cout << "\n\nDone Succssfully. new balance is " << C.Account_Balance;
				return true;
			}
		}
		return false;
	}
}
void ShowDepositMenu()
{
	system("cls");
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	cout << "               Deposit Screen                 \n";
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	vector<stClientData>vClients;
	stClientData Client;
	vClients = LoadClientsDataFromFile(FileName);
	string AccountNumber;
	cout << "\nPlease enter Account Number ? " << endl;
	cin >> AccountNumber;
	double DepositAmount = 0;
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client With Account Number [" << AccountNumber << "] does not exist!\n";
		cout << "\nPlease enter Account Number ? " << endl;
		cin >> AccountNumber;
	}
	PrintRecordCard(Client);
	cout << "\nPlease enter Deposit Amount ? ";
	cin >> DepositAmount;
	DepositBalanceToClientByAccountNumber(AccountNumber, DepositAmount, vClients);

}
void ShowWithdrawMenu()
{
	system("cls");
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	cout << "               Withdraw Screen                \n";
	cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
	vector<stClientData>vClients;
	vClients = LoadClientsDataFromFile(FileName);
	string AccountNumber;
	cout << "\nPlease enter Account Number ? " << endl;
	cin >> AccountNumber;
	stClientData Client;
	double WithDrawAmount = 0;
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client With Account Number [" << AccountNumber << "] does not exist!\n";
		cout << "\nPlease enter Account Number ? " << endl;
		cin >> AccountNumber;
	}
	PrintRecordCard(Client);
	cout << "\nPlease enter Withdraw Amount ? ";
	cin >> WithDrawAmount;
	while (WithDrawAmount > Client.Account_Balance)
	{
		cout << "\nAmount Exceeds the balance, you can Withdrow up to " << Client.Account_Balance << endl;
		cout << "Enter Another Amount ?";
		cin >> WithDrawAmount;
	}
	DepositBalanceToClientByAccountNumber(AccountNumber, WithDrawAmount * -1, vClients);
}
void GoToTransactionMenu()
{
	cout << "\nPress Any Key To Go Back To Transaction Menu...";
	system("pause>0");
	system("cls");
	TransactionMenu();
}
void PreformTransactionMenu(enTransaction TransactionOption)
{
	switch (TransactionOption)
	{
	case enTransaction::Deopsit:
	{
		system("cls");
		ShowDepositMenu();
		GoToTransactionMenu();
		break;
	}
	case enTransaction::Withdrow:
	{
		system("cls");
		ShowWithdrawMenu();
		GoToTransactionMenu();
		break;
	}
	case enTransaction::TotalBalance:
	{
		system("cls");
		ShowTotalBalance();
		GoToTransactionMenu();
		
		break;
	}
	case enTransaction::MainMenu:
	{
		system("cls");
		ShowMainMenuScreen();
		break;
	}
	}
}
void TransactionMenu()
{
	cout << "============================================\n";
	cout << "            Transaction Menu Screen         \n";
	cout << "============================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "============================================\n";
	PreformTransactionMenu((enTransaction)ReadTransactionOption());
}
void PreformMainMenuOption(enMenu MainMenuOption)
{
	switch (MainMenuOption)
	{
	case enMenu::ShowClientList:
	{
		system("cls");
		ShowClientsData();
		GoBackToMainMenu();
		break;
	}
	case enMenu::AddClient:
	{
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenu();
		break;
	}
	case enMenu::DeleteClient:
	{
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		break;
	}
	case enMenu::UpdateClient:
	{
		system("cls");
		ShowUpdateClientsScreen();
		GoBackToMainMenu();
		break;
	}
	case enMenu::FindClient:
	{
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;
	}
	case enMenu::Transaction:
	{
		system("cls");
		TransactionMenu();
		break;
	}
	case enMenu::Exit:
	{
		system("cls");
		ShowEndScreen();
		break;
	}
	}
}
void ShowMainMenuScreen()
{
	system("cls");
	cout << "============================================\n";
	cout << "              Main Menu Screen            \n";
	cout << "============================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transaction.\n";
	cout << "\t[7] Exit.\n";
	cout << "============================================\n";
	PreformMainMenuOption((enMenu)ReadMainMenuOption());
}
int main()
{

	ShowMainMenuScreen();

}
