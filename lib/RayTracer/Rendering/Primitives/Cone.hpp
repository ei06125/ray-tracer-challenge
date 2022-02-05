#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer {
namespace Rendering {
namespace Primitives {

using namespace Math;

class Cone : public Shape
{
public:
  /// @section Member functions
  /// @subsection Observers
  float GetMinimum() const;
  float GetMaximum() const;
  bool IsClosed() const;

  /// @subsection Modifiers
  void SetMinimum(float newMinimum);
  void SetMaximum(float newMaximum);
  void SetClosed(bool closed);

  // TODO: this should be removed but the tests fail if we do so
  Tuple GetNormalAt(Tuple point,
                    const Intersection* i = nullptr) const override;

protected:
  Tuple GetLocalNormalAt(Tuple point,
                         const Intersection* i = nullptr) const override;
  Intersections VirtualIntersect(const Ray& r) const override;

private:
  bool CheckCap(const Ray& r, float t) const;
  void IntersectCaps(const Ray& r, Intersections& xs) const;

  float m_Minimum{ -INFINITY };
  float m_Maximum{ INFINITY };
  bool m_Closed{ false };
};

/// @section Non-member functions
inline bool operator==(const Shape& lhs, const Cone& rhs)
{
  return lhs == static_cast<const Shape&>(rhs);
}

inline bool operator==(const Shape* lhs, const Cone& rhs)
{
  return *lhs == static_cast<const Shape&>(rhs);
}

std::tuple<float, float> check_axis(float origin, float direction);

} // namespace Primitives
} // namespace Rendering
} // namespace RayTracer
