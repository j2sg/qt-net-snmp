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
* @file qsnmpobject.cpp
* @brief Definitions for Atributes and Methods of QSNMPObject class
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#include "qsnmpobject.h"
#include "qsnmpoid.h"
#include "qsnmpdata.h"

QtNetSNMP::QSNMPObject::QSNMPObject(QSNMPOID *objID, QSNMPData *data) : _objID(objID), _data(data)
{
    _name = _description = "";
    _status = MIBStatusDeprecated;
    _access = MIBAccessNotAccessible;
}

QtNetSNMP::QSNMPObject::QSNMPObject(const QSNMPObject& snmpObj)
{
    *this = snmpObj;
}

QtNetSNMP::QSNMPObject& QtNetSNMP::QSNMPObject::operator=(const QSNMPObject& snmpObj)
{
    if(_objID)
        delete _objID;

    _objID = (snmpObj._objID != 0) ? new QSNMPOID(*snmpObj._objID) : 0;

    if(_data)
        delete _data;

    _data = (snmpObj._data != 0) ? new QSNMPData(*snmpObj._data) : 0;

    _name = snmpObj._name;
    _status = snmpObj._status;
    _access = snmpObj._access;
    _description = snmpObj._description;

    return *this;
}

QtNetSNMP::QSNMPObject::~QSNMPObject()
{
    if(_objID)
        delete _objID;
    if(_data)
        delete _data;
}

void QtNetSNMP::QSNMPObject::setObjID(QSNMPOID *objID)
{
    if(_objID)
        delete _objID;

    _objID = objID;
}

QtNetSNMP::QSNMPOID *QtNetSNMP::QSNMPObject::objID()
{
    return _objID;
}

void QtNetSNMP::QSNMPObject::setData(QSNMPData *data)
{
    if(_data)
        delete _data;

    _data = data;
}

QtNetSNMP::QSNMPData *QtNetSNMP::QSNMPObject::data()
{
    return _data;
}

void QtNetSNMP::QSNMPObject::setName(const QString& name)
{
    _name = name;
}

const QString& QtNetSNMP::QSNMPObject::name() const
{
    return _name;
}

void QtNetSNMP::QSNMPObject::setStatus(MIBStatus status)
{
    _status = status;
}

QtNetSNMP::MIBStatus QtNetSNMP::QSNMPObject::status() const
{
    return _status;
}

void QtNetSNMP::QSNMPObject::setAccess(MIBAccess access)
{
    _access = access;
}

QtNetSNMP::MIBAccess QtNetSNMP::QSNMPObject::access() const
{
    return _access;
}

void QtNetSNMP::QSNMPObject::setDescription(const QString& description)
{
    _description = description;
}

const QString& QtNetSNMP::QSNMPObject::description() const
{
    return _description;
}
