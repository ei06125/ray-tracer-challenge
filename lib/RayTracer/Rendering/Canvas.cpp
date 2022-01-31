#include "RayTracer/Rendering/Canvas.hpp"

#include "RayTracer/Core/Assertions.hpp"

namespace RayTracer::Rendering {
using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

Canvas::Canvas(int w, int h)
  : width(w)
  , height(h)
{
  pixels.reserve(width * height);
  for (std::size_t i = 0; i < pixels.capacity(); ++i) {
    pixels.push_back(make_color(0, 0, 0));
  }
}

/// ---------------------------------------------------------------------------
/// @subsection Iterators
/// ---------------------------------------------------------------------------

std::vector<Tuple>::iterator Canvas::begin()
{
  return pixels.begin();
}

std::vector<Tuple>::iterator Canvas::end()
{
  return pixels.end();
}

/// ---------------------------------------------------------------------------
/// @subsection Capacity
/// ---------------------------------------------------------------------------

std::size_t Canvas::size() const
{
  return pixels.size();
}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

const Tuple& Canvas::pixel_at(int w, int h) const
{
  return pixels.at(h * width + w);
}

/// ---------------------------------------------------------------------------
/// @subsection Modifiers
/// ---------------------------------------------------------------------------

void Canvas::write_pixel_at(int w, int h, const Tuple& color)
{
  // TODO: pixels[] vs pixels.at
  pixels.at(h * width + w) = color;
}

/// ===========================================================================
/// @section Non-member functions
/// ===========================================================================

void write_pixel(Canvas& c, int x, int y, const Tuple& color)
{
  DEBUG_ASSERT(x >= 0 && x < c.width);
  DEBUG_ASSERT(y >= 0 && y < c.height);
  c.write_pixel_at(x, y, color);
}

const Tuple& pixel_at(const Canvas& c, int w, int h)
{
  return c.pixel_at(w, h);
}

std::string canvas_to_ppm(const Canvas& c)
{
  std::string result{};
  result.reserve(2048);

  // PPM Header
  result += "P3\n";
  result += std::to_string(c.width) + " " + std::to_string(c.height) + "\n";
  result += std::to_string(255) + "\n";

  // PPM Body
  for (auto row = 0U; row < c.height; ++row) {
    int currentWidth = 0;
    std::string line = "";
    for (auto col = 0U; col < c.width; ++col) {
      const auto& color = c.pixel_at(col, row);
      line +=
        std::to_string((int)(std::clamp(color.red * 256, 0.0f, 255.0f))) + " ";
      line +=
        std::to_string((int)(std::clamp(color.green * 256, 0.0f, 255.0f))) +
        " ";
      line += std::to_string((int)(std::clamp(color.blue * 256, 0.0f, 255.0f)));

      if (col < c.width - 1) {
        line += " ";
      }
    }
    if (line.size() > 70) {
      result += line.substr(0, line.substr(0, 70).find_last_of(' '));
      result += '\n';
      result += line.substr(line.substr(0, 70).find_last_of(' ') + 1);
    } else {
      result += line;
    }
    result += "\n";
  }
  result += "\n";

  return result;
}

} // namespace RayTracer::Rendering
