/**
 *  This file is part of Qt-Net-SNMP.
 *
 *  Copyright (c) 2014-2015 Juan Jose Salazar Garcia jjslzgc@gmail.com
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
* @file qtnetsnmp_global.h
* @brief Macro definition according to compile the library or compile the client application that uses the library.
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef QTNETSNMP_GLOBAL_H
#define QTNETSNMP_GLOBAL_H

#include <QtCore/QtGlobal>

#ifdef QTNETSNMP_LIBRARY
#   define QTNETSNMP_EXPORT Q_DECL_EXPORT
#else
#   define QTNETSNMP_EXPORT Q_DECL_IMPORT
#endif

#endif // QTNETSNMP_GLOBAL_H
