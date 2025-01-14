#include <par2/osinfo/platform.h>

#define _mword __m256i
#define _MM(f) _mm256_ ## f
#define _MMI(f) _mm256_ ## f ## _si256
#define MWORD_SIZE 32
#define _FNSUFFIX _vpclmul

#define _USE_VPCLMUL 1

#if defined(__VPCLMULQDQ__) && defined(__AVX2__)
# define _AVAILABLE 1
#endif
#include <par2/gf16/gf16pmul_x86.h>
