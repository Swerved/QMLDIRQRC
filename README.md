# QMLDIRQRC
Qmldirqrc Tool
A Qt Console Application for generating qmldir and qrc files for a QML Module.
Additional Python script for generating with python

For Qt/C++:

Dependency on Qt5Core.

Build, run from a folder wihere your qml files are.
You will be prompted for a version identifier. 
Module name and QRC prefix takes the QDir::dirName() of the folder you are running the program from. 

For Python: 
Place script in working directory for qml files

Run with: 

python qmldirqrc.py
