/**
 *  This file is part of Qt-Net-SNMP.
 *
 *  Copyright (c) 2014 Juan Jose Salazar Garcia jjslzgc@gmail.com
 *
 *  QMB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  QMB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with QMB.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

/**
* @file qsnmpmanager.h
* @brief QSNMPManager class definition
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef QSNMPMANAGER_H
#define QSNMPMANAGER_H

#include <QMutex>

/**
 * @brief QSNMPManager class that implements a SNMP Manager
 */
class QSNMPManager
{
public:
    static QSNMPManager *instance();
private:
    QSNMPManager();
    QSNMPManager(const QSNMPManager& /* manager */) {}
    QSNMPManager& operator=(const QSNMPManager) { return *this; }

    static QSNMPManager *_instance;
    QMutex _mutex;
};

#endif // QSNMPMANAGER_H
