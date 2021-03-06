#ifndef HTTP_SUB_URLVARPARSER_H
#define HTTP_SUB_URLVARPARSER_H

#include <cx2_mem_vars/substreamparser.h>

namespace CX2 { namespace Network { namespace HTTP {

class HTTP_URLVarContent_SubParser : public Memory::Streams::Parsing::SubParser
{
public:
    HTTP_URLVarContent_SubParser();
    ~HTTP_URLVarContent_SubParser() override;

    bool stream(Memory::Streams::Status &) override;

    void setVarType(bool varName = true);
    void setMaxObjectSize(const uint32_t &size);
    Memory::Containers::B_Chunks *flushRetrievedContentAsBC();
    std::string flushRetrievedContentAsString();
    Memory::Containers::B_Chunks *getPData();

protected:
    Memory::Streams::Parsing::ParseStatus parse() override;
    Memory::Containers::B_Chunks * pData;

};

}}}

#endif // HTTP_SUB_URLVARPARSER_H
