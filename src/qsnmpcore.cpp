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
    SNMPSession *session; // Sesion SNMP Gestor-Agente
    SNMPPDU *requestPDU;  // PDU SNMP de peticion
    SNMPPDU *responsePDU; // PDU SNMP de respuesta

    session = createSession(version, community, agent);           // Inicializacion de sesion
    requestPDU = createPDU(type, oids, nrepeaters, mrepetitions); // Creacion de PDU de peticion
    responsePDU = sendPDU(session, requestPDU);                   // Envio de PDU de peticion
    if(type != SNMPPDUSet)                                        // Procesamos la respuesta a una consulta
        processResponse(responsePDU, oids, type);                 // Procesamiento de PDU de respuesta

    snmp_free_pdu(responsePDU);                                   // Liberacion de recursos en PDU de respuesta
    snmp_close(session);                                          // Cerramos la sesion
    SOCK_CLEANUP;                                                 // Liberacion de recursos para SOs win32 (Sin efecto en SOs Unix).
}

QtNetSNMP::QSNMPCore::QSNMPCore(unsigned short port, unsigned short retries, long timeout) : _port(port), _retries(retries), _timeout(timeout) {}

QtNetSNMP::SNMPSession *QtNetSNMP::QSNMPCore::createSession(SNMPVersion version, const QString& community, const QString& agent) throw(QSNMPException)
{
    SNMPSession session;
    SNMPSession *openedSession;

    if(version != SNMPv1 && version != SNMPv2)
        throw SNMPException("Error de inicializacion en sesion SNMP. Version no soportada.");

    snmp_sess_init(&session);                           // Inicializacion de sesion
    session.remote_port = _remotePort;                  // Numero de puerto del agente remoto
    session.retries = _retries;                         // Numero de reintentos
    session.timeout = _timeout;                         // Numero de uSegundos para timeout
    session.version = version;                          // Version SNMP
    session.community = (u_char *) community.c_str();   // Comunidad SNMPv1-2
    session.community_len = community.length();         // Longitud del nombre de la comunidad
    session.peername = (char *) agent.c_str();          // Direccion del agente
    SOCK_STARTUP;                                       // Inicializacion para SOs win32 (Sin efecto en SOs Unix).

    if(!(openedSession = snmp_open(&session))) {        // Apertura de sesion
        SOCK_CLEANUP;                                   // Liberacion de recursos para SOs win32 (Sin efecto en SOs Unix).
        throw SNMPSessionException(session, "Error de apertura en sesion SNMP");
    }

    return openedSession;
}

QtNetSNMP::SNMPPDU *QtNetSNMP::QSNMPCore::createPDU(SNMPPDUType type, const QVector<QSNMPObject *>& objs, unsigned short nrepeaters, unsigned short mrepetitions) throw(QSNMPException)
{
    SNMPPDU *pdu; // PDU SNMP de peticion

    // Verificamos el tipo de la PDU
    if(type != SNMPPDUGet && type != SNMPPDUGetNext && type != SNMPPDUGetBulk && type != SNMPPDUSet)
        throw SNMPException("Error en la creacion de la PDU. Tipo no valido");

    // Verificamos que se ha introducido al menos un OID
    if(oids.empty())
        throw SNMPException("Error en la creacion de la PDU. No especificado ningun OID.");

    pdu = snmp_pdu_create(type);            // Creacion de PDU SNMP

    // Iteramos a traves de los OIDs
    for(std::vector<SNMPOID *>::const_iterator vi = oids.begin(); vi != oids.end(); vi++) {
        if(type == SNMPPDUSet) { // Aniadimos a la PDU el valor correspondiente al k-esimo OID
            if((*vi) -> data() -> type() == SNMPDataUnknown)
                throw SNMPOIDException((*vi) -> strOID(), "Error en la creacion de la PDU. Operacion SNMPSet sobre OID de tipo desconocido.");

            char dataType; // Tipo de dato

            switch((*vi) -> data() -> type()) {
            case SNMPDataInteger:     dataType = 'i'; break;
            case SNMPDataUnsigned:    dataType = 'u'; break;
            case SNMPDataBits:        dataType = 'b'; break;
            case SNMPDataCounter:     dataType = 'c'; break;
            case SNMPDataTimeTicks:   dataType = 't'; break;
            case SNMPDataCounter64:   dataType = 'C'; break;
            case SNMPDataBitString:   dataType = 'b'; break;
            case SNMPDataOctetString: dataType = 's'; break;
            case SNMPDataIPAddress:   dataType = 'a'; break;
            case SNMPDataObjectId:    dataType = 'o'; break;
            default:                  dataType = '=';
            }

            // Aniadimos a la PDU el (tipo, valor) correspondiente al k-esimo OID
            snmp_add_var(pdu, (*vi) -> parseOID(), (*vi) -> parseOIDLength(), dataType, (const char *) (*vi) -> data() -> value());

        } else // Aniadimos a la PDU el valor nulo correspondiente al k-esimo OID
            snmp_add_null_var(pdu, (*vi) -> parseOID(), (*vi) -> parseOIDLength());
    }

    // Si la PDU es de tipo GET BULK los parametros nrepeaters y mrepetitions
    // se almacenan en los campos errstat y errindex respectivamente.
    if(type == SNMPPDUGetBulk) {
        pdu -> errstat = nrepeaters;
        pdu -> errindex = mrepetitions;
    }

    return pdu;
}

QtNetSNMP::SNMPPDU *QtNetSNMP::QSNMPCore::sendPDU(SNMPSession *session, SNMPPDU *pdu) throw(QSNMPException)
{
    SNMPPDU *response;  // PDU SNMP de respuesta
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
        throw SNMPSessionException(*session, "Error en sesion SNMP");
}

void QtNetSNMP::QSNMPCore::processResponse(SNMPPDU *pdu, std::vector<QSNMPObject *>& objs)
{
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
    }
}
