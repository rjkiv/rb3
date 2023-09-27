#ifndef WII_UNK_800AAE1C_HPP
#define WII_UNK_800AAE1C_HPP

// abstract base class
class NetMessage {
    public:
        NetMessage();
        virtual void fn_8000DD10(); // not the right prototype, does not return void
        virtual void unk1() = 0;
        virtual void unk2() = 0;
        virtual void unk3() = 0;
        virtual void fn_8077BAA0(); // returns 0
        virtual void fn_8076F540();
};

class SyncObjMsg : NetMessage {
    public:
        int unk0; // this should be a String::String - need to figure out how to include it here
        int unk4;
        int unk8;
        int unkC;
        int unk10; // this is an unknown class, constructor is in fn_80354E6C
        int unk14, unk18, unk1C;
        int unk20, unk24, unk28, unk2C;
        // char unk[0x30]; // dummy field to pad out space

        SyncObjMsg();
        // likely not the right prototypes either, double check return type and input args
        virtual void fn_800BA1EC();
        virtual void fn_800BA7E0();
        virtual void fn_800BA84C();
        virtual void fn_800BA8C8();
        virtual void fn_8077BAA0();
        virtual void fn_800BA9BC();
        virtual void fn_800BAB80();
        virtual void fn_800BABDC();
        void unk1();
        void unk2();
        void unk3();
};

class SyncUserMsg : NetMessage {
    public:
        int unk0; // this is actually an unknown class, whose constructor is fn_800AAF20
        int unk4;
        int unk8;
        int unkC;
        // char unk[0x10]; // dummy field to pad out space

        SyncUserMsg();
        // likely not the right prototypes either, double check return type and input args
        virtual void fn_800AD2DC();
        virtual void fn_800BAAE8();
        virtual void fn_800BAAF8();
        virtual void fn_800BAB08();
        virtual void fn_8077BAA0();
        virtual void fn_8076F540();
        virtual void fn_800BABE8();
        virtual void fn_800BAC44();
        void unk1();
        void unk2();
        void unk3();
};

class SyncAllMsg : NetMessage {
    public:
        SyncAllMsg();
        // likely not the right prototypes either, double check return type and input args
        virtual void fn_800AD2DC();
        virtual void fn_8076F540();
        // virtual void fn_8076F540();
        virtual void fn_800BAB74();
        virtual void fn_8077BAA0();
        // virtual void fn_8076F540();
        virtual void fn_800BAC50();
        virtual void fn_800BACAC();
        void unk1();
        void unk2();
        void unk3();
};

#endif
