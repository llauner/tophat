/*
  Copyright_License {

  Top Hat Soaring Glide Computer - http://www.tophatsoaring.org/
  Copyright (C) 2000-2016 The Top Hat Soaring Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#ifndef XCSOAR_OBSERVATION_ZONE_BOUNDARY_HPP
#define XCSOAR_OBSERVATION_ZONE_BOUNDARY_HPP

#include "Geo/GeoPoint.hpp"

#include <forward_list>

class OZBoundary : public std::forward_list<GeoPoint> {
public:
  /**
   * Generate boundary points for the arc described by the parameters.
   * This excludes the points at the start/end angle.
   */
  void GenerateArcExcluding(const GeoPoint &center, fixed radius,
                            Angle start_radial, Angle end_radial);
};

#endif
