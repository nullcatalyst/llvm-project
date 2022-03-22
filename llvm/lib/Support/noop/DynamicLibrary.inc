//===- Unix/DynamicLibrary.cpp - Unix DL Implementation ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides the UNIX specific implementation of DynamicLibrary.
//
//===----------------------------------------------------------------------===//

DynamicLibrary::HandleSet::~HandleSet() {}

void *DynamicLibrary::HandleSet::DLOpen(const char *File, std::string *Err) {
  if (Err) *Err = "dlopen() not supported on this platform";
  return &Invalid;
}

void DynamicLibrary::HandleSet::DLClose(void *Handle) {}

void *DynamicLibrary::HandleSet::DLSym(void *Handle, const char *Symbol) {
  return nullptr;
}

// Must declare the symbols in the global namespace.
static void *DoSearch(const char* SymbolName) {
  return nullptr;
}
