// ------------------------------------
// fn_800A515C
// ------------------------------------

extern "C" void fn_800A515C(int**);
extern int lbl_8082A5C0[];

void fn_800A515C(int** arg0) {
    *arg0 = &lbl_8082A5C0[0];
}

// ------------------------------------
// fn_800A516C
// ------------------------------------

extern "C" void fn_80017A8C();
extern "C" int fn_800A516C(int,int);

int fn_800A516C(int arg0, int arg1){
    if((arg0 != 0) && (arg1 > 0)){
        fn_80017A8C();
    }
    return arg0;
}

// ------------------------------------
// fn_800A51AC
// ------------------------------------

extern "C" int fn_800179A8(int, int*, int);
extern "C" void fn_800A49A0(int**, int);
extern "C" int fn_800A5278();
extern "C" int** fn_800A51AC(int**);
extern int lbl_8082A608[];
extern int lbl_8082A650[];

int** fn_800A51AC(int** arg0) {
    int temp_r3;
    int var_r4;

    temp_r3 = fn_800179A8(4, &lbl_8082A650[0], 0x15);
    var_r4 = temp_r3;
    if (temp_r3 != 0) {
        var_r4 = fn_800A5278();
    }
    fn_800A49A0(arg0, var_r4);
    *arg0 = &lbl_8082A608[0];
    return arg0;
}

// ------------------------------------
// fn_800A5214
// ------------------------------------

extern "C" void fn_800A4C84(int, int*);
extern "C" int** fn_800A5214(int**,int);
extern int lbl_8082A608[];

int** fn_800A5214(int** arg0, int arg1) {
    if (arg0 != '\0') {
        *arg0 = &lbl_8082A608[0];
        fn_800A4C84(0, &lbl_8082A608[0]);
        if (arg1 > 0) {
            fn_80017A8C();
        }
    }
    return arg0;
}

// // ------------------------------------
// // fn_800A5278
// // ------------------------------------

// extern "C" int** fn_800A5278(int**);
// void fn_800A515C();                                    /* extern */
// extern int lbl_8082A660[];

// int** fn_800A5278(int** arg0) {
//     fn_800A515C();
//     *arg0 = &lbl_8082A660[0];
//     return arg0;
// }

// // ------------------------------------
// // fn_800A52B4
// // ------------------------------------

// void fn_80017A8C(int);
// void fn_800A516C(int);

// int fn_800A52B4(int arg0, int arg1) {
//     if (arg0 != 0) {
//         fn_800A516C(0);
//         if (arg1 > 0) {
//             fn_80017A8C(arg0);
//         }
//     }
//     return arg0;
// }


// ------------------------------------
// fn_800A530C
// ------------------------------------

extern "C" int fn_800A530C();
int fn_800A530C() {
    return 1;
}

// ------------------------------------
// fn_800A5314
// ------------------------------------

extern "C" void fn_8007DFD0();
extern "C" void fn_80083734();
extern "C" void fn_800A5314();

void fn_800A5314(void) {
    fn_80083734();
    fn_8007DFD0();
}

// ------------------------------------
// fn_800A5338
// ------------------------------------

extern "C" void fn_8007E3C0();                                    /* extern */
extern "C" void fn_80083174();                                    /* extern */
extern "C" void fn_80084160();                                    /* extern */
extern char lbl_808E2DA0;
extern "C" void fn_800A5338();

void fn_800A5338(void) {
    fn_80083174();
    lbl_808E2DA0 = 0;
    fn_8007E3C0();
    fn_80084160();
}
