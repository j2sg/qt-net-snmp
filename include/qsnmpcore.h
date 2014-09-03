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
* @file qsnmpcore.h
* @brief QSNMPCore class definition
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef QSNMPCORE_H
#define QSNMPCORE_H

#include "global.h"
#include "qsnmpexception.h"
#include <QString>
#include <QVector>

namespace QtNetSNMP
{
    // Forward declarations
    class QSNMPObject;

    /**
     * @brief QSNMPCore class that implements all basic SNMP protocol primitives
     */
    class QSNMPCore
    {
    public:

        /**
         * @brief Get a QSNMPCore instance
         * @return  pointer to instance of QSNMPCore class
         */
        static QSNMPCore *instance();

        /**
         * @brief snmpoperation Send SNMP request
         * @param type SNMP request type
         * @param version SNMP version
         * @param community community name
         * @param agent ip address or domain name of SNMP agent
         * @param objs SNMP objects list
         * @param nrepaters number of objects that are only expected to return a single instance
         * @param mrepetitions number of objects that should be returned for all the repeating OIDs
         */
        void snmpoperation(SNMPPDUType type, SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs,
                           unsigned short nrepeaters = DEFAULT_NON_REPEATERS, unsigned short mrepetitions = DEFAULT_MAX_REPETITIONS) throw(QSNMPException);
    private:

        /**
         * @brief QSNMPCore constructor
         */
        QSNMPCore() {}

        /**
         * @brief QSNMPCore copy constructor
         */
        QSNMPCore(const QSNMPCore& /* core */) {}

        /**
         * @brief operator = overloaded assignment operator
         * @return reference to own object instance
         */
        QSNMPCore& operator=(const QSNMPCore& /* core */) { return *this; }

        /**
         * @brief QSNMPCore destructor
         */
        ~QSNMPCore() {}


    };
}

#endif // QSNMPCORE_H
