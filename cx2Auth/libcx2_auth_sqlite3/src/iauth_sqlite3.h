#ifndef IAUTH_SQLITE3_H
#define IAUTH_SQLITE3_H

#include <cx2_auth/iauth.h>
#include <sqlite3.h>
namespace CX2 { namespace Authorization {

class IAuth_SQLite3 : public IAuth
{
public:
    // Open authentication system:
    IAuth_SQLite3(const std::string & appName, const std::string & filePath = "");

    bool initScheme() override;

    /////////////////////////////////////////////////////////////////////////////////
    // account:
    bool accountAdd(const std::string & accountName,
                    const DataStructs::sPasswordData &passData,
                    
                    const std::string & email = "",
                    const std::string & accountDescription = "",
                    const std::string & extraData = "",
                    time_t expirationDate = std::numeric_limits<time_t>::max(),
                    bool enabled = true,
                    bool confirmed = true,
                    bool superuser = false) override;
    std::string accountConfirmationToken(const std::string & accountName) override;
    bool accountRemove(const std::string & accountName) override;
    bool accountDisable(const std::string & accountName, bool disabled = true) override;
    bool accountConfirm(const std::string & accountName, const std::string & confirmationToken) override;
    bool accountChangePassword(const std::string & accountName, const DataStructs::sPasswordData & passwordData, uint32_t passIndex=0) override;
    bool accountChangeDescription(const std::string & accountName, const std::string & description) override;
    bool accountChangeEmail(const std::string & accountName, const std::string & email) override;
    bool accountChangeExtraData(const std::string & accountName, const std::string & extraData) override;
    bool accountChangeExpiration(const std::string & accountName, time_t expiration = std::numeric_limits<time_t>::max()) override;
    bool isAccountDisabled(const std::string & accountName) override;
    bool isAccountConfirmed(const std::string & accountName) override;
    bool isAccountSuperUser(const std::string & accountName) override;
    std::string accountDescription(const std::string & accountName) override;
    std::string accountEmail(const std::string & accountName) override;
    std::string accountExtraData(const std::string & accountName) override;
    time_t accountExpirationDate(const std::string & accountName) override;
    std::set<std::string> accountsList() override;
    std::set<std::string> accountGroups(const std::string & accountName, bool lock = true) override;
    std::set<std::string> accountDirectAttribs(const std::string & accountName, bool lock = true) override;

    /////////////////////////////////////////////////////////////////////////////////
    // attributes:
    bool attribAdd(const std::string & attribName, const std::string & attribDescription) override;
    bool attribRemove(const std::string & attribName) override;
    bool attribGroupAdd(const std::string & attribName, const std::string & groupName) override;
    bool attribGroupRemove(const std::string & attribName, const std::string & groupName, bool lock = true) override;
    bool attribAccountAdd(const std::string & attribName, const std::string & accountName) override;
    bool attribAccountRemove(const std::string & attribName, const std::string & accountName, bool lock = true) override;
    bool attribChangeDescription(const std::string & attribName, const std::string & attribDescription) override;
    std::string attribDescription(const std::string & attribName) override;
    std::set<std::string> attribsList() override;
    std::set<std::string> attribGroups(const std::string & attribName, bool lock = true) override;
    std::set<std::string> attribAccounts(const std::string & attribName, bool lock = true) override;

    /////////////////////////////////////////////////////////////////////////////////
    // group:
    bool groupAdd(const std::string & groupName, const std::string & groupDescription) override;
    bool groupRemove(const std::string & groupName) override;
    bool groupExist(const std::string & groupName) override;
    bool groupAccountAdd(const std::string & groupName, const std::string & accountName) override;
    bool groupAccountRemove(const std::string & groupName, const std::string & accountName, bool lock = true) override;
    bool groupChangeDescription(const std::string & groupName, const std::string & groupDescription) override;
    bool groupValidateAttribute(const std::string & groupName, const std::string & attribName, bool lock =true) override;
    std::string groupDescription(const std::string & groupName) override;
    std::set<std::string> groupsList() override;
    std::set<std::string> groupAttribs(const std::string & groupName, bool lock = true) override;
    std::set<std::string> groupAccounts(const std::string & groupName, bool lock = true) override;

protected:
    bool accountValidateDirectAttribute(const std::string & accountName, const std::string & attribName) override;
    DataStructs::sPasswordData retrievePassword(const std::string &accountName, uint32_t passIndex, bool *found) override;

private:
    bool _pSQLTableExist(const std::string &table);
    bool _pSQLExecQuery(const std::string &query);
    bool _pSQLExecQueryF(const std::string &query, int _va_size, ...);

    std::string filePath;
    sqlite3 *ppDb;
};


}}
#endif // IAUTH_SQLITE3_H
