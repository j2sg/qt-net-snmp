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
* @file qsnmpdata.h
* @brief QSNMPData class definition
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef QSNMPDATA_H
#define QSNMPDATA_H

#include "types.h"
#include <QString>

namespace QtNetSNMP
{
    class QSNMPData
    {
        friend std::ostream& operator<<(std::ostream& os, const QSNMPData& snmpData);
    public:
        QSNMPData(SNMPDataType type = SNMPDataUnknown, void *value = 0, size_t length = sizeof(char));
        QSNMPData(const QSNMPData& snmpData);
        ~QSNMPData();
        QSNMPData& operator=(const QSNMPData& snmpData);
        SNMPDataType type() const;
        void *value() const;
        size_t length() const;
        void setValue(SNMPDataType type, void *value, size_t length = sizeof(char));
        void setValue(SNMPDataType type, const SNMPValue& value, size_t length = sizeof(char));
    private:
        void initValue(SNMPDataType type = SNMPDataUnknown);
        void delValue();

        SNMPDataType _type;
        SNMPValue _value;
        size_t _length;
    };
}

#endif // QSNMPDATA_H
