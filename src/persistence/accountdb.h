// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2013 The WaykiChain developers
// Copyright (c) 2016 The Coin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PERSIST_ACCOUNTDB_H
#define PERSIST_ACCOUNTDB_H

#include <map>
#include <string>
#include <utility>
#include <vector>
#include "commons/arith_uint256.h"
#include "database.h"
#include "leveldbwrapper.h"
#include "main.h"

class uint256;
class CKeyID;
// class CTransactionDBCache;
// -dbcache default (MiB)
static const int64_t nDefaultDbCache = 100;
// max. -dbcache in (MiB)
static const int64_t nMaxDbCache = sizeof(void *) > 4 ? 4096 : 1024;
// min. -dbcache in (MiB)
static const int64_t nMinDbCache = 4;

class CAccountViewDB : public CAccountView {
private:
    CLevelDBWrapper db;

public:
    CAccountViewDB(size_t nCacheSize, bool fMemory = false, bool fWipe = false);
    CAccountViewDB(const string &name, size_t nCacheSize, bool fMemory, bool fWipe);

private:
    CAccountViewDB(const CAccountViewDB &);
    void operator=(const CAccountViewDB &);

public:
    bool GetAccount(const CKeyID &keyId, CAccount &account);
    bool GetAccount(const vector<unsigned char> &accountId, CAccount &account);
    bool GetAccount(const CUserID &userId, CAccount &account);

    virtual bool SetAccount(const CKeyID &keyId, const CAccount &account);
    // virtual bool SetAccount(const CUserID &userId, const CAccount &account) {};
    virtual bool SetAccount(const vector<unsigned char> &accountRegId, const CAccount &account);
    
    bool HaveAccount(const CKeyID &keyId);
    uint256 GetBestBlock();
    bool SetBestBlock(const uint256 &hashBlock);
    bool BatchWrite(const map<CKeyID, CAccount> &mapAccounts, const map<vector<unsigned char>, CKeyID> &mapKeyIds, const uint256 &hashBlock);
    bool BatchWrite(const vector<CAccount> &vAccounts);
    bool EraseAccountByKeyId(const CKeyID &keyId);
    bool SetKeyId(const vector<unsigned char> &accountId, const CKeyID &keyId);
    bool GetKeyId(const vector<unsigned char> &accountId, CKeyID &keyId);
    bool EraseKeyIdByRegId(const vector<unsigned char> &accountRegId);

    bool SaveAccountInfo(const CAccount &account);
    std::tuple<uint64_t, uint64_t> TraverseAccount();
    int64_t GetDbCount() { return db.GetDbCount(); }
    Object ToJsonObj(char Prefix);
};

class CTransactionDB : public CTransactionDBView {
private:
    CLevelDBWrapper db;

public:
    CTransactionDB(size_t nCacheSize, bool fMemory = false, bool fWipe = false) : 
        db(GetDataDir() / "blocks" / "txcache", nCacheSize, fMemory, fWipe) {};
    ~CTransactionDB() {};

private:
    CTransactionDB(const CTransactionDB &);
    void operator=(const CTransactionDB &);

public:
    virtual bool IsContainBlock(const CBlock &block);
    virtual bool BatchWrite(const map<uint256, UnorderedHashSet> &mapTxHashByBlockHash);
    int64_t GetDbCount() { return db.GetDbCount(); }
};


#endif  // PERSIST_ACCOUNTDB_H