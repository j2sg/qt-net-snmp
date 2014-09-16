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
    SOCK_CLEANUP;                 // Free resources on Win32. (No effect on Unix systems)
}

QtNetSNMP::QSNMPCore::QSNMPCore(unsigned short port, unsigned short retries, long timeout) : _port(port), _retries(retries), _timeout(timeout)
{
    init_snmp(LIBRARY_NAME);
}

QtNetSNMP::SNMPSession *QtNetSNMP::QSNMPCore::createSession(SNMPVersion version, const QString& community, const QString& agent) throw(QSNMPException)
{
    SNMPSession session;
    SNMPSession *openedSession;

    if(version != SNMPv1 && version != SNMPv2)
        throw QSNMPException("SNMP Session :: Error during initializacion :: Version not supported");

    snmp_sess_init(&session);
    session.remote_port = _port;
    session.retries = _retries;
    session.timeout = _timeout;
    session.version = version;
    session.community = (u_char *) community.toStdString().c_str();
    session.community_len = community.length();
    session.peername = (char *) agent.toStdString().c_str();
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
        throw QSNMPException("SNMP PDU :: PDU creation :: Unknown type");

    if(objs.empty())
        throw QSNMPException("QSNMPCore :: Create PDU :: SNMP objects vector is empty");

    pdu = snmp_pdu_create(type);

    foreach (QSNMPObject *object, objs) {
        if(type == SNMPPDUSet) {
            if(object -> data() -> type() == SNMPDataUnknown)
                throw QSNMPException("QSNMPCore :: Create PDU :: Unknown SNMP object data type");

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

            // Aniadimos a la PDU el (tipo, valor) correspondiente al k-esimo OID
            snmp_add_var(pdu, object -> objID() -> numOID() -> data(), object -> objID() -> numOID() -> size(), dataType, static_cast<const char *>(object -> data() -> value()));

        } else // Aniadimos a la PDU el valor nulo correspondiente al k-esimo OID
            snmp_add_null_var(pdu, object -> objID() -> numOID() -> data(), object -> objID() -> numOID() -> size());
    }

    if(type == SNMPPDUGetBulk) {
        pdu -> errstat = nrepeaters;
        pdu -> errindex = mrepetitions;
    }

    return pdu;
}

QtNetSNMP::SNMPPDU *QtNetSNMP::QSNMPCore::sendPDU(SNMPSession *session, SNMPPDU *pdu) throw(QSNMPException)
{
    /*SNMPPDU *response;  // PDU SNMP de respuesta
    int status;         // Estado de la recepcion del mensaje

    // Enviamos la PDU SNMP de peticion
    status = snmp_synch_response(session, pdu, &response);

    // Evaluamos la recepcion del mensaje de respuesta
    if(status == STAT_SUCCESS) // Recibido con exito
        if(response -> errstat == SNMP_ERR_NOERROR) // Mensaje de respuesta sin errores
            return response;
        else // Mensaje de respuesta con errores
            throw SNMPPacketException(snmp_errstring(response -> errstat), "Error en la PDU de respuesta");
    else if(status == STAT_TIMEOUT) // No hay respuesta del agente
        throw SNMPException("Timeout, no hay respuesta del agente");
    else // Error de sesion (comunidad no valida, acceso no permitido, etc)
        throw SNMPSessionException(*session, "Error en sesion SNMP");*/
    return 0;
}

void QtNetSNMP::QSNMPCore::processResponse(SNMPPDU *pdu, QVector<QSNMPObject *>& objs)
{
    /*if(pdu->command != SNMPPDUResponse)
        return;

    // Liberamos memoria y borramos la lista de OIDs
    for(std::vector<SNMPOID *>::iterator vi = oids.begin();vi != oids.end(); ++vi)
        delete *vi;

    oids.clear();

    // Iteramos por la lista de variables de la PDU de
    // respuesta estableciendo el (tipo, valor) de cada OID
    for(SNMPVariableList *vl = pdu -> variables; vl; vl = vl -> next_variable) {
        SNMPOID *object = new SNMPOID(vl -> name, vl -> name_length);

        object -> data() -> setType((SNMPDataType) vl -> type);
        object -> data() -> setLength(vl -> val_len);
        object -> data() -> setValue((SNMPValue) vl -> val);

        oids.push_back(object);
    }*/
}
