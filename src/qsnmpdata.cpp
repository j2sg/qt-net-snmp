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
* @file qsnmpdata.cpp
* @brief Definitions for Atributes and Methods of QSNMPData class
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#include "qsnmpdata.h"
#include <algorithm>

QtNetSNMP::QSNMPData::QSNMPData(SNMPDataType type, void *value, size_t length)
{
    initValue(type);
    setValue(type, value, length);
}

QtNetSNMP::QSNMPData::QSNMPData(const QSNMPData& snmpData)
{
    initValue();
    *this = snmpData;
}

QtNetSNMP::QSNMPData& QtNetSNMP::QSNMPData::operator=(const QSNMPData& snmpData)
{
    setValue(snmpData._type, snmpData._value, snmpData._length);

    return *this;
}

QtNetSNMP::QSNMPData::~QSNMPData()
{
    delValue();
}

void QtNetSNMP::QSNMPData::setValue(SNMPDataType type, void *value, size_t length)
{
    delValue();

    if(!value || length <= 0) {
        initValue(type);
        return;
    }

    _type = type;
    _length = length;

    switch(type) {
    case SNMPDataInteger:
    case SNMPDataUnsigned:
    case SNMPDataBits:
    case SNMPDataCounter:
    case SNMPDataTimeTicks:
        _value.integer = new long;
        *_value.integer = *static_cast<long *>(value);
        break;
    case SNMPDataCounter64:
        _value.counter64 = new SNMPCounter64;
        *_value.counter64 = *static_cast<SNMPCounter64 *>(value);
        break;
    case SNMPDataBitString:
        _value.bitstring = new unsigned char[length + 1];
        std::copy(static_cast<unsigned char *>(value), static_cast<unsigned char *>(value) + length, _value.bitstring);
        _value.bitstring[length] = '\0';
        break;
    case SNMPDataOctetString:
    case SNMPDataIPAddress:
        _value.string = new unsigned char[length + 1];
        std::copy(static_cast<unsigned char *>(value), static_cast<unsigned char *>(value) + length, _value.string);
        _value.string[length] = '\0';
        break;
    case SNMPDataObjectId:
        _value.objid = new oid[MAX_OID_LEN];
        std::copy(static_cast<oid *>(value), static_cast<oid *>(value) + MAX_OID_LEN, _value.objid);
        break;
    default:
        initValue();
    }


}

void QtNetSNMP::QSNMPData::setValue(SNMPDataType type, const SNMPValue& value, size_t length)
{
    switch(type) {
    case SNMPDataInteger:
    case SNMPDataUnsigned:
    case SNMPDataBits:
    case SNMPDataCounter:
    case SNMPDataTimeTicks:
        setValue(type, value.integer, length);
        break;
    case SNMPDataCounter64:
        setValue(type, value.counter64, length);
        break;
    case SNMPDataBitString:
        setValue(type, value.bitstring, length);
        break;
    case SNMPDataOctetString:
    case SNMPDataIPAddress:
        setValue(type, value.string, length);
        break;
    case SNMPDataObjectId:
        setValue(type, value.objid, length);
        break;
    default:
        initValue();
    }
}

QtNetSNMP::SNMPDataType QtNetSNMP::QSNMPData::type() const
{
    return _type;
}

void *QtNetSNMP::QSNMPData::value() const
{
    void *ptr;

    switch(_type) {
    case SNMPDataInteger:
    case SNMPDataUnsigned:
    case SNMPDataBits:
    case SNMPDataCounter:
    case SNMPDataTimeTicks:
        ptr = _value.integer;
        break;
    case SNMPDataCounter64:
        ptr = _value.counter64;
        break;
    case SNMPDataBitString:
        ptr = _value.bitstring;
        break;
    case SNMPDataOctetString:
    case SNMPDataIPAddress:
        ptr = _value.string;
        break;
    case SNMPDataObjectId:
        ptr = _value.objid;
        break;
    default:
        ptr = 0;
    }

    return ptr;
}

size_t QtNetSNMP::QSNMPData::length() const
{
    return _length;
}

void QtNetSNMP::QSNMPData::initValue(SNMPDataType type)
{
    // Sets any member of netsnmp_vardata union to null pointer.
    _value.integer = 0;
    _length = 0;
    _type = type;
}

void QtNetSNMP::QSNMPData::delValue()
{
    void *ptr;

    if((ptr = value())) {
        switch(_type) {
        case SNMPDataInteger:
        case SNMPDataUnsigned:
        case SNMPDataBits:
        case SNMPDataCounter:
        case SNMPDataTimeTicks:
            delete static_cast<long *>(ptr);
            break;
        case SNMPDataCounter64:
            delete static_cast<SNMPCounter64 *>(ptr);
            break;
        case SNMPDataBitString:
        case SNMPDataOctetString:
        case SNMPDataIPAddress:
            delete [] static_cast<unsigned char *>(ptr);
            break;
        case SNMPDataObjectId:
            delete [] static_cast<oid *>(ptr);
            break;
        default:
            break;
        }

        initValue();
    }
}
