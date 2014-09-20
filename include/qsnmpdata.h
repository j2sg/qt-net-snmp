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
    /**
     * @brief QSNMPData class that implements a SNMP data
     */
    class QSNMPData
    {
        friend std::ostream& operator<<(std::ostream& os, const QSNMPData& snmpData);
    public:
        /**
         * @brief QSNMPData constructor
         * @param type SNMP data type
         * @param value SNMP data value
         * @param length SNMP data length
         */
        QSNMPData(SNMPDataType type = SNMPDataUnknown, void *value = 0, size_t length = sizeof(char));

        /**
         * @brief QSNMPData copy constructor
         * @param snmpData QSNMPData instance
         */
        QSNMPData(const QSNMPData& snmpData);

        /**
         * @brief overloaded assignment operator
         * @param snmpData QSNMPData instance
         * @return reference to own object instance
         */
        QSNMPData& operator=(const QSNMPData& snmpData);

        /**
         * @brief QSNMPData destructor
         */
        ~QSNMPData();

        /**
         * @brief Set SNMP data type, value and length
         * @param type SNMP data type
         * @param value SNMP data value
         * @param length SNMP data length
         */
        void setValue(SNMPDataType type, void *value, size_t length = sizeof(char));

        /**
         * @brief Set SNMP data type, value and length
         * @param type SNMP data type
         * @param value Net-SNMP data value
         * @param length SNMP data length
         */
        void setValue(SNMPDataType type, const SNMPValue& value, size_t length = sizeof(char));

        /**
         * @brief Get SNMP data type
         * @return SNMP data type
         */
        SNMPDataType type() const;

        /**
         * @brief Get SNMP data value
         * @return pointer to SNMP data value
         */
        void *value() const;

        /**
         * @brief Get SNMP data length
         * @return SNMP data length
         */
        size_t length() const;

    private:
        /**
         * @brief Initialize SNMP data atributes
         * @param type SNMP data type
         */
        void initValue(SNMPDataType type = SNMPDataUnknown);

        /**
         * @brief Free SNMP data resources
         */
        void delValue();

        /**
         * @brief _type SNMP data type
         */
        SNMPDataType _type;

        /**
         * @brief _value SNMP data value
         */
        SNMPValue _value;

        /**
         * @brief _length SNMP data length
         */
        size_t _length;
    };
}

#endif // QSNMPDATA_H
