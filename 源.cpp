#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <fstream>
#include<stdlib.h>
#include<stdio.h>
#include <string>
#include <iomanip>
#include <cmath>
#include <conio.h>
using namespace std;

struct Timetable		//������Ϣ�ṹ��
{
	char no[10];//����
	int hour;//����ʱ�䣨ʱ��
	int minute;//����ʱ�䣨�֣�
	char Starting_station[10];//ʼ��վ
	char Last_station[10];//�յ�վ
	float time;//�г�ʱ��
	int fare;  //Ʊ��
	int max_number;//����ؿ���
	int sold_number;//����Ʊ��
};
struct IDinformation//�˿������Ϣ�ṹ��
{
	char name[10];//�˿���Ϣ
	char ID[20];//�˿�ID
	char no1[10];//�˿���������������
	char buydata[40];//�˿͹�Ʊʱ�䣬������ʱ����
};
//����ԭ������
void GetPwd(char* pwd);  //��ȡ����
void Signin(char* password);//��¼
int AddBus(Timetable* timetables, int n);  //���ӳ���
int find(Timetable* timetables, int n, char* no);  //�����β���
int find(Timetable* timetables, int n, char* Last_station, int* b);  //���յ�վ����
int DelBus(Timetable* timetables, int n);  //ɾ������
int AdminWindowSelect();  //����Աѡ�񴰿�
int MainWindowSelect();  //��ѡ�񴰿�
int PassagerWindowSelect();  //�˿�ѡ�񴰿�
void TicketDelete(Timetable* timetables, int n);  //��Ʊ
int TicketOrder(Timetable* timetables, int n, IDinformation* IDs, int t);   //��Ʊ
int StopSerive(Timetable* timetables, int n, char* no);  //ֹͣ����
void ShowTimetable(Timetable* timetables, int n);   //��ʾ���г���
void ShowTitle();   //��ʾ����
void ShowBusInfo(Timetable* timetables, int n, int idx);   //��ʾһ��������Ϣ
int ReadFromFile(Timetable* timetables, char* filename);   //���ļ�filename�����ṹ������
void inttostr(int n, char* str);   //����ת�����ַ���
void GenerateLogFileName(char* filename);   //������־�ļ���
int WritetoFile(Timetable* timetables, int n, char* filename);  //��n��Ԫ�صĽṹ������timetablesд���ļ�filename
int QueryWindowSelect();   //��ѯѡ�񴰿�
void Query(Timetable* timetables, int n);   //�����λ�Ŀ�ĵز�ѯ����ʾ
void AdminMode(Timetable* timetables, char* password, char* filename, IDinformation* IDs);  //����Աģʽ
void SortbyTime(Timetable* timetables, int n);   //������ʱ����������
void PassagerMode(Timetable* timetables, IDinformation* IDs, int t, char* filename);  //�˿�ģʽ
int InitializaionPassageMode(Timetable* timetables, char* LogFileName, char* filename);//�ж���־����ȡ�ļ�
void change(char* password);//�����������
void passwordstart();//�������ʼ��123
void passwordin(char* password);//���ļ���ȡԭʼ����
int informationin(IDinformation* IDs);//���ļ���ȡ֮ǰ���еĳ˿���Ϣ
void writeIDs(IDinformation* IDs, int t);//�ѳ˿������Ϣд���ļ�
void showinformation(IDinformation* IDs);//��ʾ���г˿͹�Ʊ��Ϣ
void GetPwd(char* pwd)  //��ȡ�������������ַ���ת��Ϊ*��ʾ
{
	cin.sync();//���cin�������������
	int i = 0;
	char ch;

	while (1)
	{
		ch = _getch();//��ͷ�ļ�conio.h�У��Ӽ����϶�ȡһ���ַ�
		if (ch == '\r')  break; //'\r' ��ʾ�س���
		else if (ch == '\b') { cout << "\b \b";   i--; }  //'\b'��ʾ�˸��
		else { pwd[i++] = ch;	cout << '*'; }
	}
	pwd[i] = '\0';
	cout << '\n';
}
void Signin(char* password)      //����Ա��¼
{
	char ID[20];   //��Ź���Ա����
	char pwd[20];  //�������
	cin.sync();  //���cin�������������

	do
	{
		cout << "�������Ա���֣�";
		cin >> ID;
		cout << "�������룺";//������ʾ
		GetPwd(pwd);//�������벢ת����*��	
		if (strcmp(ID, "admin") == 0 && strcmp(pwd, password) == 0)
			break;

		cout << "�û�����������������룺\n";
	} while (1);

	cout << "��¼�ɹ���\n";
	system("pause");
}
int AddBus(Timetable* timetables, int n)     //���ӳ��Σ������ĵ���Ϣ��ӵ��ļ���     
{
	char no[10];
	int k;          //�ҵ�����ĳ��κ�
	while (1)
	{
		cout << "������Ҫ��ӵĳ��κ�:";
		cin >> no;
		k = find(timetables, n, no);//�ҵ�����ĳ��κ�
		if (k != -1)
		{
			cout << "�ó����Ѿ����ڣ�������ӣ�����������";
		}
		else
		{
			strcpy(timetables[n].no, no);
			cout << "�����뷢��ʱ�䣨Сʱ��:";
			cin >> timetables[n].hour;
			cout << "�����뷢��ʱ�䣨���ӣ�:";
			cin >> timetables[n].minute;
			cout << "������ʼ��վ:";
			cin >> timetables[n].Starting_station;
			cout << "�������յ�վ:";
			cin >> timetables[n].Last_station;
			cout << "�������г�ʱ��:";
			cin >> timetables[n].time;
			cout << "������Ʊ��:";
			cin >> timetables[n].fare;
			cout << "����������ؿ���:";
			cin >> timetables[n].max_number;
			cout << "����������Ʊ��:";
			cin >> timetables[n].sold_number;
			cout << "���ӳɹ�";
			break;
		}
	}
	return (n + 1);//����������һ�˳������еĳ�����
}
int find(Timetable* timetables, int n, char* no)	  //�����β���
{
	int i = 0, k=1;//i�Ǽ�����k���ж������κ��Ƿ�һ��
	for (i = 0; i < n; i++)
	{
		k = strcmp(timetables[i].no, no);
		if (k == 0)
		{
			break;
		}
	}
	if (k == 0)
	{
		return i;//���������κ�һ�µĳ������ڵ�λ��
	}
	else
	{
		return -1;//����-1����ʾδ�ҵ�
	}
}
int find(Timetable* timetables, int n, char* Last_station, int* b)  //���յ�վ����  
{
	int j = 0;  //���ͬһ�յ�վ������
	int i = 0, k;//i�Ǽ�����k���ж������κ��Ƿ�һ��
	for (i = 0; i < n; i++)
	{
		k = strcmp(timetables[i].Last_station, Last_station);
		if (k == 0)
		{
			b[j] = i;//��¼���з��ϵĳ�������λ��
			j++;
		}
	}
	if (j > 0) return j;//���ط��������ĳ��θ���

	return -1; //û�в鵽��Ӧ�յ�վ�ĳ���ʱ����ֵ-1
}
int DelBus(Timetable* timetables, int n)   //ɾ������,�����³����ļ�
{
	char no[10];
	int t, i;
	while (1)
	{
		cout << "��������Ҫɾ���ĳ��κ�:";
		cin >> no;
		t = find(timetables, n, no);
		if (t == -1)
		{
			cout << "�˳��������ڣ�ɾ������,����������" << endl;;
			break;
		}
		if (t == n - 1)//��Ϊλ������������ܳ�������һ��ʾɾ������
		{
			n = n - 1;
			cout << "ɾ���ɹ�" << endl;
			break;
		}
		if (t < n - 1 && t >= 0)
		{
			for (i = t; i < n - 1; i++)
			{
				timetables[i] = timetables[i + 1];//��λ�ò��������֮�����г���λ����ǰ1λ
			}
			n = n - 1;
			cout << "ɾ���ɹ���" << endl;
			break;
		}
	}
	return n;//�������г�������
}
int AdminWindowSelect() 				//����Ա�˵�����
{
	int num;//��ʾѡ���ѡ��
	while (1)
	{
		system("cls");
		cout << "\n                *********** ����Ա���� ***************\n\n";
		cout << "                           1�����ӳ�����Ϣ\n";
		cout << "                           2��������Ϣ���\n";
		cout << "                           3��������Ϣ��ѯ\n";
		cout << "                           4��ע��������Ϣ\n";
		cout << "                           5���鿴���г˿͹�Ʊ��Ϣ(��bug)\n";
		cout << "                           6����������\n";
		cout << "                           7������\n";
		cout << "\n                **************************************\n";
		cout << "                  ��ѡ��(1-7): ";
		cin.sync();
		cin >> num;
		if (num >= 1 && num <= 7)
			break;
	}
	return num;//����ѡ�е�ѡ���
}
int MainWindowSelect()  //�����ڲ˵�
{
	int num;//��ʾѡ���ѡ��
	while (1)
	{
		system("cls");
		cout << "\n               *********** ��ӭʹ�ó�Ʊ����ϵͳ ***********\n\n";
		cout << "                              1.����Ա����\n";
		cout << "                              2.�˿͹���\n";
		cout << "                              3.�˳�\n";
		cout << "\n               ********************************************\n";
		cout << "               ��ѡ��(1-3): ";
		cin >> num;
		if (num >= 1 && num <= 3)
			break;
	}
	return num;//����ѡ�е�ѡ���
}
int PassagerWindowSelect()    //�˿͹���
{
	int num;//��ʾѡ���ѡ��
	while (1)
	{
		system("cls");
		cout << "\n                ************** �˿͹��� **************\n\n";
		cout << "                            1��������Ϣ��ѯ\n";
		cout << "                            2����        Ʊ\n";
		cout << "                            3����        Ʊ\n";
		cout << "                            4����        ��\n";
		cout << "\n                **************************************\n";
		cout << "                  ��ѡ��(1-4): ";
		cin >> num;
		if (num >= 1 && num <= 4)
			break;
	}
	return num;//����ѡ�е�ѡ���
}
void TicketDelete(Timetable* timetables, int n)   //��Ʊ
{
	char no[10];
	int k;//�ҵ��ĳ���λ��
	system("cls");
	while (1)
	{
		cout << "����������Ҫ��Ʊ�ĳ���(����0������һ��)";
		cin >> no;
		if (no[0] == '0' && no[1] == '\0')
		{
			break;
		}
		k = find(timetables, n, no);
		if (k == -1)
		{
			cout << "�ó��β����ڣ�����������";
		}
		if (k >= 0)
		{
			ShowTitle();//��ʾ�����Ϣ
			ShowBusInfo(timetables, n, k);
			int s;//�ж�ʱ�䣬�Ƿ�����Ʊ
			s = StopSerive(timetables, n, no);
			if (s == 1)
			{
				cout << "�ð೵��ֹͣ��Ʊ,�޷���Ʊ!";
				break;
			}
			cout << "�����˶���Ʊ��";
			int ticket;
			cin >> ticket;//�˶��ĳ�Ʊ��
			if (ticket > timetables[k].sold_number)
			{
				cout << "��Ʊ����������Ʊ����������ȷ����Ʊ��";
				break;
			}
			if (ticket <= timetables[k].sold_number)
			{
				timetables[k].sold_number = timetables[k].sold_number - ticket;
				cout << "����Ϊ" << timetables[k].no << "��Ʊ�ɹ�" << endl;
				break;
			}
		}
	}
}
int TicketOrder(Timetable* timetables, int n, IDinformation* IDs, int t)  //��Ʊ    
{
	char no[10];
	int k;//�ҵ�����λ��
	system("cls");
	while (1)
	{
		cout << "����������Ҫ����ĳ���(����0������һ��)";
		cin >> no;
		if (no[0] == '0' && no[1] == '\0')
		{
			break;
		}
		k = find(timetables, n, no);
		if (k == -1)
		{
			cout << "�ó��β����ڣ�����������";
		}
		if (k >= 0)
		{
			ShowTitle();
			ShowBusInfo(timetables, n, k);//��ʾ��س���
			int s;
			s = StopSerive(timetables, n, no);//�ж�ʱ�䣬�Ƿ�����Ʊ
			if (s == 1)
			{
				cout << "�ó���Ʊ���������ֹͣ��Ʊ!";
				break;
			}
			cout << "���빺��Ʊ��";
			int ticket;
			cin >> ticket;//����Ʊ��
			if (ticket > (timetables[k].max_number - timetables[k].sold_number))
			{
				cout << "��Ʊ����";
				break;
			}
			if (ticket <= (timetables[k].max_number - timetables[k].sold_number))
			{
				timetables[k].sold_number = timetables[k].sold_number + ticket;
				for (int j = 1; j <= ticket; j++)//���г˿���Ϣ��ѯ
				{
					cout << "������˿�" << j << "�������Ϣ��" << endl;
					cout << "������";
					cin >> IDs[t].name;
					cout << "ID���룺";
					cin >> IDs[t].ID;
					strcpy(IDs[t].no1, no);
					t++;
				}
				cout << "����Ϊ" << timetables[k].no << "��Ʊ�ɹ�" << endl;
				break;
			}
		}
	}
	return t;//�������Ӻ��ļ����еĳ˿���Ϣ��
}
int StopSerive(Timetable* timetables, int n, char* no) //�ж��Ƿ�ֹͣ��Ʊ����Ʊ��0:���ԣ�1��������   
{
	struct tm* local;       //struct tm ʱ��ṹ������
	time_t t;				//�ѵ�ǰʱ���t
	t = time(NULL);
	local = localtime(&t);      //��ȡ��ǰϵͳʱ�� 
	int i = find(timetables, n, no);

	if ((local->tm_hour * 60 + local->tm_min) + 10 < (timetables[i].hour * 60 + timetables[i].minute))
		return 0;
	return 1;
}
void ShowTimetable(Timetable* timetables, int n)    //��ʾȫ��������Ϣ
{
	int i = 0;
	SortbyTime(timetables, n);//�Է���ʱ���������
	ShowTitle();
	for (i = 0; i < n; i++)
	{
		ShowBusInfo(timetables, n, i);//��ʾ������Ϣ
	}

}
void ShowTitle() //��ʾ���α���
{
	system("cls");
	cout << "\n\n***************************** ������Ϣ *********************************\n";
	cout << "\n���\tʱ��\t���\t�յ�\tʱ��\tƱ��\t���\t����Ʊ\t�Ƿ񷢳�\n\n";
}
void ShowBusInfo(Timetable* timetables, int n, int idx)   //��ʾ��idx������Ϣ   
{
	cout << timetables[idx].no << '\t';
	cout << timetables[idx].hour << ':';
	cout << timetables[idx].minute << '\t';
	cout << timetables[idx].Starting_station << '\t';
	cout << timetables[idx].Last_station << '\t';
	cout << timetables[idx].time << '\t';
	cout << timetables[idx].fare << '\t';
	cout << timetables[idx].max_number << '\t';
	cout << timetables[idx].sold_number << '\t';
	{
		//�ж��Ƿ񷢳�
		struct tm* local;       //struct tm ʱ��ṹ������
		time_t t;				//�ѵ�ǰʱ���t
		t = time(NULL);
		local = localtime(&t);      //��ȡ��ǰϵͳʱ�� 
		if ((local->tm_hour * 60 + local->tm_min) < (timetables[idx].hour * 60 + timetables[idx].minute))
		{
			cout << "δ����" << '\t';
		}
		else
		{
			cout << "�ѷ���" << '\t';
		}
	}
	cout << endl;
}
int ReadFromFile(Timetable* timetables, char* filename)//���ļ���ȡ������Ϣ
{
	int i = 0;  //��������
	ifstream infile;
	infile.open(filename);
	if (!infile)
	{
		cout << "�ļ��򿪴���";
		system("pause");
		return (-1);//����-1��ʾ����
		exit(1);
	}
	else
	{
		while (!infile.eof())
		{
			infile >> timetables[i].no;
			infile >> timetables[i].hour;
			infile >> timetables[i].minute;
			infile >> timetables[i].Starting_station;
			infile >> timetables[i].Last_station;
			infile >> timetables[i].time;
			infile >> timetables[i].fare;
			infile >> timetables[i].max_number;
			infile >> timetables[i].sold_number;
			i++;
		}
		return i;//�������г��ε�����
	}
	infile.close();
}
void inttostr(int n, char* str) //������ת�����ַ���
{
	/*int k;
 int i=0,t,j=0;
	while(n!=0)
	{
	t=n%10;
	str[j]=t+48;//ͨ��ASCII�����������ַ�ת��
	j++;
	n=n/10;
	}
	str[j]='\0';//�ַ�����β����Ҫ�С�\0�������������
	j--;
	for(i=0;i<=j;i++,j--)
	{
	k=str[i];
	str[i]=str[j];
	str[j]=k;
	}*/
	_itoa(n, str, 10);//itoa������������ת��Ϊ�ַ������ʵ�ʹ�ÿ⺯�����Խ�ʡ��������������Ϸ������˷Ǻ���ʵ�ַ�ʽ
}
void GenerateLogFileName(char* filename)  //������־�ļ����ļ���
{
	filename[0] = '\0';
	struct tm* local;				//ʱ��ṹ�� 
	time_t t;                       //�ѵ�ǰʱ���t
	t = time(NULL);					//NULL��stdio.h�ж���Ϊ0
	local = localtime(&t);			//��ȡ��ǰϵͳʱ�� 

	char year[5], month[3], day[3];	//�������շֱ�ת�����ַ�����
	inttostr(1900 + local->tm_year, year);
	inttostr(1 + local->tm_mon, month);
	inttostr(local->tm_mday, day);
	strcat(filename, year);			//������־�ļ���
	strcat(filename, "-");
	strcat(filename, month);
	strcat(filename, "-");
	strcat(filename, day);
	strcat(filename, ".log");
}
int WritetoFile(Timetable* timetables, int n, char* filename)//��������Ϣд���ļ�
{
	ofstream out;
	out.open(filename);
	int i = 0;
	for (i = 0; i < n; i++)
	{
		out << timetables[i].no << '\t';
		out << timetables[i].hour << '\t';
		out << timetables[i].minute << '\t';
		out << timetables[i].Starting_station << '\t';
		out << timetables[i].Last_station << '\t';
		out << timetables[i].time << '\t';
		out << timetables[i].fare << '\t';
		out << timetables[i].max_number << '\t';
		if (i < n - 1)//����Ҫ�ж��Ƿ�Ϊ���һ�У������ļ����������
		{
			out << timetables[i].sold_number << endl;
		}
		else
		{
			out << timetables[i].sold_number;
		}
	}
	out.close();
	return 0;
}
int QueryWindowSelect()
{
	int num;
	while (1)
	{
		system("cls");
		cout << "\n                   ********** ������Ϣ��ѯ **********\n\n";
		cout << "                             1�������κŲ�ѯ\n";
		cout << "                             2�����յ�վ��ѯ\n";
		cout << "                             3���� ��  �� ѯ\n";
		cout << "\n                   **********************************\n";
		cout << "                     ��ѡ��(1-3):";
		cin >> num;
		if (num >= 1 && num <= 3)
			break;
	}
	return num;//����ѡ�����
}
void Query(Timetable* timetables, int n)  //���β�ѯ
{
	int num;
	int i;
	char no[10];//��ѯ���κ�
	char Last_station[10];//��ѯ�յ�վ
	int b[100];//��¼������λ��
	while (1)
	{
		num = QueryWindowSelect();
		switch (num)
		{
		case 1:

		{
			cout << "��������Ҫ��ѯ�ĳ��κţ�";
			cin >> no;
			i = find(timetables, n, no);//�ҵ��ĳ���λ��
			if (i == -1)
			{
				cout << "δ�ҵ�������ѯ�ĳ���" << endl; system("pause"); break;
			}
			else
			{
				ShowTitle();
				ShowBusInfo(timetables, n, i);
				cout << endl;
				system("pause");
				break;
			}
		}
		case 2:
		{
			cout << "�������յ�վ����";
			cin >> Last_station;
			i = find(timetables, n, Last_station, b);//�ҵ����ϵĳ�������
			if (i == -1)
			{
				cout << "û�и��յ�վ�ĳ���" << endl; system("pause"); break;
			}
			else
			{
				int k = 0;
				ShowTitle();
				for (k = 0; k < i; k++)
				{
					ShowBusInfo(timetables, n, b[k]);
				}
				cout << endl;
				system("pause");
				break;
			}
		}
		case 3:
		{
			return;
			break;
		}
		}
	}
	system("pause");
}
int InitializaionPassageMode(Timetable* timetables, char* LogFileName, char* filename)//�ж϶�ȡд����־�ļ�
{
	int n = 0; //��������
	ifstream infile;
	infile.open(LogFileName);
	if (!infile)
	{
		n = ReadFromFile(timetables, filename);
		for (int i = 0; i < n; i++)
		{
			timetables[i].sold_number = 0;
		}
		WritetoFile(timetables, n, LogFileName);
	}
	else
	{
		n = ReadFromFile(timetables, LogFileName);
	}
	infile.close();
	return n;//�������г�����
}
void SortbyTime(Timetable* timetables, int n)//��������Ϣ��������
{
	int i = 0, tt1, tt2, j = 0;//ð������
	Timetable t1;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - 1 - i; j++)
		{
			tt1 = timetables[j].hour * 60 + timetables[j].minute;
			tt2 = timetables[j + 1].hour * 60 + timetables[+1].minute;
			if (tt1 > tt2)
			{
				t1 = timetables[j]; timetables[j] = timetables[j + 1]; timetables[j + 1] = t1;
			}
		}

	}
}
void change(char* password)//��������
{
	char newpassword1[20];//�������������룬�����������ȶ�
	char newpassword2[20];
	char pass[20];
	int num, a, b;
	cout << "��ȷ��Ҫ����������(����1��ʾȷ��������2����)";
	cin >> num;
	if (num == 1)
	{
		cout << "������ԭʼ���룺";
		cin >> pass;
		a = strcmp(password, pass);//��������ȶ�
		if (a == 0)
		{
			cout << "�����������룺";
			cin >> newpassword1;
			cout << "���ٴ����������룺";
			cin >> newpassword2;
			b = strcmp(newpassword1, newpassword2);
			if (b == 0)
			{
				strcpy(password, newpassword1);//��������ȶ�
				cout << "���óɹ�" << endl;
			}
			else
			{
				cout << "�������벻һ��" << endl;
			}
		}
		else
		{
			cout << "ԭ�����������" << endl;
		}
	}
	ofstream out;
	out.open("����.txt");
	out << password;//�����ĵ�����д���ļ�
	out.close();

}
void passwordstart()//��������г�ʼ�����ʼ������Ϊ123
{
	ofstream out;
	out.open("����.txt");
	char password[20] = "123";
	out << password;
	out.close();
}
void passwordin(char* password)//���ļ��������
{
	ifstream in;
	in.open("����.txt");
	if (!in)//���û���ҵ�����ļ����ͳ�ʼ������Ϊ123
	{
		passwordstart();
		password = "123";
	}
	else
	{
		while (!in.eof())//���ҵ���������ж�ȡ����
		{
			in >> password;
		}
	}
	in.close();
}
int informationin(IDinformation* IDs)//�˿���Ϣ��ȡ
{
	int i = 0;
	ifstream in;
	in.open("�˿͸�����Ϣ.txt");
	if (!in)
	{
		i = 0;
	}
	else
	{
		while (!in.eof())
		{
			in >> IDs[i].name;
			in >> IDs[i].ID;
			in >> IDs[i].no1;
			in >> IDs[i].buydata;
			i++;
		}
	}
	return i;//���س˿���Ϣ����
	in.close();

}
void writeIDs(IDinformation* IDs, int t)//���˿���Ϣд���ļ�
{
	IDinformation IDnumber;
	ifstream in;
	int k = 0;
	in.open("�˿͸�����Ϣ.txt");
	while (!in.eof())//�ж����г˿���Ϣ��
	{
		in >> IDnumber.name;
		in >> IDnumber.ID;
		in >> IDnumber.no1;
		in >> IDnumber.buydata;
		k++;
	}
	in.close();
	ofstream out;
	out.open("�˿͸�����Ϣ.txt");
	int i = 0;
	for (i = 0; i < t; i++)//��֤�����˿�֮ǰ�����ݲ��ܸı䣬֮������ݿ��Ըı�
	{
		if (i < k)
		{
			out << IDs[i].name << '\t';
			out << IDs[i].ID << '\t';
			out << IDs[i].no1 << '\t';
			out << IDs[i].buydata << endl;
		}
		else
		{
			out << IDs[i].name << '\t';
			out << IDs[i].ID << '\t';
			out << IDs[i].no1 << '\t';
			IDs[i].buydata[0] = '\0';
			struct tm* local;       //struct tm ʱ��ṹ������
			time_t t1;				//�ѵ�ǰʱ���t
			t1 = time(NULL);
			local = localtime(&t1);
			char year[5], month[3], day[3], hour[3], min[3], sec[3];	//�������շֱ�ת�����ַ�����
			inttostr(1900 + local->tm_year, year);
			inttostr(1 + local->tm_mon, month);
			inttostr(local->tm_mday, day);
			inttostr(local->tm_hour, hour);
			inttostr(local->tm_min, min);
			inttostr(local->tm_sec, sec);
			strcat(IDs[i].buydata, year);			//���ɹ�Ʊʱ��
			strcat(IDs[i].buydata, "-");
			strcat(IDs[i].buydata, month);
			strcat(IDs[i].buydata, "-");
			strcat(IDs[i].buydata, day);
			strcat(IDs[i].buydata, "-");
			strcat(IDs[i].buydata, hour);
			strcat(IDs[i].buydata, ":");
			strcat(IDs[i].buydata, min);
			strcat(IDs[i].buydata, ":");
			strcat(IDs[i].buydata, sec);
			if (i < t - 1)//�ж��Ƿ�Ϊ���һ��
			{
				out << IDs[i].buydata << endl;
			}
			else
			{
				out << IDs[i].buydata;
			}
		}

	}
	out.close();
}
void showinformation(IDinformation* IDs)//��ʾ�˿���Ϣ
{
	ifstream in;
	in.open("�˿͸�����Ϣ.txt");
	int i = 0;
	while (!in.eof())
	{
		in >> IDs[i].name;
		in >> IDs[i].ID;
		in >> IDs[i].no1;
		in >> IDs[i].buydata;
		i++;
	}//ͳ�Ƴ˿�����
	cout << setw(10) << "����" << setw(15) << "ID��" << setw(10) << "���κ�" << setw(25) << "��Ʊʱ��" << endl;
	for (int j = 0; j < i; j++)//����˿���
	{
		cout << setw(10) << IDs[j].name;
		cout << setw(15) << IDs[j].ID;
		cout << setw(10) << IDs[j].no1;
		cout << setw(25) << IDs[j].buydata << endl;
	}

}
void PassagerMode(Timetable* timetables, IDinformation* IDs, int t, char* filename) //�˿͹���
{
	char LogFileName[200];    //�����־�ļ�����
	int n;
	GenerateLogFileName(LogFileName);//���ݵ�ǰ����������־�ļ���
	n = InitializaionPassageMode(timetables, LogFileName, filename);
	int PassagerChoice;
	while (1)
	{
		switch (PassagerChoice = PassagerWindowSelect())
		{
		case 1: Query(timetables, n); system("pause"); break;//������Ϣ��ѯ
		case 2: t = TicketOrder(timetables, n, IDs, t); WritetoFile(timetables, n, LogFileName); writeIDs(IDs, t); system("pause"); break;  //��Ʊ���������ļ���Ϣ
		case 3: TicketDelete(timetables, n); WritetoFile(timetables, n, LogFileName); system("pause"); break;//��Ʊ���������ļ���Ϣ
		case 4: WritetoFile(timetables, n, LogFileName); 	return;//�����ϼ��˵�
		}
	}
}
void AdminMode(Timetable* timetables, char* password, char* filename, IDinformation* IDs)  //����Ա����
{
	int n;
	Signin(password);  //��¼
	n = ReadFromFile(timetables, "bus.txt");
	while (1)
	{
		int AdminChoice = AdminWindowSelect();
		switch (AdminChoice)
		{
		case 1:	n = AddBus(timetables, n); WritetoFile(timetables, n, filename); system("pause"); break;	//���ӳ�����Ϣ,����ʱд���ļ���
		case 2:	ShowTimetable(timetables, n); system("pause"); break;	//���ʱ�̱�
		case 3:	Query(timetables, n); system("pause"); break;	//������Ϣ��ѯ	   			
		case 4:	n = DelBus(timetables, n); system("pause"); WritetoFile(timetables, n, filename); break;//ע������,����ʱд���ļ���
		case 5: showinformation(IDs); system("pause"); break;//��ʾ�˿���Ϣ
		case 6: change(password); system("pause"); break;//��������
		case 7: WritetoFile(timetables, n, filename); return;//�����ϼ��˵�
		}
	}
}
int Quit()//�˳�ϵͳ
{
	cin.sync(); //������뻺����
	cout << "�˳�ϵͳ��(y/n)?";
	char ans;
	cin >> ans;
	if (ans == 'Y' || ans == 'y')
		return 1;
	return 0;
}
int main()
{
	int UserChoice;
	int t;
	system("color 3d");//���Ĳ���������ɫ
	Timetable timetables[100];
	IDinformation IDs[1000];
	char password[20];//������������
	passwordin(password);
	t = informationin(IDs);//�˿���Ϣ��
	while (1)
	{
		switch (UserChoice = MainWindowSelect())
		{
		case 1:  AdminMode(timetables, password, "bus.txt", IDs); break;	    //����Աģʽ
		case 2:  PassagerMode(timetables, IDs, t, "bus.txt"); break;	//�˿�ģʽ	
		case 3:  if (Quit() != 1) continue;				    //�˳�
		}
		if (UserChoice == 3) break;
	}

	return 0;
}