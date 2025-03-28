#include "char/CharTransCopy.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

INIT_REVS(CharTransCopy);

CharTransCopy::CharTransCopy() : mSrc(this), mDest(this) {}

CharTransCopy::~CharTransCopy() {}

void CharTransCopy::Poll() {
    if (!mSrc || !mDest)
        return;
    mDest->SetLocalXfm(mSrc->mLocalXfm);
}

void CharTransCopy::PollDeps(
    std::list<Hmx::Object *> &changedBy, std::list<Hmx::Object *> &change
) {
    change.push_back(mDest);
    changedBy.push_back(mSrc);
}

SAVE_OBJ(CharTransCopy, 0x2D);

BEGIN_LOADS(CharTransCopy)
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mSrc;
    bs >> mDest;
END_LOADS

BEGIN_COPYS(CharTransCopy)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharTransCopy)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mSrc)
        COPY_MEMBER(mDest)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharTransCopy)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x4C)
END_HANDLERS

BEGIN_PROPSYNCS(CharTransCopy)
    SYNC_PROP(src, mSrc)
    SYNC_PROP(dest, mDest)
END_PROPSYNCS
