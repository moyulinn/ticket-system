#include "administratorwidget.h"
#include "ui_administratorwidget.h"
#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<stdio.h>
#include <string>
#include <iomanip>
#include <cmath>
#include <conio.h>
#include <QMessageBox>
#include "datastructrue.h"

#pragma execution_character_set("utf-8")

AdministratorWidget::AdministratorWidget(QWidget *parent):QWidget(parent),ui(new Ui::AdministratorWidget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
}

AdministratorWidget::~AdministratorWidget()
{
    delete ui;
}

void AdministratorWidget::init(Timetable* timetables, int m_iBusNum,std::string password,std::string passwordpath,
          std::string filename,std::string filenamePassenger,IDinformation* IDs,int iDsNum)
{
    m_pTimetables = timetables;
    this->m_iBusNum = m_iBusNum;
    m_szCurpassword = password;
    m_szPasswordFilePath = passwordpath;
    m_szPassengerFilePath = filenamePassenger;
    m_szTimatableFilePath = filename;
    m_pIDs=  IDs;
    m_iPassengerNum = iDsNum;
}



int AdministratorWidget::findByBusNum(QString no)
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

void AdministratorWidget::on_pBtnChangepassword_clicked()
{
    //清理上次留下的消息
    ui->lineEditpageChangePassword0->clear();
    ui->lineEditpageChangePassword2->clear();
    ui->lineEditpageChangePassword->clear();
    //切换到修改密码页面
    ui->stackedWidget->setCurrentIndex(0);
}


void AdministratorWidget::on_pBtnResetPassword_clicked()
{
    //原密码
    QString originpassword = ui->lineEditpageChangePassword0->text();
    //第二次输入的密码
    QString newpassword2 = ui->lineEditpageChangePassword2->text();
    //第一次输入的密码
    QString newpassword1 = ui->lineEditpageChangePassword->text();
    if(originpassword.isEmpty() || newpassword1.isEmpty() || newpassword2.isEmpty())
    {
        QMessageBox::critical(this,"错误","任意一项不能为空,请重新输入!");
        return;
    }
    //新密码和原密码比对
    if(!originpassword.compare(QString(m_szCurpassword.c_str())))
    {
        //两次新密码比对
        if(!newpassword1.compare(newpassword2))
        {
            std::ofstream out;
            out.open(m_szPasswordFilePath);
            out << newpassword1.toStdString();//将更改的密码写入文件
            out.close();
            //设置当前密码
            m_szCurpassword = newpassword1.toStdString();
            QMessageBox::information(this,"成功","重置密码成功");
        }
        else
        {
            QMessageBox::critical(this,"错误","两次输入不一样");
        }
    }
    else
    {
        QMessageBox::critical(this,"错误","原密码输入错误");
    }
}


void AdministratorWidget::on_pBtnpageAddBus_clicked()
{
    int k = -1;
    QString no = ui->lineEditpageAddBusBusID->text();
    QString hour = ui->lineEditpageAddBusHour->text();
    QString minute = ui->lineEditpageAddBusMinutes->text();
    QString starting_station = ui->lineEditpageAddBusStartStation->text();
    QString last_station = ui->lineEditpageaddBusLastStation->text();
    QString time = ui->lineEditpageaddBusTime->text();
    QString fare = ui->lineEditpageaddBufare->text();
    QString max_number = ui->lineEditpageAddBusMaxNum->text();
    QString sold_number = ui->lineEditaddBusSoldNum->text();
    k = findByBusNum(no);
    if(k != -1)
    {
        QMessageBox::warning(this,"警告","该车次已经存在，无需添加，请重新输入");
        return;
    }
    else
    {
        m_pTimetables[m_iBusNum].no = no.toStdString();
        m_pTimetables[m_iBusNum].hour = hour.toInt();
        m_pTimetables[m_iBusNum].minute = minute.toInt();
        m_pTimetables[m_iBusNum].Starting_station = starting_station.toStdString();
        m_pTimetables[m_iBusNum].Last_station = last_station.toStdString();
        m_pTimetables[m_iBusNum].time = time.toFloat();
        m_pTimetables[m_iBusNum].fare = fare.toInt();
        m_pTimetables[m_iBusNum].max_number = max_number.toInt();
        m_pTimetables[m_iBusNum].sold_number = sold_number.toInt();
        m_iBusNum++;
        WritetoFile();
        QMessageBox::information(this,"成功","添加成功");
    }
}
void AdministratorWidget::WritetoFile()
{
    std::ofstream out;
    out.open(m_szTimatableFilePath);
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
}

void AdministratorWidget::on_pBtnExitSys_clicked()
{
    //将信息重新写入配置文件
    WritetoFile();
    exit(0);
}


void AdministratorWidget::on_pBtnViewPassengerInfo_clicked()
{
    //切换到乘客信息浏览页
    ui->stackedWidget->setCurrentIndex(3);
    showPassengerInfo();
}


void AdministratorWidget::on_pBtnDelete_clicked()
{
    ui->lineEditPageDelBus->clear();
    ui->stackedWidget->setCurrentIndex(2);
}


void AdministratorWidget::on_pBtnFind_clicked()
{
    // 切换到信息查询页
    ui->stackedWidget->setCurrentIndex(4);
}


void AdministratorWidget::on_pBtnView_clicked()
{
    //切换到浏览车次信息页
    ui->stackedWidget->setCurrentIndex(3);
    ui->tableWidget->clear();
    SortbyTime();
    showBusInfo();
}


void AdministratorWidget::on_pBtnAdd_clicked()
{
    //清理上次留下的
    ui->lineEditpageAddBusBusID->clear();
    ui->lineEditpageAddBusHour->clear();
    ui->lineEditpageAddBusMinutes->clear();
    ui->lineEditpageAddBusStartStation->clear();
    ui->lineEditpageaddBusLastStation->clear();
    ui->lineEditpageaddBusTime->clear();
    ui->lineEditpageaddBufare->clear();
    ui->lineEditpageAddBusMaxNum->clear();
    ui->lineEditaddBusSoldNum->clear();
    // 切换到增加车次页
    ui->stackedWidget->setCurrentIndex(1);
}


void AdministratorWidget::on_pBtnpageDelBusDelete_clicked()
{
    QString no = ui->lineEditPageDelBus->text();
    if(no.isEmpty())
    {
        QMessageBox::critical(this,"错误","车次号不能为空");
        return;
    }
    int t = findByBusNum(no);
    if(t == -1)
    {
        QMessageBox::critical(this,"错误","此车辆不存在，删除错误,请重新输入");
        return;
    }
    //若为位置在最后，则以总车次数减一表示删除车次
    if (t == m_iBusNum - 1)
    {
        m_iBusNum = m_iBusNum - 1;
        QMessageBox::information(this,"成功","删除成功！");
        WritetoFile();
    }
    if (t < m_iBusNum - 1 && t >= 0)
    {
        for (int i = t; i < m_iBusNum - 1; i++)
        {
            m_pTimetables[i] = m_pTimetables[i + 1];//若位置不在最后，则之后所有车次位置往前1位
        }
        m_iBusNum = m_iBusNum - 1;
        QMessageBox::information(this,"成功","删除成功！");
        WritetoFile();
    }
}


void AdministratorWidget::on_pBtnpageFindBus_clicked()
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
            ui->stackedWidget->setCurrentIndex(3);
            ui->tableWidget->clear();
            showBusInfo(b,1);
            //找到车次
        }
    }
    //按终点站名查找
    else
    {
        int b[100];
        int i = findByBusDestination(no,b);
        if(i == -1)
        {
            QMessageBox::critical(this,"错误","没有该终点站的车次");
            return;
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(3);
            ui->tableWidget->clear();
            showBusInfo(b,i);
        }
    }
}

int AdministratorWidget::findByBusDestination(QString lastStation,int*b)
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
void AdministratorWidget::SortbyTime()
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


void AdministratorWidget::ReadFromFile(const char* filename)//从文件读取车次信息
{
    int i = 0;  //车次数量
    std::ifstream infile;
    infile.open(filename);
    if (!infile)
    {
        //QMessageBox::critical(this,"错误","车次文件打开错误，系统自动退出");
        exit(1);
    }
    else
    {
        while (!infile.eof())
        {
            infile >> m_pTimetables[i].no;
            infile >> m_pTimetables[i].hour;
            infile >> m_pTimetables[i].minute;
            infile >> m_pTimetables[i].Starting_station;
            infile >> m_pTimetables[i].Last_station;
            infile >> m_pTimetables[i].time;
            infile >> m_pTimetables[i].fare;
            infile >> m_pTimetables[i].max_number;
            infile >> m_pTimetables[i].sold_number;
            i++;
        }
        //return i;//返回现有车次的数量
    }
    infile.close();
    m_iBusNum = i;
}

void AdministratorWidget::showBusInfo()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setRowCount(m_iBusNum);
    QStringList headers;
    headers << "班次" << "时间(小时)" << "时间(分钟)" <<"起点" << "终点" << "时长" << "票价" << "额定量" << "已售票" << "是否发车";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    for(int row = 0; row < m_iBusNum; ++row) {
        for(int column = 0; column < 10; ++column) {
            QTableWidgetItem *item = nullptr;
            switch(column)
            {
            case 0:
                item = new QTableWidgetItem(m_pTimetables[row].no.c_str());
                break;
            case 1:
                item = new QTableWidgetItem(QString::number(m_pTimetables[row].hour));
                break;
            case 2:
                item = new QTableWidgetItem(QString::number(m_pTimetables[row].minute));
                break;
            case 3:
                item = new QTableWidgetItem(m_pTimetables[row].Starting_station.c_str());
                break;
            case 4:
                item = new QTableWidgetItem(m_pTimetables[row].Last_station.c_str());
                break;
            case 5:
                item = new QTableWidgetItem(QString::number(m_pTimetables[row].time));
                break;
            case 6:
                item = new QTableWidgetItem(QString::number(m_pTimetables[row].fare));
                break;
            case 7:
                item = new QTableWidgetItem(QString::number(m_pTimetables[row].max_number));
                break;
            case 8:
                item = new QTableWidgetItem(QString::number(m_pTimetables[row].sold_number));
                break;
            case 9:
            {
                //判断是否发车
                struct tm* local;       //struct tm 时间结构体类型
                time_t t;				//把当前时间给t
                t = time(NULL);
                local = localtime(&t);      //获取当前系统时间
                if ((local->tm_hour * 60 + local->tm_min) < (m_pTimetables[row].hour * 60 + m_pTimetables[row].minute))
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
void AdministratorWidget::showBusInfo(int *ids,int n)
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

void AdministratorWidget::showPassengerInfo()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(m_iPassengerNum);
    QStringList headers;
    headers << "姓名" << "ID号"<< "车次号" << "购票时间";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    for(int row = 0; row < m_iPassengerNum; ++row) {
        for(int column = 0; column < 4; ++column) {
            QTableWidgetItem *item = nullptr;
            switch(column){
            case 0:
                item = new QTableWidgetItem(m_pIDs[row].name.c_str());
                break;
            case 1:
                item = new QTableWidgetItem(m_pIDs[row].ID.c_str());
                break;
            case 2:
                item = new QTableWidgetItem(m_pIDs[row].no1.c_str());
                break;
            case 3:
                item = new QTableWidgetItem(m_pIDs[row].buydata.c_str());
                break;
            }
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row, column, item);
        }
    }
}
