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

#ifndef XCSOAR_BACKGROUND_RENDERER_HPP
#define XCSOAR_BACKGROUND_RENDERER_HPP

#include "Math/Angle.hpp"

class Canvas;
class WindowProjection;
struct TerrainRendererSettings;
class TerrainRenderer;
class RasterTerrain;
class RasterWeatherCache;
struct DerivedInfo;

/**
 * Utility class to draw terrain, topography (not implemented yet)
 */
class BackgroundRenderer {
  const RasterTerrain *terrain;
  const RasterWeatherCache *weather;
  TerrainRenderer *renderer;
  Angle shading_angle;

public:
  BackgroundRenderer();

  ~BackgroundRenderer() {
    Reset();
  }

  /**
   * Flush all caches.
   */
  void Flush();

  void Draw(Canvas& canvas,
            const WindowProjection& proj,
            const TerrainRendererSettings &terrain_settings);

  void SetShadingAngle(const WindowProjection &projection,
                       const TerrainRendererSettings &settings,
                       const DerivedInfo &calculated);
  void Reset();
  void SetTerrain(const RasterTerrain *terrain);
  void SetWeather(const RasterWeatherCache *weather);

private:
  void SetShadingAngle(const WindowProjection& proj, Angle angle);
};

#endif
