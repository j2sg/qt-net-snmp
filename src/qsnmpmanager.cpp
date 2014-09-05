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
#include <QDebug>

QtNetSNMP::QSNMPManager *QtNetSNMP::QSNMPManager::instance()
{
    // Meyers implementation of Singleton pattern, thread-safe in C++11
    static QSNMPManager instance;

    return &instance;
}

void QtNetSNMP::QSNMPManager::snmpget(SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs) throw(QSNMPException)
{
    QSNMPCore *core = QSNMPCore::instance();

    core -> snmpoperation(SNMPPDUGet, version, community, agent, objs);
}

void QtNetSNMP::QSNMPManager::snmpgetnext(SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs) throw(QSNMPException)
{
    QSNMPCore *core = QSNMPCore::instance();

    core -> snmpoperation(SNMPPDUGetNext, version, community, agent, objs);
}

void QtNetSNMP::QSNMPManager::snmpgetbulk(SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs,
                                          unsigned short nrepeaters, unsigned short mrepetitions) throw(QSNMPException)
{
    QSNMPCore *core = QSNMPCore::instance();

    core -> snmpoperation(SNMPPDUGetBulk, version, community, agent, objs, nrepeaters, mrepetitions);
}

void QtNetSNMP::QSNMPManager::snmpset(SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs) throw(QSNMPException)
{
    QSNMPCore *core = QSNMPCore::instance();

    core -> snmpoperation(SNMPPDUSet, version, community, agent, objs);
}


QtNetSNMP::QSNMPManager::QSNMPManager()
{
    init_snmp(LIBRARY_NAME);

    qDebug() << "QtNetSNMP::QSNMPManager::QSNMPManager -> Net-SNMP library initialized";
}
