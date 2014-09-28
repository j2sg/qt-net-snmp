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
#include "qsnmpobject.h"
#include "qsnmpoid.h"
#include "qsnmpostream.h"
#include <iostream>
#include <QVector>

/**
 * Main function for debug purposes
 */
int main()
{   
    try {
        QtNetSNMP::QSNMPManager *manager = QtNetSNMP::QSNMPManager::instance();
        QtNetSNMP::QMIBTree *mib = manager -> getMIBModule();

        if(mib)
            std::cout << "MIB loaded and avaible" << std::endl;

        /**QtNetSNMP::QSNMPObject *snmpObj = new QtNetSNMP::QSNMPObject(new QtNetSNMP::QSNMPOID("1.3.6.1.2.1.1.1.0"));

        manager -> snmpget(QtNetSNMP::SNMPv2, "public", "192.168.1.30", QVector<QtNetSNMP::QSNMPObject *>() << snmpObj);

        std::cout << *snmpObj << std::endl;**/

    } catch(QtNetSNMP::QSNMPException& exception) {
        std::cout << exception.message().toStdString() << std::endl;
    }

    return 0;
}
