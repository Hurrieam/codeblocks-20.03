#ifndef EDITORTWEAKSCONFDLG_H
#define EDITORTWEAKSCONFDLG_H

#include <configurationpanel.h>
//(*Headers(EditorTweaksConfDlg)
#include <wx/panel.h>
#include <wx/spinctrl.h>
//*)

class EditorTweaksConfDlg: public cbConfigurationPanel
{
	public:

		EditorTweaksConfDlg(wxWindow* parent);
		virtual ~EditorTweaksConfDlg();

		//(*Declarations(EditorTweaksConfDlg)
		wxSpinCtrl* SpinCtrl1;
		//*)

	protected:

		//(*Identifiers(EditorTweaksConfDlg)
		//*)

	private:

		//(*Handlers(EditorTweaksConfDlg)
		//*)
        wxString GetTitle() const { return _("EditorTweaks settings"); }
        wxString GetBitmapBaseName() const { return _T("EditorTweaks"); }
        void OnApply() { SaveSettings(); }
        void OnCancel() {}
        void SaveSettings();

		DECLARE_EVENT_TABLE()
};

#endif
