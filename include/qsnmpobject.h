/**
 *  This file is part of Qt-Net-SNMP.
 *
 *  Copyright (c) 2014-2015 Juan Jose Salazar Garcia jjslzgc@gmail.com
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
* @file qsnmpobject.h
* @brief QSNMPObject class definition
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef QSNMPOBJECT_H
#define QSNMPOBJECT_H

#include "qtnetsnmp_global.h"
#include "qsnmptypes.h"
#include <QString>

namespace QtNetSNMP
{
    // Forward declarations
    class QSNMPOID;
    class QSNMPData;

    /**
     * @brief QSNMPObject class that implements a SNMP object
     */
    class QTNETSNMP_EXPORT QSNMPObject
    {
        friend std::ostream& operator<<(std::ostream& os, const QSNMPObject& snmpObj);
    public:
        /**
         * @brief QSNMPObject constructor
         * @param objID SNMP OID
         * @param data SNMP data
         */
        QSNMPObject(QSNMPOID *objID = 0, QSNMPData *data = 0);

        /**
         * @brief QSNMPObject copy constructor
         * @param snmpObj QSNMPObject instance
         */
        QSNMPObject(const QSNMPObject& snmpObj);

        /**
         * @brief overloaded assignment operator
         * @param snmpObj QSNMPObject instance
         * @return reference to own object instance
         */
        QSNMPObject& operator=(const QSNMPObject& snmpObj);

        /**
         * @brief QSNMPObject destructor
         */
        ~QSNMPObject();

        /**
         * @brief Set SNMP OID
         * @param objID SNMP OID
         *
         */
        void setObjID(QSNMPOID *objID);

        /**
         * @brief Get SNMP OID
         * @return pointer to SNMP OID
         */
        QSNMPOID *objID();

        /**
         * @brief Set SNMP data
         * @param data SNMP data
         */
        void setData(QSNMPData *data);

        /**
         * @brief Get SNMP data
         * @return pointer to SNMP data
         */
        QSNMPData *data();

        /**
         * @brief Set community name
         * @param name community name
         */
        void setName(const QString& name);

        /**
         * @brief Get community name
         * @return community name
         */
        const QString& name() const;

        /**
         * @brief Set object status
         * @param status object status
         */
        void setStatus(MIBStatus status);

        /**
         * @brief Get object status
         * @return object status
         */
        MIBStatus status() const;

        /**
         * @brief Set object access type
         * @param access object access type
         */
        void setAccess(MIBAccess access);

        /**
         * @brief Get object access type
         * @return object access type
         */
        MIBAccess access() const;

        /**
         * @brief Set object description
         * @param description object description
         */
        void setDescription(const QString& description);

        /**
         * @brief Get object description
         * @return object description
         */
        const QString& description() const;

    private:
        /**
         * @brief _objID SNMP OID
         */
        QSNMPOID *_objID;
        /**
         * @brief _data SNMP data
         */
        QSNMPData *_data;
        /**
         * @brief _name Community name
         */
        QString _name;
        /**
         * @brief _status Object status
         */
        MIBStatus _status;
        /**
         * @brief _access Object access type
         */
        MIBAccess _access;
        /**
         * @brief _description Object status
         */
        QString _description;
    };
}

#endif // QSNMPOBJECT_H
