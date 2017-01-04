//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// gc_manager.h
//
// Identification: src/include/gc/gc_manager.h
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//


#pragma once

#include <memory>

#include "common/macros.h"
#include "type/types.h"
#include "common/logger.h"

namespace peloton {
namespace gc {

//===--------------------------------------------------------------------===//
// GC Manager
//===--------------------------------------------------------------------===//

class GCManager {
public:
  GCManager(const GCManager &) = delete;
  GCManager &operator=(const GCManager &) = delete;
  GCManager(GCManager &&) = delete;
  GCManager &operator=(GCManager &&) = delete;

  GCManager() : is_running_(false) { }

  virtual ~GCManager() { }

  static GCManager& GetInstance() {
    static GCManager gc_manager;
    return gc_manager;
  }

  virtual void Reset() { is_running_ = false; }

  // Get status of whether GC thread is running or not
  bool GetStatus() { return this->is_running_; }

  virtual void StartGC() {}

  virtual void StopGC() {}

  virtual ItemPointer ReturnFreeSlot(const oid_t &table_id UNUSED_ATTRIBUTE) {
    return INVALID_ITEMPOINTER;
  }

  virtual void RegisterTable(const oid_t &table_id UNUSED_ATTRIBUTE) { }

  virtual void DeregisterTable(const oid_t &table_id UNUSED_ATTRIBUTE) { }

  virtual size_t GetTableCount() { return 0; }

  virtual void RecycleTransaction(std::shared_ptr<ReadWriteSet> gc_set UNUSED_ATTRIBUTE, 
                                   const cid_t &timestamp UNUSED_ATTRIBUTE,
                                   const GCSetType gc_set_type UNUSED_ATTRIBUTE) {}

protected:
  volatile bool is_running_;

};

}  // namespace gc
}  // namespace peloton
