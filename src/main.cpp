/**
 *  This file is part of Qt-Net-SNMP.
 *
 *  Copyright (c) 2014 Juan Jose Salazar Garcia jjslzgc@gmail.com
 *
 *  Qt-Net-SNMP is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Qt-Net-SNMP is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Qt-Net-SNMP.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#include "qsnmpmanager.h"
#include <iostream>

/**
 * Main function for debug purposes
 */
int main()
{
    QtNetSNMP::QSNMPManager *manager = QtNetSNMP::QSNMPManager::instance();

    std::cout << "MIB directories" << std::endl;

    foreach(QString dir, manager->getMIBDirectories())
       std::cout << dir.toStdString() << std::endl;

    std::cout << "Modules" << std::endl;

    QStringList modules = manager->getModulesInstalled();

    foreach(QString module, modules)
       std::cout << module.toStdString() << std::endl;

    std::cout << modules.length() << " modules installed" << std::endl;

    return 0;
}
