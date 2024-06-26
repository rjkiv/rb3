/*
 * Copyright (c) 1999
 * Boris Fomitchev
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

#ifndef _STLP_INTERNAL_CCTYPE
#define _STLP_INTERNAL_CCTYPE

#include _STLP_NATIVE_CPP_C_HEADER(cctype)

namespace _STLP_STD {
using _STLP_VENDOR_STD::isalnum;
using _STLP_VENDOR_STD::isalpha;
using _STLP_VENDOR_STD::iscntrl;
using _STLP_VENDOR_STD::isdigit;
using _STLP_VENDOR_STD::isgraph;
using _STLP_VENDOR_STD::islower;
using _STLP_VENDOR_STD::isprint;
using _STLP_VENDOR_STD::ispunct;
using _STLP_VENDOR_STD::isspace;
using _STLP_VENDOR_STD::isupper;
using _STLP_VENDOR_STD::isxdigit;
using _STLP_VENDOR_STD::tolower;
using _STLP_VENDOR_STD::toupper;
}

#endif
