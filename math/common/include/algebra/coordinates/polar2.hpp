/** Algebra plugins library, part of the ACTS project
 *
 * (c) 2020-2022 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

#pragma once

// Project include(s).
#include "algebra/coordinates/coordinate_base.hpp"
#include "algebra/qualifiers.hpp"

// System include(s).
#include <cmath>

namespace algebra::common {

template <typename transform3_t, typename track_indices_t>
struct polar2 : public coordinate_base<polar2, transform3_t, track_indices_t> {

  /// @name Type definitions for the struct
  /// @{

  /// Base type
  using base_type = coordinate_base<polar2, transform3_t, track_indices_t>;
  /// Transformation matching this struct
  using transform3_type = typename base_type::transform3_type;
  /// Sclar type
  using scalar_type = typename base_type::scalar_type;
  /// Point in 2D space
  using point2 = typename base_type::point2;
  /// Point in 3D space
  using point3 = typename base_type::point3;
  /// Vector in 3D space
  using vector3 = typename base_type::vector3;
  /// Vector actor
  using vector_actor = typename base_type::vector_actor;
  /// Matrix actor
  using matrix_actor = typename base_type::matrix_actor;
  /// Matrix size type
  using size_type = typename base_type::size_type;
  /// 2D matrix type
  template <size_type ROWS, size_type COLS>
  using matrix_type = typename base_type::matrix_type<ROWS, COLS>;
  /// Track indices
  using E = track_indices_t;
  // Trigonometrics
  using trigonometrics = typename base_type::trigonometrics;
  // Vector types
  using bound_vector = typename base_type::bound_vector;
  using free_vector = typename base_type::free_vector;

  /** This method transform from a point from 2D cartesian frame to a 2D
   * polar point */
  ALGEBRA_HOST_DEVICE inline point2 operator()(const point2 &p) const {

    return {vector_actor().perp(p), vector_actor().phi(p)};
  }

  /** This method transform from a point in 3D cartesian frame to a 2D
   * polar point */
  ALGEBRA_HOST_DEVICE inline point2 operator()(const point3 &p) const {

    return {vector_actor().perp(p), vector_actor().phi(p)};
  }

  /** This method transform from a point from global cartesian 3D frame to a
   * local 2D polar point */
  ALGEBRA_HOST_DEVICE
  inline point2 global_to_local(const transform3_type &trf, const point3 &p,
                                const vector3 & /*d*/) const {
    const auto local3 = trf.point_to_local(p);
    return this->operator()(local3);
  }

  /** This method transform from a local 2D polar point to a point global
   * cartesian 3D frame*/
  template <typename mask_t>
  ALGEBRA_HOST_DEVICE inline point3 local_to_global(
      const transform3_type &trf, const mask_t & /*mask*/, const point2 &p,
      const vector3 & /*d*/) const {
    const scalar_type x = p[0] * std::cos(p[1]);
    const scalar_type y = p[0] * std::sin(p[1]);

    return trf.point_to_global(point3{x, y, 0.});
  }

  ALGEBRA_HOST_DEVICE
  inline matrix_type<3, 2> bound_to_free_rotation(
      const transform3_type &trf3, const trigonometrics & /*t*/) {

    matrix_type<3, 2> bound_to_free_rotation =
        matrix_actor().template zero<3, 2>();
  }

  ALGEBRA_HOST_DEVICE inline matrix_type<2, 3> free_to_bound_rotation(
      const transform3_type &trf3, const trigonometrics & /*t*/) {}
};

}  // namespace algebra::common