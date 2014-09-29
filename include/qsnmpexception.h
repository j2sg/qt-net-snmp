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
* @file qsnmpexception.h
* @brief QSNMPException class definition
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef QSNMPEXCEPTION_H
#define QSNMPEXCEPTION_H

#include "qtnetsnmp_global.h"
#include <QString>

namespace QtNetSNMP
{
    /**
     * @brief QSNMPException class to error handling
     */
    class QTNETSNMP_EXPORT QSNMPException
    {
    public:
        /**
         * @brief QSNMPException constructor
         * @param message error description
         */
        QSNMPException(const QString& message)
        {
            _message = message;
        }

        /**
         * @brief Get error description
         * @return error description
         */
        const QString& message() const
        {
            return _message;
        }

    private:
        /**
         * @brief _message error description
         */
        QString _message;
    };
}

#endif // QSNMPEXCEPTION_H
