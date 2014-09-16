#include "ostream.h"

std::ostream& QtNetSNMP::operator<<(std::ostream& os, const QSNMPData& snmpData)
{
    QChar type;
    QString value;
    QString length(static_cast<int>(snmpData.length()));

    switch(snmpData.type()) {
    case SNMPDataInteger:
        type = 'i';
        break;
    case SNMPDataUnsigned:
        type = 'u';
        break;
    case SNMPDataBits:
        type = 'b';
        break;
    case SNMPDataCounter:
        type = 'c';
        break;
    case SNMPDataTimeTicks:
        type = 't';
        break;
    case SNMPDataCounter64:
        type = 'C';
        break;
    case SNMPDataBitString:
        type = 'b';
        break;
    case SNMPDataOctetString:
        type = 's';
        break;
    case SNMPDataIPAddress:
        type = 'a';
        break;
    case SNMPDataObjectId:
        type = 'o';
        break;
    default:
        type = '=';
    }

    void *valuePtr = snmpData.value();

    if(!valuePtr)
        value = QString("Null");
    else {
        switch(snmpData.type()) {
        case SNMPDataInteger:
        case SNMPDataUnsigned:
        case SNMPDataBits:
        case SNMPDataCounter:
        case SNMPDataTimeTicks:
            value = QString::number(*static_cast<long *>(snmpData.value()));
            break;
        case SNMPDataCounter64:
            value = QString("%1 %2").arg(static_cast<SNMPCounter64 *>(snmpData.value()) -> high)
                                    .arg(static_cast<SNMPCounter64 *>(snmpData.value()) -> low);
            break;
        case SNMPDataBitString:
        case SNMPDataOctetString:
        case SNMPDataIPAddress:
            value = QString(*static_cast<unsigned char *>(snmpData.value()));
            break;
        case SNMPDataObjectId:
            value = QSNMPOID(static_cast<oid *>(snmpData.value()), snmpData.length()).textOID();
            break;
        default:
            value = QString("=");
        }
    }

    return os << QString("t:%1 v:%2 l:%3").arg(type).arg(value).arg(length);
}

std::ostream& QtNetSNMP::operator<<(std::ostream& os, const QSNMPObject& obj)
{
    //QSNMPOID *snmpOID = const_cast<QSNMPOID *>(obj.objID());
    //QSNMPData *snmpData = const_cast<QSNMPData *>(obj.data());

    //return os << *snmpOID << " " << *snmpData;
    return os;

    //return os << ((snmpOID != 0) ? *snmpOID : "") << " := " << ((snmpData != 0) ? *snmpData : "");
}

std::ostream& QtNetSNMP::operator<<(std::ostream& os, const QSNMPOID& snmpOID)
{
    return os << snmpOID.textOID();
}
