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

#include "qsnmpoid.h"
#include <QVector>

QtNetSNMP::QSNMPOID::QSNMPOID(QVector<int> *numOID)
{
}

QtNetSNMP::QSNMPOID::QSNMPOID(const QString& textOID)
{
}

QtNetSNMP::QSNMPOID::QSNMPOID(const QSNMPOID& snmpOID)
{
}

QtNetSNMP::QSNMPOID& QtNetSNMP::QSNMPOID::operator=(const QSNMPOID& snmpOID)
{
    return *this;
}

QtNetSNMP::QSNMPOID& QtNetSNMP::QSNMPOID::operator+(int n)
{
    return *this;
}

QtNetSNMP::QSNMPOID::~QSNMPOID()
{
    if(_numOID)
        delete _numOID;
}

const QVector<int> *QtNetSNMP::QSNMPOID::numOID() const
{
    return 0;
}

void QtNetSNMP::QSNMPOID::setNumOID(QVector<int> *numOID) throw(QSNMPException)
{
}

const QString& QtNetSNMP::QSNMPOID::textOID() const
{
    return QString();
}

void QtNetSNMP::QSNMPOID::setTextOID(const QString& textOID) throw(QSNMPException)
{
}

QVector<int> *QtNetSNMP::QSNMPOID::toNumeric(const QString& textOID)
{
    return 0;
}

QString QtNetSNMP::QSNMPOID::toTextual()
{
    return QString();
}
