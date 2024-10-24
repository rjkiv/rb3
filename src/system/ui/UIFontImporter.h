#ifndef UI_UIFONTIMPORTER_H
#define UI_UIFONTIMPORTER_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Font.h"
#include "rndobj/Mat.h"

class RndText;

class UIFontImporter : public virtual Hmx::Object {
public:

    enum FontQuality {
        kFontQuality_AntiAliased,
        kFontQuality_ClearType,
        kFontQuality_Default
    };

    enum FontSuperSample {
        kFontSuperSample_None,
        kFontSuperSample_2x,
        kFontSuperSample_4x
    };

    UIFontImporter();
    OBJ_CLASSNAME(UIFontImporter);
    OBJ_SET_TYPE(UIFontImporter);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~UIFontImporter();

    void GenerateBitmapFilename();
    RndText* GetGennedText(Symbol) const;
    void FontImporterSyncObjects();
    void SyncWithGennedFonts();
    void HandmadeFontChanged();
    Symbol GetMatVariationName(unsigned int) const;
    const char* GetResourcesPath();
    String GetBaseName() const;
    RndFont* GetGennedFont(unsigned int) const;
    RndText* FindTextForFont(RndFont*) const;
    RndFont* FindFontForMat(RndMat*) const;
    void AttachImporterToFont(RndFont*);
    void ImportSettingsFromFont(RndFont*);
    RndFont* GetGennedFont(Symbol) const;
    int GetMatVariationIdx(Symbol) const;
    RndMat* GetMatVariation(unsigned int) const;
    int NumMatVariations() const { return mMatVariations.size(); }
    int NumGennedFonts() const { return mGennedFonts.size(); }
    bool HandMadeFontExists() const { return mHandmadeFont; }

    DataNode OnShowFontPicker(DataArray*);
    DataNode OnGenerate(DataArray*);
    DataNode OnGenerateOG(DataArray*);
    DataNode OnForgetGened(DataArray*);
    DataNode OnAttachToImportFont(DataArray*);
    DataNode OnImportSettings(DataArray*);
    DataNode OnSyncWithResourceFile(DataArray*);
    DataNode OnGetResourcesPath(DataArray*);
    DataNode OnGetGennedBitmapPath(DataArray*);

    DELETE_OVERLOAD;
    
    bool mUpperCaseAthroughZ; // 0x8
    bool mLowerCaseAthroughZ; // 0x9
    bool mNumbers0through9; // 0xa
    bool mPunctuation; // 0xb
    bool mUpperEuro; // 0xc
    bool mLowerEuro; // 0xd
    String mPlus; // 0x10
    String mMinus; // 0x1c
    String mFontName; // 0x28
    float mFontPctSize; // 0x34
    bool mItalics; // 0x38
    FontQuality mFontQuality; // 0x3c
    int mFontWeight; // 0x40
    int mPitchAndFamily; // 0x44
    int mFontCharset; // 0x48
    FontSuperSample mFontSupersample; // 0x4c
    int mLeft; // 0x50
    int mRight; // 0x54
    int mTop; // 0x58
    int mBottom; // 0x5c
    bool mFillWithSafeWhite; // 0x60
    ObjPtr<RndFont, ObjectDir> mFontToImportFrom; // 0x64
    String mBitmapSavePath; // 0x70
    String mBitMapSaveName; // 0x7c
    ObjPtrList<RndFont, ObjectDir> mGennedFonts; // 0x88
    ObjPtr<RndFont, ObjectDir> mReferenceKerning; // 0x98
    ObjPtrList<RndMat, ObjectDir> mMatVariations; // 0xa4
    ObjPtr<RndMat, ObjectDir> mDefaultMat; // 0xb4
    ObjPtr<RndFont, ObjectDir> mHandmadeFont; // 0xc0
    bool mCheckNG; // 0xcc
    String mSyncResource; // 0xd0
    bool mLastGenWasNG; // 0xdc
};

#endif
