/***************************************************************************
 *   Copyright 2005-2008 Last.fm Ltd.                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#ifndef DLL_EXPORT_MACRO_H
#define DLL_EXPORT_MACRO_H

/** Exports symbols when compiled as part of libunicorn, imports when included
  * from some external target. */
#if defined(_WIN32) || defined(WIN32)
    #ifdef _MOOSE_DLLEXPORT
        #define MOOSE_DLLEXPORT __declspec(dllexport)
    #else
        #define MOOSE_DLLEXPORT __declspec(dllimport)
    #endif

    #ifdef _UNICORN_DLLEXPORT
        #define UNICORN_DLLEXPORT __declspec(dllexport)
    #else
        #define UNICORN_DLLEXPORT __declspec(dllimport)
    #endif

    #ifdef _RADIO_DLLEXPORT
        #define RADIO_DLLEXPORT __declspec(dllexport)
    #else
        #define RADIO_DLLEXPORT __declspec(dllimport)
    #endif

    #ifdef _FINGERPRINT_DLLEXPORT
        #define FINGERPRINT_DLLEXPORT __declspec(dllexport)
    #else
        #define FINGERPRINT_DLLEXPORT __declspec(dllimport)
    #endif

    #ifdef _WS_DLLEXPORT
        #define WS_DLLEXPORT __declspec(dllexport)
    #else
        #define WS_DLLEXPORT __declspec(dllimport)
    #endif

    #ifdef _TYPES_DLLEXPORT
        #define TYPES_DLLEXPORT __declspec(dllexport)
    #else
        #define TYPES_DLLEXPORT __declspec(dllimport)
    #endif
    
    #ifdef _CORE_DLLEXPORT
        #define CORE_DLLEXPORT __declspec(dllexport)
    #else
        #define CORE_DLLEXPORT __declspec(dllimport)
    #endif

    #ifdef _SCROBBLE_DLLEXPORT
        #define SCROBBLE_DLLEXPORT __declspec(dllexport)
    #else
        #define SCROBBLE_DLLEXPORT __declspec(dllimport)
    #endif

    
#else
    #define MOOSE_DLLEXPORT
    #define UNICORN_DLLEXPORT
    #define RADIO_DLLEXPORT
    #define FINGERPRINT_DLLEXPORT
    #define WS_DLLEXPORT
    #define CORE_DLLEXPORT
    #define TYPES_DLLEXPORT
    #define SCROBBLE_DLLEXPORT
#endif

#endif
