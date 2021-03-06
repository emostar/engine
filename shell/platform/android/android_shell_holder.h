// Copyright 2018 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_SHELL_PLATFORM_ANDROID_ANDROID_SHELL_HOLDER_H_
#define FLUTTER_SHELL_PLATFORM_ANDROID_ANDROID_SHELL_HOLDER_H_

#include <memory>

#include "flutter/fml/macros.h"
#include "flutter/fml/platform/android/jni_weak_ref.h"
#include "flutter/fml/unique_fd.h"
#include "flutter/lib/ui/window/viewport_metrics.h"
#include "flutter/shell/common/run_configuration.h"
#include "flutter/shell/common/shell.h"
#include "flutter/shell/common/thread_host.h"
#include "flutter/shell/platform/android/platform_view_android.h"

namespace shell {

class AndroidShellHolder {
 public:
  AndroidShellHolder(blink::Settings settings,
                     fml::jni::JavaObjectWeakGlobalRef java_object,
                     bool is_background_view);

  ~AndroidShellHolder();

  bool IsValid() const;

  void Launch(RunConfiguration configuration);

  void SetViewportMetrics(const blink::ViewportMetrics& metrics);

  void DispatchPointerDataPacket(
      std::unique_ptr<blink::PointerDataPacket> packet);

  const blink::Settings& GetSettings() const;

  fml::WeakPtr<PlatformViewAndroid> GetPlatformView();

  Rasterizer::Screenshot Screenshot(Rasterizer::ScreenshotType type,
                                    bool base64_encode);

  void UpdateAssetManager(fml::RefPtr<blink::AssetManager> asset_manager);

 private:
  const blink::Settings settings_;
  const fml::jni::JavaObjectWeakGlobalRef java_object_;
  fml::WeakPtr<PlatformViewAndroid> platform_view_;
  ThreadHost thread_host_;
  std::unique_ptr<Shell> shell_;
  bool is_valid_ = false;
  pthread_key_t thread_destruct_key_;

  static void ThreadDestructCallback(void* value);

  FML_DISALLOW_COPY_AND_ASSIGN(AndroidShellHolder);
};

}  // namespace shell

#endif  // FLUTTER_SHELL_PLATFORM_ANDROID_ANDROID_SHELL_HOLDER_H_
