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
* @file qsnmpostream.h
* @brief Declarations of overloaded insertion operators to SNMP Classes
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef QSNMPOSTREAM_H
#define QSNMPOSTREAM_H

#include "qmibtree.h"
#include "qsnmpdata.h"
#include "qsnmpobject.h"
#include "qsnmpoid.h"

namespace QtNetSNMP
{
    /**
     * @brief Overloaded insertion operator to QMIBTree class
     * @param os Output stream reference
     * @param mibTree QMIBTree instance reference
     * @return Output stream reference to chain calls
     */
    std::ostream& operator<<(std::ostream& os, const QMIBTree& mibTree);
    /**
     * @brief Overloaded insertion operator to QSNMPData class
     * @param os Output stream reference
     * @param snmpData QSNMPData instance reference
     * @return Output stream reference to chain calls
     */
    std::ostream& operator<<(std::ostream& os, const QSNMPData& snmpData);

    /**
     * @brief Overloaded insertion operator to QSNMPObject class
     * @param os Output stream reference
     * @param snmpObj QSNMPObject instance reference
     * @return Output stream reference to chain calls
     */
    std::ostream& operator<<(std::ostream& os, const QSNMPObject& snmpObj);

    /**
     * @brief Overloaded insertion operator to QSNMPOID class
     * @param os Output stream reference
     * @param snmpOID QSNMPOID instance reference
     * @return Output stream reference to chain calls
     */
    std::ostream& operator<<(std::ostream& os, const QSNMPOID& snmpOID);
}

#endif // QSNMPOSTREAM_H
