//===- llvm/Support/Unix/Host.inc -------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the UNIX Host support.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//=== WARNING: Implementation here must contain only generic UNIX code that
//===          is guaranteed to work on *all* UNIX variants.
//===----------------------------------------------------------------------===//

#include "noop.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Config/config.h"
#include <cctype>
#include <string>
#include <sys/utsname.h>

using namespace llvm;

static std::string updateTripleOSVersion(std::string TargetTripleString) {
  return TargetTripleString;
}

std::string sys::getDefaultTargetTriple() {
  return updateTripleOSVersion(LLVM_DEFAULT_TARGET_TRIPLE);
}
