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
 * @brief QSNMPManager class that implements the SNMP Manager Behavior
 */
class QSNMPManager
{
public:

    /**
     * @brief Get the unique QSNMPManager instance (Singleton pattern)
     * @return object instance of QSNMPManager class
     */
    static QSNMPManager *instance();
private:

    /**
     * @brief QSNMPManager constructor
     */
    QSNMPManager();

    /**
     * @brief QSNMPManager copy constructor
     */
    QSNMPManager(const QSNMPManager& /* manager */) {}

    /**
     * @brief operator = QSNMPManager assign overloaded operator
     * @return reference to instance of QSNMPManager class
     */
    QSNMPManager& operator=(const QSNMPManager) { return *this; }

    /**
     * @brief _instance unique QSNMPManager instance
     */
    static QSNMPManager *_instance;

    /**
     * @brief _mutex mutex to provide access serialization between threads (thread-safe)
     */
    QMutex _mutex;
};

#endif // QSNMPMANAGER_H
