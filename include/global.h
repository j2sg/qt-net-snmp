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
* @file global.h
* @brief Global constants
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef GLOBAL_H
#define GLOBAL_H

#include "types.h"

#define DEFAULT_VERSION QtNetSNMP::SNMPv1
#define DEFAULT_COMMUNITY_NAME "public"
#define DEFAULT_NON_REPEATERS 0
#define DEFAULT_MAX_REPETITIONS 10
#define DEFAULT_PORT 161
#define DEFAULT_RETRIES 2
#define DEFAULT_TIMEOUT 1000000

#endif // GLOBAL_H
