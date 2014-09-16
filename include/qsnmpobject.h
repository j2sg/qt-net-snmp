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

#ifndef QSNMPOBJECT_H
#define QSNMPOBJECT_H

#include "types.h"
#include <QString>

namespace QtNetSNMP
{
    class QSNMPOID;
    class QSNMPData;

    /**
     * @brief QSNMPObject class
     */
    class QSNMPObject
    {
        friend std::ostream& operator<<(std::ostream& os, const QSNMPObject& obj);
    public:
        QSNMPObject(QSNMPOID *objID = 0, QSNMPData *data = 0);
        QSNMPObject(const QSNMPObject& obj);
        QSNMPObject& operator=(const QSNMPObject& obj);
        ~QSNMPObject();
        QSNMPOID *objID();
        void setObjID(QSNMPOID *objID);
        QSNMPData *data();
        void setData(QSNMPData *data);
        const QString& name() const;
        void setName(const QString& name);
        MIBStatus status() const;
        void setStatus(MIBStatus status);
        MIBAccess access() const;
        void setAccess(MIBAccess access);
        const QString& description() const;
        void setDescription(const QString& description);
    private:
        QSNMPOID *_objID;
        QSNMPData *_data;
        QString _name;
        MIBStatus _status;
        MIBAccess _access;
        QString _description;
    };
}

#endif // QSNMPOBJECT_H
