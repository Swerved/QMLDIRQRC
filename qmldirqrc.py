# QMLDir QRC File Script
# Copyright Swerve Games, 2021.

import os, fnmatch

folder = str(os.getcwd().split('\\')[-1]).lower()
modules = ["module " + str(folder).upper()]
xml = ["<RCC>"]
version = "1.0"
qmldir = "qmldir"
qrc = folder + ".qrc"

def get():
    print("Preparing qmldir and rcc files...")
    xml.append("\t<qresource prefix =\"/" + str(folder).upper() + "\">")
    xml.append("\t\t<file>qmldir</file>")
    for file in os.listdir('.'):
        if fnmatch.fnmatch(file, '*.py'):
            modules.append(file.replace(".py", "") + " " + version + " " + file)
            xml.append("\t\t\t<file>" + file + "</file>")
    xml.append("\t</qresource>")
    xml.append("</RCC>")

def write(file, list):
    with open(file, 'w') as f:
        print("Writing to " + file + "...")
        f.write('\n'.join(list[0:]) + '\n')

def remove(file):
    if os.path.exists(file):
        print("Removing " + file + "...")
        os.remove(file)

print("QML QRC Tool generates QRC and QMLDir files based on .qml files in the current working directory")
remove(qmldir)
remove(qrc)
get()
write(qmldir, modules)
write(qrc, xml)
print("QML QRC Tool complete")
