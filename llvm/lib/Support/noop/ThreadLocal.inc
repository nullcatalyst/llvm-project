//=== llvm/Support/Unix/ThreadLocal.inc - Unix Thread Local Data -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the Unix specific (non-pthread) ThreadLocal class.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//=== WARNING: Implementation here must contain only generic UNIX code that
//===          is guaranteed to work on *all* UNIX variants.
//===----------------------------------------------------------------------===//

#include "llvm/Config/config.h"

namespace llvm {
using namespace sys;

ThreadLocalImpl::ThreadLocalImpl() : data() {}

ThreadLocalImpl::~ThreadLocalImpl() {}

void ThreadLocalImpl::setInstance(const void* d) {
  memcpy(data, d, sizeof(data));
}

void *ThreadLocalImpl::getInstance() {
  return data;
}

void ThreadLocalImpl::removeInstance() {
  setInstance(0);
}

}
