/** 
 * \file ArchitectureInfo.h
 * \brief Here you can get information about compiler, CPU architecture, machine
 * parameters, etc.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef ARCHITECTUREINFO_H
#define ARCHITECTUREINFO_H

#undef NUT_X86
#undef NUT_X64



// If the target architecture is x86
#if defined(_M_IX86) || defined(_X86_)

    #define NUT_X86

// If the target architecture is x64
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)

    #define NUT_X64

#endif



#endif // ARCHITECTUREINFO_H
