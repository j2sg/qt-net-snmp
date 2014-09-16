#ifndef OSTREAM_H
#define OSTREAM_H

#include "qsnmpdata.h"
#include "qsnmpobject.h"
#include "qsnmpoid.h"

namespace QtNetSNMP
{
    std::ostream& operator<<(std::ostream& os, const QSNMPData& snmpData);
    std::ostream& operator<<(std::ostream& os, const QSNMPObject& obj);
    std::ostream& operator<<(std::ostream& os, const QSNMPOID& snmpOID);
}

#endif // OSTREAM_H
