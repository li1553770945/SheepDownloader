#include "setting.h"
#include <string>
#include <qfile.h>
#include <qiodevice.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qmessagebox.h>
#include <fstream>
Config::Config()
{

}
QJsonValue Config::Get(QString key)
{
    return object.value(key);
}
int Config::Set(QString key, QString value)
{
    object.insert(key,value);
    return 0;
}
int Config::Read()
{
    std::fstream _file;
    _file.open("config.json", std::ios::in);//检测是否存在；配置文件
    if (_file)
    {
        _file.close();
        QFile file("config.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);//打开文件
        QString value = file.readAll();//读取
        file.close();
        QJsonParseError parseJsonErr;
        QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);
        qDebug() << parseJsonErr.error;
        if (!(parseJsonErr.error == QJsonParseError::NoError))
        {
            QMessageBox box(QMessageBox::Critical,"错误", "读取配置文件失败:"+ QString::fromStdString(std::to_string(parseJsonErr.error)));
            box.exec();
            return -1;
        }
        object = document.object();//将配置设置为根据配置文件构建的QJsonObject
    }
    else
    {
        QMessageBox box(QMessageBox::Information, "提示", "未找到配置文件，将使用默认配置");
        box.exec();
    }
    return 0;
}
int Config::Save()
{
    QJsonDocument doc;

    doc.setObject(object);
    QByteArray data = doc.toJson();//也不知道为什么要这么复杂的操作
    QFile file("config.json");//json写入文件
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();
    return true;
}

