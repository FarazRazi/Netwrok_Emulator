//Main
#include <iostream>
#include "Header.h"
#include <fstream>
#include "string"
#include <string>
#include <sstream>
#include <conio.h>

using namespace std;
int main()
{
	cout << "Hello Fastians!!!" << endl;
	Network o;
	char choice;
	o.GraphLoading();

	cout << "\n\n\t\t\t\t\tWelcome to Router Network" << endl;
	cout << "\t\tPress Enter to continue: ";
	_getch();
mainmenu:
	cout << "\n";
	cout << " \t\tPress 1 for Running using Menu " << endl;
	cout << " \t\tPress 2 for Running using CommandLine " << endl;
	cout << " \t\tPress 0 to Exit" << endl;
	choice = _getch();
	system("cls");
	string str1, str2, str3;
	int w;
	switch (choice)
	{
	case 49:
	menu:
		cout << "\n";
		cout << " \t\tPress 1 for Sending Message " << endl;
		cout << " \t\tPress 2 for viewing Graph (Adjacency List) " << endl;
		cout << " \t\tPress 3 for viewing WieghtGraph (Matrix) " << endl;
		cout << " \t\tPress 4 for printing path " << endl;
		cout << " \t\tPress 5 to add edge " << endl;
		cout << " \t\tPress 0 to Back" << endl;
		choice = _getch();
		system("cls");

		switch (choice)
		{
		case 49:
			//for usersending message
			o.takeMessage();
			goto menu;
		case 50:
			cout << "\t\tAdjacency List Garph Representation\n" << endl;
			o.DisplayGraph();
			goto menu;
		case 51:
			cout << "\t\t Wiegth Matrix of Graph\n" << endl;
			o.DisplayMatrix();
			goto menu;

		case 52:
			o.getPaths();
			goto menu;
		case 53:
			cout << "\t\tInput Source : ";
			cin >> str1;
			cout << "\t\tInput Destiantion : ";
			cin >> str2;
			cout << "\t\tInput Weight : ";
			cin >> w;
			o.changeedge(str1, str2, w);
			goto menu;

		case 48:
		{
			//Exit
			cout << "\n\t\t\t Closing..." << endl;
			goto mainmenu;
		}
		default:
			cout << "\n\t\tWrong Input\n ERROR!!" << endl;
			goto menu;

		}
		goto mainmenu;
	case 50:
		Message M;
		string commad;
	commandmenu:
		cout << "\n\t--------------Commands Entering--------------\n";
		cout << "\n\n\t\tCommands Available : \n\n";
		cout << "\n\tsend msg hello.txt" << endl;
		cout << "\n\tsend ID prioritykey source destination payload" << endl;
		cout << "\n\tprint path M6 to M9" << endl;
		cout << "\n\tprint path M6 to *" << endl;
		cout << "\n\tprint path * to M9" << endl;
		cout << "\n\tchange edge R1 R2 25" << endl;
		cout << "\n\nType End or end to go back " << endl;

		cout << "\n\t\tInput Here : ";

		getline(cin, commad);

		system("cls");
		cout << " Command being Proccessed " << commad << " ...\n\n";
		int i = 0;
		string ins;
		while (commad[i] != ' ' && commad[i] != '\0')
			ins += commad[i++];
		i++;

		if (ins == "Send" || ins == "send")
		{
			int x = i;
			ins = "\0";
			while (commad[x] != ' ')
				ins += commad[x++];
			if (ins != "msg")
			{
				string array[5];
				int j = 0;
				while (commad[i] != '\0' && j < 5)
				{
					if (commad[i] != ' ')
					{
						array[j] += commad[i];
					}
					else
					{
						j++;
					}
					i++;
				}
				M.id = stoi(array[0]);
				M.priority = stoi(array[1]);
				M.sourceAddress = array[2];
				M.destinationAddress = array[3];
				M.payload = array[4];
				o.sendMessage(M);
			}
			else
			{
				i++;
				while (commad[i++] != ' ') {}

				string str;
				while (commad[i] != '\0')
					str += commad[i++];
				o.readMessage(str);
			}
		}
		if (ins == "print" || ins == "Print")
		{
			while (commad[i++] != ' ') {}
			string str, str2;
			while (commad[i] != ' ')
			{
				str += commad[i++];
			}
			if (str == "*")
			{
				i++;
				while (commad[i++] != ' ') {}
				str = "\0";
				while (commad[i] != '\0')
				{
					str += commad[i++];
				}
				o.pathallto1(str);
			}
			else
			{
				i++;
				while (commad[i++] != ' ') {
				}

				while (commad[i] != '\0')
				{
					str2 += commad[i++];
				}
				if (str2 == "*")
				{
					o.path1toall(str);
				}
				else
				{
					o.path1to1(str, str2);
				}
			}
		}
		if (ins == "change" || ins == "Change")
		{
			i++;
			while (commad[i++] != ' ') {}

			while (commad[i] != ' ')
			{
				str1 += commad[i++];
			}
			i++;

			while (commad[i] != ' ')
			{
				str2 += commad[i++];
			}
			i++;

			while (commad[i] != '\0')
			{
				str3 += commad[i++];
			}

			o.changeedge(str1, str2, stoi(str3));
			goto commandmenu;
		}
		if (ins == "end" || ins == "End")
		{
			goto mainmenu;
		}
		else
		{
			cout << "\nwrongInput\n";
		}
		goto commandmenu;
	}

}