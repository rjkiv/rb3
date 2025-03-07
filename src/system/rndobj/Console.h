#pragma once
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/Keyboard.h"
#include "utl/Str.h"
#include <list>

class RndOverlay;

class RndConsole : public Hmx::Object { // 0x58 - 0x1c = 0x3c
public:
    struct Breakpoint { // total size: 0x8
        Breakpoint() : parent(0) {}
        ~Breakpoint();
        DataArray *parent; // offset 0x0, size 0x4
        int index; // offset 0x4, size 0x4
    };

    RndConsole();
    virtual ~RndConsole();
    virtual DataNode Handle(DataArray *, bool);

    void MoveLevel(int);
    void InsertBreak(DataArray *, int);
    void SetBreak(DataArray *);
    void Clear(int);
    void Breakpoints();
    void Break(DataArray *);
    void List();
    void Where();
    void Step(int);
    void Continue();
    void Help(Symbol);
    bool Showing() { return mShowing; }
    void SetShowing(bool);
    void ExecuteLine();
    int OnMsg(const KeyboardKeyMsg &);

    NEW_POOL_OVERLOAD(RndConsole);
    DELETE_POOL_OVERLOAD(RndConsole);

    bool mShowing; // 0x1c
    RndOverlay *mOutput; // 0x20
    RndOverlay *mInput; // 0x24
    std::list<String> mBuffer; // 0x28
    std::list<String>::iterator mBufPtr; // 0x30
    int mMaxBuffer; // 0x34
    int mTabLen; // 0x38
    int mCursor; // 0x3c
    Object *mKeyboardOverride; // 0x40
    bool mPumpMsgs; // 0x44
    DataArray *mDebugging; // 0x48
    int mLevel; // 0x4c
    std::list<Breakpoint> mBreakpoints; // 0x50
};
