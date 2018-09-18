#ifndef FTXUI_CORE_SCREEN
#define FTXUI_CORE_SCREEN

#include <string>
#include <vector>

namespace ftxui {

class Screen {
 public:
  Screen(size_t dimx, size_t dimy);
  wchar_t& at(size_t x, size_t y);
  std::string ToString();

  size_t dimx() { return dimx_;}
  size_t dimy() { return dimy_;}

  static Screen WholeTerminal();

 private:
  size_t dimx_;
  size_t dimy_;
  std::vector<std::wstring> lines_;
};

};  // namespace ftxui

#endif /* end of include guard: FTXUI_CORE_SCREEN */