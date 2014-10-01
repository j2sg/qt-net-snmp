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
* @file qsnmpglobal.h
* @brief Global constants declarations
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef QSNMPGLOBAL_H
#define QSNMPGLOBAL_H

#include "qsnmptypes.h"

#define LIBRARY_NAME "QtNetSNMP"            /**< Library name */
#define DEFAULT_VERSION QtNetSNMP::SNMPv1   /**< SNMP version by default */
#define DEFAULT_COMMUNITY_NAME "public"     /**< SNMP community name by default */
#define DEFAULT_NON_REPEATERS 0             /**< Non-repeaters value used by default on SNMP GET BULK requests */
#define DEFAULT_MAX_REPETITIONS 10          /**< Max-repetitions value used by default on SNMP GET BULK requests */
#define DEFAULT_PORT 161                    /**< SNMP Agent port number used by default */
#define DEFAULT_RETRIES 2                   /**< Number of retries by default */
#define DEFAULT_TIMEOUT 1000000             /**< Timeout (microseconds) by default */

#endif // QSNMPGLOBAL_H
