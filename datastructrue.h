#ifndef DATASTRUCTRUE_H
#define DATASTRUCTRUE_H

#include <string>
// @brief 车次信息表
#define BUSFILEPATH "bus.txt"
// @brief 乘客信息表
#define PASSENGERINFOFILEPATH "passengerinfo.txt"
// @brief 密码表
#define PASSWORDFILEPATH "password.txt"


/*
 * @ brief 车次信息结构体
*/
struct Timetable
{
    // 车次
    std::string no;
    // 发车时间
    int hour;
    //发车时间（分）
    int minute;
    // 始发站
    std::string Starting_station;
    // 终点站
    std::string Last_station;
    // 行车时间
    float time;
    // 票价
    int fare;
    // 最大载客数
    int max_number;
    // 已售票数
    int sold_number;
};

/*
 * @brief 乘客身份信息结构
 *
*/
struct IDinformation
{
    // 乘客信息
    std::string name;
    // 乘客ID
    std::string ID;
    // 乘客所乘坐的汽车号
    std::string no1;
    // 乘客购票时间，年月日时分秒
    std::string buydata;
};

#endif // DATASTRUCTRUE_H
