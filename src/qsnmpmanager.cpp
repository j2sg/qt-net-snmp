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

/**
* @file qsnmpmanager.cpp
* @brief Definitions for Atributes and Methods of QSNMPManager class
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#include "qsnmpmanager.h"
#include "qsnmpcore.h"
#include "qsnmpobject.h"

QtNetSNMP::QSNMPManager *QtNetSNMP::QSNMPManager::instance()
{
    // Meyers implementation of Singleton pattern, thread-safe in C++11
    static QSNMPManager instance;

    return &instance;
}

void QtNetSNMP::QSNMPManager::setup(unsigned short port, unsigned short retries, long timeout)
{
    _core -> setPort(port);
    _core -> setRetries(retries);
    _core -> setTimeout(timeout);
}

void QtNetSNMP::QSNMPManager::snmpget(SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs) throw(QSNMPException)
{
    _core -> snmpoperation(SNMPPDUGet, version, community, agent, objs);
}

void QtNetSNMP::QSNMPManager::snmpgetnext(SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs) throw(QSNMPException)
{
    _core -> snmpoperation(SNMPPDUGetNext, version, community, agent, objs);
}

void QtNetSNMP::QSNMPManager::snmpgetbulk(SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs,
                                          unsigned short nrepeaters, unsigned short mrepetitions) throw(QSNMPException)
{
    _core -> snmpoperation(SNMPPDUGetBulk, version, community, agent, objs, nrepeaters, mrepetitions);
}

void QtNetSNMP::QSNMPManager::snmpset(SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs) throw(QSNMPException)
{
    _core -> snmpoperation(SNMPPDUSet, version, community, agent, objs);
}


QtNetSNMP::QSNMPManager::QSNMPManager()
{
    _core = QSNMPCore::instance();
}
