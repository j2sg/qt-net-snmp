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
* @file qsnmpmanager.h
* @brief QSNMPManager class definition
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef QSNMPMANAGER_H
#define QSNMPMANAGER_H

#include "qtnetsnmp_global.h"
#include "qsnmpglobal.h"
#include "qsnmpexception.h"
#include <QString>
#include <QStringList>
#include <QVector>

namespace QtNetSNMP
{
    // Forward declarations
    class QSNMPCore;
    class QSNMPObject;
    class QMIBTree;

    /**
     * @brief QSNMPManager class that implements the SNMP Manager Behavior
     */
    class QTNETSNMP_EXPORT QSNMPManager
    {
    public:

        /**
         * @brief Get a QSNMPManager instance
         * @return pointer to instance of QSNMPManager class
         */
        static QSNMPManager *instance();

        /**
         * @brief Set up SNMP Manager parameters
         * @param port SNMP agent port
         * @param retries number of retries
         * @param timeout number of microseconds for timeout
         */
        void setup(unsigned short port, unsigned short retries = QTNETSNMP_DEFAULT_RETRIES, long timeout = QTNETSNMP_DEFAULT_TIMEOUT);

        /**
         * @brief Send SNMP GET request
         * @param version SNMP version
         * @param community community name
         * @param agent ip address or domain name of SNMP agent
         * @param objs SNMP objects list
         */
        void snmpget(SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs) throw(QSNMPException);

        /**
         * @brief Send SNMP GET NEXT request
         * @param version SNMP version
         * @param community community name
         * @param agent ip address or domain name of SNMP agent
         * @param objs SNMP objects list
         */
        void snmpgetnext(SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs) throw(QSNMPException);

        /**
         * @brief Send SNMP GET BULK request
         * @param version SNMP version
         * @param community community name
         * @param agent ip address or domain name of SNMP agent
         * @param objs SNMP objects list
         * @param nrepaters number of objects that are only expected to return a single instance
         * @param mrepetitions number of objects that should be returned for all the repeating OIDs
         */
        void snmpgetbulk(SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs,
                         unsigned short nrepeaters = QTNETSNMP_DEFAULT_NON_REPEATERS, unsigned short mrepetitions = QTNETSNMP_DEFAULT_MAX_REPETITIONS) throw(QSNMPException);

        /**
         * @brief Send SNMP SET request
         * @param version SNMP version
         * @param community community name
         * @param agent ip address or domain name of SNMP agent
         * @param objs SNMP objects list
         */
        void snmpset(SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs) throw(QSNMPException);

        /**
         * @brief Get MIB tree for a MIB module
         * @param module MIB module name, Whether this is empty will get all MIBs
         * @return pointer to MIB tree
         */
        QMIBTree *getMIBModule(const QString& module = QString()) throw(QSNMPException);

        /**
         * @brief Get MIB tree for a MIB module contained in a file
         * @param fileName File name that contains the MIB module
         * @return pointer to MIB tree
         */
        QMIBTree *getMIBFile(const QString& fileName) throw(QSNMPException);

        /**
         * @brief Get MIB modules list installed on system
         * @return MIB modules list
         */
        QStringList getModulesInstalled();

        /**
         * @brief Get MIB directories list where there are the MIB modules
         * @return MIB directories list
         */
        QStringList getMIBDirectories();
    private:

        /**
         * @brief QSNMPCore constructor
         */
        QSNMPManager();

        /**
         * @brief QSNMPManager copy constructor
         */
        QSNMPManager(const QSNMPManager& /* manager */) {}

        /**
         * @brief overloaded assignment operator
         * @return reference to own object instance
         */
        QSNMPManager& operator=(const QSNMPManager& /* manager */) { return *this; }

        /**
         * @brief QSNMPManager destructor
         */
        ~QSNMPManager() {}

        /**
         * @brief _core SNMP core that offers support to protocol
         */
        QSNMPCore *_core;
    };
}

#endif // QSNMPMANAGER_H
