/*
 *  @file customerwidget.h
 *  @brief 乘客功能页面
*/
/*
 *  @file administratorwidget.h
 *  @brief 管理员功能页面
*/
#ifndef CUSTOMERWIDGET_H
#define CUSTOMERWIDGET_H

#include <QWidget>
#include <string>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "datastructrue.h"

namespace Ui {
class CustomerWidget;
}
struct IDinformation;
struct Timetable;
class CustomerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerWidget(QWidget *parent = nullptr);
    ~CustomerWidget();
    void init(Timetable* timetables,int iBusNum,std::string filename,std::string filenamePassenger,
              IDinformation* IDs,int iIDNum);

private slots:
    void on_pBtnFind_clicked();

    void on_pBtnBookTicket_clicked();

    void on_pBtnRefund_clicked();

    void on_pBtnExitSys_clicked();

    void on_pBtnpageFindBus_clicked();

    void on_pBtnpageBookTicket_clicked();

    void on_pBtnDelBus_clicked();

private:

    void ReadIDsFromFile(const char* filename);
    // @brief 根据系统时间生成日志文件名
    void GenerateLogFileName();
    // @brief 初始化，并写入文件判断读取写入日志文(暂时不会用到)
    void InitializaionPassageMode();
    // @brief 会将车次信息写入日志文件和车次表文件，根据输入的文件名确定
    int WritetoFile(const char* filename);
    // @brief 将乘客信息写入乘客表文件
    void WriteToPassengerFile();
    // @brief 显示指定
    void showBusInfo(int *ids,int n);
    // @brief 判断是否停止售票或退票，0:可以，1：不可以
    int StopSerive(QString no);
    // @brief 按车次查找
    int findByBusNum(QString no);
    // @brief 按车站名查找
    int findByBusDestination(QString lastStation,int*b);
    // @brief 将车次信息进行排序
    void SortbyTime();
private:
    Ui::CustomerWidget *ui;
    // @brief 车次时刻列表
    Timetable* m_pTimetables;
    // @brief 用户信息
    IDinformation* m_pIDs;
    // @brief 当前车次数量
    int m_iBusNum;
    // @brief 当前乘客数量
    int m_iPassengerNum;
    // @brief 存放日志文件名
    char LogFileName[200];
    // @brief 存放车次表的文件路径
    std::string m_szTimatableFilePath;
    // @brief 存放乘客信息的文件路径
    std::string m_szPassengerFilePath;
};

#endif // CUSTOMERWIDGET_H
