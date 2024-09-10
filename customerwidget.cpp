#include "customerwidget.h"
#include "ui_customerwidget.h"
#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<stdio.h>
#include <string>
#include <iomanip>
#include <cmath>
#include <conio.h>
#include <QMessageBox>
#include <QDebug>
#include "datastructrue.h"
#pragma execution_character_set("utf-8")
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

CustomerWidget::CustomerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CustomerWidget)
{
    GenerateLogFileName();
    ui->setupUi(this);
}

CustomerWidget::~CustomerWidget()
{
    delete ui;
}
void CustomerWidget::init(Timetable* timetables,int iBusNum,std::string filename,std::string filenamePassenger,
          IDinformation* IDs,int iIDNum)
{
    m_pTimetables = timetables;
    m_pIDs = IDs;
    m_iBusNum = iBusNum;
    //qDebug() << "乘客数" << iIDNum;
    m_iPassengerNum = iIDNum;
    m_szPassengerFilePath = filenamePassenger;
    m_szTimatableFilePath = filename;
    GenerateLogFileName();
}

void CustomerWidget::GenerateLogFileName()
{
    LogFileName[0] = '\0';
    memset(LogFileName,'\0',sizeof(LogFileName));
    struct tm* local;				//时间结构体
    time_t t;                       //把当前时间给t
    t = time(NULL);					//NULL在stdio.h中定义为0
    local = localtime(&t);			//获取当前系统时间

    char year[5], month[3], day[3];	//将年月日分别转换成字符串型
    inttostr(1900 + local->tm_year, year);
    inttostr(1 + local->tm_mon, month);
    inttostr(local->tm_mday, day);
    strcat(LogFileName, year);			//生成日志文件名
    strcat(LogFileName, "-");
    strcat(LogFileName, month);
    strcat(LogFileName, "-");
    strcat(LogFileName, day);
    strcat(LogFileName, ".log");
}


void CustomerWidget::InitializaionPassageMode()
{
    int n = 0; //车次数量
    std::ifstream infile;
    infile.open(LogFileName);
    if (!infile)
    {

        //ReadFromFile(m_szTimatableFilePath.c_str());
        for (int i = 0; i < m_iBusNum; i++)
        {
            m_pTimetables[i].sold_number = 0;
        }
        WritetoFile(LogFileName);
    }
    else
    {
        //ReadFromFile(LogFileName);
    }
    infile.close();

}

int CustomerWidget::WritetoFile(const char* filename)//将车次信息写入文件
{
    std::ofstream out;
    out.open(filename);
    int i = 0;
    for (i = 0; i < m_iBusNum; i++)
    {
        out << m_pTimetables[i].no << '\t';
        out << m_pTimetables[i].hour << '\t';
        out << m_pTimetables[i].minute << '\t';
        out << m_pTimetables[i].Starting_station << '\t';
        out << m_pTimetables[i].Last_station << '\t';
        out << m_pTimetables[i].time << '\t';
        out << m_pTimetables[i].fare << '\t';
        out << m_pTimetables[i].max_number << '\t';
        if (i < m_iBusNum - 1)//这里要判断是否为最后一行，否则文件会产生乱码
        {
            out << m_pTimetables[i].sold_number << std::endl;
        }
        else
        {
            out << m_pTimetables[i].sold_number;
        }
    }
    out.close();
    return 0;
}
void CustomerWidget::WriteToPassengerFile()
{
    std::ofstream out;
    out.open(PASSENGERINFOFILEPATH);
    int i = 0;
    for (i = 0; i < m_iPassengerNum; i++)//保证新增乘客之前的数据不能改变，之后的数据可以改变
    {
        {
            out << m_pIDs[i].name << '\t';
            out << m_pIDs[i].ID << '\t';
            out << m_pIDs[i].no1 << '\t';
            if (i < m_iPassengerNum - 1)//判断是否为最后一行
            {
                out << m_pIDs[i].buydata << std::endl;
            }
            else
            {
                out << m_pIDs[i].buydata;
            }
        }

    }
    out.close();
}


int CustomerWidget::findByBusNum(QString no)
{
    int i = 0, k=1;//i是计数，k是判断两车次号是否一致
    for (i = 0; i < m_iBusNum; i++)
    {
        k = strcmp(m_pTimetables[i].no.c_str(), no.toStdString().c_str());
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

int CustomerWidget::findByBusDestination(QString lastStation,int*b)
{
    int j = 0;  //存放同一终点站车次数
    int i = 0, k;//i是计数，k是判断两车次号是否一致
    for (i = 0; i < m_iBusNum; i++)
    {

        k = strcmp(m_pTimetables[i].Last_station.c_str(),lastStation.toStdString().c_str());
        if (k == 0)
        {
            b[j] = i;//记录所有符合的车次所在位置
            j++;
        }
    }
    if (j > 0) return j;//返回符合条件的车次个数

    return -1; //没有查到相应终点站的车次时返回值-1
}

void CustomerWidget::SortbyTime()//将车次信息进行排序
{
    int i = 0, tt1, tt2, j = 0;//冒泡排序
    Timetable t1;
    for (i = 0; i < m_iBusNum - 1; i++)
    {
        for (j = 0; j < m_iBusNum - 1 - i; j++)
        {
            tt1 = m_pTimetables[j].hour * 60 + m_pTimetables[j].minute;
            tt2 = m_pTimetables[j + 1].hour * 60 + m_pTimetables[j+1].minute;
            if (tt1 > tt2)
            {
                t1 = m_pTimetables[j]; m_pTimetables[j] = m_pTimetables[j + 1]; m_pTimetables[j + 1] = t1;
            }
        }

    }
}


int CustomerWidget::StopSerive(QString no) //判断是否停止售票或退票，0:可以，1：不可以
{
    struct tm* local;       //struct tm 时间结构体类型
    time_t t;				//把当前时间给t
    t = time(NULL);
    local = localtime(&t);      //获取当前系统时间
    int i = findByBusNum(no);

    if ((local->tm_hour * 60 + local->tm_min) + 10 < (m_pTimetables[i].hour * 60 + m_pTimetables[i].minute))
        return 0;
    return 1;
}


void CustomerWidget::on_pBtnFind_clicked()
{
    //切换到查询页面
    ui->stackedWidget->setCurrentIndex(0);
}


void CustomerWidget::on_pBtnBookTicket_clicked()
{
    //切换到订票页面
    ui->stackedWidget->setCurrentIndex(1);
}


void CustomerWidget::on_pBtnRefund_clicked()
{
    //切换到退票页面
    ui->stackedWidget->setCurrentIndex(3);
}


void CustomerWidget::on_pBtnExitSys_clicked()
{
    exit(0);
}



void CustomerWidget::on_pBtnpageFindBus_clicked()
{
    QString no = ui->lineEditpageFindBus->text();
    if(no.isEmpty())
        return;
    //按车次号查找

    if(ui->rBtnpageFindBus0->isChecked())
    {
        int i = findByBusNum(no);
        if(i == -1)
        {
            QMessageBox::critical(this,"错误","未找到你所查询的车次");
            return;
        }
        else
        {
            int b[100];
            b[0] = i;
            ui->stackedWidget->setCurrentIndex(2);
            ui->tableWidget->clear();
            showBusInfo(b,1);
            //找到车次
        }
    }
    //按终点站名查找
    else
    {
        SortbyTime();
        int b[100];
        int i = findByBusDestination(no,b);
        if(i == -1)
        {
            QMessageBox::critical(this,"错误","没有该终点站的车次");
            return;
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(2);
            ui->tableWidget->clear();
            showBusInfo(b,i);
        }
    }
}


void CustomerWidget::on_pBtnpageBookTicket_clicked()
{
    QString name = ui->lineEditpageBookTicketName->text();
    QString IDs = ui->lineEditpageBookTicketID->text();
    QString no = ui->lineEditpageBookTicketNo->text();
    QString ticknum = ui->lineEditpageBookTickNum->text();
    if(name.isEmpty() || IDs.isEmpty() || no.isEmpty() ||ticknum.isEmpty())
    {
        QMessageBox::critical(this,"错误","任意一个输入不能为空!,请重新输入");
        return;
    }
    if(ticknum.toInt() > 1)
    {
        QMessageBox::critical(this,"错误","每名乘客只能购买一张票");
        return;
    }
    int i = findByBusNum(no);
    if(i == -1)
    {
        QMessageBox::critical(this,"错误","未找到你所查询的车次");
        return;
    }
    else if (i >= 0)
    {
        int s;
        s = StopSerive(no);//判断时间，是否能退票
        if (s == 1)
        {
            QMessageBox::critical(this,"错误","该车次票已售完或已停止售票!");
            return;
        }
        else
        {
            if (ticknum.toInt() > (m_pTimetables[i].max_number - m_pTimetables[i].sold_number))
            {
                QMessageBox::critical(this,"错误","车票不足");
                return;
            }
            else
            {
                m_pTimetables[i].sold_number = m_pTimetables[i].sold_number + ticknum.toInt();

                qDebug() << "当前乘客数" << m_iPassengerNum;
                m_pIDs[m_iPassengerNum].name = name.toStdString();
                m_pIDs[m_iPassengerNum].ID = IDs.toStdString();
                m_pIDs[m_iPassengerNum].no1 = no.toStdString();
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

                m_pIDs[m_iPassengerNum].buydata += year;
                m_pIDs[m_iPassengerNum].buydata += "-";
                m_pIDs[m_iPassengerNum].buydata += month;
                m_pIDs[m_iPassengerNum].buydata += "-";
                m_pIDs[m_iPassengerNum].buydata += day;
                m_pIDs[m_iPassengerNum].buydata += "-";
                m_pIDs[m_iPassengerNum].buydata += hour;
                m_pIDs[m_iPassengerNum].buydata += ":";
                m_pIDs[m_iPassengerNum].buydata += min;
                m_pIDs[m_iPassengerNum].buydata += ":";
                m_pIDs[m_iPassengerNum].buydata += sec;
                m_iPassengerNum++;

                WritetoFile(BUSFILEPATH);
                WritetoFile(LogFileName);
                WriteToPassengerFile();
                int b[2];
                b[0] = i;
                ui->stackedWidget->setCurrentIndex(2);
                showBusInfo(b,1);
                QMessageBox::information(this,"成功","购票成功");
            }
        }
    }
}

void CustomerWidget::showBusInfo(int *ids,int n)
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setRowCount(n);
    QStringList headers;
    headers << "班次" << "时间(小时)" << "时间(分钟)" <<"起点" << "终点" << "时长" << "票价" << "额定量" << "已售票" << "是否发车";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    for(int row = 0; row < n && row < m_iBusNum; ++row) {
        for(int column = 0; column < 10; ++column) {
            QTableWidgetItem *item = nullptr;
            switch(column)
            {
            case 0:
                item = new QTableWidgetItem(m_pTimetables[ids[row]].no.c_str());
                break;
            case 1:
                item = new QTableWidgetItem(QString::number(m_pTimetables[ids[row]].hour));
                break;
            case 2:
                item = new QTableWidgetItem(QString::number(m_pTimetables[ids[row]].minute));
                break;
            case 3:
                item = new QTableWidgetItem(m_pTimetables[ids[row]].Starting_station.c_str());
                break;
            case 4:
                item = new QTableWidgetItem(m_pTimetables[ids[row]].Last_station.c_str());
                break;
            case 5:
                item = new QTableWidgetItem(QString::number(m_pTimetables[ids[row]].time));
                break;
            case 6:
                item = new QTableWidgetItem(QString::number(m_pTimetables[ids[row]].fare));
                break;
            case 7:
                item = new QTableWidgetItem(QString::number(m_pTimetables[ids[row]].max_number));
                break;
            case 8:
                item = new QTableWidgetItem(QString::number(m_pTimetables[ids[row]].sold_number));
                break;
            case 9:
            {
                //判断是否发车
                struct tm* local;       //struct tm 时间结构体类型
                time_t t;				//把当前时间给t
                t = time(NULL);
                local = localtime(&t);      //获取当前系统时间
                if ((local->tm_hour * 60 + local->tm_min) < (m_pTimetables[ids[row]].hour * 60 + m_pTimetables[ids[row]].minute))
                {
                    item = new QTableWidgetItem("未发车");
                }
                else
                {
                    item = new QTableWidgetItem("已发车");
                }
            }
            break;

            }
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row, column, item);
        }
    }
}


void CustomerWidget::on_pBtnDelBus_clicked()
{
    QString no = ui->lineEditpageDelBusNo->text();
    QString ticknum = ui->lineEditpageDelBusTicketNum->text();
    if(no.isEmpty()|| ticknum.isEmpty())
    {
        QMessageBox::critical(this,"错误","任意一个输入不能为空!,请重新输入");
        return;
    }
    int i = findByBusNum(no);
    if(i == -1)
    {
        QMessageBox::critical(this,"错误","未找到你所查询的车次");
        return;
    }
    else
    {
        int s;//判断时间，是否能退票
        s = StopSerive(no);
        if (s == 1)
        {
            QMessageBox::critical(this,"错误","该班车已停止退票,无法退票!!");
            return;
        }
        else
        {
            if(ticknum.toInt() > m_pTimetables[i].sold_number)
            {
                QMessageBox::critical(this,"错误","退票数大于已售票数，请重新确认退票数");
                return;
            }
            if(ticknum.toInt() <= m_pTimetables[i].sold_number)
            {
                m_pTimetables[i].sold_number = m_pTimetables[i].sold_number - ticknum.toInt();
                WritetoFile(LogFileName);
                WritetoFile(BUSFILEPATH);
                QString msg = "车次为";
                msg += QString(m_pTimetables[i].no.c_str())+"退票成功";
                QMessageBox::information(this,"成功",msg);
                return;
            }
        }
    }
}

