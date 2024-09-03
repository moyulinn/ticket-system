#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include<Qpainter>
#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

   // void paintEvent(QPaintEvent *event);

    // @brief 将文件密码读入，并取出密码
    void passWordIn(QString filePath);

    // @brief 获取登陆成功的标志，以便于应用程序初始化相应的页面
    void getSuccessFlag(bool& bClientSuccess,bool& bAdminSuccess);

    //@ brief 如果管理员登陆成功，则获取登陆成功的密码
    QString getAdminpassword();
private slots:
    // @brief 处理顾客点击进入系统槽函数
    void on_pBtnClientEnter_clicked();
    // @brief 处理管理员登陆按钮点击槽函数
    void on_pBtnAdminEnter_clicked();

private:
    // @brief 当密码文件路径不存在时，添加新的密码文件
    void passwordStart();
private:
    Ui::LoginDialog *ui;

    // @brief 密码文件路径
    QString m_szPassWordFilePath;

    // @brief 定义管理员初始密码，
    // 密码文件路径对应的文件不存在，则初始化为123，否则设置为密码文件对应密码
    QString m_szPassWord;

    // @brief 管理员成功登陆系统标志
    bool m_bAdminLoginSuccess;

    // @brief 顾客成功登陆系统标志
    bool m_bClientLoginSuccess;
};

#endif // LOGINDIALOG_H
