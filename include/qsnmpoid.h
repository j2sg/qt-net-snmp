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

#ifndef QSNMPOID_H
#define QSNMPOID_H

#include "types.h"
#include "qsnmpexception.h"
#include <QString>

namespace QtNetSNMP
{
    class QSNMPOID
    {
    public:
        QSNMPOID(oid *numOID, size_t numOIDLength);
        QSNMPOID(const QString& textOID);
        QSNMPOID(const QSNMPOID& snmpOID);
        ~QSNMPOID();
        QSNMPOID& operator=(const QSNMPOID& snmpOID);
        const oid *numOID() const;
        size_t numOIDLength() const;
        void setNumOID(oid *numOID, size_t numOIDLength) throw(QSNMPException);
        const QString& textOID() const;
        void setTextOID(const QString& textOID) throw(QSNMPException);
    private:
        oid *toNumeric();
        QString& toTextual();

        QVector<int> _numOID;
    };
}

#endif // QSNMPOID_H
