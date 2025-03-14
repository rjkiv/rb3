#pragma once
#include "utl/Song.h"

class BandSong : public Song {
public:
    BandSong() {}
    OBJ_CLASSNAME(Song);
    OBJ_SET_TYPE(Song);
    virtual ~BandSong() {}
    virtual void CreateSong(Symbol, DataArray *, HxSongData **, HxMaster **);

    NEW_OBJ(BandSong)
    static void Init() { Register(); }
    REGISTER_OBJ_FACTORY_FUNC(BandSong)
};