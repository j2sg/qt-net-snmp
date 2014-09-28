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
* @file qsnmpcore.cpp
* @brief Definitions for Atributes and Methods of QSNMPCore class
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#include "qsnmpcore.h"
#include "qsnmpobject.h"
#include "qsnmpdata.h"
#include "qsnmpoid.h"
#include "qmibtree.h"

void QtNetSNMP::QSNMPCore::setPort(unsigned short port)
{
    _port = port;
}

unsigned short QtNetSNMP::QSNMPCore::port() const
{
    return _port;
}

void QtNetSNMP::QSNMPCore::setRetries(unsigned short retries)
{
    _retries = retries;
}

unsigned short QtNetSNMP::QSNMPCore::retries() const
{
    return _retries;
}

void QtNetSNMP::QSNMPCore::setTimeout(long timeout)
{
    _timeout = timeout;
}

long QtNetSNMP::QSNMPCore::timeout() const
{
    return _timeout;
}

QtNetSNMP::QSNMPCore *QtNetSNMP::QSNMPCore::instance()
{
    // Meyers implementation of Singleton pattern, thread-safe in C++11
    static QSNMPCore instance;

    return &instance;
}

void QtNetSNMP::QSNMPCore::snmpoperation(SNMPPDUType type, SNMPVersion version, const QString& community, const QString& agent, QVector<QSNMPObject *>& objs,
                           unsigned short nrepeaters, unsigned short mrepetitions) throw(QSNMPException)
{
    SNMPSession *session;
    SNMPPDU *requestPDU;
    SNMPPDU *responsePDU;

    session = createSession(version, community, agent);
    requestPDU = createPDU(type, objs, nrepeaters, mrepetitions);
    responsePDU = sendPDU(session, requestPDU);

    if(type != SNMPPDUSet)
        processResponse(responsePDU, objs);

    snmp_free_pdu(responsePDU);
    snmp_close(session);
    SOCK_CLEANUP; // Free resources on Win32. (No effect on Unix systems)
}

QtNetSNMP::QMIBTree *QtNetSNMP::QSNMPCore::getMIBTree(SNMPMIBTree *root)
{
    QMIBTree *mibTree = 0;

    if(root) {
        mibTree = new QMIBTree;
        parseMIBTree(root, mibTree);
    }

    return mibTree;
}


QtNetSNMP::QSNMPCore::QSNMPCore(unsigned short port, unsigned short retries, long timeout) : _port(port), _retries(retries), _timeout(timeout)
{
    init_snmp(LIBRARY_NAME);
    snmp_set_mib_warnings(0);
    snmp_set_mib_errors(0);
    snmp_set_save_descriptions(1);
}

QtNetSNMP::SNMPSession *QtNetSNMP::QSNMPCore::createSession(SNMPVersion version, const QString& community, const QString& agent) throw(QSNMPException)
{
    SNMPSession session;
    SNMPSession *openedSession;
    std::string stdCommunity = community.toStdString();
    std::string stdAgent = agent.toStdString();

    if(version != SNMPv1 && version != SNMPv2)
        throw QSNMPException("QSNMPCore :: Create Session :: Version not supported");

    snmp_sess_init(&session);
    session.remote_port = _port;
    session.retries = _retries;
    session.timeout = _timeout;
    session.version = version;
    session.community = reinterpret_cast<u_char *>(const_cast<char *>(stdCommunity.c_str()));
    session.community_len = stdCommunity.length();
    session.peername = const_cast<char *>(stdAgent.c_str());
    SOCK_STARTUP;

    if(!(openedSession = snmp_open(&session))) {
        SOCK_CLEANUP;
        throw QSNMPException("QSNMPCore :: Create Session :: Open Session");
    }

    return openedSession;
}

QtNetSNMP::SNMPPDU *QtNetSNMP::QSNMPCore::createPDU(SNMPPDUType type, QVector<QSNMPObject *>& objs, unsigned short nrepeaters, unsigned short mrepetitions) throw(QSNMPException)
{
    SNMPPDU *pdu;

    if(type != SNMPPDUGet && type != SNMPPDUGetNext && type != SNMPPDUGetBulk && type != SNMPPDUSet)
        throw QSNMPException("QSNMPCore :: Create PDU :: Unknown PDU type");

    if(objs.empty())
        throw QSNMPException("QSNMPCore :: Create PDU :: SNMP objects vector is empty");

    pdu = snmp_pdu_create(type);

    foreach (QSNMPObject *object, objs) {
        if(type == SNMPPDUSet) {
            if(object -> data() -> type() == SNMPDataUnknown)
                throw QSNMPException("QSNMPCore :: Create PDU :: Unknown SNMP data type");

            char dataType;

            switch(object -> data() -> type()) {
            case SNMPDataInteger:
                dataType = 'i';
                break;
            case SNMPDataUnsigned:
                dataType = 'u';
                break;
            case SNMPDataBits:
                dataType = 'b';
                break;
            case SNMPDataCounter:
                dataType = 'c';
                break;
            case SNMPDataTimeTicks:
                dataType = 't';
                break;
            case SNMPDataCounter64:
                dataType = 'C';
                break;
            case SNMPDataBitString:
                dataType = 'b';
                break;
            case SNMPDataOctetString:
                dataType = 's';
                break;
            case SNMPDataIPAddress:
                dataType = 'a';
                break;
            case SNMPDataObjectId:
                dataType = 'o';
                break;
            default:
                dataType = '=';
            }

            snmp_add_var(pdu, object -> objID() -> numOID() -> data(), static_cast<size_t>(object -> objID() -> numOID() -> size()), dataType, static_cast<const char *>(object -> data() -> value()));

        } else
            snmp_add_null_var(pdu, object -> objID() -> numOID() -> data(), static_cast<size_t>(object -> objID() -> numOID() -> size()));
    }

    if(type == SNMPPDUGetBulk) {
        pdu -> errstat = nrepeaters;
        pdu -> errindex = mrepetitions;
    }

    return pdu;
}

QtNetSNMP::SNMPPDU *QtNetSNMP::QSNMPCore::sendPDU(SNMPSession *session, SNMPPDU *pdu) throw(QSNMPException)
{
    SNMPPDU *response;
    int status;

    status = snmp_synch_response(session, pdu, &response);

    if(status == STAT_SUCCESS)
        if(response -> errstat == SNMP_ERR_NOERROR)
            return response;
        else
            throw QSNMPException("QSNMPCore :: Send PDU :: Responde PDU has errors");
    else if(status == STAT_TIMEOUT)
        throw QSNMPException("QSNMPCore :: Send PDU :: Timeout. No response from agent");
    else
        throw QSNMPException("QSNMPCore :: Send PDU :: SNMP Session error");
}

void QtNetSNMP::QSNMPCore::processResponse(SNMPPDU *pdu, QVector<QSNMPObject *>& objs)
{
    if(pdu->command != SNMPPDUResponse)
        return;

    foreach(QSNMPObject *snmpObj, objs)
        delete snmpObj;

    objs.clear();

    for(SNMPVariableList *var = pdu -> variables; var; var = var -> next_variable) {
        QSNMPOID *snmpOID = new QSNMPOID(var -> name, var -> name_length);
        QSNMPData *snmpData = new QSNMPData;

        snmpData -> setValue(static_cast<SNMPDataType>(var -> type), static_cast<SNMPValue>(var -> val), var -> val_len);

        objs.append(new QSNMPObject(snmpOID, snmpData));
    }
}

void QtNetSNMP::QSNMPCore::parseMIBTree(SNMPMIBTree *tree, QMIBTree *mibTree)
{
    if(!tree || !mibTree)
        return;

    QSNMPOID *objID = new QSNMPOID(((mibTree -> parent() != 0 && mibTree -> parent() -> object()) ?
                                        QSNMPOID(*mibTree -> parent() -> object() -> objID()) + static_cast<int>(tree -> subid) :
                                        QString::number(tree -> subid)));
    SNMPDataType type;

    switch(tree -> type) {
    case TYPE_INTEGER:
    case TYPE_INTEGER32:
        type = SNMPDataInteger;
        break;
    case TYPE_UINTEGER:
    case TYPE_UNSIGNED32:
        type = SNMPDataUnsigned;
        break;
    case TYPE_BITSTRING:
        type = SNMPDataBitString;
        break;
    case TYPE_COUNTER:
        type = SNMPDataCounter;
        break;
    case TYPE_TIMETICKS:
        type = SNMPDataTimeTicks;
        break;
    case TYPE_COUNTER64:
        type = SNMPDataCounter64;
        break;
    case TYPE_OCTETSTR:
        type = SNMPDataOctetString;
        break;
    case TYPE_IPADDR:
        type = SNMPDataIPAddress;
        break;
    case TYPE_OBJID:
        type = SNMPDataObjectId;
        break;
    case TYPE_NULL:
        type = SNMPDataNull;
        break;
    default:
        type = SNMPDataUnknown;
    }

    QSNMPObject *snmpObj = new QSNMPObject(objID, new QSNMPData(type));

    snmpObj -> setName(tree -> label ? tree -> label : "");
    snmpObj -> setStatus(static_cast<MIBStatus>(tree -> status));
    snmpObj -> setAccess(static_cast<MIBAccess>(tree -> access));
    snmpObj -> setDescription(tree -> description ? tree -> description : "");

    mibTree -> setObject(snmpObj);

    for(SNMPMIBTree *child = tree -> child_list; child; child = child -> next_peer) {
        QMIBTree *mibChild = new QMIBTree;
        mibTree -> addChild(mibChild);
        parseMIBTree(child, mibChild);
    }
}
