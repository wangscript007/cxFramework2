#ifndef ABSVAR_IPV6_H
#define ABSVAR_IPV6_H

#include "abstract.h"
#include <netinet/in.h>
#include <cx2_thr_mutex/mutex_shared.h>

namespace CX2 { namespace Memory { namespace Vars {

class A_IPV6: public Abstract
{
public:
    A_IPV6();
    ~A_IPV6() override;
    A_IPV6& operator=(const in6_addr & value)
    {
        setValue(value);
        return *this;
    }

    in6_addr getValue();
    bool setValue(const in6_addr & value);

    std::string toString() override;
    bool fromString(const std::string & value) override;
protected:
    Abstract * protectedCopy() override;

private:
    in6_addr value;
    Threads::Sync::Mutex_Shared mutex;
};

}}}

#endif // ABSVAR_IPV6_H
