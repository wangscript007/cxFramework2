#ifndef PASSWORD_MODES_H
#define PASSWORD_MODES_H

#include <stdint.h>
namespace CX2 { namespace Authorization { namespace DataStructs {

enum PasswordModes
{
    PASS_MODE_NOTFOUND=500,
    PASS_MODE_PLAIN=0,
    PASS_MODE_SHA256=1,
    PASS_MODE_SHA512=2,
    PASS_MODE_SSHA256=3,
    PASS_MODE_SSHA512=4,
    PASS_MODE_GAUTHTIME=5
};

}}}

#endif // PASSWORD_MODES_H
