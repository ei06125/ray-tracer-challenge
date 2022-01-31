#pragma once

#include "RayTracer/Math/Tuple.hpp"
#include "RayTracer/Rendering/Patterns/Pattern.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

class BlendedPattern : public Pattern
{
public:
  /// @section Member functions
  BlendedPattern(std::shared_ptr<Pattern> a, std::shared_ptr<Pattern> b);

  /// @subsection Observers
  Color At(Tuple point) const override;

private:
  std::shared_ptr<Pattern> m_PatternA;
  std::shared_ptr<Pattern> m_PatternB;
};

} // namespace Textures
} // namespace Rendering
} // namespace RayTracer
