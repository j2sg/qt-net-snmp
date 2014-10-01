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
* @file qsnmptypes.h
* @brief Type declarations
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef QSNMPTYPES_H
#define QSNMPTYPES_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

namespace QtNetSNMP
{
    /**
     * @brief SNMP version to be used
     */
    typedef enum SNMPVersionEnum {
        SNMPv1 = SNMP_VERSION_1,                /**< SNMP version 1 */
        SNMPv2 = SNMP_VERSION_2c,               /**< SNMP version 2 */
        SNMPv3 = SNMP_VERSION_3                 /**< SNMP version 3 */
    } SNMPVersion;

    /**
     * @brief PDU type to be encapsulated into SNMP message
     */
    typedef enum SNMPPDUTypeEnum {
        SNMPPDUGet      = SNMP_MSG_GET,         /**< GET request */
        SNMPPDUGetNext  = SNMP_MSG_GETNEXT,     /**< GET NEXT request */
        SNMPPDUGetBulk  = SNMP_MSG_GETBULK,     /**< GET BULK request */
        SNMPPDUSet      = SNMP_MSG_SET,         /**< SET request */
        SNMPPDUResponse = SNMP_MSG_RESPONSE     /**< Response */
    } SNMPPDUType;

    /**
     * @brief SNMP Data type to MIB object
     */
    typedef enum SNMPDataTypeEnum {
        SNMPDataUnknown     = -1,               /**< Unknown type */
        SNMPDataNull        = ASN_NULL,         /**< Null type */
        SNMPDataInteger     = ASN_INTEGER,      /**< Signed Integer type */
        SNMPDataUnsigned    = ASN_UNSIGNED,     /**< Unsigned Integer type */
        SNMPDataOctetString = ASN_OCTET_STR,    /**< Octet String type */
        SNMPDataBits        = ASN_BIT8,         /**< Bits type */
        SNMPDataBitString   = ASN_BIT_STR,      /**< BitString type */
        SNMPDataObjectId    = ASN_OBJECT_ID,    /**< OID type */
        SNMPDataIPAddress   = ASN_IPADDRESS,    /**< IP Address type */
        SNMPDataCounter     = ASN_COUNTER,      /**< Counter type */
        SNMPDataCounter64   = ASN_COUNTER64,    /**< 64 bits Counter type */
        SNMPDataGauge       = ASN_GAUGE,        /**< Gauge type */
        SNMPDataTimeTicks   = ASN_TIMETICKS     /**< Time Ticks type*/
    } SNMPDataType;

    /**
     * @brief Current status to MIB object
     */
    typedef enum MIBStatusEnum {
        MIBStatusMandatory  = MIB_STATUS_MANDATORY,     /**< Mandatory status */
        MIBStatusOptional   = MIB_STATUS_OPTIONAL,      /**< Optional status */
        MIBStatusObsolete   = MIB_STATUS_OBSOLETE,      /**< Obsolete status */
        MIBStatusDeprecated = MIB_STATUS_DEPRECATED     /**< Deprecated status */
    } MIBStatus;

    /**
     * @brief Access mode to MIB object
     */
    typedef enum MIBAccessEnum {
        MIBAccessReadOnly      = MIB_ACCESS_READONLY,   /**< Read-Only access */
        MIBAccessReadWrite     = MIB_ACCESS_READWRITE,  /**< Read-Write access */
        MIBAccessWriteOnly     = MIB_ACCESS_WRITEONLY,  /**< Write-Only access */
        MIBAccessNotAccessible = MIB_ACCESS_NOACCESS    /**< Not-Accessible access */
    } MIBAccess;

    /**
     * @brief Net-SNMP data value
     * More details in http://www.net-snmp.org/dev/agent/unionnetsnmp__vardata.html
     */
    typedef netsnmp_vardata SNMPValue;

    /**
     * @brief Net-SNMP 64 bits counter
     * More details in http://www.net-snmp.org/dev/agent/structcounter64.html
     */
    typedef struct counter64 SNMPCounter64;

    /**
     * @brief Net-SNMP session with agent
     * More details in http://www.net-snmp.org/dev/agent/structsnmp__session.html
     */
    typedef netsnmp_session SNMPSession;

    /**
     * @brief Net-SNMP request/response PDU
     * More details in http://www.net-snmp.org/dev/agent/structsnmp__pdu.html
     */
    typedef struct snmp_pdu SNMPPDU;

    /**
     * @brief Net-SNMP variable list
     * More details in http://www.net-snmp.org/dev/agent/structvariable__list.html
     */
    typedef netsnmp_variable_list SNMPVariableList;

    /**
     * @brief Net-SNMP MIB tree
     * More details in http://www.net-snmp.org/dev/agent/structtree.html
     */
    typedef struct tree SNMPMIBTree;
}

#endif // QSNMPTYPES_H
