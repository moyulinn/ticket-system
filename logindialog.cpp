#include "logindialog.h"
#include "ui_logindialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <fstream>
#pragma execution_character_set("utf-8")
LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    m_szPassWord = "123";
    m_bClientLoginSuccess = false;
    m_bAdminLoginSuccess = false;
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

//void LoginDialog::paintEvent(QPaintEvent *event)
//{
    //Qpainter painter(this);
    //painter.drawPixmap(0,0,width(),height(),Qpixmap(":/new/prefix1/bj.png"))
//}



void LoginDialog::passwordStart()
{
    if(!m_szPassWordFilePath.endsWith(".txt"))
    {
        m_szPassWordFilePath += ".txt";
    }
    std::ofstream out;
    out.open(m_szPassWordFilePath.toStdString());
    char password[20] = "123";
    out << password;
    out.close();
#if 0
    QFile file(m_szPassWordFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件以写入：";
        return;
    }

    // 将字符串写入文件
    QTextStream out(&file);
    out << "123";
    file.close();
#endif
}

void LoginDialog::getSuccessFlag(bool& bClientSuccess,bool& bAdminSuccess)
{
    bClientSuccess = m_bClientLoginSuccess;
    bAdminSuccess = m_bAdminLoginSuccess;
}

QString LoginDialog::getAdminpassword()
{
    return m_szPassWord;
}

void LoginDialog::on_pBtnClientEnter_clicked()
{
    m_bClientLoginSuccess = true;
    m_bAdminLoginSuccess = false;
    accept();
}

void LoginDialog::passWordIn(QString filePath)
{
    //密码文件后缀目前只有.txt
    if(!filePath.endsWith(".txt"))
        filePath += ".txt";

    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        // 如果没有找到这个文件则，密码初始化为123
        m_szPassWordFilePath = filePath;
        //创建新的密码文件，并将密码写入文件
        passwordStart();
        m_szPassWord = "123";
        return;
    }
    else
    {
        QTextStream text_stream(&file);
        QString sz_line;
        //循环读取密码文件每一行，目前只取最后一行
        while(!text_stream.atEnd())
        {
            sz_line = text_stream.readLine();
        }
        //将读取出来的密码进行赋值
        if(sz_line.size())
            m_szPassWord = sz_line;
        else
            m_szPassWord = "123";
        file.close();
        m_szPassWordFilePath = filePath;
    }

}
void LoginDialog::on_pBtnAdminEnter_clicked()
{
    //获取界面上的账号和密码
    QString sz_account  = ui->lineEditAccount->text();
    QString sz_password = ui->lineEditPassword->text();
    //账号和密码判空操作
    if(sz_account.isEmpty() || sz_password.isEmpty())
    {
        QMessageBox::critical(this,"错误",
                              sz_account.isEmpty()?"账号不能为空!":"密码不能为空!");
        return;
    }
    //账号和密码比对操作
    if(!sz_account.compare("admin") && !sz_password.compare(m_szPassWord))
    {
        m_bAdminLoginSuccess = true;
        m_bClientLoginSuccess = false;
        accept();
    }
    else
    {
        QMessageBox::critical(this,"错误","账号或密码错误,请重新输入");
        //清空账号密码输入
        ui->lineEditAccount->clear();
        ui->lineEditPassword->clear();
    }
}

