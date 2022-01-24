#include "Rendering/RayTracing/Material.hpp"

// Project Library
#include "Rendering/RayTracing/Light.hpp"

// C++ Standard Library
#include <cmath>

bool operator==(const Material& lhs, const Material& rhs)
{
  return memcmp(&lhs, &rhs, sizeof(Material)) == 0;
}

Tuple lighting(const Material& material,
               const PointLight& light,
               const Tuple& point,
               const Tuple& eyev,
               const Tuple& normalv,
               bool in_shadow)
{
  // combine the surface color with the light's color/intensity
  auto effective_color = material.color * light.intensity;

  // find the direction to the light source
  auto lightv = normalize(light.position - point);

  // compute the ambient contribution
  auto ambient = effective_color * material.ambient;

  // early exit point
  if (in_shadow) {
    return ambient;
  }

  // light_dot_normal represents the cosine of the angle between the
  // light vector and the normal vector. A negative number means the
  // light is on the other side of the surface
  auto light_dot_normal = dot(lightv, normalv);

  Tuple diffuse = make_color(0, 0, 0);  // black
  Tuple specular = make_color(0, 0, 0); // black
  if (light_dot_normal >= 0) {
    // compute the diffuse contribution
    diffuse = effective_color * material.diffuse * light_dot_normal;

    // reflect_dot_eye represents the cosine of the angle between the
    // reflection vector and the eye vector. A negative number means the
    // light reflects away from the eye.
    auto reflectv = reflect(-lightv, normalv);
    auto reflect_dot_eye = dot(reflectv, eyev);

    if (reflect_dot_eye > 0) {
      // compute the specular contribution
      auto factor = std::pow(reflect_dot_eye, material.shininess);
      specular = light.intensity * material.specular * factor;
    }
  }

  // Add the three contributions together to get the final shading
  return ambient + diffuse + specular;
}
