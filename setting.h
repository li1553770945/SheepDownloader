#ifndef SETTING_H
#define SETTING_H

#endif // SETTING_H
#pragma once
#include <string>
#include <qwidget.h>
#include <qjsonobject.h>
class Config {
    QJsonObject object;
public:
    Config();
    QJsonValue Get(QString key);//获取key对应的配置
    int Set(QString key,QString value);//设置key对应的配置为value
    int Save();//保存当前配置到文件
    int Read();//读取配置文件
};
