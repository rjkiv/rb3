#include "unk_800AAE1C.hpp"
#include "unknown.hpp"

// ------------------------------------
// fn_800AAE1C
// ------------------------------------
extern "C" void fn_800AAE1C(SyncObjMsg*);

void fn_800AAE1C(SyncObjMsg* obj){
    obj = new SyncObjMsg();
}

// ------------------------------------
// fn_800AAE4C
// ------------------------------------
SyncObjMsg::SyncObjMsg(){ 

}

// ------------------------------------
// fn_800AAE9C - abstract base class NetMessage's constructor
// ------------------------------------

// ------------------------------------
// fn_800AAEAC
// ------------------------------------
extern "C" void fn_800AAEAC(SyncUserMsg*);

void fn_800AAEAC(SyncUserMsg* obj){
    obj = new SyncUserMsg();
}

// ------------------------------------
// fn_800AAEDC
// ------------------------------------
SyncUserMsg::SyncUserMsg(){ }

// ------------------------------------
// fn_800AAF20
// ------------------------------------
// this is a constructor for some other currently unknown class

// ------------------------------------
// fn_800AAF50
// ------------------------------------
extern "C" void fn_800AAF50(SyncAllMsg*);

void fn_800AAF50(SyncAllMsg* obj){
    obj = new SyncAllMsg();
}

// ------------------------------------
// fn_800AAF80
// ------------------------------------
SyncAllMsg::SyncAllMsg(){ }

// ------------------------------------
// fn_800AAFBC
// ------------------------------------
extern int lbl_808F43D8;
extern void fn_800AEC08(int);
extern "C" void fn_800AAFBC();

void fn_800AAFBC(){
    if(lbl_808F43D8 == 0) return;
    fn_800AEC08(lbl_808F43D8);
}


// fn_800AAFD4
// fn_800AB054

// fn_800AB060
// constructor for derived class Net
// base class constructor appears to be fn_8033560C

// fn_800AB0B0

// fn_800AB0F8

// fn_800AB140
// fn_800AB2DC
// fn_800AB2E4
// fn_800AB30C
// fn_800AB360
// fn_800AB3C4
// fn_800AB414
// fn_800AB420
// fn_800AB428
// fn_800AB434
// fn_800AB450
// fn_800AB458
// fn_800AB464
// fn_800AB590
// fn_800AB5E8
// fn_800AB640
// fn_800AB6D8
// fn_800AB6E0
// fn_800AB6EC

// ------------------------------------
// fn_800AB72C
// some class's method - stores a one-byte value into a field with an offset of 0x1C

// fn_800AB734
// some class's method - loads a one-byte value from a field with an offset of 0x1C
// ------------------------------------

// ------------------------------------
// fn_800AB73C
// ------------------------------------
extern "C" void fn_800AB73C();

void fn_800AB73C() { }

// fn_800AB740

// fn_800AB8A8
// some class's method - stores two values into offsets 0x0 and 0x4 of a class

// fn_800AB8B4