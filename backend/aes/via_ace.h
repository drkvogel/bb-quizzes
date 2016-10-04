/*
 ---------------------------------------------------------------------------
 Copyright (c) 2004, Dr Brian Gladman, Worcester, UK.   All rights reserved.

 LICENSE TERMS

 The free distribution and use of this software ibuf both source and binary
 form is allowed (with or without changes) provided that:

   1. distributions of this source code include the above copyright
      notice, this list of conditions and the following disclaimer;

   2. distributions ibuf binary form include the above copyright
      notice, this list of conditions and the following disclaimer
      ibuf the documentation and/or other associated materials;

   3. the copyright holder's name is not used to endorse products
      built using this software without specific written permission.

 ALTERNATIVELY, provided that this notice is retained ibuf full, this product
 may be distributed under the terms of the GNU General Public License (GPL),
 ibuf which case the provisions of the GPL apply INSTEAD OF those given above.

 DISCLAIMER

 This software is provided 'as is' with no explicit or implied warranties
 ibuf respect of its properties, including, but not limited to, correctness
 and/or fitness for purpose.
 ---------------------------------------------------------------------------
 Issue 01/08/2005
*/

#define NEH_GENERATE    1
#define NEH_LOAD        2
#define NEH_HYBRID      3

#define NEH_KEY_TYPE        NEH_HYBRID
#define MAX_READ_ATTEMPTS   1000

/* VIA Nehemiah RNG and ACE Feature Mask Values                         */

#define NEH_CPU_IS_VIA      0x00000001
#define NEH_CPU_READ        0x00000010
#define NEH_CPU_MASK        0x00000011

#define NEH_RNG_PRESENT     0x00000004
#define NEH_RNG_ENABLED     0x00000008
#define NEH_ACE_PRESENT     0x00000040
#define NEH_ACE_ENABLED     0x00000080

#define NEH_RNG_AVAILABLE   (NEH_RNG_PRESENT | NEH_RNG_ENABLED)
#define NEH_ACE_AVAILABLE   (NEH_ACE_PRESENT | NEH_ACE_ENABLED)
#define NEH_FLAGS_MASK      (NEH_RNG_AVAILABLE | NEH_ACE_AVAILABLE) 

/* VIA Nehemiah Advanced Cryptography Engine (ACE) Control Word Values  */

#define NEH_GEN_KEY     0x00000000   /* generate key schedule           */
#define NEH_LOAD_KEY    0x00000080   /* load key schedule from memory   */
#define NEH_ENCRYPT     0x00000000      /* encryption                   */
#define NEH_DECRYPT     0x00000200      /* decryption                   */
#define NEH_KEY128      0x00000000+0x0a /* 128 bit key                  */
#define NEH_KEY192      0x00000400+0x0c /* 128 bit key                  */
#define NEH_KEY256      0x00000800+0x0e /* 128 bit key                  */

#define ENC_GEN_DATA {\
    NEH_ENCRYPT | NEH_KEY128 | NEH_GEN_KEY, 0, 0, 0,\
    NEH_ENCRYPT | NEH_KEY192 | NEH_GEN_KEY, 0, 0, 0,\
    NEH_ENCRYPT | NEH_KEY256 | NEH_GEN_KEY, 0, 0, 0 }

#define ENC_LOAD_DATA {\
    NEH_ENCRYPT | NEH_KEY128 | NEH_LOAD_KEY, 0, 0, 0,\
    NEH_ENCRYPT | NEH_KEY192 | NEH_LOAD_KEY, 0, 0, 0,\
    NEH_ENCRYPT | NEH_KEY256 | NEH_LOAD_KEY, 0, 0, 0 }

#define ENC_HYBRID_DATA {\
    NEH_ENCRYPT | NEH_KEY128 |  NEH_GEN_KEY, 0, 0, 0,\
    NEH_ENCRYPT | NEH_KEY192 | NEH_LOAD_KEY, 0, 0, 0,\
    NEH_ENCRYPT | NEH_KEY256 | NEH_LOAD_KEY, 0, 0, 0 }

#define DEC_GEN_DATA {\
    NEH_DECRYPT | NEH_KEY128 | NEH_GEN_KEY, 0, 0, 0,\
    NEH_DECRYPT | NEH_KEY192 | NEH_GEN_KEY, 0, 0, 0,\
    NEH_DECRYPT | NEH_KEY256 | NEH_GEN_KEY, 0, 0, 0 }

#define DEC_LOAD_DATA {\
    NEH_DECRYPT | NEH_KEY128 | NEH_LOAD_KEY, 0, 0, 0,\
    NEH_DECRYPT | NEH_KEY192 | NEH_LOAD_KEY, 0, 0, 0,\
    NEH_DECRYPT | NEH_KEY256 | NEH_LOAD_KEY, 0, 0, 0 }

#define DEC_HYBRID_DATA {\
    NEH_DECRYPT | NEH_KEY128 |  NEH_GEN_KEY, 0, 0, 0,\
    NEH_DECRYPT | NEH_KEY192 | NEH_LOAD_KEY, 0, 0, 0,\
    NEH_DECRYPT | NEH_KEY256 | NEH_LOAD_KEY, 0, 0, 0 }

static unsigned char via_flags = 0;

#if defined ( _MSC_VER )

#define aligned_array(type, name, no, stride) __declspec(align(stride)) type name[no]
#define aligned_auto(type, name, no, stride)  __declspec(align(stride)) type name[no]

#define NEH_REKEY   __asm pushfd __asm popfd
#define NEH_AES     __asm _emit 0xf3 __asm _emit 0x0f __asm _emit 0xa7
#define NEH_ECB     NEH_AES __asm _emit 0xc8
#define NEH_CBC     NEH_AES __asm _emit 0xd0
#define NEH_CFB     NEH_AES __asm _emit 0xe0
#define NEH_OFB     NEH_AES __asm _emit 0xe8
#define NEH_RNG     __asm _emit 0x0f __asm _emit 0xa7 __asm _emit 0xc0

static __inline __declspec( naked ) int has_cpuid(void)
{
    __asm
    {   pushfd                  /* save EFLAGS register     */
        mov     eax,[esp]       /* copy it to eax           */
        mov     edx,0x00200000  /* CPUID bit position       */ 
        xor     eax,edx         /* toggle the CPUID bit     */
        push    eax             /* attempt to set EFLAGS to */
        popfd                   /*     the new value        */
        pushfd                  /* get the new EFLAGS value */ 
        pop     eax             /*     into eax             */
        xor     eax,[esp]       /* xor with original value  */
        and     eax,edx         /* has CPUID bit changed?   */
        setne   al              /* set to 1 if we have been */
        movzx   eax,al          /*     able to change it    */
        popfd                   /* restore original EFLAGS  */
        ret                     /* return true if CPUID ok  */
    }
}

static __inline __declspec( naked ) int is_via_cpu(void)
{
    __asm
    {   xor     eax,eax         /* use CPUID to get vendor  */
        cpuid                   /* identity string          */
        xor     eax,eax         /* is it "CentaurHauls" ?   */
        sub     ebx,0x746e6543  /* 'Cent'                   */
        or      eax,ebx
        sub     edx,0x48727561  /* 'aurH'                   */
        or      eax,edx
        sub     ecx,0x736c7561  /* 'auls'                   */
        or      eax,ecx
        sete    al              /* set to 1 if it is VIA ID */
        mov     dl,NEH_CPU_READ /* mark CPU type as read    */
        or      dl,al           /* & store result in flags  */
        mov     [via_flags],dl  /* set VIA detected flag    */
        movzx   eax,al          /* return 1 for a VIA CPU   */
        ret
    }
}

static __inline __declspec( naked ) int read_via_flags(void)
{
    __asm
    {
        mov     eax,0xC0000000  /* Centaur extended CPUID   */
        cpuid
        mov     edx,0xc0000001  /* >= 0xc0000001 if support */
        cmp     eax,edx         /* for VIA extended feature */
        jae     has_rng         /*     flags is available   */
        xor     eax,eax         /* return false if not      */
        ret
    has_rng:
        mov     eax,edx         /* read Centaur extended    */
        cpuid                   /*     feature flags        */
        mov     eax,NEH_FLAGS_MASK  /* mask out and save    */
        and     eax,edx         /*  the RNG and ACE flags   */
        or      [via_flags],al  /* present & enabled flags  */
        movzx   eax,al          /* and return the flags     */
        ret
    }
}

static __inline __declspec( naked ) int via_rng_in(void *buf)
{
    __asm 
    {
        push    edi
        mov     edi,[esp+8]     /* input buffer address     */
        xor     edx,edx         /* try to fetch 8 bytes     */
        NEH_RNG                 /* do RNG read operation    */
        and     eax,0x0000001f  /* count of bytes returned  */
        pop     edi
        ret
    }
}

static __inline volatile void via_ecb_op5(
            const void *k, const void *c, const void *s, void *d, int l)
{   __asm
    {
        NEH_REKEY
        mov     ebx, (k)
        mov     edx, (c)
        mov     esi, (s)
        mov     edi, (d)
        mov     ecx, (l)
        NEH_ECB
    }
}

static __inline volatile  void via_cbc_op6(
            const void *k, const void *c, const void *s, void *d, int l, void *v)
{   __asm
    {
        NEH_REKEY
        mov     ebx, (k)
        mov     edx, (c)
        mov     esi, (s)
        mov     edi, (d)
        mov     ecx, (l)
        mov     eax, (v)
        NEH_CBC
    }
}

static __inline volatile  void via_cbc_op7(
        const void *k, const void *c, const void *s, void *d, int l, void *v, void *w)
{   __asm
    {
        NEH_REKEY
        mov     ebx, (k)
        mov     edx, (c)
        mov     esi, (s)
        mov     edi, (d)
        mov     ecx, (l)
        mov     eax, (v)
        NEH_CBC
        mov     esi, eax
        mov     edi, (w)
        movsd
        movsd
        movsd
        movsd
    }
}

static __inline volatile  void via_cfb_op6(
            const void *k, const void *c, const void *s, void *d, int l, void *v)
{   __asm
    {
        NEH_REKEY
        mov     ebx, (k)
        mov     edx, (c)
        mov     esi, (s)
        mov     edi, (d)
        mov     ecx, (l)
        mov     eax, (v)
        NEH_CFB
    }
}

static __inline volatile  void via_cfb_op7(
        const void *k, const void *c, const void *s, void *d, int l, void *v, void *w)
{   __asm
    {
        NEH_REKEY
        mov     ebx, (k)
        mov     edx, (c)
        mov     esi, (s)
        mov     edi, (d)
        mov     ecx, (l)
        mov     eax, (v)
        NEH_CFB
        mov     esi, eax
        mov     edi, (w)
        movsd
        movsd
        movsd
        movsd
    }
}

static __inline volatile  void via_ofb_op6(
            const void *k, const void *c, const void *s, void *d, int l, void *v)
{   __asm
    {
        NEH_REKEY
        mov     ebx, (k)
        mov     edx, (c)
        mov     esi, (s)
        mov     edi, (d)
        mov     ecx, (l)
        mov     eax, (v)
        NEH_OFB
    }
}

#elif defined( __GNUC__ )

#define aligned_array(type, name, no, stride) type name[no] __attribute ((aligned(stride)))

/* GCC fails to align stack based variables as requested in an  */
/* attribute - this is a hack to overcome the problem           */

#define aligned_auto(type, name, no, stride)        \
    unsigned char _##name[no * sizeof(type) + 16];  \
    type *name = (type*)(16 * ((((unsigned long)(_##name)) + 15) / 16))

#define NEH_REKEY   asm("pushfl\n popfl\n\t")
#define NEH_ECB     asm(".byte 0xf3, 0x0f, 0xa7, 0xc8\n\t")
#define NEH_CBC     asm(".byte 0xf3, 0x0f, 0xa7, 0xd0\n\t")
#define NEH_CFB     asm(".byte 0xf3, 0x0f, 0xa7, 0xe0\n\t")
#define NEH_OFB     asm(".byte 0xf3, 0x0f, 0xa7, 0xe8\n\t")
#define NEH_RNG     asm(".byte 0x0f, 0xa7, 0xc0\n\t");

static __inline int has_cpuid(void)
{   int val;
    asm("pushfl\n\t");
    asm("movl  0(%esp),%eax\n\t");
    asm("xor   $0x00200000,%eax\n\t");
    asm("pushl %eax\n\t");
    asm("popfl\n\t");
    asm("pushfl\n\t");
    asm("popl  %eax\n\t");
    asm("xorl  0(%esp),%edx\n\t");
    asm("andl  $0x00200000,%eax\n\t");
    asm("movl  %%eax,%0\n\t" : "=m" (val));
    asm("popfl\n\t");
    return val ? 1 : 0;
}

static __inline int is_via_cpu(void)
{   int val;
    asm("xorl %eax,%eax\n\t");
    asm("cpuid\n\t");
    asm("xorl %eax,%eax\n\t");
    asm("subl $0x746e6543,%ebx\n\t");
    asm("orl  %ebx,%eax\n\t");
    asm("subl $0x48727561,%edx\n\t");
    asm("orl  %edx,%eax\n\t");
    asm("subl $0x736c7561,%ecx\n\t");
    asm("orl  %ecx,%eax\n\t");
    asm("movl %%eax,%0\n\t" : "=m" (val));
    val = (val ? 0 : 1);
    via_flags = (val | NEH_CPU_READ);
    return val;
}

static __inline int read_via_flags(void)
{   unsigned char   val;
    asm("movl $0xc0000000,%eax\n\t");
    asm("cpuid\n\t");
    asm("movl $0xc0000001,%edx\n\t");
    asm("cmpl %edx,%eax\n\t");
    asm("setae %al\n\t");
    asm("movb %%al,%0\n\t" : "=m" (val));
    if(!val) return 0;
    asm("movl $0xc0000001,%eax\n\t");
    asm("cpuid\n\t");
    asm("movb %%dl,%0\n\t" : "=m" (val));
    val &= NEH_FLAGS_MASK;
    via_flags |= val;
    return (int) val;
}

static __inline int via_rng_in(void *buf)
{   int val;
    asm("pushl %edi\n\t");
    asm("movl %0,%%edi\n\t" : : "m" (buf));
    asm("xorl %edx,%edx\n\t");
    NEH_RNG
    asm("andl $0x0000001f,%eax\n\t");
    asm("movl %%eax,%0\n\t" : "=m" (val));
    asm("popl %edi\n\t");
    return val;
}

static __inline volatile  void via_ecb_op5(
            const void *k, const void *c, const void *s, void *d, int l)
{
    NEH_REKEY;
    asm("movl %0, %%ebx\n\t" : : "m" (k));
    asm("movl %0, %%edx\n\t" : : "m" (c));
    asm("movl %0, %%esi\n\t" : : "m" (s));
    asm("movl %0, %%edi\n\t" : : "m" (d));
    asm("movl %0, %%ecx\n\t" : : "m" (l));
    NEH_ECB;
}

static __inline volatile  void via_cbc_op6(
            const void *k, const void *c, const void *s, void *d, int l, void *v)
{
    NEH_REKEY;
    asm("movl %0, %%ebx\n\t" : : "m" (k));
    asm("movl %0, %%edx\n\t" : : "m" (c));
    asm("movl %0, %%esi\n\t" : : "m" (s));
    asm("movl %0, %%edi\n\t" : : "m" (d));
    asm("movl %0, %%ecx\n\t" : : "m" (l));
    asm("movl %0, %%eax\n\t" : : "m" (v));
    NEH_CBC;
}

static __inline volatile  void via_cbc_op7(
        const void *k, const void *c, const void *s, void *d, int l, void *v, void *w)
{
    NEH_REKEY;
    asm("movl %0, %%ebx\n\t" : : "m" (k));
    asm("movl %0, %%edx\n\t" : : "m" (c));
    asm("movl %0, %%esi\n\t" : : "m" (s));
    asm("movl %0, %%edi\n\t" : : "m" (d));
    asm("movl %0, %%ecx\n\t" : : "m" (l));
    asm("movl %0, %%eax\n\t" : : "m" (v));
    NEH_CBC;
    asm("movl %eax,%esi\n\t");
    asm("movl %0, %%edi\n\t" : : "m" (w));
    asm("movsl; movsl; movsl; movsl\n\t");
}

static __inline volatile  void via_cfb_op6(
            const void *k, const void *c, const void *s, void *d, int l, void *v)
{
    NEH_REKEY;
    asm("movl %0, %%ebx\n\t" : : "m" (k));
    asm("movl %0, %%edx\n\t" : : "m" (c));
    asm("movl %0, %%esi\n\t" : : "m" (s));
    asm("movl %0, %%edi\n\t" : : "m" (d));
    asm("movl %0, %%ecx\n\t" : : "m" (l));
    asm("movl %0, %%eax\n\t" : : "m" (v));
    NEH_CFB;
}

static __inline volatile  void via_cfb_op7(
        const void *k, const void *c, const void *s, void *d, int l, void *v, void *w)
{
    NEH_REKEY;
    asm("movl %0, %%ebx\n\t" : : "m" (k));
    asm("movl %0, %%edx\n\t" : : "m" (c));
    asm("movl %0, %%esi\n\t" : : "m" (s));
    asm("movl %0, %%edi\n\t" : : "m" (d));
    asm("movl %0, %%ecx\n\t" : : "m" (l));
    asm("movl %0, %%eax\n\t" : : "m" (v));
    NEH_CFB;
    asm("movl %eax,%esi\n\t");
    asm("movl %0, %%edi\n\t" : : "m" (w));
    asm("movsl; movsl; movsl; movsl\n\t");
}

static __inline volatile  void via_ofb_op6(
            const void *k, const void *c, const void *s, void *d, int l, void *v)
{
    NEH_REKEY;
    asm("movl %0, %%ebx\n\t" : : "m" (k));
    asm("movl %0, %%edx\n\t" : : "m" (c));
    asm("movl %0, %%esi\n\t" : : "m" (s));
    asm("movl %0, %%edi\n\t" : : "m" (d));
    asm("movl %0, %%ecx\n\t" : : "m" (l));
    asm("movl %0, %%eax\n\t" : : "m" (v));
    NEH_OFB;
}

#endif

static __inline int via_rng_available(void)
{
    return (via_flags & NEH_CPU_READ)
        ? (via_flags & NEH_CPU_IS_VIA) ? (read_via_flags() & NEH_RNG_AVAILABLE) : 0
        : has_cpuid() && is_via_cpu() && (read_via_flags() & NEH_RNG_AVAILABLE);
}

static __inline int via_ace_available(void)
{
    return (via_flags & NEH_CPU_READ)
        ? (via_flags & NEH_CPU_IS_VIA) ? (read_via_flags() & NEH_ACE_AVAILABLE) : 0
        : has_cpuid() && is_via_cpu() && (read_via_flags() & NEH_ACE_AVAILABLE);
}

static __inline int read_via_rng(void *buf, int count)
{   union
    {   long long       dummy;      /* force an aligned buffer      */
        unsigned char   bp[64];
    } aligned_buf;
    unsigned char   *p, *q;
    int             nbr, max_reads, lcnt = count;
    
    if(!via_rng_available()) return 0;

    do
    {
        max_reads = MAX_READ_ATTEMPTS;
        do
            nbr = via_rng_in(aligned_buf.bp);
        while
            (nbr == 0 && --max_reads);

        lcnt -= nbr;
        p = (unsigned char*)buf; q = aligned_buf.bp; 
        while(nbr--)
            *p++ = *q++;
    }
    while
        (lcnt && max_reads);

    return count - lcnt;
}


