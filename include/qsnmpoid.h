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
* @file qsnmpoid.h
* @brief QSNMPOID class definition
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef QSNMPOID_H
#define QSNMPOID_H

#include "qtnetsnmp_global.h"
#include "qsnmptypes.h"
#include "qsnmpexception.h"
#include <QString>
#include <QVector>

namespace QtNetSNMP
{
    /**
     * @brief QSNMPOID class that implements a SNMP OID
     */
    class QTNETSNMP_EXPORT QSNMPOID
    {
        friend std::ostream& operator<<(std::ostream& os, const QSNMPOID& snmpOID);
    public:
        /**
         * @brief QSNMPOID constructor
         * @param numOID vector of integers that represents the OID numeric notation
         */
        QSNMPOID(QVector<oid> *numOID);

        /**
         * @brief QSNMPOID constructor
         * @param numOID array of integers that represents the OID numeric notation
         * @param numOIDLength array length
         */
        QSNMPOID(oid *numOID, size_t numOIDLength);

        /**
         * @brief QSNMPOID constructor
         * @param textOID string that represents the OID textual notation
         */
        QSNMPOID(const QString& textOID);

        /**
         * @brief QSNMPOID copy constructor
         * @param snmpOID QSNMPOID instance
         */
        QSNMPOID(const QSNMPOID& snmpOID);

        /**
         * @brief overloaded assignment operator
         * @param snmpOID QSNMPOID instance
         * @return reference to the own object instance
         */
        QSNMPOID& operator=(const QSNMPOID& snmpOID);

        /**
         * @brief overloaded addition operator
         * @param n sub-identifier append to the OID
         * @return QSNMPOID instance
         */
        QSNMPOID operator+(int n);

        /**
         * @brief QSNMPOID destructor
         */
        ~QSNMPOID();

        /**
         * @brief Set OID numeric notation
         * @param numOID OID numeric notation
         */
        void setNumOID(QVector<oid> *numOID) throw(QSNMPException);

        /**
         * @brief Get OID numeric notation
         * @return OID numeric notation
         */
        QVector<oid> *numOID();

        /**
         * @brief Set OID textual notation
         * @param textOID OID textual notation
         */
        void setTextOID(const QString& textOID) throw(QSNMPException);

        /**
         * @brief Get OID textual notation
         * @return OID textual notation
         */
        QString textOID() const;

    private:
        /**
         * @brief _numOID OID numeric notation
         */
        QVector<oid> *_numOID;
    };
}

#endif // QSNMPOID_H
