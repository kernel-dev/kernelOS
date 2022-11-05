#ifndef KERN_ASSERT_H
#define KERN_ASSERT_H

#include "../Util/KernRuntimeValues.h"
#include "../Graphics/KernText.h"

#define STR_EXPR(expr) #expr
#define ASSERT(expr) \
    if (!(expr)) \
    { \
        kprint ("ASSERT ( "); \
        kprint (STR_EXPR(expr)); \
        kprint (" )"); \
        kprint (" == "); \
        kprint (expr ? "1\n" : "0\n"); \
    }

#endif /* KernAssert.h */