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

#ifndef XCSOAR_IO_ZIP_SOURCE_HPP
#define XCSOAR_IO_ZIP_SOURCE_HPP

#include "BufferedSource.hpp"

#include <zlib/zlib.h>

struct zzip_file;
struct zzip_dir;

class InflateSource : public BufferedSource<char, 4096u> {
  Source<char> &src;

  z_stream strm;

public:
  InflateSource(Source<char> &_src);
  virtual ~InflateSource();

  bool HasFailed() const {
    return strm.opaque != nullptr;
  }

protected:
  /* virtual methods from class BufferedSource */
  unsigned Read(char *p, unsigned n) override;
};

#endif
