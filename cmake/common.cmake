if (CMAKE_SYSTEM_PROCESSOR MATCHES "i386|i686|x86|x86_64|x64|amd64|AMD64|win32|Win32")
    set(IS_X86 TRUE)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|x64|amd64|AMD64")
        set(IS_X64 TRUE)
    endif()
endif()
if (CMAKE_SYSTEM_PROCESSOR MATCHES "arm|ARM|aarch64|arm64|ARM64|armeb|aarch64be|aarch64_be")
    set(IS_ARM TRUE)
endif()
if (CMAKE_SYSTEM_PROCESSOR MATCHES "riscv64|rv64")
    set(IS_RISCV64 TRUE)
endif()
if (CMAKE_SYSTEM_PROCESSOR MATCHES "riscv32|rv32")
    set(IS_RISCV32 TRUE)
endif()

include(CheckCXXCompilerFlag)
include(CheckIncludeFileCXX)
include(CheckCXXSymbolExists)

add_compile_definitions(HAVE_CONFIG_H PARPAR_ENABLE_HASHER_MD5CRC)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
        add_compile_options(-Weverything)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-Wall -Wextra)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        add_compile_options(/Zi /MTd /MP /W4 /utf-8)
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        add_compile_options(/MT /Oi /MP /GS- /W0 /utf-8)
    else()
        add_compile_options(-fno-rtti -Wno-unused-function)
    endif()
endif()