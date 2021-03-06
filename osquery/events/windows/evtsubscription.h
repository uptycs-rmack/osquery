/**
 *  Copyright (c) 2014-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed in accordance with the terms specified in
 *  the LICENSE file found in the root directory of this source tree.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <osquery/utils/status/status.h>

#include <windows.h>
#include <winevt.h>

namespace osquery {
DWORD WINAPI EvtSubscriptionCallbackDispatcher(
    EVT_SUBSCRIBE_NOTIFY_ACTION action, PVOID context, EVT_HANDLE event);

class EvtSubscription final {
 public:
  using Ref = std::unique_ptr<EvtSubscription>;
  using Event = std::wstring;
  using EventList = std::vector<Event>;

  static Status create(Ref& obj, const std::string& channel);
  ~EvtSubscription();

  const std::string channel() const;
  EventList getEvents();

  EvtSubscription(const EvtSubscription&) = delete;
  EvtSubscription& operator=(const EvtSubscription&) = delete;

 private:
  struct PrivateData;
  std::unique_ptr<PrivateData> d_;

  EvtSubscription(const std::string& channel);
  void processEvent(EVT_HANDLE event);

  friend DWORD WINAPI EvtSubscriptionCallbackDispatcher(
      EVT_SUBSCRIBE_NOTIFY_ACTION action, PVOID context, EVT_HANDLE event);
};
} // namespace osquery
