#include "rndobj/MultiMeshProxy.h"
#include "utl/Symbols.h"

RndMultiMeshProxy::RndMultiMeshProxy() : mMultiMesh(this), mIndex(0) {}

void RndMultiMeshProxy::SetMultiMesh(
    RndMultiMesh *mesh, const std::list<RndMultiMesh::Instance>::iterator &it
) {
    mMultiMesh = 0;
    if (mesh)
        SetLocalXfm(it->mXfm);
    mMultiMesh = mesh;
    mIndex = it;
}

void RndMultiMeshProxy::DrawShowing() {
    if (mMultiMesh) {
        RndMesh *theMesh = mMultiMesh->mMesh;
        if (theMesh) {
            theMesh->SetWorldXfm(mIndex->mXfm);
            mMultiMesh->mMesh->Draw();
        }
    }
}

void RndMultiMeshProxy::UpdatedWorldXfm() {
#ifdef MILO_DEBUG
    if (mMultiMesh) {
        Transform &tfm = WorldXfm();
        mIndex->mXfm = tfm;
    }
#else
    if (mMultiMesh) {
        Transform &tfm = mIndex->mXfm;
        tfm = WorldXfm();
    }
#endif
}

BEGIN_LOADS(RndMultiMeshProxy)
    MILO_FAIL("Attempting to load a MultiMesh proxy");
END_LOADS

void RndMultiMeshProxy::Save(BinStream &bs) {
    MILO_FAIL("Attempting to save a MultiMesh proxy");
}

BEGIN_COPYS(RndMultiMeshProxy)
    MILO_FAIL("Attempting to copy a MultiMesh proxy");
END_COPYS

BEGIN_HANDLERS(RndMultiMeshProxy)
    HANDLE_CHECK(0x3F)
END_HANDLERS

BEGIN_PROPSYNCS(RndMultiMeshProxy)
END_PROPSYNCS