//===- Unix/Memory.cpp - Generic UNIX System Configuration ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines some functions for various memory management utilities.
//
//===----------------------------------------------------------------------===//

#include "noop.h"
#include "llvm/Config/config.h"
#include "llvm/Support/Alignment.h"
#include "llvm/Support/DataTypes.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/Process.h"

namespace llvm {
namespace sys {

MemoryBlock
Memory::allocateMappedMemory(size_t NumBytes,
                             const MemoryBlock *const NearBlock,
                             unsigned PFlags,
                             std::error_code &EC) {
  EC = make_error_code(errc::function_not_supported);
  return MemoryBlock{};
}

std::error_code
Memory::releaseMappedMemory(MemoryBlock &M) {
  return make_error_code(errc::function_not_supported);
}

std::error_code
Memory::protectMappedMemory(const MemoryBlock &M, unsigned Flags) {
  return make_error_code(errc::function_not_supported);
}

/// InvalidateInstructionCache - Before the JIT can run a block of code
/// that has been emitted it must invalidate the instruction cache on some
/// platforms.
void Memory::InvalidateInstructionCache(const void *Addr,
                                        size_t Len) {}

} // namespace sys
} // namespace llvm
