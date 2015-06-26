/* ==========================================================================
 * features.h - Preprocessor-based feature detection
 * --------------------------------------------------------------------------
 * Copyright (c) 2015  William Ahern
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ==========================================================================
 */
#ifndef FEATURES_H
#define FEATURES_H

/*
 * C O M P I L E R  D E T E C T I O N
 *
 * See http://sourceforge.net/p/predef/wiki/Compilers/
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define GNUC_2VER(M, m, p) (((M) * 10000) + ((m) * 100) + (p))
#define GNUC_PREREQ(M, m, p) (defined __GNUC__ && GNUC_2VER(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__) >= GNUC_2VER((M), (m), (p)))

#define MSC_2VER(M, m, p) ((((M) + 6) * 10000000) + ((m) * 1000000) + (p))
#define MSC_PREREQ(M, m, p) (defined _MSC_VER_FULL && _MSC_VER_FULL >= MSC_2VER((M), (m), (p)))

#define SUNPRO_PREREQ(M, m, p) (defined __SUNPRO_C && __SUNPRO_C >= 0x ## M ## m ## p)

#if defined __has_extension
#define has_extension(...) __has_extension(...)
#else
#define has_extension(...) 0
#endif

#if defiend __has_include
#define has_include(...) __has_include(...)
#else
#define has_include(...) 0
#endif


/*
 * C O M P I L E R / L A N G U A G E  D E T E C T I O N
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef HAVE_C___ATTRIBUTE__
#define HAVE_C___ATTRIBUTE__ (__GNUC__)
#endif

#ifndef HAVE_C___ATTRIBUTE___UNUSED
#define HAVE_C___ATTRIBUTE___UNUSED (__GNUC__)
#endif

#ifndef HAVE_C___ATTRIBUTE___VISIBILITY
#define HAVE_C___ATTRIBUTE___VISIBILITY (__GNUC__ || SUNPRO_PREREQ(5,9,0))
#endif

#ifndef HAVE_C__GENERIC
#define HAVE_C__GENERIC (GNUC_PREREQ(4,9,0) || has_extension(c_generic_selections) || __STDC_VERSION__ >= 201112L)
#endif

#ifndef HAVE_C___HAS_EXTENSION
#define HAVE_C___HAS_EXTENSION (defined __has_extension)
#endif

#ifndef HAVE_C___HAS_INCLUDE
#define HAVE_C___HAS_INCLUDE (defined __has_include)
#endif

#ifndef HAVE_C___EXTENSION__
#define HAVE_C___EXTENSION__ (__GNUC__)
#endif

#ifndef HAVE_C___TYPEOF__
#define HAVE_C___TYPEOF__ (__GNUC__)
#endif

#ifndef HAVE___BUILTIN_UNREACHABLE
#define HAVE___BUILTIN_UNREACHABLE (GNUC_PREPREQ(4,5,0) || __clang__)
#endif

#ifndef HAVE__STATIC_ASSERT
#define HAVE__STATIC_ASSERT (GNUC_PREREQ(4,6,0) || has_extension(c_static_assert) || defined __C11FEATURES__ || __STDC_VERSION__ >= 201112L)
#endif


/*
 * L I B C  D E T E C T I O N
 *
 * See http://sourceforge.net/p/predef/wiki/Libraries/
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <limits.h> /* <features.h> __GLIBC__ __GLIBC_PREREQ __UCLIBC__ */

#ifndef HAVE_SYS_FEATURE_TESTS_H
#define HAVE_SYS_FEATURE_TESTS_H (defined __sun || has_include(<sys/feature_tests.h>))
#endif

#if HAVE_SYS_FEATURE_TESTS_H
#include <sys/feature_tests.h> /* _DTRACE_VERSION */
#endif

#ifndef HAVE_SYS_PARAM_H
#define HAVE_SYS_PARAM_H \
	(has_include(<sys/param.h>) || defined BSD || defined __GLIBC__ || \
	 defined __APPLE__ || defined __DragonFly__ || defined __FreeBSD__ || \
	 defined __NetBSD__ || defined __OpenBSD__ || defined __bsdi__)
#endif

#if HAVE_SYS_PARAM_H
#include <sys/param.h> /* __FreeBSD_version __NetBSD_Prereq__ BSD OpenBSD */
#endif

#include <fcntl.h> /* F_DUPFD_CLOEXEC */


#define AIX_PREREQ(M, m) (_AIX # M # m)

#if defined __GLIBC_PREREQ && !defined __UCLIBC__
#define GLIBC_PREREQ(M, m) (__GLIBC_PREREQ(M, m))
#else
#define GLIBC_PREREQ(M, m) 0
#endif

#define FREEBSD_2VER(M, m, p) (((M) * 100000) + ((m) * 1000) + (p))
#define FREEBSD_PREREQ(M, m, p) (defined __FreeBSD__ && __FreeBSD_version >= FREEBSD_2VER((M), (m), (p)))

#define MUSL_MAYBE (defined __linux && !defined __GLIBC__ && !defined __BIONIC__)

#if defined __NetBSD_Prereq__
#define NETBSD_PREREQ(M, m, p) __NetBSD_Prereq__(M, m, p)
#else
#define NETBSD_PREREQ(M, m, p) 0
#endif

#define SUNOS_PREREQ_5_10 (defined __sun && defined _DTRACE_VERSION)
#define SUNOS_PREREQ_5_11 (defined __sun && defined F_DUPFD_CLOEXEC)
#define SUNOS_PREREQ(M, m) (SUNOS_PREREQ_ ## M ## _ ## m)

#define UCLIBC_2VER(M, m, p) (((M) * 10000) + ((m) * 100) + (p))
#define UCLIBC_PREREQ(M, m, p) (defined __UCLIBC__ && UCLIBC_2VER(__UCLIBC_MAJOR__, __UCLIBC_MINOR__, __UCLIBC_SUBLEVEL__) >= UCLIBC_2VER((M), (m), (p)))


/*
 * H E A D E R  D E T E C T I O N
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef HAVE_DLFCN_H
#define HAVE_DLFCN_H (has_include(<dlfcn.h>) || (!HAVE_C___HAS_INCLUDE && 1))
#endif

#ifndef HAVE_IFADDRS_H
#define HAVE_IFADDRS_H_ (!defined _AIX && (!defined __sun || SUNOS_PREREQ(5,11))
#define HAVE_IFADDRS_H (has_include(<ifaddrs.h>) || (!HAVE_C___HAS_INCLUDE && HAVE_IFADDRS_H_))
#endif

#ifndef HAVE_MACH_CLOCK_H
#define HAVE_MACH_CLOCK_H (has_include(<mach/clock.h>) || (!HAVE_C___HAS_INCLUDE && defined __APPLE__))
#endif

#ifndef HAVE_MACH_MACH_H
#define HAVE_MACH_MACH_H (has_include(<mach/mach.h>) || (!HAVE_C___HAS_INCLUDE && defined __APPLE__))
#endif

#ifndef HAVE_MACH_MACH_TIME_H
#define HAVE_MACH_MACH_TIME_H (has_include(<mach/mach_time.h>) || (!HAVE_C___HAS_INCLUDE && defined __APPLE__))
#endif

#ifndef HAVE_SYS_EPOLL_H
#define HAVE_SYS_EPOLL_H (has_include(<sys/epoll.h>) || (!HAVE_C___HAS_INCLUDE && defined __linux))
#endif

#ifndef HAVE_SYS_EVENT_H
#define HAVE_SYS_EVENT_H (has_include(<sys/event.h>) || (!HAVE_C___HAS_INCLUDE && defined BSD))
#endif

#ifndef HAVE_SYS_EVENTFD_H
#define HAVE_SYS_EVENTFD_H (has_include(<sys/eventfd.h>) || (!HAVE_C___HAS_INCLUDE && defined __linux))
#endif

#ifndef HAVE_SYS_INOTIFY_H
#define HAVE_SYS_INOTIFY_H (has_include(<sys/inotify.h>) || (!HAVE_C___HAS_INCLUDE && defined __linux))
#endif

#ifndef HAVE_SYS_PROCFS_H
#define HAVE_SYS_PROCFS_H (has_include(<sys/procfs.h>) || (!HAVE_C___HAS_INCLUDE && defined _AIX))
#endif

#ifndef HAVE_SYS_SIGNALFD_H
#define HAVE_SYS_SIGNALFD_H (has_include(<sys/signalfd.h>) || (!HAVE_C___HAS_INCLUDE && defined __linux))
#endif

#ifndef HAVE_SYS_SOCKIO_H
#define HAVE_SYS_SOCKIO_H (has_include(<sys/sockio.h>) || (!HAVE_C___HAS_INCLUDE && defined __sun))
#endif

#ifndef HAVE_SYS_SYSCTL_H
#define HAVE_SYS_SYSCTL_H_ (defined BSD || defined __GLIBC__)
#define HAVE_SYS_SYSCTL_H (has_include(<sys/sysctl.h>) || (!HAVE_C___HAS_INCLUDE && HAVE_SYS_SYSCTL_H_))
#endif

#ifndef HAVE_SYS_TIMERFD_H
#define HAVE_SYS_TIMERFD_H (has_include(<sys/timerfd.h>) || (!HAVE_C___HAS_INCLUDE && defined __linux))
#endif


/*
 * T Y P E  D E T E C T I O N
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef HAVE_STRUCT_SOCKADDR_SA_LEN
#define HAVE_STRUCT_SOCKADDR_SA_LEN (!defined __linux && !defined __sun)
#endif


/*
 * V A R I A B L E  D E T E C T I O N
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef HAVE__LIBC_ENABLE_SECURE
#define HAVE__LIBC_ENABLE_SECURE GLIBC_PREREQ(2,1) /* added to glibc between 2.0.98 and 2.0.99 */
#endif

#ifndef HAVE_PROGRAM_INVOCATION_SHORT_NAME
#define HAVE_PROGRAM_INVOCATION_SHORT_NAME (defined __linux)
#endif


/*
 * F U N C T I O N  D E T E C T I O N
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef HAVE_ACCEPT4
#define HAVE_ACCEPT4 (defined SOCK_CLOEXEC && !__NetBSD__)
#endif

#ifndef HAVE_ARC4RANDOM
#define HAVE_ARC4RANDOM \
	(defined __APPLE__ || defined __DragonFly__ || defined __FreeBSD__ || \
	 defined __NetBSD__ || defined __OpenBSD__)
#endif

#ifndef HAVE_ARC4RANDOM_ADDRANDOM
#define HAVE_ARC4RANDOM_ADDRANDOM (HAVE_ARC4RANDOM && OpenBSD < 201405)
#endif

#ifndef HAVE_ARC4RANDOM_STIR
#define HAVE_ARC4RANDOM_STIR HAVE_ARC4RANDOM_ADDRANDOM
#endif

#ifndef HAVE_DLADDR
#define HAVE_DLADDR (HAVE_DLOPEN && !defined _AIX && ((!__GLIBC__ && !MUSL_MAYBE) || _GNU_SOURCE))
#endif

#ifndef HAVE_DLOPEN
#define HAVE_DLOPEN HAVE_DLFCN_H
#endif

#ifndef HAVE_DLSYM
#define HAVE_DLSYM HAVE_DLOPEN
#endif

#ifndef HAVE_DUP3
#define HAVE_DUP3 (GLIBC_PREREQ(2,9) || FREEBSD_PREREQ(10,0) || NETBSD_PREREQ(6,0) || UCLIBC_PREREQ(0,9,34) || MUSL_MAYBE || __BIONIC__)
#endif

#ifndef HAVE_FDOPENDIR
#define HAVE_FDOPENDIR (!defined __APPLE__ && (!defined __NetBSD__ || NETBSD_PREREQ(6,0)))
#endif

#ifndef HAVE_EPOLL_CREATE
#define HAVE_EPOLL_CREATE HAVE_SYS_EPOLL_H
#endif

#ifndef HAVE_EPOLL_CREATE1
#define HAVE_EPOLL_CREATE1 (HAVE_EPOLL_CREATE && defined EPOLL_CLOEXEC)
#endif

#ifndef HAVE_EPOLL_CTL
#define HAVE_EPOLL_CTL HAVE_EPOLL_CREATE
#endif

#ifndef HAVE_EPOLL_PWAIT
#define HAVE_EPOLL_PWAIT 0
#endif

#ifndef HAVE_EPOLL_WAIT
#define HAVE_EPOLL_WAIT HAVE_EPOLL_CREATE
#endif

#ifndef HAVE_EVENTFD
#define HAVE_EVENTFD HAVE_SYS_EVENTFD_H
#endif

#ifndef HAVE_INOTIFY_INIT
#define HAVE_INOTIFY_INIT HAVE_SYS_INOTIFY_H
#endif

#ifndef HAVE_INOTIFY_INIT1
#define HAVE_INOTIFY_INIT1 (HAVE_INOTIFY_INIT && defined IN_CLOEXEC)
#endif

#ifndef HAVE_GETAUXVAL
#define HAVE_GETAUXVAL GLIBC_PREREQ(2,16)
#endif

#ifndef HAVE_GETEXECNAME
#define HAVE_GETEXECNAME (defined __sun)
#endif

#ifndef HAVE_GETIFADDRS
#define HAVE_GETIFADDRS HAVE_IFADDRS_H
#endif

#ifndef HAVE_GETPROGNAME
#define HAVE_GETPROGNAME HAVE_ARC4RANDOM
#endif

#ifndef HAVE_ISSETUGID
#define HAVE_ISSETUGID (!defined __linux && !defined _AIX)
#endif

#if HAVE_SYS_EVENT_H
#include <sys/event.h>
#endif

#ifndef HAVE_KEVENT
#define HAVE_KEVENT (defined EV_SET)
#endif

#ifndef HAVE_KQUEUE
#define HAVE_KQUEUE HAVE_KEVENT
#endif

#ifndef HAVE_KQUEUE1
#define HAVE_KQUEUE1 (HAVE_KQUEUE && NETBSD_PREREQ(6,0,0))
#endif

#ifndef HAVE_PIPE2
#define HAVE_PIPE2 (GLIBC_PREREQ(2,9) || FREEBSD_PREREQ(10,0) || NETBSD_PREREQ(6,0) || UCLIBC_PREREQ(0,9,32) || MUSL_MAYBE || __BIONIC__)
#endif

#ifndef HAVE_POSIX_FADVISE
#define HAVE_POSIX_FADVISE GLIBC_PREREQ(2,2)
#endif

#ifndef HAVE_POSIX_FALLOCATE
#define HAVE_POSIX_FALLOCATE GLIBC_PREREQ(2,2)
#endif

#ifndef HAVE_SIGNALFD
#define HAVE_SIGNALFD HAVE_SYS_SIGNALFD_H
#endif

#ifndef HAVE_SIGTIMEDWAIT
#define HAVE_SIGTIMEDWAIT (!defined __APPLE__ && !defined __OpenBSD__)
#endif

#include <assert.h> /* static_assert */

#ifndef HAVE_STATIC_ASSERT
#if GNUC_PREREQ(0,0,0) && !GNUC_PREREQ(4,6,0)
#define HAVE_STATIC_ASSERT 0 /* glibc doesn't check GCC version */
#else
#define HAVE_STATIC_ASSERT (defined static_assert)
#endif

#ifndef HAVE_SYSCTL
#define HAVE_SYSCTL HAVE_SYS_SYSCTL_H
#endif

#ifndef HAVE_TIMERFD_CREATE
#define HAVE_TIMERFD_CREATE HAVE_SYS_TIMERFD_H
#endif

#ifndef HAVE_TIMERFD_GETTIME
#define HAVE_TIMERFD_GETTIME HAVE_TIMERFD_CREATE
#endif

#ifndef HAVE_TIMERFD_SETTIME
#define HAVE_TIMERFD_SETTIME HAVE_TIMERFD_CREATE
#endif

#ifndef STRERROR_R_CHAR_P
#define STRERROR_R_CHAR_P ((GLIBC_PREREQ(0,0) || UCLIBC_PREREQ(0,0,0)) && (_GNU_SOURCE || !(_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600)))
#endif


#endif /* FEATURES_H */
