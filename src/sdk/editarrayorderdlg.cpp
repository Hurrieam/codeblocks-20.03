/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 *
 * $Revision: 11846 $
 * $Id: editarrayorderdlg.cpp 11846 2019-09-08 22:37:55Z fuscated $
 * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/branches/release-20.xx/src/sdk/editarrayorderdlg.cpp $
 */

#include "sdk_precomp.h"

#ifndef CB_PRECOMP
    #include <wx/xrc/xmlres.h>
    #include <wx/intl.h>
    #include <wx/button.h>
    #include <wx/listbox.h>
#endif

#include "editarrayorderdlg.h" // class's header file

BEGIN_EVENT_TABLE(EditArrayOrderDlg, wxScrollingDialog)
    EVT_UPDATE_UI( -1, EditArrayOrderDlg::OnUpdateUI)
    EVT_BUTTON(XRCID("btnMoveUp"), EditArrayOrderDlg::OnMoveUp)
    EVT_BUTTON(XRCID("btnMoveDown"), EditArrayOrderDlg::OnMoveDown)
END_EVENT_TABLE()

// class constructor
EditArrayOrderDlg::EditArrayOrderDlg(wxWindow* parent, const wxArrayString& array)
    : m_Array(array)
{
    wxXmlResource::Get()->LoadObject(this, parent, _T("dlgEditArrayOrder"),_T("wxScrollingDialog"));
    DoFillList();

    XRCCTRL(*this, "wxID_OK", wxButton)->SetDefault();
    wxListBox* list = XRCCTRL(*this, "lstItems", wxListBox);
    list->SetFocus();
}

// class destructor
EditArrayOrderDlg::~EditArrayOrderDlg()
{
}

void EditArrayOrderDlg::DoFillList()
{
    wxListBox* list = XRCCTRL(*this, "lstItems", wxListBox);
    list->Clear();
    for (unsigned int i = 0; i < m_Array.GetCount(); ++i)
        list->Append(m_Array[i]);
}

void EditArrayOrderDlg::OnUpdateUI(wxUpdateUIEvent& WXUNUSED(event))
{
    wxListBox* list = XRCCTRL(*this, "lstItems", wxListBox);

    XRCCTRL(*this, "btnMoveUp", wxButton)->Enable(list->GetSelection() > 0);
    XRCCTRL(*this, "btnMoveDown", wxButton)->Enable(list->GetSelection() >= 0 && list->GetSelection() < (int)list->GetCount() - 1);
}

void EditArrayOrderDlg::OnMoveUp(wxCommandEvent& WXUNUSED(event))
{
    wxListBox* list = XRCCTRL(*this, "lstItems", wxListBox);
    int sel = list->GetSelection();

    if (sel > 0)
    {
        wxString tmp = list->GetString(sel);
        list->Delete(sel);
        list->InsertItems(1, &tmp, sel - 1);
        list->SetSelection(sel - 1);
    }
}

void EditArrayOrderDlg::OnMoveDown(wxCommandEvent& WXUNUSED(event))
{
    wxListBox* list = XRCCTRL(*this, "lstItems", wxListBox);
    int sel = list->GetSelection();

    if (sel < (int)list->GetCount() - 1)
    {
        wxString tmp = list->GetString(sel);
        list->Delete(sel);
        list->InsertItems(1, &tmp, sel + 1);
        list->SetSelection(sel + 1);
    }
}

void EditArrayOrderDlg::EndModal(int retCode)
{
    if (retCode == wxID_OK)
    {
        wxListBox* list = XRCCTRL(*this, "lstItems", wxListBox);

        m_Array.Clear();
        for (int i = 0; i < (int)list->GetCount(); ++i)
            m_Array.Add(list->GetString(i));
    }

    wxScrollingDialog::EndModal(retCode);
}

