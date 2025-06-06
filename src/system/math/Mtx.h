#ifndef MATH_MTX_H
#define MATH_MTX_H
#include "math/Vec.h"
#include "math/Trig.h"
#include "obj/Data.h"
#include "utl/BinStream.h"
#include "decomp.h"

#define PSQ_MOVE(dst, src) *(__vec2x32float__ *)&dst = *(__vec2x32float__ *)&src

namespace Hmx {
    class Matrix3 {
    public:
        Vector3 x;
        Vector3 y;
        Vector3 z;

        // all of these are weak
        Matrix3() {}

        Matrix3(const Matrix3 &mtx) {
            x = mtx.x;
            y = mtx.y;
            z = mtx.z;
        }

        Matrix3(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3)
            : x(v1), y(v2), z(v3) {}

        // clang-format off
        Matrix3(
            float f1, float f2, float f3,
            float f4, float f5, float f6,
            float f7, float f8, float f9
        )
            : x(f1, f2, f3), y(f4, f5, f6), z(f7, f8, f9) {}

        void Set(
            float f1, float f2, float f3,
            float f4, float f5, float f6,
            float f7, float f8, float f9
        ) {
            x.Set(f1, f2, f3);
            y.Set(f4, f5, f6);
            z.Set(f7, f8, f9);
        }
        // clang-format on
        void Set(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3) {
            x = v1;
            y = v2;
            z = v3;
        }
        void Zero() {
            x.Zero();
            y.Zero();
            z.Zero();
        }
        void RotateAboutZ(float angle) {
            float c = Cosine(angle);
            float s = Sine(angle);
            Set(c, -s, 0.0f, s, c, 0.0f, 0.0f, 0.0f, 1.0f);
        }
        void RotateAboutY(float angle) {
            float c = Cosine(angle);
            float s = Sine(angle);
            Set(c, 0.0f, -s, 0.0f, 1.0f, 0.0f, s, 0.0f, c);
        }
        void RotateAboutX(float angle) {
            float c = Cosine(angle);
            float s = Sine(angle);
            Set(1.0f, 0.0f, 0.0f, 0.0f, c, s, 0.0f, -s, c);
        }
        void Identity() {
            x.Set(1.0f, 0.0f, 0.0f);
            y.Set(0.0f, 1.0f, 0.0f);
            z.Set(0.0f, 0.0f, 1.0f);
        }
        Matrix3 &operator=(const Matrix3 &mtx) {
            PSQ_MOVE(x.x, mtx.x.x);
            x.z = mtx.x.z;

            PSQ_MOVE(y.x, mtx.y.x);
            y.z = mtx.y.z;

            PSQ_MOVE(z.x, mtx.z.x);
            z.z = mtx.z.z;
            return *this;
        }
        Vector3 &operator[](int i) { return *(&x + i); }

        bool operator==(const Matrix3 &mtx) const {
            return x == mtx.x && y == mtx.y && z == mtx.z;
        }

        bool operator!=(const Matrix3 &mtx) const {
            return x != mtx.x || y != mtx.y || z != mtx.z;
        }
    };

    class Quat {
    public:
        Quat() {}
        Quat(float f1, float f2, float f3, float f4) : x(f1), y(f2), z(f3), w(f4) {}
        Quat(const Matrix3 &m) { Set(m); }
        Quat(const Vector3 &v) { Set(v); }
        Quat(const Vector3 &, float);

        void Reset() {
            x = y = z = 0.0f;
            w = 1.0f;
        }
        void Zero() { w = x = y = z = 0.0f; }
        void Set(const Matrix3 &);
        void Set(const Vector3 &);
        void Set(const Vector3 &, float);
        void Set(float f1, float f2, float f3, float f4) {
            x = f1;
            y = f2;
            z = f3;
            w = f4;
        }

        bool operator!=(const Quat &q) const {
            return x != q.x || y != q.y || z != q.z || w != q.w;
        }

        float x;
        float y;
        float z;
        float w;
    };
}

inline BinStream &operator>>(BinStream &bs, Hmx::Matrix3 &mtx) {
    bs >> mtx.x >> mtx.y >> mtx.z;
    return bs;
}

inline BinStream &operator<<(BinStream &bs, const Hmx::Quat &q) {
    bs << q.x << q.y << q.z << q.w;
    return bs;
}

inline BinStream &operator>>(BinStream &bs, Hmx::Quat &q) {
    bs >> q.x >> q.y >> q.z >> q.w;
    return bs;
}

class Transform {
public:
    class Hmx::Matrix3 m;
    class Vector3 v;

    // all of these are weak
    Transform() {}

    Transform(const Hmx::Matrix3 &mtx, const Vector3 &vec) : m(mtx), v(vec) {}

    // both of these use powerpc asm magic
    Transform(const register Transform &tf) {
        // m.x.x = tf.m.x.x;
        // m.x.y = tf.m.x.y;
        PSQ_MOVE(m.x.x, tf.m.x.x);
        m.x.z = tf.m.x.z;

        // m.y.x = tf.m.y.x;
        // m.y.y = tf.m.y.y;
        PSQ_MOVE(m.y.x, tf.m.y.x);
        m.y.z = tf.m.y.z;

        // m.z.x = tf.m.z.x;
        // m.z.y = tf.m.z.y;
        PSQ_MOVE(m.z.x, tf.m.z.x);
        m.z.z = tf.m.z.z;

        // v.x = tf.v.x;
        // v.y = tf.v.y;
        PSQ_MOVE(v.x, tf.v.x);
        v.z = tf.v.z;
    }
    Transform &operator=(const Transform &tf) {
        // m.x.x = tf.m.x.x;
        // m.x.y = tf.m.x.y;
        PSQ_MOVE(m.x.x, tf.m.x.x);
        m.x.z = tf.m.x.z;

        // m.y.x = tf.m.y.x;
        // m.y.y = tf.m.y.y;
        PSQ_MOVE(m.y.x, tf.m.y.x);
        m.y.z = tf.m.y.z;

        // m.z.x = tf.m.z.x;
        // m.z.y = tf.m.z.y;
        PSQ_MOVE(m.z.x, tf.m.z.x);
        m.z.z = tf.m.z.z;

        // v.x = tf.v.x;
        // v.y = tf.v.y;
        PSQ_MOVE(v.x, tf.v.x);
        v.z = tf.v.z;
        return *this;
    }

    void Reset() {
        m.Identity();
        v.Zero();
    }

    void Set(const Hmx::Matrix3 &mtx, const Vector3 &vec) {
        m = mtx;
        v = vec;
    }

    void LookAt(const Vector3 &, const Vector3 &);
    void Zero() {
        m.Zero();
        v.Zero();
    }

    bool operator==(const Transform &tf) const { return m == tf.m && v == tf.v; }
};

inline BinStream &operator>>(BinStream &bs, Transform &tf) {
    bs >> tf.m >> tf.v;
    return bs;
}

class QuatXfm {
public:
    Vector3 v; // 0x0
    Hmx::Quat q; // 0xc
};

class ShortQuat {
public:
    short x, y, z, w;
    void Reset() {
        x = y = z = 0;
        w = 32767;
    }
    void ToQuat(Hmx::Quat& q) const {
        q.Set(x * 0.000030518509f, y * 0.000030518509f, z * 0.000030518509f, w * 0.000030518509f);
    }
};

class ByteQuat {
public:
    char x, y, z, w;
    void ToQuat(Hmx::Quat& q) const {
        q.Set(x * 0.0078740157f, y * 0.0078740157f, z * 0.0078740157f, w * 0.0078740157f);
    }
};

class TransformNoScale {
public:
    TransformNoScale() {}
    TransformNoScale(const TransformNoScale &t) { Set(t); }
    void Set(const Transform &);
    void Set(const TransformNoScale &);
    void SetRot(const Hmx::Matrix3 &);
    void Reset();
    void ToTransform(Transform &) const;
    TransformNoScale &operator=(const TransformNoScale &t) { Set(t); }

    ShortQuat q; // 0x0/2/4/6
    class Vector3 v; // 0x8
};

BinStream &operator>>(BinStream &, TransformNoScale &);

class Plane {
public:
    Plane() {}
    Plane(const Vector3 &v1, const Vector3 &v2) { Set(v1, v2); }

    void Set(const Vector3 &, const Vector3 &);
    float Dot(const Vector3 &vec) const { return a * vec.x + b * vec.y + c * vec.z + d; }
    Vector3 On() const;

    float a, b, c, d;
};

inline BinStream &operator>>(BinStream &bs, Plane &pl) {
    bs >> pl.a >> pl.b >> pl.c >> pl.d;
    return bs;
}

class Frustum {
    // total size: 0x60
public:
    void Set(float, float, float, float);

    class Plane front; // offset 0x0, size 0x10
    class Plane back; // offset 0x10, size 0x10
    class Plane left; // offset 0x20, size 0x10
    class Plane right; // offset 0x30, size 0x10
    class Plane top; // offset 0x40, size 0x10
    class Plane bottom; // offset 0x50, size 0x10
};

class Triangle {
public:
    Triangle() {}
    Triangle(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3) { Set(v1, v2, v3); }
    void Set(const Vector3 &, const Vector3 &, const Vector3 &);

    Vector3 origin; // 0x0
    Hmx::Matrix3 frame; // 0xc
};

void Scale(const Hmx::Matrix3 &mtx, const Vector3 &vec, Hmx::Matrix3 &res);

// https://decomp.me/scratch/kGwAB
// lol, regswaps galore
inline void Scale(const Vector3 &vec, const Hmx::Matrix3 &mtx, Hmx::Matrix3 &res) {
    Scale(mtx.x, vec.x, res.x);
    Scale(mtx.y, vec.y, res.y);
    Scale(mtx.z, vec.z, res.z);
}

inline void Negate(const Hmx::Quat &q, Hmx::Quat &qres) {
    qres.Set(-q.x, -q.y, -q.z, q.w);
}

void ScaleAddEq(Hmx::Quat &, const Hmx::Quat &, float);
void Normalize(const Hmx::Quat &, Hmx::Quat &);
void Multiply(const Hmx::Quat &, const Hmx::Quat &, Hmx::Quat &);
void FastInterp(const Hmx::Quat &, const Hmx::Quat &, float, Hmx::Quat &);
void Invert(const Hmx::Matrix3 &, Hmx::Matrix3 &);
void FastInvert(const Hmx::Matrix3 &, Hmx::Matrix3 &);
void Multiply(const Hmx::Matrix3 &, const Vector3 &, Vector3 &);
void Multiply(const Vector3 &, const Hmx::Matrix3 &, Vector3 &);
void Multiply(const Transform &, const Transform &, Transform &);
void Multiply(const Transform &, const Vector3 &, Vector3 &);
void Multiply(const Vector3 &, const Hmx::Quat &, Vector3 &);
void Multiply(const Vector3 &, const Transform &, Vector3 &);
void Multiply(const Plane &, const Transform &, Plane &);
void Multiply(const Hmx::Matrix3 &, const Hmx::Matrix3 &, Hmx::Matrix3 &);
void IdentityInterp(const Hmx::Quat &, float, const Hmx::Quat &);
void Multiply(const Transform &, const Hmx::Matrix3 &, Transform &);

inline void Multiply(const Frustum &fin, const Transform &tf, Frustum &fout) {
    Multiply(fin.front, tf, fout.front);
    Multiply(fin.back, tf, fout.back);
    Multiply(fin.left, tf, fout.left);
    Multiply(fin.right, tf, fout.right);
    Multiply(fin.top, tf, fout.top);
    Multiply(fin.bottom, tf, fout.bottom);
}

void Interp(const Hmx::Matrix3 &, const Hmx::Matrix3 &, float, Hmx::Matrix3 &);
void NormalizeTo(const Hmx::Quat &, Hmx::Quat &);
bool operator<=(const Vector3 &, const Plane &);
Vector3 TransformNormal(const Vector3 &, const Hmx::Matrix3 &);
inline void ScaleAddEq(Hmx::Matrix3 &m1, const Hmx::Matrix3 &m2, float f) {
    ScaleAddEq(m1.x, m2.x, f);
    ScaleAddEq(m1.y, m2.y, f);
    ScaleAddEq(m1.z, m2.z, f);
}
inline void ScaleAddEq(Transform &tf1, const Transform &tf2, float f) {
    ScaleAddEq(tf1.m, tf2.m, f);
    ScaleAddEq(tf1.v, tf2.v, f);
}

inline float AngleBetween(const Hmx::Quat &q1, const Hmx::Quat &q2) {
    Hmx::Quat q18;
    Negate(q1, q18);
    Multiply(q2, q18, q18);
    if (q18.w > 1.0f)
        return 0;
    else
        return acosf(q18.w) * 2.0f;
}

inline void Transpose(const Hmx::Matrix3 &min, Hmx::Matrix3 &mout) {
    mout.Set(
        min.x.x, min.y.x, min.z.x, min.x.y, min.y.y, min.z.y, min.x.z, min.y.z, min.z.z
    );
}

inline void Transpose(const Transform &tfin, Transform &tfout) {
    Vector3 vtmp;
    Transpose(tfin.m, tfout.m);
    Negate(tfin.v, vtmp);
    Multiply(vtmp, tfout.m, tfout.v);
}

inline void Normalize(const Hmx::Matrix3 &src, Hmx::Matrix3 &dst) {
    Normalize(src.y, dst.y);
    Cross(dst.y, src.z, dst.x);
    Normalize(dst.x, dst.x);
    Cross(dst.x, dst.y, dst.z);
}

inline void Multiply(const Vector3 &vin, const Hmx::Matrix3 &mtx, Vector3 &vout) {
    register __vec2x32float__ i1, i2, m1, m2, o1, o2;

    register const Vector3 *_vin = &vin;
    register Vector3 *_vout = &vout;
    register const Hmx::Matrix3 *_m = &mtx;

    typedef Hmx::Matrix3 Matrix3;

    ASM_BLOCK(
        psq_l i1, Vector3.x(_vin), 0, 0
        psq_l i2, Vector3.y(_vin), 0, 0

        psq_l m1, Matrix3.z.x(_m), 0, 0
        psq_l m2, Matrix3.z.z(_m), 1, 0

        ps_muls1 o1, m1, i2
        ps_muls1 o2, m2, i2

        psq_l m1, Matrix3.y.x(_m), 0, 0
        psq_l m2, Matrix3.y.z(_m), 1, 0

        ps_madds0 o1, m1, i2, o1
        ps_madds0 o2, m2, i2, o2

        psq_l m1, Matrix3.x.x(_m), 0, 0
        psq_l m2, Matrix3.x.z(_m), 1, 0

        ps_madds0 o1, m1, i1, o1
        ps_madds0 o2, m2, i1, o2

        psq_st o1, Vector3.x(_vout), 0, 0
        psq_st o2, Vector3.z(_vout), 1, 0
    )
}

inline void Invert(const Transform &tfin, Transform &tfout) {
#ifdef VERSION_SZBE69_B8 // DEBUG
    Vector3 vtmp(tfin.v.x, tfin.v.y, tfin.v.z);
    vtmp.x = -vtmp.x;
    vtmp.z = -vtmp.z;
    vtmp.y = -vtmp.y;
#else // RETAIL
    Vector3 vtmp;
    Negate(tfin.v, vtmp);
#endif
    Invert(tfin.m, tfout.m);
    Multiply(vtmp, tfout.m, tfout.v);
}

inline void FastInvert(const Transform &tfin, Transform &tfout) {
#ifdef VERSION_SZBE69_B8 // DEBUG
    Vector3 vtmp(tfin.v.x, tfin.v.y, tfin.v.z);
    vtmp.x = -vtmp.x;
    vtmp.z = -vtmp.z;
    vtmp.y = -vtmp.y;
#else // RETAIL
    Vector3 vtmp;
    Negate(tfin.v, vtmp);
#endif
    FastInvert(tfin.m, tfout.m);
    Multiply(vtmp, tfout.m, tfout.v);
}

// https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process
// https://gamedev.stackexchange.com/questions/139703/compute-up-and-right-from-a-direction
// Looks similar to C_MTXLookAt from the dolphin SDK.
inline void LookAt(Hmx::Matrix3 &mtx) {
    Cross(mtx.x, mtx.y, mtx.z);
    Normalize(mtx.z, mtx.z);
    Cross(mtx.z, mtx.x, mtx.y);
}

#endif
