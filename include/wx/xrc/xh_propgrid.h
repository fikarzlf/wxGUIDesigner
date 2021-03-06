/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_propgrid.h
// Purpose:     XML resource handler for wxPropertyGrid
// Author:      Jaakko Salli
// Modified by: Andrea Zanellato
// Created:     May-16-2007
// Revision:    $Hash$
// Copyleft:    (ɔ) Jaakko Salli
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_PROPGRID_H_
#define _WX_XH_PROPGRID_H_

#include <wx/xrc/xmlres.h>

#if wxUSE_XRC && wxUSE_PROPGRID

class wxPropertyGrid;
class wxPropertyGridPopulator;
class wxPropertyGridManager;
class wxPropertyGridPageState;

class wxPropertyGridXmlHandler : public wxXmlResourceHandler
{
public:
    wxPropertyGridXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);

    void InitPopulator();
    void PopulatePage(wxPropertyGridPageState* state);
    void DonePopulator();

    void HandlePropertyGridParams();

private:
    wxPropertyGrid*             m_pg;
    wxPropertyGridPopulator*    m_populator;
    wxPropertyGridManager*      m_manager;

    bool m_isInside;

    friend class wxPropertyGridXrcPopulator;

    wxDECLARE_DYNAMIC_CLASS(wxPropertyGridXmlHandler);
};

#endif // wxUSE_XRC && wxUSE_PROPGRID

#endif // _WX_XH_PROPGRID_H_
