#ifndef UI_UILISTDIR_H
#define UI_UILISTDIR_H
#include "rndobj/Dir.h"
#include "ui/UIListProvider.h"
#include "ui/UIListState.h"
#include "ui/UIListWidget.h"

enum UIListOrientation {
    kUIListVertical,
    kUIListHorizontal
};

class UIListDir : public RndDir, public UIListProvider, public UIListStateCallback {
public:
    UIListDir();
    OBJ_CLASSNAME(UIListDir)
    OBJ_SET_TYPE(UIListDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual ~UIListDir();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void DrawShowing();
    virtual void Poll();
    virtual void StartScroll(const UIListState&, int, bool);
    virtual void CompleteScroll(const UIListState&);
    virtual int NumData() const;
    virtual float GapSize(int, int, int, int) const;
    virtual bool IsActive(int) const;

    UIListOrientation Orientation() const;
    float ElementSpacing() const;
    UIList* SubList(int, std::vector<UIListWidget*>&);
    void CompleteScroll(const UIListState&, std::vector<UIListWidget*>&);
    void CreateElements(UIList*, std::vector<UIListWidget*>&, int);
    void FillElements(const UIListState&, std::vector<UIListWidget*>&);
    void FillElement(const UIListState&, std::vector<UIListWidget*>&, int);
    void PollWidgets(std::vector<UIListWidget*>&);
    void ListEntered();
    void StartScroll(const UIListState&, std::vector<UIListWidget*>&, int, bool);
    void Reset();
    void DrawWidgets(const UIListState&, std::vector<UIListWidget*>&, const Transform&, UIComponent::State, Box*, bool);
    void BuildDrawState(UIListWidgetDrawState&, const UIListState&, UIComponent::State, float) const;
    void SetElementPos(Vector3&, float, int, float, float) const;

    DECLARE_REVS;
    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(UIListDir)
    static void Init(){
        REGISTER_OBJ_FACTORY(UIListDir)
    }

    UIListOrientation mOrientation; // 0x194
    int mFadeOffset; // 0x198
    float mElementSpacing; // 0x19c
    float mScrollHighlightChange; // 0x1a0
    bool mTestMode; // 0x1a4
    UIListState mTestState; // 0x1a8
    int mTestNumData; // 0x1ec
    float mTestGapSize; // 0x1f0
    UIComponent::State mTestComponentState; // 0x1f4
    bool mTestDisableElements; // 0x1f8
    std::vector<UIListWidget*> unk1fc; // 0x1fc
    int mDirection; // 0x204
};

#endif
