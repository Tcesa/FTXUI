#include <memory>  // for shared_ptr, __shared_ptr_access, allocator_traits<>::value_type
#include <string>  // for operator+, to_string
#include <vector>  // for vector

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Checkbox, Renderer, Vertical
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for operator|, Element, size, border, frame, HEIGHT, LESS_THAN

using namespace ftxui;

struct CheckboxState {
  bool checked;
};

int main(int argc, const char* argv[]) {
  std::vector<CheckboxState> states(30);
  auto container = Container::Vertical({});
  for (int i = 0; i < 30; ++i) {
    states[i].checked = false;
    container->Add(
        Checkbox("Checkbox" + std::to_string(i), &states[i].checked));
  }

  auto renderer = Renderer(container, [&] {
    return container->Render() | frame | size(HEIGHT, LESS_THAN, 10) | border;
  });

  auto screen = ScreenInteractive::FitComponent();
  screen.Loop(renderer);

  return 0;
}

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
