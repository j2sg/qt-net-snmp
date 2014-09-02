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
* @file qsnmpmanager.h
* @brief QSNMPManager class definition
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef QSNMPMANAGER_H
#define QSNMPMANAGER_H

#include "global.h"

namespace QtNetSNMP
{
    /**
     * @brief QSNMPManager class that implements the SNMP Manager Behavior
     */
    class QSNMPManager
    {
    public:
        // Setters && Getters methods

        /**
         * @brief Set SNMP agent port
         * @param port SNMP agent port
         */
        void setPort(unsigned short port);

        /**
         * @brief Get SNMP agent port
         * @return SNMP agent port
         */
        unsigned short port() const;

        /**
         * @brief Set number of retries
         * @param retries number of retries
         */
        void setRetries(unsigned short retries);

        /**
         * @brief Get number of retries
         * @return number of retries
         */
        unsigned short retries() const;

        /**
         * @brief Set timeout
         * @param timeout timeout
         */
        void setTimeout(long timeout);

        /**
         * @brief Get timeout
         * @return  timeout
         */
        long timeout() const;

        /**
         * @brief Get a QSNMPManager instance
         * @return pointer to instance of QSNMPManager class
         */
        static QSNMPManager *instance();
    private:

        /**
         * @brief QSNMPManager constructor
         * @param port SNMP agent port
         * @param retries number of retries
         * @param timeout number of microseconds for timeout
         */
        QSNMPManager(unsigned short port = DEFAULT_PORT, unsigned short retries = DEFAULT_RETRIES, long timeout = DEFAULT_TIMEOUT);

        /**
         * @brief QSNMPManager copy constructor
         */
        QSNMPManager(const QSNMPManager& /* manager */) {}

        /**
         * @brief overloaded assignment operator
         * @return reference to instance of QSNMPManager class
         */
        QSNMPManager& operator=(const QSNMPManager) { return *this; }

        /**
         * @brief QSNMPManager destructor
         */
        ~QSNMPManager() {}

        /**
         * @brief _port SNMP Agent remote port
         */
        unsigned short _port;

        /**
         * @brief retries Number of retries before timeout
         */
        unsigned short _retries;

        /**
         * @brief _timeout Number of microseconds until first timeout
         */
        unsigned long _timeout;
    };
}

#endif // QSNMPMANAGER_H
