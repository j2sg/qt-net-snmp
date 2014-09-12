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

#include "qsnmpdata.h"

QtNetSNMP::QSNMPData::QSNMPData(SNMPDataType type, void *value, size_t length)
{

}

QtNetSNMP::QSNMPData::QSNMPData(const QSNMPData& snmpData)
{

}

QtNetSNMP::QSNMPData::~QSNMPData()
{

}

QtNetSNMP::QSNMPData& QtNetSNMP::QSNMPData::operator=(const QSNMPData& snmpData)
{
    return *this;
}

QtNetSNMP::SNMPDataType QtNetSNMP::QSNMPData::type() const
{
    return SNMPDataUnknown;
}

void QtNetSNMP::QSNMPData::setType(SNMPDataType type)
{
}

void *QtNetSNMP::QSNMPData::value() const
{
    return 0;
}

void QtNetSNMP::QSNMPData::setValue(void *value)
{
}

void QtNetSNMP::QSNMPData::setValue(const SNMPValue& value)
{
}

size_t QtNetSNMP::QSNMPData::length() const
{
    return 0;
}

void QtNetSNMP::QSNMPData::setLength(size_t length)
{
}

const QString& QtNetSNMP::QSNMPData::toString() const
{
    return QString();
}
