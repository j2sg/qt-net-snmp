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

#include "ostream.h"

std::ostream& QtNetSNMP::operator<<(std::ostream& os, const QSNMPData& snmpData)
{
    QChar type;
    QString value;
    QString length(static_cast<int>(snmpData._length));

    switch(snmpData._type) {
    case SNMPDataInteger:
        type = 'i';
        break;
    case SNMPDataUnsigned:
        type = 'u';
        break;
    case SNMPDataBits:
        type = 'b';
        break;
    case SNMPDataCounter:
        type = 'c';
        break;
    case SNMPDataTimeTicks:
        type = 't';
        break;
    case SNMPDataCounter64:
        type = 'C';
        break;
    case SNMPDataBitString:
        type = 'b';
        break;
    case SNMPDataOctetString:
        type = 's';
        break;
    case SNMPDataIPAddress:
        type = 'a';
        break;
    case SNMPDataObjectId:
        type = 'o';
        break;
    default:
        type = '=';
    }

    void *valuePtr = snmpData.value();

    if(!valuePtr)
        value = QString("Null");
    else {
        switch(snmpData._type) {
        case SNMPDataInteger:
        case SNMPDataUnsigned:
        case SNMPDataBits:
        case SNMPDataCounter:
        case SNMPDataTimeTicks:
            value = QString::number(*static_cast<long *>(valuePtr));
            break;
        case SNMPDataCounter64:
            value = QString("%1 %2").arg(static_cast<SNMPCounter64 *>(valuePtr) -> high)
                                    .arg(static_cast<SNMPCounter64 *>(valuePtr) -> low);
            break;
        case SNMPDataBitString:
        case SNMPDataOctetString:
        case SNMPDataIPAddress:
            value = QString(*static_cast<unsigned char *>(valuePtr));
            break;
        case SNMPDataObjectId:
            value = QSNMPOID(static_cast<oid *>(valuePtr), snmpData._length).textOID();
            break;
        default:
            value = QString("=");
        }
    }

    return os << QString("t:%1 v:%2 l:%3").arg(type).arg(value).arg(length);
}

std::ostream& QtNetSNMP::operator<<(std::ostream& os, const QSNMPObject& snmpObj)
{
    if(snmpObj._objID)
        os << *snmpObj._objID << " := ";
    if(snmpObj._data)
        os << *snmpObj._data;

    return os;
}

std::ostream& QtNetSNMP::operator<<(std::ostream& os, const QSNMPOID& snmpOID)
{
    return os << snmpOID.textOID();
}
