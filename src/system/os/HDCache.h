#pragma once
#include "os/CritSec.h"
#include "os/ArkFile.h"
#include "utl/Str.h"
#include "utl/FileStream.h"
#include "utl/MemStream.h"
#include <vector>
#include <revolution/OS.h>

class HDCache {
public:
    HDCache();
    ~HDCache();
    void Init();
    bool LockCache();
    void UnlockCache();
    void Poll();
    int HdrSize();
    bool WriteAsync(int, int, const void *);
    void WriteDone();
    void WriteHdr();
    bool ReadAsync(int, int, void *);
    bool ReadFail();
    bool ReadDone();
    FileStream *OpenHeader();

    int **mBlockState; // 0x0
    std::vector<ArkFile *> mReadArkFiles; // 0x4
    std::vector<ArkFile *> mWriteArkFiles; // 0xc
    int mWriteFileIdx; // 0x14
    int unk18; // 0x18
    int unk1c;
    int unk20; // 0x20
    int unk24;
    int unk28;
    int unk2c;
    OSThread *mLockId; // 0x30
    int unk34;
    CriticalSection *mCritSec; // 0x38
    int mHdrIdx; // 0x3c
    File *mHdr[2]; // 0x40
    MemStream *mHdrBuf; // 0x48
    String mHdrFmt; // 0x4c
    String mFileFmt; // 0x58
    bool unk64; // 0x64
};

extern HDCache TheHDCache;
