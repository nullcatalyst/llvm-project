//===- Unix/Process.cpp - Unix Process Implementation --------- -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides the generic Unix implementation of the Process class.
//
//===----------------------------------------------------------------------===//

#include "noop.h"
#include "llvm/ADT/Hashing.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Config/config.h"
#include "llvm/Support/ManagedStatic.h"
#include <mutex>

//===----------------------------------------------------------------------===//
//=== WARNING: Implementation here must contain only generic UNIX code that
//===          is guaranteed to work on *all* UNIX variants.
//===----------------------------------------------------------------------===//

using namespace llvm;
using namespace sys;

Process::Pid Process::getProcessId() {
  static_assert(sizeof(Pid) >= sizeof(pid_t),
                "Process::Pid should be big enough to store pid_t");
  return Pid(0);
}

Expected<unsigned> Process::getPageSize() {
  return static_cast<unsigned>(1 << 16);
}

size_t Process::GetMallocUsage() {
  return 0;
}

void Process::GetTimeUsage(TimePoint<> &elapsed, std::chrono::nanoseconds &user_time,
                           std::chrono::nanoseconds &sys_time) {}

void Process::PreventCoreFiles() {
  coreFilesPrevented = true;
}

Optional<std::string> Process::GetEnv(StringRef Name) {
  return None;
}

namespace {
class FDCloser {
public:
  FDCloser(int &FD) : KeepOpen(false) {}
  void keepOpen() { KeepOpen = true; }
  ~FDCloser() = default;

private:
  FDCloser(const FDCloser &) = delete;
  void operator=(const FDCloser &) = delete;

  bool KeepOpen;
};
}

std::error_code Process::FixupStandardFileDescriptors() {
  return make_error_code(errc::function_not_supported);
}

std::error_code Process::SafelyCloseFileDescriptor(int FD) {
  return make_error_code(errc::function_not_supported);
}

bool Process::StandardInIsUserInput() {
  return false;
}

bool Process::StandardOutIsDisplayed() {
  return false;
}

bool Process::StandardErrIsDisplayed() {
  return false;
}

bool Process::FileDescriptorIsDisplayed(int fd) {
  return false;
}

unsigned Process::StandardOutColumns() {
    return 0;
}

unsigned Process::StandardErrColumns() {
  return 0;
}

bool Process::FileDescriptorHasColors(int fd) {
  return false;
}

bool Process::StandardOutHasColors() {
  return false;
}

bool Process::StandardErrHasColors() {
  return false;
}

void Process::UseANSIEscapeCodes(bool /*enable*/) {
  // No effect.
}

bool Process::ColorNeedsFlush() {
  // No, we use ANSI escape sequences.
  return false;
}

const char *Process::OutputColor(char code, bool bold, bool bg) {
  return colorcodes[bg?1:0][bold?1:0][code&7];
}

const char *Process::OutputBold(bool bg) {
  return "";
}

const char *Process::OutputReverse() {
  return "";
}

const char *Process::ResetColor() {
  return "";
}

unsigned llvm::sys::Process::GetRandomNumber() {
  return 0;
}

LLVM_ATTRIBUTE_NORETURN
void Process::ExitNoCleanup(int RetCode) {
  abort();
  // _Exit(RetCode);
}
