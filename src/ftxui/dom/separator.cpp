#include <memory>  // for make_shared
#include <string>  // for string

#include "ftxui/dom/elements.hpp"     // for Element, separator
#include "ftxui/dom/node.hpp"         // for Node
#include "ftxui/dom/requirement.hpp"  // for Requirement
#include "ftxui/screen/box.hpp"       // for Box
#include "ftxui/screen/screen.hpp"    // for Pixel, Screen

namespace ftxui {

using ftxui::Screen;

const std::string charset[][2] = {
    {"│", "─"},
    {"┃", "━"},
    {"║", "═"},
    {"│", "─"},
};

class Separator : public Node {
 public:
  Separator(BorderStyle style) : style_(style) {}

  void ComputeRequirement() override {
    requirement_.min_x = 1;
    requirement_.min_y = 1;
  }

  void Render(Screen& screen) override {
    bool is_column = (box_.x_max == box_.x_min);
    bool is_line = (box_.y_min == box_.y_max);

    const std::string c = charset[style_][is_line && !is_column];

    for (int y = box_.y_min; y <= box_.y_max; ++y) {
      for (int x = box_.x_min; x <= box_.x_max; ++x) {
        screen.PixelAt(x, y).character = c;
      }
    }
  }

  BorderStyle style_;
};

class SeparatorWithPixel : public Separator {
 public:
  SeparatorWithPixel(Pixel pixel) : Separator(LIGHT), pixel_(pixel) {}
  void Render(Screen& screen) override {
    for (int y = box_.y_min; y <= box_.y_max; ++y) {
      for (int x = box_.x_min; x <= box_.x_max; ++x) {
        screen.PixelAt(x, y) = pixel_;
      }
    }
  }

 private:
  Pixel pixel_;
};

Element separator() {
  return std::make_shared<Separator>(LIGHT);
}

Element separatorStyled(BorderStyle style) {
  return std::make_shared<Separator>(style);
}

Element separatorLight() {
  return std::make_shared<Separator>(LIGHT);
}
Element separatorHeavy() {
  return std::make_shared<Separator>(HEAVY);
}
Element separatorDouble() {
  return std::make_shared<Separator>(DOUBLE);
}

}  // namespace ftxui

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
