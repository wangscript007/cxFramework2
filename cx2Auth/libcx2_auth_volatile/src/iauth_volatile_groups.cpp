#include "iauth_volatile.h"
#include <cx2_thr_mutex/lock_shared.h>

using namespace CX2::Authorization;

bool IAuth_Volatile::groupAdd(const std::string &groupName, const std::string &groupDescription)
{
    Threads::Sync::Lock_RW lock(mutex);
    if (groups.find(groupName) != groups.end()) return false;
    groups[groupName].name = groupName;
    groups[groupName].description = groupDescription;
    return true;
}

bool IAuth_Volatile::groupRemove(const std::string &groupName)
{
    Threads::Sync::Lock_RW lock(mutex);

    for ( auto & acct : groupAccounts(groupName,false) )
    {
        accounts[acct].accountGroups.erase(groupName);
    }

    if (groups.find(groupName) == groups.end()) return false;
    groups.erase(groupName);

    return true;
}

bool IAuth_Volatile::groupExist(const std::string &groupName)
{
    Threads::Sync::Lock_RD lock(mutex);

    return groups.find(groupName)!=groups.end();
}

bool IAuth_Volatile::groupAccountAdd(const std::string &groupName, const std::string &accountName)
{
    bool ret = false;
    Threads::Sync::Lock_RW lock(mutex);

    if (    accounts.find(accountName) != accounts.end() &&
            groups.find(groupName) != groups.end() &&
            accounts[accountName].accountGroups.find(groupName) == accounts[accountName].accountGroups.end()
            )
    {
        accounts[accountName].accountGroups.insert(groupName);
        ret = true;
    }

    return ret;
}

bool IAuth_Volatile::groupAccountRemove(const std::string &groupName, const std::string &accountName, bool lock)
{
    bool ret = false;
    if (lock) mutex.lock();

    if (    accounts.find(accountName) != accounts.end() &&
            groups.find(groupName) != groups.end() &&
            accounts[accountName].accountGroups.find(groupName) != accounts[accountName].accountGroups.end()
            )
    {
        accounts[accountName].accountGroups.erase(groupName);
        ret = true;
    }
    if (lock) mutex.unlock();
    return ret;
}

bool IAuth_Volatile::groupChangeDescription(const std::string &groupName, const std::string &groupDescription)
{
    Threads::Sync::Lock_RW lock(mutex);
    if (groups.find(groupName) == groups.end()) return false;
    groups[groupName].description = groupDescription;
    return true;
}

bool IAuth_Volatile::groupValidateAttribute(const std::string &groupName, const std::string &attribName, bool lock)
{
    bool ret = false;
    if (lock) mutex.lock_shared();

    if (groups.find(groupName) != groups.end() && groups[groupName].groupAttribs.find(attribName) != groups[groupName].groupAttribs.end())
    {
        ret = true;
    }

    if (lock) mutex.unlock_shared();
    return ret;
}

std::string IAuth_Volatile::groupDescription(const std::string &groupName)
{
    Threads::Sync::Lock_RD lock(mutex);
    if (groups.find(groupName) == groups.end()) return "";
    return groups[groupName].description;
}

std::set<std::string> IAuth_Volatile::groupsList()
{
    std::set<std::string> ret;
    Threads::Sync::Lock_RD lock(mutex);
    for (const auto &i : groups) ret.insert(i.first);
    return ret;
}

std::set<std::string> IAuth_Volatile::groupAttribs(const std::string &groupName, bool lock)
{
    std::set<std::string> ret;
    if (lock) mutex.lock_shared();

    if (groups.find(groupName) != groups.end() )
    {
        ret = groups[groupName].groupAttribs;
    }

    if (lock) mutex.unlock_shared();
    return ret;
}

std::set<std::string> IAuth_Volatile::groupAccounts(const std::string &groupName, bool lock)
{
    std::set<std::string> ret;
    if (lock) mutex.lock_shared();

    for (auto & acct :  accounts)
    {
        if (acct.second.accountGroups.find(groupName) != acct.second.accountGroups.end())
        {
            ret.insert(acct.first);
        }
    }

    if (lock) mutex.unlock_shared();
    return ret;
}

