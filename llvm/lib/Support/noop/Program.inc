//===- llvm/Support/Unix/Program.cpp -----------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the Unix specific portion of the Program class.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//=== WARNING: Implementation here must contain only generic UNIX code that
//===          is guaranteed to work on *all* UNIX variants.
//===----------------------------------------------------------------------===//

#include "llvm/Support/Program.h"

#include "noop.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/Config/config.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Errc.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/StringSaver.h"
#include "llvm/Support/raw_ostream.h"


using namespace llvm;
using namespace sys;

ProcessInfo::ProcessInfo() : Pid(0), ReturnCode(0) {}

ErrorOr<std::string> sys::findProgramByName(StringRef Name,
                                            ArrayRef<StringRef> Paths) {
  return errc::no_such_file_or_directory;
}

static bool Execute(ProcessInfo &PI, StringRef Program,
                    ArrayRef<StringRef> Args, Optional<ArrayRef<StringRef>> Env,
                    ArrayRef<Optional<StringRef>> Redirects,
                    unsigned MemoryLimit, std::string *ErrMsg,
                    BitVector *AffinityMask) {
  return false;
}

ProcessInfo llvm::sys::Wait(const ProcessInfo &PI, unsigned SecondsToWait,
                            bool WaitUntilTerminates, std::string *ErrMsg,
                            Optional<ProcessStatistics> *ProcStat) {
  return ProcessInfo{};
}

std::error_code llvm::sys::ChangeStdinMode(fs::OpenFlags Flags){
  return std::error_code();
}

std::error_code llvm::sys::ChangeStdoutMode(fs::OpenFlags Flags){
  return std::error_code();
}

std::error_code llvm::sys::ChangeStdinToBinary() {
  return std::error_code();
}

std::error_code llvm::sys::ChangeStdoutToBinary() {
  return std::error_code();
}

std::error_code
llvm::sys::writeFileWithEncoding(StringRef FileName, StringRef Contents,
                                 WindowsEncodingMethod Encoding /*unused*/) {
  return make_error_code(errc::io_error);
}

bool llvm::sys::commandLineFitsWithinSystemLimits(StringRef Program,
                                                  ArrayRef<StringRef> Args) {
  return false;
}
