/*
 * Copyright (c) 2003
 * Francois Dumont
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef _STLP_POINTERS_SPEC_TOOLS_H
#define _STLP_POINTERS_SPEC_TOOLS_H

#ifndef _STLP_TYPE_TRAITS_H
#  include <stl/type_traits.h>
#endif

namespace _STLP_STD {

//Some usefull declarations:
template <class _Tp> struct less;

}

namespace _STLP_PRIV {

template <class _StorageT, class _ValueT, class _BinaryPredicate>
struct _BinaryPredWrapper;

/*
 * Since the compiler only allows at most one non-trivial
 * implicit conversion we can make use of a shim class to
 * be sure that functions below doesn't accept classes with
 * implicit pointer conversion operators
 */
struct _ConstVolatileVoidPointerShim
{ _ConstVolatileVoidPointerShim(const volatile void*); };

//The dispatch functions:
struct _VoidPointerShim
{ _VoidPointerShim(void*); };
struct _ConstVoidPointerShim
{ _ConstVoidPointerShim(const void*); };
struct _VolatileVoidPointerShim
{ _VolatileVoidPointerShim(volatile void*); };

template <class _Tp>
char _UseVoidPtrStorageType(const __false_type& /*POD*/, const _Tp&);
char _UseVoidPtrStorageType(const __true_type& /*POD*/, ...);
char* _UseVoidPtrStorageType(const __true_type& /*POD*/, _VoidPointerShim);

template <class _Tp>
char _UseConstVoidPtrStorageType(const __false_type& /*POD*/, const _Tp&);
char _UseConstVoidPtrStorageType(const __true_type& /*POD*/, ...);
char* _UseConstVoidPtrStorageType(const __true_type& /*POD*/, _ConstVoidPointerShim);

template <class _Tp>
char _UseVolatileVoidPtrStorageType(const __false_type& /*POD*/, const _Tp&);
char _UseVolatileVoidPtrStorageType(const __true_type& /*POD*/, ...);
char* _UseVolatileVoidPtrStorageType(const __true_type& /*POD*/, _VolatileVoidPointerShim);

template <class _Tp>
char _UseConstVolatileVoidPtrStorageType(const __false_type& /*POD*/, const _Tp&);
char _UseConstVolatileVoidPtrStorageType(const __true_type& /*POD*/, ...);
char* _UseConstVolatileVoidPtrStorageType(const __true_type& /*POD*/, _ConstVolatileVoidPointerShim);

template <class _Tp>
struct _StorageType {
  typedef typename __type_traits<_Tp>::is_POD_type _PODType;
  static _Tp __null_rep();

  enum { use_void_ptr = (sizeof(_UseVoidPtrStorageType(_PODType(), __null_rep())) == sizeof(char*)) };
  enum { use_const_void_ptr = (sizeof(_UseConstVoidPtrStorageType(_PODType(), __null_rep())) == sizeof(char*)) };
  enum { use_volatile_void_ptr = (sizeof(_UseVolatileVoidPtrStorageType(_PODType(), __null_rep())) == sizeof(char*)) };
  enum { use_const_volatile_void_ptr = (sizeof(_UseConstVolatileVoidPtrStorageType(_PODType(), __null_rep())) == sizeof(char*)) };

  typedef typename __select<!use_const_volatile_void_ptr,
                            _Tp,
          typename __select<use_void_ptr,
                            void*,
          typename __select<use_const_void_ptr,
                            const void*,
          typename __select<use_volatile_void_ptr,
                            volatile void*,
                            const volatile void*>::_Ret >::_Ret >::_Ret >::_Ret _QualifiedType;

  typedef typename __select<use_const_volatile_void_ptr,
                            void*,
                            _Tp>::_Ret _Type;
};

template <class _Tp, class _Compare>
struct _AssocStorageTypes {
  typedef _StorageType<_Tp> _StorageTypeInfo;
  typedef typename _StorageTypeInfo::_Type _SType;

  //We need to also check that the comparison functor used to instanciate the assoc container
  //is the default Standard less implementation:
  typedef typename _IsSTLportClass<_Compare>::_Ret _STLportLess;
  enum { is_default_less = __type2bool<_STLportLess>::_Ret };

  typedef typename __select<is_default_less, _SType, _Tp>::_Ret _KeyStorageType;
  enum { ptr_type = _StorageTypeInfo::use_const_volatile_void_ptr };
  typedef typename __select<is_default_less && ptr_type,
                            _BinaryPredWrapper<_KeyStorageType, _Tp, _Compare>,
                            _Compare>::_Ret _CompareStorageType;
};

/*
 * Base struct to deal with qualifiers
 */
template <class _StorageT, class _QualifiedStorageT>
struct _VoidCastTraitsAux {
  typedef _QualifiedStorageT void_cv_type;
  typedef _StorageT void_type;

  static void_type * uncv_ptr(void_cv_type *__ptr)
  { return __ptr; }
  static void_type const* uncv_cptr(void_cv_type const*__ptr)
  { return __ptr; }
  static void_type ** uncv_pptr(void_cv_type **__ptr)
  { return __ptr; }
  static void_type & uncv_ref(void_cv_type & __ref)
  { return __ref; }
  static void_type const& uncv_cref(void_cv_type const& __ref)
  { return __ref; }
  static void_cv_type* cv_ptr(void_type *__ptr)
  { return __ptr; }
  static void_cv_type const* cv_cptr(void_type const*__ptr)
  { return __ptr; }
  static void_cv_type ** cv_pptr(void_type **__ptr)
  { return __ptr; }
  static void_cv_type & cv_ref(void_type & __ref)
  { return __ref; }
  static void_cv_type const& cv_cref(void_type const& __ref)
  { return __ref; }
};

template <class _VoidCVType>
struct _VoidCastTraitsAuxBase {
  typedef _VoidCVType* void_cv_type;
  typedef void* void_type;

  static void_type* uncv_ptr(void_cv_type *__ptr)
  { return const_cast<void_type*>(__ptr); }
  static void_type const* uncv_cptr(void_cv_type const*__ptr)
  { return const_cast<void_type const*>(__ptr); }
  static void_type** uncv_pptr(void_cv_type **__ptr)
  { return const_cast<void_type**>(__ptr); }
  static void_type& uncv_ref(void_cv_type &__ref)
  { return const_cast<void_type&>(__ref); }
  static void_type const& uncv_cref(void_cv_type const& __ptr)
  { return const_cast<void_type const&>(__ptr); }
  // The reverse versions
  static void_cv_type * cv_ptr(void_type *__ptr)
  { return const_cast<void_cv_type *>(__ptr); }
  static void_cv_type const* cv_cptr(void_type const*__ptr)
  { return const_cast<void_cv_type const*>(__ptr); }
  static void_cv_type ** cv_pptr(void_type **__ptr)
  { return const_cast<void_cv_type**>(__ptr); }
  static void_cv_type & cv_ref(void_type &__ref)
  { return const_cast<void_cv_type &>(__ref); }
  static void_cv_type const& cv_cref(void_type const& __ref)
  { return const_cast<void_cv_type const&>(__ref); }
};

template<>
struct _VoidCastTraitsAux<void*, const void*> : _VoidCastTraitsAuxBase<void const>
{};
template<>
struct _VoidCastTraitsAux<void*, volatile void*> : _VoidCastTraitsAuxBase<void volatile>
{};
template<>
struct _VoidCastTraitsAux<void*, const volatile void*> : _VoidCastTraitsAuxBase<void const volatile>
{};

template <class _StorageT, class _ValueT>
struct _CastTraits {
  typedef _ValueT value_type;
  typedef typename _StorageType<_ValueT>::_QualifiedType _QualifiedStorageT;
  typedef _VoidCastTraitsAux<_StorageT, _QualifiedStorageT> cv_traits;
  typedef typename cv_traits::void_type void_type;
  typedef typename cv_traits::void_cv_type void_cv_type;

  static value_type * to_value_type_ptr(void_type *__ptr)
  { return reinterpret_cast<value_type *>(cv_traits::cv_ptr(__ptr)); }
  static value_type const* to_value_type_cptr(void_type const*__ptr)
  { return reinterpret_cast<value_type const*>(cv_traits::cv_cptr(__ptr)); }
  static value_type ** to_value_type_pptr(void_type **__ptr)
  { return reinterpret_cast<value_type **>(cv_traits::cv_pptr(__ptr)); }
  static value_type & to_value_type_ref(void_type &__ref)
  { return reinterpret_cast<value_type &>(cv_traits::cv_ref(__ref)); }
  static value_type const& to_value_type_cref(void_type const& __ptr)
  { return reinterpret_cast<value_type const&>(cv_traits::cv_cref(__ptr)); }
  // Reverse versions
  static void_type * to_storage_type_ptr(value_type *__ptr)
  { return cv_traits::uncv_ptr(reinterpret_cast<void_cv_type *>(__ptr)); }
  static void_type const* to_storage_type_cptr(value_type const*__ptr)
  { return cv_traits::uncv_cptr(reinterpret_cast<void_cv_type const*>(__ptr)); }
  static void_type ** to_storage_type_pptr(value_type **__ptr)
  { return cv_traits::uncv_pptr(reinterpret_cast<void_cv_type **>(__ptr)); }
  static void_type const& to_storage_type_cref(value_type const& __ref)
  { return cv_traits::uncv_cref(reinterpret_cast<void_cv_type const&>(__ref)); }

  //Method used to treat set container template method extension
  static void_type const& to_storage_type_crefT(value_type const& __ref)
  { return to_storage_type_cref(__ref); }
};

template <class _Tp>
struct _CastTraits<_Tp, _Tp> {
  typedef _Tp storage_type;
  typedef _Tp value_type;

  static value_type * to_value_type_ptr(storage_type *__ptr)
  { return __ptr; }
  static value_type const* to_value_type_cptr(storage_type const*__ptr)
  { return __ptr; }
  static value_type ** to_value_type_pptr(storage_type **__ptr)
  { return __ptr; }
  static value_type & to_value_type_ref(storage_type &__ref)
  { return __ref; }
  static value_type const& to_value_type_cref(storage_type const&__ref)
  { return __ref; }
  // Reverse versions
  static storage_type * to_storage_type_ptr(value_type *__ptr)
  { return __ptr; }
  static storage_type const* to_storage_type_cptr(value_type const*__ptr)
  { return __ptr; }
  static storage_type ** to_storage_type_pptr(value_type **__ptr)
  { return __ptr; }
  static storage_type const& to_storage_type_cref(value_type const& __ref)
  { return __ref; }

  //Method used to treat set container template method extension
  template <class _Tp1>
  static _Tp1 const& to_storage_type_crefT(_Tp1 const& __ref)
  { return __ref; }
};

#define _STLP_USE_ITERATOR_WRAPPER

template <class _StorageT, class _ValueT, class _Iterator>
struct _IteWrapper {
  typedef _CastTraits<_StorageT, _ValueT> cast_traits;
  typedef iterator_traits<_Iterator> _IteTraits;

  typedef typename _IteTraits::iterator_category iterator_category;
  typedef _StorageT value_type;
  typedef typename _IteTraits::difference_type difference_type;
  typedef value_type* pointer;
  typedef value_type const& const_reference;
  //This wrapper won't be used for input so to avoid surprise
  //the reference type will be a const reference:
  typedef const_reference reference;

  typedef _IteWrapper<_StorageT, _ValueT, _Iterator> _Self;
  typedef _Self _Ite;

  _IteWrapper(_Iterator &__ite) : _M_ite(__ite) {}

  const_reference operator*() const { return cast_traits::to_storage_type_cref(*_M_ite); }

  _Self& operator= (_Self const& __rhs) {
    _M_ite = __rhs._M_ite;
    return *this;
  }

  _Self& operator++() {
    ++_M_ite;
    return *this;
  }

  _Self& operator--() {
    --_M_ite;
    return *this;
  }

  _Self& operator += (difference_type __offset) {
    _M_ite += __offset;
    return *this;
  }
  difference_type operator -(_Self const& __other) const
  { return _M_ite - __other._M_ite; }

  bool operator == (_Self const& __other) const
  { return _M_ite == __other._M_ite; }

  bool operator != (_Self const& __other) const
  { return _M_ite != __other._M_ite; }

  bool operator < (_Self const& __rhs) const
  { return _M_ite < __rhs._M_ite; }

private:
  _Iterator _M_ite;
};

template <class _Tp, class _Iterator>
struct _IteWrapper<_Tp, _Tp, _Iterator>
{ typedef _Iterator _Ite; };

//Wrapper functors:
template <class _StorageT, class _ValueT, class _UnaryPredicate>
struct _UnaryPredWrapper {
  typedef _CastTraits<_StorageT, _ValueT> cast_traits;

  _UnaryPredWrapper (_UnaryPredicate const& __pred) : _M_pred(__pred) {}

  bool operator () (_StorageT const& __ref) const
  { return _M_pred(cast_traits::to_value_type_cref(__ref)); }

private:
  _UnaryPredicate _M_pred;
};

template <class _StorageT, class _ValueT, class _BinaryPredicate>
struct _BinaryPredWrapper {
  typedef _CastTraits<_StorageT, _ValueT> cast_traits;

  _BinaryPredWrapper () {}
  _BinaryPredWrapper (_BinaryPredicate const& __pred) : _M_pred(__pred) {}

  _BinaryPredicate get_pred() const { return _M_pred; }

  bool operator () (_StorageT const& __fst, _StorageT const& __snd) const
  { return _M_pred(cast_traits::to_value_type_cref(__fst), cast_traits::to_value_type_cref(__snd)); }

  //Cast operator used to transparently access underlying predicate
  //in set::key_comp() method
  operator _BinaryPredicate() const
  { return _M_pred; }

private:
  _BinaryPredicate _M_pred;
};

}

#endif /* _STLP_POINTERS_SPEC_TOOLS_H */
