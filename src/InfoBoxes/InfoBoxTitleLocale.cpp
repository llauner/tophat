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
/*
 * InfoBoxCustomTitle.cpp
 * Allows for customisation of InfoBox titles.
 * This is done by reading from a key=value file located in the current profile directory.
 * @see InfoBoxManager::DisplayInfoBox()
 * Titles (key) having an entry in the file will have their title replaced by the corresponding value.
 * If no entry can be found, the default title (using gettext) is used.
 *
 *  Created on: Nov 3, 2017
 *      Author: Ludovic Launer
 */

#include "InfoBoxTitleLocale.hpp"

#include "LogFile.hpp"
#include "Profile/File.hpp"
#include "LocalPath.hpp"
#include "Util/Macros.hpp"
#include "Util/ConvertString.hpp"
#include "LogFile.hpp"
#include <windef.h> /* for MAX_PATH */
#include "TextResources.c"  // Automatically generated by generate.mk to include text files in /Data/text
#include "InfoBoxes/Content/Factory.hpp"

#ifdef _UNICODE
#include "Util/tstring.hpp"
#include <map>
#include <windows.h>
typedef std::map<std::string,tstring> unicode_map_string;
static unicode_map_string map_titles_locale_unicode; // Store localised titles for unicode
#endif

#include <unistd.h>
#include <fstream>

#define INFOBOX_LOCALE_FILE "infoBoxTitle.locale"
#define RESOURCE_INFOBOX_LOCALE_FILE "Data/text/infoBoxTitle.locale"

/**
 * Initialise
 * Init and Load local title from file.
 * This needs to be called first to populate the map.
 * @return true if the file was found. false otherwise
 */
bool
InfoBoxTitleLocale::Initialise()
{
  LogFormat("Loading InfoBox Titles locale...");
  bool fileRead = LoadFile();
  return fileRead;
}

/**
 * LoadFile
 * Try to read (key="value") custom titles from a file.
 * @return true if the file was found. false otherwise
 */
bool
InfoBoxTitleLocale::LoadFile()
{
  static TCHAR path[MAX_PATH];
  LocalPath(path, _T(INFOBOX_LOCALE_FILE));

  // Create Default file if it doesn't exist
  CreateDefaultFile(path);

  // Load file into map
  if (!Profile::LoadFile(map_title_locale, path))
    LogFormat(_T("%s : File not found, will use default values"), path);
  else {
    LogFormat(_T("Loaded %d InfoBox Titles locale from: %s"),
              (int)map_title_locale.size(), path);

    // TODO: Save file but preserve comments. The labels should be sorted by alphabetical orders, but the comments preserved

#ifdef _UNICODE
    // Populate a map with tstring
    for (auto iter : map_title_locale) { // Browse through previously loaded map
      std::string key = iter.first;
      std::string value = iter.second;

      UTF8ToWideConverter wide_locale(value.c_str());
      // Add the translated TCHAR string to the unicode map so that we can send a pointer back
      map_titles_locale_unicode[key.c_str()] = wide_locale;
    }
#endif

  }

  return true;
}

/**
 * CreateDefaultFile
 * Creates a default infoBoxTitle.locale file by combining
 * static content from resources (help comments) with existing InfoBoxes
 * caption.
 * @param path Full path of the default infoBoxTitle.locale file to create
 */
void
InfoBoxTitleLocale::CreateDefaultFile(TCHAR* path)
{
  // Create file if it doesn't exist
  WideToUTF8Converter filePath(path);

  bool fileExists = access(filePath, R_OK) == 0;
  if (fileExists)
    LogFormat(_T("%s File already exists. Will use it..."),
    INFOBOX_LOCALE_FILE);
  else {
    LogFormat(_T("%s File not found, will generate default file in: %s"),
              _T(INFOBOX_LOCALE_FILE), path);

    // Get file from resources
    size_t size;
    const char *data = InfoBoxTitleLocale::find_embedded_file(
    RESOURCE_INFOBOX_LOCALE_FILE, &size);

    std::ofstream out(filePath);
    if (!out) {
      LogFormat(_T("Error. Cannot write to: %s"), path);
    } else {
      // Write static content from Data/text/infoBoxTitle.locale
      out.write(data, size);

      // Browse through InfoBoxes Types and add corresponding caption
      for (int i = 0; i != InfoBoxFactory::e_NUM_TYPES; i++) {

        InfoBoxFactory::Type type = static_cast<InfoBoxFactory::Type>(i);
        const TCHAR* wideCaption = InfoBoxFactory::GetCaption(type);
        WideToUTF8Converter caption(wideCaption);

        // Special cases where a default title is already provided in en.po
        // TODO: Ideally the special cases should not be hard-coded. We'd need to find a way to get the caption from en.po even when English is not the chosen language.
        std::string defaultValue("");

        std::map<std::string, std::string>::iterator it;
        it = InfoBoxTitleLocale::map_title_locale_existing_en_po.find(std::string(caption));
        if (it != map_title_locale_existing_en_po.end())
          defaultValue = it->second;

        // Add entry
        std::string entry("#");
        entry.append(caption);
        entry.append("=\"");
        entry.append(defaultValue.c_str());
        entry.append("\"\n");

        out.write(entry.c_str(), strlen(entry.c_str()));
      }

      out.close();
    }
  }
}

/**
 * Look up a string value in locale InfoBoxTile file
 *
 * @param key name of the value
 * @return the value or null if it cannot be found
 */
const TCHAR*
InfoBoxTitleLocale::GetLocale(const TCHAR *caption)
{
  if (caption == nullptr)
    return nullptr;

  WideToUTF8Converter key(caption);

  const char* locale = map_title_locale.Get(key, nullptr);
  if (locale == nullptr)
    return nullptr;

#ifdef _UNICODE
  return map_titles_locale_unicode[(const char*)key].c_str();
#else
  return locale;
#endif
}

