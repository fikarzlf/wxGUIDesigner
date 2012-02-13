///////////////////////////////////////////////////////////////////////////////
// Name:        core/utils.h
// Purpose:     
// Author:      Andrea Zanellato
// Modified by:
// Created:     2011/12/20
// Revision:    $Hash$
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_UTILS_H__
#define __CORE_UTILS_H__

#include "core/defs.h"

#include <wx/stdpaths.h>
#include <wx/window.h>

class wxColour;
class wxString;

inline wxWindow *wxFindWindowById( long winid, const wxWindow *parent = NULL )
{
    return wxWindow::FindWindowById( winid, parent );
}

inline wxString GetDataBasePath()
{
    return wxStandardPaths::Get().GetResourcesDir() + wxFILE_SEP_PATH + "db";
}

inline wxString GetResourcePath()
{
#ifdef __WXMSW__
    return wxStandardPaths::Get().GetDataDir() + wxFILE_SEP_PATH;
#else
    return wxStandardPaths::Get().GetResourcesDir().BeforeLast( wxFILE_SEP_PATH ) +
                            wxFILE_SEP_PATH + "wxguidesigner" + wxFILE_SEP_PATH;
#endif
}

namespace wxGDConv
{
    const wxString  HexToString         ( int value );
    const int       StringToHex         ( const wxString &text );
    const ClassType ClassTypeFromString ( const wxString &value );
    const int       IntFromString       ( const wxString &value );
    const wxColour  GetSystemColour     ( const wxString &name );
    const int       GetSystemColourIndex( const wxString &name );
    const wxFont    GetSystemFont       ( const wxString &name );
};

#endif //__CORE_UTILS_H__