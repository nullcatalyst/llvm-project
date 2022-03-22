//===- llvm/Support/Unix/Path.inc - Unix Path Implementation ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the Unix specific implementation of the Path API.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//=== WARNING: Implementation here must contain only generic UNIX code that
//===          is guaranteed to work on *all* UNIX variants.
//===----------------------------------------------------------------------===//

#include "noop.h"
#include <limits.h>
#include <stdio.h>

// Both stdio.h and cstdio are included via different paths and
// stdcxx's cstdio doesn't include stdio.h, so it doesn't #undef the macros
// either.
#undef ferror
#undef feof

using namespace llvm;

namespace llvm {
namespace sys  {
namespace fs {

const file_t kInvalidFile = -1;

std::string getMainExecutable(const char *argv0, void *MainAddr) {
  return "";
}

TimePoint<> basic_file_status::getLastAccessedTime() const {
  return toTimePoint(0, 0);
}

TimePoint<> basic_file_status::getLastModificationTime() const {
  return toTimePoint(0, 0);
}

UniqueID file_status::getUniqueID() const {
  return UniqueID{};
}

uint32_t file_status::getLinkCount() const {
  return 0;
}

ErrorOr<space_info> disk_space(const Twine &Path) {
  return make_error_code(errc::function_not_supported);
  // return space_info{};
}

std::error_code current_path(SmallVectorImpl<char> &result) {
  return make_error_code(errc::function_not_supported);
}

std::error_code set_current_path(const Twine &path) {
  return make_error_code(errc::function_not_supported);
}

std::error_code create_directory(const Twine &path, bool IgnoreExisting,
                                 perms Perms) {
  return make_error_code(errc::function_not_supported);
}

std::error_code create_link(const Twine &to, const Twine &from) {
  return make_error_code(errc::function_not_supported);
}

std::error_code create_hard_link(const Twine &to, const Twine &from) {
  return make_error_code(errc::function_not_supported);
}

std::error_code remove(const Twine &path, bool IgnoreNonExisting) {
  return make_error_code(errc::function_not_supported);
}

std::error_code is_local(const Twine &Path, bool &Result) {
  return make_error_code(errc::function_not_supported);
}

std::error_code is_local(int FD, bool &Result) {
  return make_error_code(errc::function_not_supported);
}

std::error_code rename(const Twine &from, const Twine &to) {
  return make_error_code(errc::function_not_supported);
}

std::error_code resize_file(int FD, uint64_t Size) {
  return make_error_code(errc::function_not_supported);
}

std::error_code access(const Twine &Path, AccessMode Mode) {
  return make_error_code(errc::function_not_supported);
}

bool can_execute(const Twine &Path) {
  return false;
}

bool equivalent(file_status A, file_status B) {
  return false;
}

std::error_code equivalent(const Twine &A, const Twine &B, bool &result) {
  return make_error_code(errc::function_not_supported);
}

void expand_tilde(const Twine &path, SmallVectorImpl<char> &dest) {}

std::error_code status(const Twine &Path, file_status &Result, bool Follow) {
  return make_error_code(errc::function_not_supported);
}

std::error_code status(int FD, file_status &Result) {
  return make_error_code(errc::function_not_supported);
}

unsigned getUmask() {
  return 0;
}

std::error_code setPermissions(const Twine &Path, perms Permissions) {
  return make_error_code(errc::function_not_supported);
}

std::error_code setPermissions(int FD, perms Permissions) {
  return make_error_code(errc::function_not_supported);
}

std::error_code setLastAccessAndModificationTime(int FD, TimePoint<> AccessTime,
                                                 TimePoint<> ModificationTime) {
  return make_error_code(errc::function_not_supported);
}

std::error_code mapped_file_region::init(int FD, uint64_t Offset,
                                         mapmode Mode) {
  return make_error_code(errc::function_not_supported);
}

mapped_file_region::mapped_file_region(int fd, mapmode mode, size_t length,
                                       uint64_t offset, std::error_code &ec)
    : Size(length), Mode(mode) {
}

void mapped_file_region::unmapImpl() {}

int mapped_file_region::alignment() {
  return Process::getPageSizeEstimate();
}

std::error_code detail::directory_iterator_construct(detail::DirIterState &it,
                                                     StringRef path,
                                                     bool follow_symlinks) {
  return make_error_code(errc::function_not_supported);
}

std::error_code detail::directory_iterator_destruct(detail::DirIterState &it) {
  return make_error_code(errc::function_not_supported);
}

std::error_code detail::directory_iterator_increment(detail::DirIterState &It) {
  return make_error_code(errc::function_not_supported);
}

ErrorOr<basic_file_status> directory_entry::status() const {
  return make_error_code(errc::function_not_supported);
}

std::error_code openFile(const Twine &Name, int &ResultFD,
                         CreationDisposition Disp, FileAccess Access,
                         OpenFlags Flags, unsigned Mode) {
  return make_error_code(errc::function_not_supported);
}

Expected<int> openNativeFile(const Twine &Name, CreationDisposition Disp,
                             FileAccess Access, OpenFlags Flags,
                             unsigned Mode) {
  return kInvalidFile;
}

std::error_code openFileForRead(const Twine &Name, int &ResultFD,
                                OpenFlags Flags,
                                SmallVectorImpl<char> *RealPath) {
  return make_error_code(errc::function_not_supported);
}

Expected<file_t> openNativeFileForRead(const Twine &Name, OpenFlags Flags,
                                       SmallVectorImpl<char> *RealPath) {
  file_t ResultFD;
  std::error_code EC = openFileForRead(Name, ResultFD, Flags, RealPath);
  if (EC)
    return errorCodeToError(EC);
  return ResultFD;
}

file_t getStdinHandle() { return 0; }
file_t getStdoutHandle() { return 1; }
file_t getStderrHandle() { return 2; }

Expected<size_t> readNativeFile(file_t FD, MutableArrayRef<char> Buf) {
  return 0;
}

Expected<size_t> readNativeFileSlice(file_t FD, MutableArrayRef<char> Buf,
                                     uint64_t Offset) {
  return 0;
}

std::error_code tryLockFile(int FD, std::chrono::milliseconds Timeout) {
  return make_error_code(errc::function_not_supported);
}

std::error_code lockFile(int FD) {
  return make_error_code(errc::function_not_supported);
}

std::error_code unlockFile(int FD) {
  return make_error_code(errc::function_not_supported);
}

std::error_code closeFile(file_t &F) {
  return make_error_code(errc::function_not_supported);
}

template <typename T>
static std::error_code remove_directories_impl(const T &Entry,
                                               bool IgnoreErrors) {
  return make_error_code(errc::function_not_supported);
}

std::error_code remove_directories(const Twine &path, bool IgnoreErrors) {
  return make_error_code(errc::function_not_supported);
}

std::error_code real_path(const Twine &path, SmallVectorImpl<char> &dest,
                          bool expand_tilde) {
  return make_error_code(errc::function_not_supported);
}

std::error_code changeFileOwnership(int FD, uint32_t Owner, uint32_t Group) {
  return make_error_code(errc::function_not_supported);
}

} // end namespace fs

namespace path {

bool home_directory(SmallVectorImpl<char> &result) {
  return false;
}

bool user_config_directory(SmallVectorImpl<char> &result) {
  return false;
}

bool cache_directory(SmallVectorImpl<char> &result) {
  return false;
}

void system_temp_directory(bool ErasedOnReboot, SmallVectorImpl<char> &Result) {
  Result.clear();
}

} // end namespace path

} // end namespace sys
} // end namespace llvm
