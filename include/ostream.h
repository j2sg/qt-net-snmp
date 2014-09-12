#ifndef OSTREAM_H
#define OSTREAM_H

#include "qsnmpoid.h"

namespace QtNetSNMP
{
    std::ostream& operator<<(std::ostream& os, const QSNMPOID& snmpOID);
}

#endif // OSTREAM_H
