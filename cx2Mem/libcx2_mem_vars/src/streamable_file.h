#ifndef STREAMABLEFD_H
#define STREAMABLEFD_H

#include "streamable.h"
#include <unistd.h>

namespace CX2 { namespace Memory { namespace Streams {

class Streamable_File : public Memory::Streams::Streamable
{
public:
    Streamable_File(int _rd_fd = STDIN_FILENO, int _wr_fd = STDOUT_FILENO);
    /**
     * Retrieve Stream to another Streamable.
     * @param objDst pointer to the destination object.
     * @return false if failed, true otherwise.
     */
    virtual bool streamTo(Memory::Streams::Streamable * out, Status & wrStatUpd) override;
    virtual Status write(const void * buf, const size_t &count, Status & wrStatUpd) override;

private:
    int rd_fd,wr_fd;

};

}}}

#endif // STREAMABLEFD_H
