#pragma once

#ifdef FAST_MODE
#define VECTORADD_ARGS()                                                                                               \
  ->Arg(512)->Arg(2048)->Arg(8192)->Arg(32768)->Arg(131072)->Arg(524288)->Arg(2097152)->Arg(8388608)->Arg(33554432)
#else // FAST_MODE
#define VECTORADD_ARGS()                                                                                               \
  Arg(256)                                                                                                             \
      ->Arg(512)                                                                                                       \
      ->Arg(1024)                                                                                                      \
      ->Arg(2048)                                                                                                      \
      ->Arg(4096)                                                                                                      \
      ->Arg(8192)                                                                                                      \
      ->Arg(16384)                                                                                                     \
      ->Arg(32768)                                                                                                     \
      ->Arg(65536)                                                                                                     \
      ->Arg(131072)                                                                                                    \
      ->Arg(262144)                                                                                                    \
      ->Arg(524288)                                                                                                    \
      ->Arg(1048576)                                                                                                   \
      ->Arg(2097152)                                                                                                   \
      ->Arg(4194304)                                                                                                   \
      ->Arg(8388608)                                                                                                   \
      ->Arg(16777216)                                                                                                  \
      ->Arg(33554432)                                                                                                  \
      ->Arg(67108864)                                                                                                  \
      ->Arg(134217728)                                                                                                 \
      ->Arg(268435456)                                                                                                 \
      ->Arg(536870912)                                                                                                 \
      ->Arg(1073741824)
#endif // FAST_MODE