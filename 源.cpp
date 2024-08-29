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

struct Timetable		//车次信息结构体
{
	char no[10];//车次
	int hour;//发车时间（时）
	int minute;//发车时间（分）
	char Starting_station[10];//始发站
	char Last_station[10];//终点站
	float time;//行车时间
	int fare;  //票价
	int max_number;//最大载客数
	int sold_number;//已售票数
};
struct IDinformation//乘客身份信息结构体
{
	char name[10];//乘客信息
	char ID[20];//乘客ID
	char no1[10];//乘客所乘坐的汽车号
	char buydata[40];//乘客购票时间，年月日时分秒
};
//函数原型声明
void GetPwd(char* pwd);  //读取口令
void Signin(char* password);//登录
int AddBus(Timetable* timetables, int n);  //增加车次
int find(Timetable* timetables, int n, char* no);  //按车次查找
int find(Timetable* timetables, int n, char* Last_station, int* b);  //按终点站查找
int DelBus(Timetable* timetables, int n);  //删除车次
int AdminWindowSelect();  //管理员选择窗口
int MainWindowSelect();  //主选择窗口
int PassagerWindowSelect();  //顾客选择窗口
void TicketDelete(Timetable* timetables, int n);  //退票
int TicketOrder(Timetable* timetables, int n, IDinformation* IDs, int t);   //售票
int StopSerive(Timetable* timetables, int n, char* no);  //停止服务
void ShowTimetable(Timetable* timetables, int n);   //显示所有车次
void ShowTitle();   //显示标题
void ShowBusInfo(Timetable* timetables, int n, int idx);   //显示一个车次信息
int ReadFromFile(Timetable* timetables, char* filename);   //从文件filename读到结构体数组
void inttostr(int n, char* str);   //整数转换成字符串
void GenerateLogFileName(char* filename);   //产生日志文件名
int WritetoFile(Timetable* timetables, int n, char* filename);  //将n个元素的结构体数组timetables写入文件filename
int QueryWindowSelect();   //查询选择窗口
void Query(Timetable* timetables, int n);   //按车次或按目的地查询并显示
void AdminMode(Timetable* timetables, char* password, char* filename, IDinformation* IDs);  //管理员模式
void SortbyTime(Timetable* timetables, int n);   //按发车时间升序排序
void PassagerMode(Timetable* timetables, IDinformation* IDs, int t, char* filename);  //顾客模式
int InitializaionPassageMode(Timetable* timetables, char* LogFileName, char* filename);//判断日志，读取文件
void change(char* password);//进行密码更改
void passwordstart();//对密码初始化123
void passwordin(char* password);//从文件读取原始密码
int informationin(IDinformation* IDs);//从文件读取之前所有的乘客信息
void writeIDs(IDinformation* IDs, int t);//把乘客相关信息写入文件
void showinformation(IDinformation* IDs);//显示所有乘客购票信息
void GetPwd(char* pwd)  //读取口令，并将输入的字符串转换为*显示
{
	cin.sync();//清空cin数据流里的内容
	int i = 0;
	char ch;

	while (1)
	{
		ch = _getch();//在头文件conio.h中，从键盘上读取一个字符
		if (ch == '\r')  break; //'\r' 表示回车键
		else if (ch == '\b') { cout << "\b \b";   i--; }  //'\b'表示退格键
		else { pwd[i++] = ch;	cout << '*'; }
	}
	pwd[i] = '\0';
	cout << '\n';
}
void Signin(char* password)      //管理员登录
{
	char ID[20];   //存放管理员名字
	char pwd[20];  //存放密码
	cin.sync();  //清空cin数据流里的内容

	do
	{
		cout << "输入管理员名字：";
		cin >> ID;
		cout << "输入密码：";//输入提示
		GetPwd(pwd);//输入密码并转换成*号	
		if (strcmp(ID, "admin") == 0 && strcmp(pwd, password) == 0)
			break;

		cout << "用户或密码错误，重新输入：\n";
	} while (1);

	cout << "登录成功！\n";
	system("pause");
}
int AddBus(Timetable* timetables, int n)     //增加车次，将更改的信息添加到文件中     
{
	char no[10];
	int k;          //找到输入的车次号
	while (1)
	{
		cout << "请输入要添加的车次号:";
		cin >> no;
		k = find(timetables, n, no);//找到输入的车次号
		if (k != -1)
		{
			cout << "该车次已经存在，无需添加，请重新输入";
		}
		else
		{
			strcpy(timetables[n].no, no);
			cout << "请输入发车时间（小时）:";
			cin >> timetables[n].hour;
			cout << "请输入发车时间（分钟）:";
			cin >> timetables[n].minute;
			cout << "请输入始发站:";
			cin >> timetables[n].Starting_station;
			cout << "请输入终点站:";
			cin >> timetables[n].Last_station;
			cout << "请输入行车时间:";
			cin >> timetables[n].time;
			cout << "请输入票价:";
			cin >> timetables[n].fare;
			cout << "请输入最大载客数:";
			cin >> timetables[n].max_number;
			cout << "请输入已售票数:";
			cin >> timetables[n].sold_number;
			cout << "增加成功";
			break;
		}
	}
	return (n + 1);//返回增加了一趟车后现有的车辆数
}
int find(Timetable* timetables, int n, char* no)	  //按车次查找
{
	int i = 0, k=1;//i是计数，k是判断两车次号是否一致
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
		return i;//返回两车次号一致的车次所在的位置
	}
	else
	{
		return -1;//返回-1，表示未找到
	}
}
int find(Timetable* timetables, int n, char* Last_station, int* b)  //按终点站查找  
{
	int j = 0;  //存放同一终点站车次数
	int i = 0, k;//i是计数，k是判断两车次号是否一致
	for (i = 0; i < n; i++)
	{
		k = strcmp(timetables[i].Last_station, Last_station);
		if (k == 0)
		{
			b[j] = i;//记录所有符合的车次所在位置
			j++;
		}
	}
	if (j > 0) return j;//返回符合条件的车次个数

	return -1; //没有查到相应终点站的车次时返回值-1
}
int DelBus(Timetable* timetables, int n)   //删除车次,并更新车次文件
{
	char no[10];
	int t, i;
	while (1)
	{
		cout << "请输入你要删除的车次号:";
		cin >> no;
		t = find(timetables, n, no);
		if (t == -1)
		{
			cout << "此车辆不存在，删除错误,请重新输入" << endl;;
			break;
		}
		if (t == n - 1)//若为位置在最后，则以总车次数减一表示删除车次
		{
			n = n - 1;
			cout << "删除成功" << endl;
			break;
		}
		if (t < n - 1 && t >= 0)
		{
			for (i = t; i < n - 1; i++)
			{
				timetables[i] = timetables[i + 1];//若位置不在最后，则之后所有车次位置往前1位
			}
			n = n - 1;
			cout << "删除成功！" << endl;
			break;
		}
	}
	return n;//返回现有车次数量
}
int AdminWindowSelect() 				//管理员菜单界面
{
	int num;//表示选择的选项
	while (1)
	{
		system("cls");
		cout << "\n                *********** 管理员功能 ***************\n\n";
		cout << "                           1、增加车次信息\n";
		cout << "                           2、车次信息浏览\n";
		cout << "                           3、车次信息查询\n";
		cout << "                           4、注销车次信息\n";
		cout << "                           5、查看所有乘客购票信息(有bug)\n";
		cout << "                           6、更改密码\n";
		cout << "                           7、返回\n";
		cout << "\n                **************************************\n";
		cout << "                  请选择(1-7): ";
		cin.sync();
		cin >> num;
		if (num >= 1 && num <= 7)
			break;
	}
	return num;//返回选中的选项号
}
int MainWindowSelect()  //主窗口菜单
{
	int num;//表示选择的选项
	while (1)
	{
		system("cls");
		cout << "\n               *********** 欢迎使用车票管理系统 ***********\n\n";
		cout << "                              1.管理员功能\n";
		cout << "                              2.顾客功能\n";
		cout << "                              3.退出\n";
		cout << "\n               ********************************************\n";
		cout << "               请选择(1-3): ";
		cin >> num;
		if (num >= 1 && num <= 3)
			break;
	}
	return num;//返回选中的选项号
}
int PassagerWindowSelect()    //顾客功能
{
	int num;//表示选择的选项
	while (1)
	{
		system("cls");
		cout << "\n                ************** 顾客功能 **************\n\n";
		cout << "                            1、车次信息查询\n";
		cout << "                            2、购        票\n";
		cout << "                            3、退        票\n";
		cout << "                            4、返        回\n";
		cout << "\n                **************************************\n";
		cout << "                  请选择(1-4): ";
		cin >> num;
		if (num >= 1 && num <= 4)
			break;
	}
	return num;//返回选中的选项号
}
void TicketDelete(Timetable* timetables, int n)   //退票
{
	char no[10];
	int k;//找到的车次位置
	system("cls");
	while (1)
	{
		cout << "请输入你所要退票的车次(输入0返回上一层)";
		cin >> no;
		if (no[0] == '0' && no[1] == '\0')
		{
			break;
		}
		k = find(timetables, n, no);
		if (k == -1)
		{
			cout << "该车次不存在，请重新输入";
		}
		if (k >= 0)
		{
			ShowTitle();//显示相关信息
			ShowBusInfo(timetables, n, k);
			int s;//判断时间，是否能退票
			s = StopSerive(timetables, n, no);
			if (s == 1)
			{
				cout << "该班车已停止退票,无法退票!";
				break;
			}
			cout << "输入退订的票数";
			int ticket;
			cin >> ticket;//退订的车票数
			if (ticket > timetables[k].sold_number)
			{
				cout << "退票数大于已售票数，请重新确认退票数";
				break;
			}
			if (ticket <= timetables[k].sold_number)
			{
				timetables[k].sold_number = timetables[k].sold_number - ticket;
				cout << "车次为" << timetables[k].no << "退票成功" << endl;
				break;
			}
		}
	}
}
int TicketOrder(Timetable* timetables, int n, IDinformation* IDs, int t)  //购票    
{
	char no[10];
	int k;//找到车次位置
	system("cls");
	while (1)
	{
		cout << "请输入你所要购买的车次(输入0返回上一层)";
		cin >> no;
		if (no[0] == '0' && no[1] == '\0')
		{
			break;
		}
		k = find(timetables, n, no);
		if (k == -1)
		{
			cout << "该车次不存在，请重新输入";
		}
		if (k >= 0)
		{
			ShowTitle();
			ShowBusInfo(timetables, n, k);//显示相关车次
			int s;
			s = StopSerive(timetables, n, no);//判断时间，是否能退票
			if (s == 1)
			{
				cout << "该车次票已售完或已停止售票!";
				break;
			}
			cout << "输入购买票数";
			int ticket;
			cin >> ticket;//购买车票数
			if (ticket > (timetables[k].max_number - timetables[k].sold_number))
			{
				cout << "车票不足";
				break;
			}
			if (ticket <= (timetables[k].max_number - timetables[k].sold_number))
			{
				timetables[k].sold_number = timetables[k].sold_number + ticket;
				for (int j = 1; j <= ticket; j++)//进行乘客信息查询
				{
					cout << "请输入乘客" << j << "的身份信息：" << endl;
					cout << "姓名：";
					cin >> IDs[t].name;
					cout << "ID号码：";
					cin >> IDs[t].ID;
					strcpy(IDs[t].no1, no);
					t++;
				}
				cout << "车次为" << timetables[k].no << "购票成功" << endl;
				break;
			}
		}
	}
	return t;//返回增加后文件含有的乘客信息数
}
int StopSerive(Timetable* timetables, int n, char* no) //判断是否停止售票或退票，0:可以，1：不可以   
{
	struct tm* local;       //struct tm 时间结构体类型
	time_t t;				//把当前时间给t
	t = time(NULL);
	local = localtime(&t);      //获取当前系统时间 
	int i = find(timetables, n, no);

	if ((local->tm_hour * 60 + local->tm_min) + 10 < (timetables[i].hour * 60 + timetables[i].minute))
		return 0;
	return 1;
}
void ShowTimetable(Timetable* timetables, int n)    //显示全部车次信息
{
	int i = 0;
	SortbyTime(timetables, n);//对发车时间进行排序
	ShowTitle();
	for (i = 0; i < n; i++)
	{
		ShowBusInfo(timetables, n, i);//显示车次信息
	}

}
void ShowTitle() //显示车次标题
{
	system("cls");
	cout << "\n\n***************************** 车次信息 *********************************\n";
	cout << "\n班次\t时间\t起点\t终点\t时长\t票价\t额定量\t已售票\t是否发车\n\n";
}
void ShowBusInfo(Timetable* timetables, int n, int idx)   //显示第idx车次信息   
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
		//判断是否发车
		struct tm* local;       //struct tm 时间结构体类型
		time_t t;				//把当前时间给t
		t = time(NULL);
		local = localtime(&t);      //获取当前系统时间 
		if ((local->tm_hour * 60 + local->tm_min) < (timetables[idx].hour * 60 + timetables[idx].minute))
		{
			cout << "未发车" << '\t';
		}
		else
		{
			cout << "已发车" << '\t';
		}
	}
	cout << endl;
}
int ReadFromFile(Timetable* timetables, char* filename)//从文件读取车次信息
{
	int i = 0;  //车次数量
	ifstream infile;
	infile.open(filename);
	if (!infile)
	{
		cout << "文件打开错误";
		system("pause");
		return (-1);//返回-1表示错误
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
		return i;//返回现有车次的数量
	}
	infile.close();
}
void inttostr(int n, char* str) //将数字转换成字符串
{
	/*int k;
 int i=0,t,j=0;
	while(n!=0)
	{
	t=n%10;
	str[j]=t+48;//通过ASCII进行数字与字符转化
	j++;
	n=n/10;
	}
	str[j]='\0';//字符串结尾必须要有‘\0’否则会有乱码
	j--;
	for(i=0;i<=j;i++,j--)
	{
	k=str[i];
	str[i]=str[j];
	str[j]=k;
	}*/
	_itoa(n, str, 10);//itoa函数，将数字转化为字符串，适当使用库函数可以节省程序代码数。但上方给出了非函数实现方式
}
void GenerateLogFileName(char* filename)  //生成日志文件的文件名
{
	filename[0] = '\0';
	struct tm* local;				//时间结构体 
	time_t t;                       //把当前时间给t
	t = time(NULL);					//NULL在stdio.h中定义为0
	local = localtime(&t);			//获取当前系统时间 

	char year[5], month[3], day[3];	//将年月日分别转换成字符串型
	inttostr(1900 + local->tm_year, year);
	inttostr(1 + local->tm_mon, month);
	inttostr(local->tm_mday, day);
	strcat(filename, year);			//生成日志文件名
	strcat(filename, "-");
	strcat(filename, month);
	strcat(filename, "-");
	strcat(filename, day);
	strcat(filename, ".log");
}
int WritetoFile(Timetable* timetables, int n, char* filename)//将车次信息写入文件
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
		if (i < n - 1)//这里要判断是否为最后一行，否则文件会产生乱码
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
		cout << "\n                   ********** 车次信息查询 **********\n\n";
		cout << "                             1、按车次号查询\n";
		cout << "                             2、按终点站查询\n";
		cout << "                             3、退 出  查 询\n";
		cout << "\n                   **********************************\n";
		cout << "                     请选择(1-3):";
		cin >> num;
		if (num >= 1 && num <= 3)
			break;
	}
	return num;//返回选择的数
}
void Query(Timetable* timetables, int n)  //车次查询
{
	int num;
	int i;
	char no[10];//查询车次号
	char Last_station[10];//查询终点站
	int b[100];//记录车所在位置
	while (1)
	{
		num = QueryWindowSelect();
		switch (num)
		{
		case 1:

		{
			cout << "请输入你要查询的车次号：";
			cin >> no;
			i = find(timetables, n, no);//找到的车次位置
			if (i == -1)
			{
				cout << "未找到你所查询的车次" << endl; system("pause"); break;
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
			cout << "请输入终点站名：";
			cin >> Last_station;
			i = find(timetables, n, Last_station, b);//找到符合的车次数量
			if (i == -1)
			{
				cout << "没有该终点站的车次" << endl; system("pause"); break;
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
int InitializaionPassageMode(Timetable* timetables, char* LogFileName, char* filename)//判断读取写入日志文件
{
	int n = 0; //车次数量
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
	return n;//返回现有车次数
}
void SortbyTime(Timetable* timetables, int n)//将车次信息进行排序
{
	int i = 0, tt1, tt2, j = 0;//冒泡排序
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
void change(char* password)//更改密码
{
	char newpassword1[20];//定义两个新密码，完成两个密码比对
	char newpassword2[20];
	char pass[20];
	int num, a, b;
	cout << "你确定要更改密码吗？(输入1表示确定，输入2返回)";
	cin >> num;
	if (num == 1)
	{
		cout << "请输入原始密码：";
		cin >> pass;
		a = strcmp(password, pass);//两个密码比对
		if (a == 0)
		{
			cout << "请输入新密码：";
			cin >> newpassword1;
			cout << "请再次输入新密码：";
			cin >> newpassword2;
			b = strcmp(newpassword1, newpassword2);
			if (b == 0)
			{
				strcpy(password, newpassword1);//两个密码比对
				cout << "重置成功" << endl;
			}
			else
			{
				cout << "两次输入不一样" << endl;
			}
		}
		else
		{
			cout << "原密码输入错误" << endl;
		}
	}
	ofstream out;
	out.open("密码.txt");
	out << password;//将更改的密码写入文件
	out.close();

}
void passwordstart()//对密码进行初始化，最开始的密码为123
{
	ofstream out;
	out.open("密码.txt");
	char password[20] = "123";
	out << password;
	out.close();
}
void passwordin(char* password)//将文件密码读入
{
	ifstream in;
	in.open("密码.txt");
	if (!in)//如果没有找到这个文件，就初始化密码为123
	{
		passwordstart();
		password = "123";
	}
	else
	{
		while (!in.eof())//若找到密码则从中读取密码
		{
			in >> password;
		}
	}
	in.close();
}
int informationin(IDinformation* IDs)//乘客信息读取
{
	int i = 0;
	ifstream in;
	in.open("乘客个人信息.txt");
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
	return i;//返回乘客信息数量
	in.close();

}
void writeIDs(IDinformation* IDs, int t)//将乘客信息写入文件
{
	IDinformation IDnumber;
	ifstream in;
	int k = 0;
	in.open("乘客个人信息.txt");
	while (!in.eof())//判断现有乘客信息数
	{
		in >> IDnumber.name;
		in >> IDnumber.ID;
		in >> IDnumber.no1;
		in >> IDnumber.buydata;
		k++;
	}
	in.close();
	ofstream out;
	out.open("乘客个人信息.txt");
	int i = 0;
	for (i = 0; i < t; i++)//保证新增乘客之前的数据不能改变，之后的数据可以改变
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
			struct tm* local;       //struct tm 时间结构体类型
			time_t t1;				//把当前时间给t
			t1 = time(NULL);
			local = localtime(&t1);
			char year[5], month[3], day[3], hour[3], min[3], sec[3];	//将年月日分别转换成字符串型
			inttostr(1900 + local->tm_year, year);
			inttostr(1 + local->tm_mon, month);
			inttostr(local->tm_mday, day);
			inttostr(local->tm_hour, hour);
			inttostr(local->tm_min, min);
			inttostr(local->tm_sec, sec);
			strcat(IDs[i].buydata, year);			//生成购票时间
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
			if (i < t - 1)//判断是否为最后一行
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
void showinformation(IDinformation* IDs)//显示乘客信息
{
	ifstream in;
	in.open("乘客个人信息.txt");
	int i = 0;
	while (!in.eof())
	{
		in >> IDs[i].name;
		in >> IDs[i].ID;
		in >> IDs[i].no1;
		in >> IDs[i].buydata;
		i++;
	}//统计乘客数量
	cout << setw(10) << "姓名" << setw(15) << "ID号" << setw(10) << "车次号" << setw(25) << "购票时间" << endl;
	for (int j = 0; j < i; j++)//输出乘客数
	{
		cout << setw(10) << IDs[j].name;
		cout << setw(15) << IDs[j].ID;
		cout << setw(10) << IDs[j].no1;
		cout << setw(25) << IDs[j].buydata << endl;
	}

}
void PassagerMode(Timetable* timetables, IDinformation* IDs, int t, char* filename) //顾客功能
{
	char LogFileName[200];    //存放日志文件名。
	int n;
	GenerateLogFileName(LogFileName);//根据当前日期生成日志文件名
	n = InitializaionPassageMode(timetables, LogFileName, filename);
	int PassagerChoice;
	while (1)
	{
		switch (PassagerChoice = PassagerWindowSelect())
		{
		case 1: Query(timetables, n); system("pause"); break;//车次信息查询
		case 2: t = TicketOrder(timetables, n, IDs, t); WritetoFile(timetables, n, LogFileName); writeIDs(IDs, t); system("pause"); break;  //购票，并更改文件信息
		case 3: TicketDelete(timetables, n); WritetoFile(timetables, n, LogFileName); system("pause"); break;//退票，并更改文件信息
		case 4: WritetoFile(timetables, n, LogFileName); 	return;//返回上级菜单
		}
	}
}
void AdminMode(Timetable* timetables, char* password, char* filename, IDinformation* IDs)  //管理员功能
{
	int n;
	Signin(password);  //登录
	n = ReadFromFile(timetables, "bus.txt");
	while (1)
	{
		int AdminChoice = AdminWindowSelect();
		switch (AdminChoice)
		{
		case 1:	n = AddBus(timetables, n); WritetoFile(timetables, n, filename); system("pause"); break;	//增加车次信息,并及时写到文件中
		case 2:	ShowTimetable(timetables, n); system("pause"); break;	//浏览时刻表
		case 3:	Query(timetables, n); system("pause"); break;	//车次信息查询	   			
		case 4:	n = DelBus(timetables, n); system("pause"); WritetoFile(timetables, n, filename); break;//注销车次,并及时写到文件中
		case 5: showinformation(IDs); system("pause"); break;//显示乘客信息
		case 6: change(password); system("pause"); break;//更改密码
		case 7: WritetoFile(timetables, n, filename); return;//返回上级菜单
		}
	}
}
int Quit()//退出系统
{
	cin.sync(); //清空输入缓冲区
	cout << "退出系统吗(y/n)?";
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
	system("color 3d");//更改操作界面颜色
	Timetable timetables[100];
	IDinformation IDs[1000];
	char password[20];//定义密码数组
	passwordin(password);
	t = informationin(IDs);//乘客信息数
	while (1)
	{
		switch (UserChoice = MainWindowSelect())
		{
		case 1:  AdminMode(timetables, password, "bus.txt", IDs); break;	    //管理员模式
		case 2:  PassagerMode(timetables, IDs, t, "bus.txt"); break;	//顾客模式	
		case 3:  if (Quit() != 1) continue;				    //退出
		}
		if (UserChoice == 3) break;
	}

	return 0;
}