///////////////////////////////////////////////////////////////////////////////
// Name:        core/gui/manager.h
// Purpose:     
// Author:      Andrea Zanellato
// Modified by:
// Created:     2011/11/20
// Revision:    $Hash$
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_GUI_MANAGER_H__
#define __CORE_GUI_MANAGER_H__

#include "core/dllimpexp.h"
#include "core/utils.h"

class MainFrame;
class EditorHandler;
class PropBookHandler;
class PaletteHandler;
class TreeViewHandler;

class PluginManager;

class wxDialog;
class wxImageList;
class wxMenuBar;
class wxNotebook;
class wxPanel;
class wxPropertyGrid;
class wxToolBar;
class wxTreeCtrl;
class wxXmlResource;

class wxPropertyGridXmlHandler;

class DLLIMPEXP_CORE GUIManager
{
public:
    wxDialog        *GetAboutDialog      ( wxWindow *parent = NULL );
    wxFrame         *GetMainFrame        ( wxWindow *parent = NULL );
    wxMenuBar       *GetMainMenu         ( wxWindow *parent = NULL );
    wxPanel         *GetDesignPanel();
    wxNotebook      *GetEditorBook       ( wxWindow *parent = NULL );
    wxNotebook      *GetPropertyBook     ( wxWindow *parent = NULL );
    wxNotebook      *GetPaletteBook      ( wxWindow *parent = NULL );
    wxTreeCtrl      *GetTreeView         ( wxWindow *parent = NULL );
    wxToolBar       *GetToolBar          ( wxWindow *parent = NULL );

    wxPropertyGrid  *GetPropertiesGrid() { return m_pgProps; }
    wxPropertyGrid  *GetEventsGrid()     { return m_pgEvents; }

//  void NewProject();
//  void CreateObject( const wxString &classname );

    static GUIManager *Get();
    void Free();

private:
    GUIManager();
    virtual ~GUIManager();

    void OnWindowPaint( wxPaintEvent &event );

    MainFrame  *m_frame;
    wxMenuBar  *m_menuBar;
    wxToolBar  *m_toolBar;
    wxNotebook *m_editBook;
    wxNotebook *m_propBook;
    wxNotebook *m_palette;
    wxTreeCtrl *m_treeView;

    wxImageList *m_ilsPropBook;

    wxPropertyGrid  *m_pgProps;
    wxPropertyGrid  *m_pgEvents;

    EditorHandler   *m_editBookHndlr;
    PaletteHandler  *m_paletteHndlr;
    PropBookHandler *m_propBookHndlr;
    TreeViewHandler *m_treeViewHndlr;

    static GUIManager *ms_instance;
};

#endif //__CORE_GUI_MANAGER_H__
