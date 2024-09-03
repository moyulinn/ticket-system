/*
 *  @file administratorwidget.h
 *  @brief 管理员功能页面
*/
#ifndef ADMINISTRATORWIDGET__H__
#define ADMINISTRATORWIDGET__H__

#include <QWidget>
#include <string>

namespace Ui {
class AdministratorWidget;
}

struct Timetable;
struct IDinformation;
class AdministratorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdministratorWidget(QWidget *parent = nullptr);
    ~AdministratorWidget();

    // @brief 初始化管理员页面使用的相关参数
    // @param 车次表,车次数量,管理员登陆的密码，存储管理员密码的路径,车次文件路径，乘客文件路径,乘客信息表,乘客信息数量
    void init(Timetable* timetables, int m_iBusNum,std::string password,std::string passwordpath,
              std::string filename,std::string filenamePassenger,IDinformation* IDs,int iDsNum);

private slots:
    // @brief 更改管理员密码按钮点击槽函数，会切换到更改密码页面
    void on_pBtnChangepassword_clicked();
    // @brief 更改密码按钮点击槽函数，处理密码信息
    void on_pBtnResetPassword_clicked();
    // @brief 增加车次按钮点击槽函数
    void on_pBtnpageAddBus_clicked();
    // @brief 退出系统按钮点击槽函数
    void on_pBtnExitSys_clicked();
    // @brief 查看乘客信息按钮点击槽函数，会切换到显示乘客信息页面
    void on_pBtnViewPassengerInfo_clicked();
    // @brief 注销车次信息按钮点击槽函数，会切换到注销车次页面
    void on_pBtnDelete_clicked();
    // @brief 查询车次信息按钮点击槽函数，会切换到查询车次信息页面
    void on_pBtnFind_clicked();
    // @brief 查看车次信息按钮点击参函数，会切换到显示车次信息的页面
    void on_pBtnView_clicked();
    // @brief 增加车次按钮点击槽函数，会切换到增加车次页面
    void on_pBtnAdd_clicked();
    // @brief 删除车次按钮点击槽函数，处理车次，并会删除指定车次
    void on_pBtnpageDelBusDelete_clicked();
    // @brief 查询车次按钮点击槽函数，会处理输入，并查找车次
    void on_pBtnpageFindBus_clicked();

private:
    // @brief //从文件读取车次信息
    void ReadFromFile(const char* filename);
    // @brief //从文件读取乘客信息
    void ReadIDsFromFile(const char* filename);
    // @brief 将车次信息写入文件
    void WritetoFile();

    // @brief 按车次查找
    int findByBusNum(QString no);
    // @brief 按车站名查找
    int findByBusDestination(QString lastStation,int*b);
    // @brief 将车次信息进行排序
    void SortbyTime();

    // @brief 显示车次信息
    void showBusInfo();
    // @brief 显示指定索引的车次信息
    void showBusInfo(int *ids,int n);
    //@ brief 显示乘客信息
    void showPassengerInfo();

private:
    Ui::AdministratorWidget *ui;
    // @brief 当前管理员密码
    std::string m_szCurpassword;
    // @brief 车次时刻列表
    Timetable* m_pTimetables;
    // @brief 用户信息
    IDinformation* m_pIDs;
    // @brief 当前车次数量
    int m_iBusNum;
    // @brief 当前乘客数量
    int m_iPassengerNum;
    // @brief 密码文件路径
    std::string m_szPasswordFilePath;
    // @brief 车次表文件路径
    std::string m_szTimatableFilePath;
    // @brief 乘客表文件路径
    std::string m_szPassengerFilePath;

};

#endif // ADMINISTRATORWIDGET_H
