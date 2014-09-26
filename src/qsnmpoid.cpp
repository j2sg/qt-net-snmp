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
* @file qsnmpoid.cpp
* @brief Definitions for Atributes and Methods of QSNMPOID class
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#include "qsnmpoid.h"
#include <QRegExp>
#include <QStringList>

QtNetSNMP::QSNMPOID::QSNMPOID(QVector<oid> *numOID) : _numOID(0)
{
    setNumOID(numOID);
}

QtNetSNMP::QSNMPOID::QSNMPOID(oid *numOID, size_t numOIDLength)
{
    _numOID = new QVector<oid>();

    for(int k = 0;k < static_cast<int>(numOIDLength);++k)
        _numOID -> append(numOID[k]);
}

QtNetSNMP::QSNMPOID::QSNMPOID(const QString& textOID) : _numOID(0)
{
    setTextOID(textOID);
}

QtNetSNMP::QSNMPOID::QSNMPOID(const QSNMPOID& snmpOID) : _numOID(0)
{
    *this = snmpOID;
}

QtNetSNMP::QSNMPOID& QtNetSNMP::QSNMPOID::operator=(const QSNMPOID& snmpOID)
{
    setNumOID(snmpOID._numOID);

    return *this;
}

QtNetSNMP::QSNMPOID QtNetSNMP::QSNMPOID::operator+(int n)
{
    QSNMPOID resOID(*this);

    resOID.numOID() -> append(static_cast<oid>(n));

    return resOID;
}

QtNetSNMP::QSNMPOID::~QSNMPOID()
{
    if(_numOID)
        delete _numOID;
}

void QtNetSNMP::QSNMPOID::setNumOID(QVector<oid> *numOID) throw(QSNMPException)
{
    if(_numOID)
        delete _numOID;

    _numOID = new QVector<oid>(numOID -> size());

    qCopy(numOID -> begin(), numOID -> end(), _numOID -> begin());
}

QVector<oid> *QtNetSNMP::QSNMPOID::numOID()
{
    return _numOID;
}

void QtNetSNMP::QSNMPOID::setTextOID(const QString& textOID) throw(QSNMPException)
{
    QRegExp regExp("\\d+(\\.\\d+)*");

    if(!regExp.exactMatch(textOID))
        throw QSNMPException("QSNMPOID :: Set Text OID :: Textual representation of OID is wrong");

    if(_numOID)
        delete _numOID;

    _numOID = new QVector<oid>();

    foreach(QString str, textOID.split("."))
        _numOID -> append(str.toInt());
}

QString QtNetSNMP::QSNMPOID::textOID() const
{
    QString str;

    for(int k = 0; k < _numOID -> size(); ++k) {
        str.append(QString::number(static_cast<oid>(_numOID -> at(k))));
        if(k != _numOID -> size() - 1)
            str.append(".");
    }

    return str;
}
