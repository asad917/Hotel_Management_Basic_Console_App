#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>
using namespace std;
int room_no, r_no;
char fname[15];
char lname[15];
string address;
char phone[20];
int in_min, in_hr, out_min, out_hr, in_day, in_month, in_yr, out_day, out_month, out_yr;
void main_menu();
int add();
void display();
void rooms();
void edit();
void delete_rec(int r);
bool check(int r);
void calculate_bill(int r);
void main_menu()
{
	int choice = 0;
	while (choice != 5)
	{
		system("cls");
		cout << "\n\t\t\t\t*************";
		cout << "\n\t\t\t\t* MAIN MENU *";
		cout << "\n\t\t\t\t*************";
		cout << "\n\n\n\t\t\t1.Book A Room";
		cout << "\n\t\t\t2.Customer Record";
		cout << "\n\t\t\t3.Rooms Allotted";
		cout << "\n\t\t\t4.Delete Record";
		cout << "\n\t\t\t5.Exit";
		cout << "\n\n\t\t\tEnter Your Choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1: add();
			break;
		case 2: display();
			break;
		case 3: rooms();
			break;
		case 4: edit();
			break;
		case 5: break;
		default:
		{
			cout << "\n\n\t\t\tWrong choice!!!";
			cout << "\n\t\t\tPress any key to continue!!";
			_getch();
		}
		}
	}
	return;
}
int add()
{
	system("cls");
	int r = 0, in_day = 0, in_month = 0, in_yr = 0;
	bool flag = 0;
	ofstream write_file;
	ofstream timeout("Recordbill.txt", ios::app);
	write_file.open("Record.txt", ios::app);
	cout << "\n Enter Customer Detalis";
	cout << "\n **********************";
	while (r <= 0 || r > 40)
	{
		cout << "\n\n Room no: (1-20 AC and 21-40 Non-Ac)";
		cin >> r;
	}
	flag = check(r);
	if (!flag)
	{
		cout << " Check In Date/Day :";

		cin >> in_day;
		cout << " Check In Month :";
		cin >> in_month;
		cout << " Check In Year :";
		cin >> in_yr;
		timeout << r << " " << in_day << " " << in_month << " " << in_yr << endl;
		cout << " First Name: (Without Space)";
		cin.ignore();
		cin.get(fname, 14);
		cin.ignore();
		cout << " Last Name: (Without Space)";
		cin.get(lname, 14);
		cin.ignore();
		cout << " Phone No: (Without Space)";
		cin.get(phone, 19);
		cin.ignore();
		cout << " Address:  ";
		getline(cin, address);
		cin.ignore();


		write_file << r << " ";
		write_file << fname << " ";
		write_file << lname << " ";
		write_file << phone << " ";
		write_file << address << "\n";
		cout << "\n Room is booked!!!";
		_getch();
	}

	else
		cout << "\n Sorry..!!!Room is already booked";
	write_file.close();
	timeout.close();
	cout << "\n Press any key to continue!!";
	_getch();
	return 0;
}
bool check(int r)
{
	bool flag = 0;
	ifstream read_file;
	read_file.open("Record.txt");
	while (!read_file.eof())
	{
		read_file >> room_no;
		getline(read_file, address);
		if (room_no == r)
		{
			flag = 1;
		}
	}
	read_file.close();
	return(flag);
}
void display()
{
	system("cls");
	ifstream read_file;
	read_file.open("Record.txt");
	int r;
	bool flag = 0;
	cout << "\n Enter room no: ";
	cin >> r;
	string line;
	while (!read_file.eof())
	{
		read_file >> room_no;
		getline(read_file, line);
		if (room_no == r)
		{
			system("cls");
			cout << "\n Cusromer Details";
			cout << "\n ****************\n\n";
			cout << room_no << " " << line << endl;
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		cout << "\n Sorry Room no. not found or vacant!!";
	cout << "\n\n Press any key to continue!!";
	_getch();
	read_file.close();
}
void rooms()
{
	system("cls");
	string line;
	int r_no1 = 0, r_no2 = 0;
	ifstream read_file;
	read_file.open("Record.txt");
	cout << "\n\t\t\tList Of Rooms Allotted";
	cout << "\n\t\t\t*********************";
	cout << "\n\n Room No--First Name--Last Name--Phone No--Address\n";
	while (!read_file.eof())
	{
		read_file >> room_no;
		getline(read_file, line);
		r_no2 = room_no;
		if (r_no1 != r_no2)
		{
			cout << room_no << " " << line << endl;
			r_no1 = r_no2;
		}
	}
	cout << "\n\n\n\t\t\tPress any key to continue!!";
	_getch();
	read_file.close();
}
void edit()
{
	system("cls");
	int  r = 0;
	cout << "\n DELETE RECORDE";
	cout << "\n *********";
	cout << "\n Enter room no: ";
	cin >> r;
	delete_rec(r);
}
void delete_rec(int r)
{
	int  r_no1 = 0, r_no2 = 0;
	char ch = '0';
	bool flag = false;
	string line;
	fstream fin("Record.txt", ios::in);
	fstream fout("temp.txt", ios::out);
	while (!fin.eof())
	{
		fin >> room_no;
		getline(fin, line);
		if (room_no == r)
		{
			cout << room_no << line;
			cout << "\n\n Do you want to delete this record(y/n): ";
			cin >> ch;
			if (ch == 'n')
			{
				r_no2 = room_no;
				if (r_no1 != r_no2)
				{
					fout << room_no << " " << line << endl;
					r_no1 = r_no2;
				}
				char choice = 'n';
				cout << "\n\nDo you want to go to main menu(y/n): ";
				if (choice == 'y')
					return;
			}
			flag = true;
			calculate_bill(r);
		}
		else
		{
			r_no2 = room_no;
			if (r_no1 != r_no2)
			{
				fout << room_no << " " << line << endl;
				r_no1 = r_no2;
			}
		}
	}
	fin.close();
	fout.close();
	fin.open("temp.txt", ios::in);
	fout.open("Record.txt", ios::out);
	while (!fin.eof())
	{
		fin.get(ch);
		fout << ch;
	}
	fin.close();
	fout.close();
	if (!flag)
		cout << "Sorry Room not found OR vacant!!\n";
	cout << "\n\n\n\t\t\tPress any key to continue!";
	_getch();

}
void calculate_bill(int r)
{
	fstream fin("Recordbill.txt", ios::in);
	fstream fout("tempbillRecord.txt", ios::app);
	int current_date, current_month, current_year, in_date, in_month, in_year;
	int month[] = { 31, 28, 31, 30, 31, 30, 31,31, 30, 31, 30, 31 };
	int r_no, r_no1 = 0, r_no2 = 0;
	string line;
	cout << "Enter Current date\n";
	cin >> current_date;
	cout << "Enter Current month\n";
	cin >> current_month;
	cout << "Enter Current year\n";
	cin >> current_year;
	while (!fin.eof())
	{
		fin >> r_no >> in_date >> in_month >> in_year;
		if (r_no == r)
		{
			if (in_date > current_date)
			{
				current_date = current_date + month[in_month - 1];
				current_month = current_month - 1;
			}
			if (in_month > current_month)
			{
				current_year = current_year - 1;
				current_month = current_month + 12;
			}
			int calculated_date = current_date - in_date;
			int calculated_month = current_month - in_month;
			int calculated_year = current_year - in_year;
			switch (calculated_month)
			{
			case 1:
				calculated_month = 31;
				break;
			case 2:
				calculated_month = 59;
				break;

			case 3:
				calculated_month = 90;
				break;
			case 4:
				calculated_month = 120;
				break;
			case 5:
				calculated_month = 151;
				break;
			case 6:
				calculated_month = 181;
				break;
			case 7:
				calculated_month = 212;
				break;
			case 8:
				calculated_month = 243;
				break;
			case 9:
				calculated_month = 273;
				break;
			case 10:
				calculated_month = 304;
				break;
			case 11:
				calculated_month = 334;
				break;
			case 12:
				calculated_month = 365;
				break;
			}
			int total_days = (calculated_year * 365) + (calculated_month)+calculated_date;
			if (r <= 20)
			{
				total_days *= 6000;
			}
			else if (r > 20)
			{
				total_days *= 3000;
			}
			int bill = total_days;
			cout << "Your Bill is Rs " << bill << "/-";
			break;
		}

	}


	fin.close();
	fout.close();

	fin.open("Recordbill.txt", ios::in);
	fout.open("tempbillRecord.txt", ios::app);

	while (!fin.eof())
	{
		fin >> room_no;
		getline(fin, line);

		if (room_no != r)
		{
			r_no2 = room_no;
			if (r_no1 != r_no2)
			{
				fout << room_no << " " << line << endl;
				r_no1 = r_no2;
			}

		}
	}

	fin.close();
	fout.close();

	fin.open("tempbillrecord.txt", ios::in);
	fout.open("Recordbill.txt", ios::out);
	char ch;
	while (!fin.eof())
	{
		fin.get(ch);
		fout << ch;
	}
	fin.close();
	fout.close();
	cout << "\n\t\t\tPress any key to continue!!";
	_getch();
	return;
}
void main()
{
	system("cls");
	cout << "\n\t\t\t****************************";
	cout << "\n\t\t\t* HOTEL MANAGEMENT SYSTEM  *";
	cout << "\n\t\t\t****************************";
	cout << "\n\n\n\n\t\tMade By: Asad Sarwar\n\n\n\n\n\t\t\tPress any key to continue!!";
	_getch();
	main_menu();
}