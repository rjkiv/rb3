#ifndef METABAND_ACCOMPLISHMENT_H
#define METABAND_ACCOMPLISHMENT_H

#include "system/obj/Data.h"
#include <set>
#include "BandProfile.h"
#include "band3/game/BandUser.h"
#include "band3/game/Tracker.h"
#include "band3/meta_band/MusicLibrary.h"

class Accomplishment {
public:
    Accomplishment(DataArray*, int);
    virtual ~Accomplishment();

protected:
    virtual Difficulty GetRequiredDifficulty() const;

private:
    void Configure(DataArray*);
    virtual int GetType() const;
    Symbol GetName() const;
    Symbol GetDescription() const;
    Symbol GetSecretDescription() const;
    Symbol GetFlavorText() const;
    bool GetShouldShowDenominator() const;
    bool ShowBestAfterEarn() const;
    bool HideProgress() const;
    Symbol GetSecretCampaignLevelPrereq() const;
    const std::vector<Symbol>& GetSecretPrereqs() const;
    bool IsDynamic() const;
    bool GetDynamicAlwaysVisible() const;
    const std::vector<Symbol>& GetDynamicPrereqsSongs() const;
    int GetDynamicPrereqsNumSongs() const;
    Symbol GetDynamicPrereqsFilter() const;
    Symbol GetCategory() const;
    Symbol GetContextID() const;
    void GetIconArt() const;
    bool IsFulfilled(BandProfile*) const;
    bool IsRelevantForSong(Symbol) const;
    bool InqProgressValues(BandProfile*, int&, int&);
    Symbol GetFirstUnfinishedAccomplishmentEntry(BandProfile*) const;
    bool InqIncrementalSymbols(BandProfile*, std::vector<Symbol, unsigned short>&) const;
    bool IsSymbolEntryFulfilled(BandProfile*, Symbol) const;
    virtual bool CanBeLaunched() const;
    virtual bool HasSpecificSongsToLaunch() const;
    Symbol GetAward() const;
    bool HasAward() const;
    int GetMetaScoreValue() const;
    char* GetIconPath();
    bool IsUserOnValidScoreType(LocalBandUser*) const;
    bool IsUserOnValidController(LocalBandUser*) const;
    ScoreType GetRequiredScoreType() const;
    virtual bool InqRequiredScoreTypes(std::set<ScoreType>&) const;
    int GetRequiredMinPlayers() const;
    int GetRequiredMaxPlayers() const;
    bool GetRequiresUnisonAbility() const;
    bool GetRequiresBREAbility() const;
    void InitializeMusicLibraryTask(MusicLibrary::MusicLibraryTask&, BandProfile*) const;
    virtual void InitializeTrackerDesc(TrackerDesc&) const;
    bool CanBeEarnedWithNoFail() const;
    bool IsTrackedInLeaderboard() const;
    Symbol GetUnitsToken(int) const;
    Symbol GetPassiveMsgChannel() const;
    int GetPassiveMsgPriority() const;

    Symbol mName;       // 0x04
    std::vector<Symbol> mSecretPrereqs; // 0x08
    int mAccomplishmentType;    //0x10
    Symbol mCategory; // 0x14
    Symbol mAward; // 0x18
    Symbol mUnitsToken; // 0x1c
    Symbol mUnitsTokenSingular; // 0x20
    Symbol mIconOverride; // 0x24
    Symbol mSecretCampaignLevelPrereq; // 0x28
    std::vector<ControllerType> mControllerTypes; // 0x2c
    ScoreType mScoreType; //0x34
    Difficulty mLaunchableDifficulty; // 0x38
    Symbol mPassiveMsgChannel;  // 0x3c
    int mPassiveMsgPriority; // 0x40
    int mPlayerCountMin; // 0x44
    int mPlayerCountMax; // 0x48
    int mDynamicPrereqsNumSongs; // 0x4c
    std::vector<Symbol> mDynamicPrereqsSongs; // 0x50
    Symbol mDynamicPrereqsFilter; // 0x58
    int mProgressStep; // 0x5c

    int mIndex; // 0x60
    
    Symbol mContextId;  // 0x64

    int mMetaScoreValue; // 0x68
    bool mRequiresUnison; // 0x6c
    bool mRequiresBre; // 0x6d
    bool mDynamicAlwaysVisible; // 0x6e
    bool mShouldShowDenominator; // ox6f
    bool mShowBestAfterEarn; // 0x70
    bool mHideProgress; // 0x71
    bool mCanBeEarnedWithNoFail; // 0x72
    bool mIsTrackedInLeaderboard; // 0x73
};
#endif // METABAND_ACCOMPLISHMENT_H