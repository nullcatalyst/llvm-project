//===- Signals.cpp - Generic Unix Signals Implementation -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines some helpful functions for dealing with the possibility of
// Unix signals occurring while your program is running.
//
//===----------------------------------------------------------------------===//
//
// This file is extremely careful to only do signal-safe things while in a
// signal handler. In particular, memory allocation and acquiring a mutex
// while in a signal handler should never occur. ManagedStatic isn't usable from
// a signal handler for 2 reasons:
//
//  1. Creating a new one allocates.
//  2. The signal handler could fire while llvm_shutdown is being processed, in
//     which case the ManagedStatic is in an unknown state because it could
//     already have been destroyed, or be in the process of being destroyed.
//
// Modifying the behavior of the signal handlers (such as registering new ones)
// can acquire a mutex, but all this guarantees is that the signal handler
// behavior is only modified by one thread at a time. A signal handler can still
// fire while this occurs!
//
// Adding work to a signal handler requires lock-freedom (and assume atomics are
// always lock-free) because the signal handler could fire while new work is
// being added.
//
//===----------------------------------------------------------------------===//

#include "noop.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Config/config.h"
#include "llvm/Demangle/Demangle.h"
#include "llvm/Support/ExitCodes.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/FileUtilities.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/Mutex.h"
#include "llvm/Support/Program.h"
#include "llvm/Support/SaveAndRestore.h"
#include "llvm/Support/raw_ostream.h"
#include <algorithm>
#include <string>

using namespace llvm;

void sys::unregisterHandlers() {}

void sys::CleanupOnSignal(uintptr_t Context) {}

void llvm::sys::RunInterruptHandlers() {}

void llvm::sys::SetInterruptFunction(void (*IF)()) {}

void llvm::sys::SetInfoSignalFunction(void (*Handler)()) {}

void llvm::sys::SetOneShotPipeSignalFunction(void (*Handler)()) {}

void llvm::sys::DefaultOneShotPipeSignalHandler() {
  // Send a special return code that drivers can check for, from sysexits.h.
  // exit(EX_IOERR);
  abort();
}

// The public API
bool llvm::sys::RemoveFileOnSignal(StringRef Filename,
                                   std::string* ErrMsg) {
  return false;
}

// The public API
void llvm::sys::DontRemoveFileOnSignal(StringRef Filename) {}

/// Add a function to be called when a signal is delivered to the process. The
/// handler can have a cookie passed to it to identify what instance of the
/// handler it is.
void llvm::sys::AddSignalHandler(sys::SignalHandlerCallback FnPtr,
                                 void *Cookie) {}

/// This platform does not have dl_iterate_phdr, so we do not yet know how to
/// find all loaded DSOs.
static bool findModulesAndOffsets(void **StackTrace, int Depth,
                                  const char **Modules, intptr_t *Offsets,
                                  const char *MainExecutableName,
                                  StringSaver &StrPool) {
  return false;
}

// In the case of a program crash or fault, print out a stack trace so that the
// user has an indication of why and where we died.
//
// On glibc systems we have the 'backtrace' function, which works nicely, but
// doesn't demangle symbols.
void llvm::sys::PrintStackTrace(raw_ostream &OS, int Depth) {}

void llvm::sys::DisableSystemDialogsOnCrash() {}

void llvm::sys::PrintStackTraceOnErrorSignal(StringRef Argv0,
                                             bool DisableCrashReporting) {}
