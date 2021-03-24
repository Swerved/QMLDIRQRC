#include <QCoreApplication>
#include <iostream>
#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << "QML QRC Tool" << std::endl;
    std::cout << "This tool will generate QRC and QMLDir files based on .qml files in the current working directory" << std::endl;
    std::cout << "Choose a version identifier, ie: 1.0" << std::endl;
    auto version = std::string{};
    std::cin >> version;
    QDir dir(QDir::currentPath());
    auto module = dir.dirName();
    QStringList filters;
    filters << "*.qml";
    dir.setNameFilters(filters);
    const auto &list = dir.entryList();
    QFile file;
    file.setFileName(dir.currentPath()+"/qmldir");
    file.open(QFile::ReadWrite);
    QTextStream qmldir(&file);
    qmldir << "module " << module << Qt::endl;
    for(const auto &qml : list)
    {
        if (qml.contains(".qml"))
        {
            QString type = qml;
            type.chop(4);
            qmldir << type << " " << QString::fromStdString(version) << " " << qml << Qt::endl;
        }
    }
    file.close();
    file.setFileName(dir.currentPath()+"/"+module+".qrc");
    file.open(QFile::ReadWrite);
    QTextStream qrc(&file);
    qrc << "<RCC>\n\t<qresource prefix=\"" << module << "\">" << Qt::endl;
    qrc << "\t\t<file>qmldir</file>"<< Qt::endl;
    for(const auto &qml : list)
    {
        if (qml.contains(".qml"))
        {
            QString type = qml;
            type.chop(4);
            qrc << "\t\t\t" << "<file>" << qml << "</file>"<< Qt::endl;
        }
    }
    qrc << "\t</qresource>\n</RCC>" << Qt::endl;

    std::string input;
    std::cout << "You may wish to rename the module and qrc prefix, but the prefix and the module name must match the folder name containing your module." << std::endl;
    std::cout << "QML QRC Tool Finished" << std::endl;
    std::cin >> input;
    return a.exec();
}
