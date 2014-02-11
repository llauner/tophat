/*
Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2013 The XCSoar Project
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

#include "MapSettings.hpp"
#include "Asset.hpp"

void
MapItemListSettings::SetDefaults()
{
  add_location = true;
  add_arrival_altitude = true;
}

void
TrailSettings::SetDefaults()
{
  wind_drift_enabled = true;
  scaling_enabled = true;
  if (HasColors())
    type = Type::VARIO_1;
  else
    type = Type::SIMPLE;

  length = Length::LONG;
}

void
MapSettings::SetDefaults()
{
  circle_zoom_enabled = true;
  max_auto_zoom_distance = fixed(100000); /* 100 km */
  topography_enabled = true;
  terrain.SetDefaults();
  aircraft_symbol = AircraftSymbol::SIMPLE_LARGE;
  detour_cost_markers_enabled = false;
  display_ground_track = DisplayGroundTrack::AUTO;
  auto_zoom_enabled = false;
  wind_arrow_style = WindArrowStyle::ARROW_HEAD;
  wind_arrow_location = WindArrowLocation::MAP_AND_INFOBOX;
  waypoint.SetDefaults();
  airspace.SetDefaults();
  glider_screen_position = 30; // 30% from bottom
  map_shift_bias = MapShiftBias::NONE;
  circling_orientation = DisplayOrientation::NORTH_UP;
  cruise_orientation = DisplayOrientation::NORTH_UP;
  circling_scale = fixed(1) / 2;
  cruise_scale = fixed(1) / 60;
  show_flarm_on_map = true;
  show_flarm_alarm_level = true;
  show_thermal_profile = true;
  final_glide_bar_mc0_enabled = false;
  final_glide_bar_display_mode = FinalGlideBarDisplayMode::ON;
  vario_bar_enabled = false;
  show_fai_triangle_areas = false;

  trail.SetDefaults();
  item_list.SetDefaults();
}
