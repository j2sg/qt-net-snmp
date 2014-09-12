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

#include "qsnmpobject.h"
#include "qsnmpoid.h"
#include "qsnmpdata.h"

QtNetSNMP::QSNMPObject::QSNMPObject(QSNMPOID *objID, QSNMPData *data)
{
}

QtNetSNMP::QSNMPObject::QSNMPObject(const QSNMPObject& obj)
{
}

QtNetSNMP::QSNMPObject& QtNetSNMP::QSNMPObject::operator=(const QSNMPObject& obj)
{
    return *this;
}

QtNetSNMP::QSNMPObject::~QSNMPObject()
{
}

QtNetSNMP::QSNMPObject *QtNetSNMP::QSNMPObject::objID()
{
    return 0;
}

void QtNetSNMP::QSNMPObject::setObjID(QSNMPObject *objID)
{
}

QtNetSNMP::QSNMPData *QtNetSNMP::QSNMPObject::data()
{
    return 0;
}

void QtNetSNMP::QSNMPObject::setData(QSNMPData *data)
{
}

const QString& QtNetSNMP::QSNMPObject::name() const
{
    return QString();
}

void QtNetSNMP::QSNMPObject::setName(const QString& name)
{
}

QtNetSNMP::MIBStatus QtNetSNMP::QSNMPObject::status() const
{
    return MIBStatusMandatory;
}

void QtNetSNMP::QSNMPObject::setStatus(MIBStatus status)
{
}

QtNetSNMP::MIBAccess QtNetSNMP::QSNMPObject::access() const
{
    return MIBAccessReadOnly;
}

void QtNetSNMP::QSNMPObject::setAccess(MIBAccess access)
{
}

const QString& QtNetSNMP::QSNMPObject::description() const
{
    return QString();
}

void QtNetSNMP::QSNMPObject::setDescription(const QString& description)
{
}
