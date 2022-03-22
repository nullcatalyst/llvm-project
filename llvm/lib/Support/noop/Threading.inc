//===- Unix/Threading.inc - Unix Threading Implementation ----- -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides the Unix specific implementation of Threading functions.
//
//===----------------------------------------------------------------------===//

#include "noop.h"
#include "llvm/ADT/ScopeExit.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/Twine.h"

namespace llvm {

pthread_t
llvm_execute_on_thread_impl(void *(*ThreadFunc)(void *), void *Arg,
                            llvm::Optional<unsigned> StackSizeInBytes) {
  return 0;
}

void llvm_thread_detach_impl(pthread_t Thread) {}

void llvm_thread_join_impl(pthread_t Thread) {}

pthread_t llvm_thread_get_id_impl(pthread_t Thread) {
  return Thread;
}

pthread_t llvm_thread_get_current_id_impl() {
  return 0;
}

} // namespace llvm

uint64_t llvm::get_threadid() {
  return uint64_t(0);
}


static constexpr uint32_t get_max_thread_name_length_impl() {
  return 0;
}

uint32_t llvm::get_max_thread_name_length() {
  return get_max_thread_name_length_impl();
}

void llvm::set_thread_name(const Twine &Name) {}

void llvm::get_thread_name(SmallVectorImpl<char> &Name) {
  Name.clear();
}

SetThreadPriorityResult llvm::set_thread_priority(ThreadPriority Priority) {
  return SetThreadPriorityResult::FAILURE;
}

int computeHostNumHardwareThreads() {
  return 1;
}

void llvm::ThreadPoolStrategy::apply_thread_strategy(
    unsigned ThreadPoolNum) const {}

llvm::BitVector llvm::get_thread_affinity_mask() {
  // FIXME: Implement
  llvm_unreachable("Not implemented!");
}

unsigned llvm::get_cpus() { return 1; }
