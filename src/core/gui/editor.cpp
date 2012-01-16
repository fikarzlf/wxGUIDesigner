///////////////////////////////////////////////////////////////////////////////
// Name:        core/gui/editor.cpp
// Purpose:     
// Author:      Andrea Zanellato
// Modified by:
// Created:     2011/11/30
// Revision:    $Hash$
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#include "core/gui/editor.h"
#include "core/gui/manager.h"

#include <wx/notebook.h>
#include <wx/stc/stc.h>
#include <wx/xrc/xmlres.h>

void EditorHandler::OnPluginLoaded( Plugin *plugin )
{
    wxXmlResource *xmlRes  = wxXmlResource::Get();
    wxString      category = plugin->GetCategory();
    wxString      plugDir  = wxGD_PLUGIN_DIR + category + wxFILE_SEP_PATH;

    if ( plugin && category == "languages" )
    {
        wxImageList *imgLst  = m_editBook->GetImageList();
        wxImageList *itmLst  = new wxImageList( 16, 16 );
        wxImage     img      = plugin->GetBitmap().ConvertToImage().Scale( 16, 16 );
        int         imgIdx   = imgLst->Add( img );
        wxString    plugName = plugin->GetName();

        wxVector< PluginItem * > items = plugin->GetItems();

        wxString xrcFileName = plugDir + plugName + wxFILE_SEP_PATH +
                                                    plugName + ".xml";
        if ( !xmlRes->Load( xrcFileName ) ) return;

        if ( items.size() )
        {
            wxNotebook *nb = new wxNotebook( m_editBook, wxID_ANY );

            nb->SetImageList( itmLst );

            m_editBook->AddPage( nb, plugin->GetLabel(), false, imgIdx );

            for( wxVector< PluginItem * >::iterator it = items.begin();
                it != items.end(); ++it )
            {
                PluginItem  *item    = (*it);
                wxString    itemName = item->GetName();
                wxObject    *obj     =
                    xmlRes->LoadObject( nb, itemName, "wxStyledTextCtrl" );

                wxStyledTextCtrl *edit = wxDynamicCast( obj, wxStyledTextCtrl );

                if ( edit )
                {
                    nb->AddPage( edit, itemName, false,
                                itmLst->Add( item->GetBitmap() ) );
                }
            }
        }
        else
        {
            wxObject *obj = xmlRes->LoadObject( m_editBook, plugName,
                                                        "wxStyledTextCtrl");
            wxStyledTextCtrl *edit = wxDynamicCast( obj, wxStyledTextCtrl );

            if ( edit )
            {
                m_editBook->AddPage( edit, plugin->GetLabel(), false, imgIdx );
            }
        }
    }
}

void EditorHandler::OnObjectCreated( IObject *object )
{
    
}

void EditorHandler::OnObjectDeleted( IObject *object )
{
    
}

void EditorHandler::OnObjectExpanded( IObject *object )
{
    
}

void EditorHandler::OnObjectSelected( IObject *object )
{
    
}
