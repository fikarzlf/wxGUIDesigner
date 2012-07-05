///////////////////////////////////////////////////////////////////////////////
// Name:        wxguidesigner/rtti/tree.h
// Purpose:     
// Author:      Andrea Zanellato
// Modified by: 
// Created:     2011/11/21
// Revision:    $Hash$
// Copyleft:    (ɔ) Andrea Zanellato
// Licence:     GNU General Public License Version 3
///////////////////////////////////////////////////////////////////////////////
#ifndef __WXGUIDESIGNER_RTTI_TREE_H__
#define __WXGUIDESIGNER_RTTI_TREE_H__

class wxAny;
class wxBitmap;
class wxFont;
class wxPoint;
class wxSize;
class wxXmlDocument;

#include "wxguidesigner/defs.h"

class ClassNode;
class EventInfoNode;
class PropertyInfoNode;

class IObject;
//=============================================================================
// EventNode Class
//=============================================================================
class EventNode
{
public:
    EventNode( EventInfo eventInfo ) : m_info( eventInfo ), m_hasFunc( false )
    {
        for( size_t i = 0; i < m_info->GetTypeCount(); i++ )
            m_funcs.Add( wxEmptyString );
    }

    ~EventNode() {}

    wxString GetName()        const { return m_info->GetName(); }
    wxString GetDescription() const { return m_info->GetDescription(); }

    void SetFunctionName( size_t typeIndex, const wxString &funcName )
    {
        if( typeIndex < m_info->GetTypeCount() )
        {
            m_funcs.RemoveAt( typeIndex );
            m_funcs.Insert( funcName, typeIndex );
            m_hasFunc = funcName.empty() ? false : true;
        }
    }

    void SetFunctionName( const wxString &typeName, const wxString &funcName )
    {
        for( size_t i = 0; i < m_info->GetTypeCount(); i++ )
        {
            if( m_info->GetTypeName(i) == typeName )
            {
                m_funcs.RemoveAt(i);
                m_funcs.Insert( funcName, i );
                m_hasFunc = funcName.empty() ? false : true;
            }
        }
    }

    bool HasFunctions() { return m_hasFunc; }

    wxString GetFunctionName( size_t typeIndex ) const
    {
        if( typeIndex < m_funcs.GetCount() )
            return m_funcs.Item( typeIndex );

        return wxEmptyString;
    }

    wxString GetTypeName( size_t typeIndex  ) const
    {
        if( typeIndex < m_info->GetTypeCount() )
            return m_info->GetTypeName( typeIndex );

        return wxEmptyString;
    }

    wxString GetTypeDescription( size_t typeIndex  ) const
    {
        if( typeIndex < m_info->GetTypeCount() )
            return m_info->GetTypeDescription( typeIndex );

        return wxEmptyString;
    }

    size_t GetTypeCount() { return m_info->GetTypeCount(); }

private:
    EventInfo       m_info;
    wxArrayString   m_funcs;
    bool            m_hasFunc;
};
//=============================================================================
// PropertyNode Class
//=============================================================================
class PropertyNode
{
public:
    PropertyNode( PropertyInfo info );
    ~PropertyNode();

    wxString        GetName()           const;
    wxString        GetLabel()          const;
    wxString        GetDescription()    const;
    PropertyType    GetType()           const;
    PropertyInfo    GetInfo()           const;

    wxArrayString   GetAsArrayString()  const;
    wxBitmap        GetAsBitmap()       const;
    bool            GetAsBool()         const;
    Colour          GetAsColour()       const;
    double          GetAsDouble()       const;
    wxFont          GetAsFont()         const;
    int             GetAsInt()          const;
    wxPoint         GetAsPoint()        const;
    wxSize          GetAsSize()         const;
    wxString        GetAsString()       const;
    int             GetAsStyle()        const;
    wxString        GetAsText()         const;
    wxString        GetAsURL()          const;

    bool            IsCategory()        { return m_info->GetType() ==
                                            PROPERTY_TYPE_CATEGORY; }
    size_t          GetChildCount();
    Properties      GetChildren()       const { return m_children; }
    Property        GetChild( size_t index ) const;
    void            AddChild( Property prop );

    size_t          GetAttributeCount();
    Attribute       GetAttribute( size_t index )      const;
    wxString        GetAttributeName( size_t index )  const;
    wxString        GetAttributeValue( size_t index ) const;
    void            AddAttribute( const wxString &name, const wxString &value );

    void            SetValue( const wxAny &value );

private:
    Attributes      m_attributes;
    PropertyInfo    m_info;
    Properties      m_children;
    wxAny           m_value;
};
//=============================================================================
// ObjectNode Class
//=============================================================================
class ObjectNode //: public IObject
{
public:
    ObjectNode( ClassInfo classInfo, Object parent,
                bool expanded = true, bool isReference = false );
    ~ObjectNode();

    wxString    GetName()           const;
    wxString    GetDescription()    const;

    bool        IsReference()       const;
    bool        IsRoot();
    bool        IsTopLevel();
//-----------------------------------------------------------------------------
// State into the tree
//-----------------------------------------------------------------------------
    bool        IsExpanded() const;
    void        Collapse();
    void        Expand();
//-----------------------------------------------------------------------------
// ClassInfos
//-----------------------------------------------------------------------------
    ClassInfo   GetClassInfo() const;
    wxString    GetClassName() const;
//-----------------------------------------------------------------------------
// Events
//-----------------------------------------------------------------------------
    void        AddEvent        ( Event event );
    Event       GetEvent        ( size_t index )         const;
    Event       GetEvent        ( const wxString &name ) const;
    size_t      GetEventCount();
//-----------------------------------------------------------------------------
// Properties
//-----------------------------------------------------------------------------
    void        AddProperty     ( Property prop );
    bool        PropertyExists  ( const wxString &name );
    Property    GetProperty     ( size_t index )         const;
    Property    GetProperty     ( const wxString &name ) const;
    Property    GetChildProperty( Property parent,
                                  const wxString &name ) const;
    Properties  GetProperties()                          const;
    size_t      GetPropertyCount();
//-----------------------------------------------------------------------------
// Parent / children objects
//-----------------------------------------------------------------------------
    void        AddChild( Object child );
    Object      GetChild( size_t index ) const;
    Object      GetParent()              const;
    Objects     GetChildren()            const;
    size_t      GetChildCount()          const;
//-----------------------------------------------------------------------------
// Serialize
//-----------------------------------------------------------------------------
    wxXmlNode  *Serialize( wxXmlNode *parent );

private:
    friend class ObjectTree;

    wxXmlNode  *SerializeChildren( Objects children, wxXmlNode *parent );
    wxXmlNode  *SerializeProperties( Properties props, wxXmlNode *parent );

    ClassInfo   m_info;
    Object      m_parent;
    Objects     m_children;
    bool        m_expanded;
    bool        m_isRef;
    Events      m_events;
    Properties  m_props;
};
//=============================================================================
// ObjectTree Class
//=============================================================================
class ObjectTree
{
public:
    ObjectTree();
    ~ObjectTree();

    virtual Object  CreateObject    ( const wxString &className,
                                        Object parent = Object() );

    virtual Object  GetSelectedObject() const;
    Object          GetTopLevelObject( Object object ) const;

    virtual void    SelectObject    ( Object object, bool withEvent = true );

    virtual bool    Load            ( const wxString &filePath );
    bool            IsChildOk       ( Object parent, ClassInfo child );
//-----------------------------------------------------------------------------
// Serialize
//-----------------------------------------------------------------------------
    virtual bool    Serialize       ( wxXmlNode *rootNode );
    virtual bool    Serialize       ( const wxString &filePath );

private:
    size_t          GetSiblingsCount( Object parent, ClassInfo info );

    Object          DoCreateObject( Object parentObject, wxXmlNode *parentNode,
                                    bool isReference = false );
    Object m_root; // Root object
    Object m_sel;  // Selected object
};

#endif //__WXGUIDESIGNER_RTTI_TREE_H__
