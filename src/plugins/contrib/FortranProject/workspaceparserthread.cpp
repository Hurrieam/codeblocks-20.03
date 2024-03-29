
#include "workspaceparserthread.h"

#include <sdk.h>
#ifndef CB_PRECOMP
    #include <logmanager.h>
#endif

#include "parserthreadf.h"
#include "nativeparserf.h"

wxMutex s_WorkspaceParserMutex;
wxMutex s_NewTokensMutex;

WorkspaceParserThread::WorkspaceParserThread(NativeParserF* parent, int idWSPThreadEvent) :
    m_pNativeParser(parent),
    m_idWSPThreadEvent(idWSPThreadEvent)
{
}

WorkspaceParserThread::~WorkspaceParserThread()
{
}

int WorkspaceParserThread::Execute()
{
    s_WorkspaceParserMutex.Lock();
    ParseFiles();
    s_WorkspaceParserMutex.Unlock();

    return 0;
}

void WorkspaceParserThread::ParseFiles()
{
    TokensArrayF* pTokens = new TokensArrayF();
    IncludeDB* pIncludeDB = new IncludeDB();
    wxArrayString* pWSFiles = m_pNativeParser->GetWSFiles();
    ArrayOfFortranSourceForm* pWSFileForms = m_pNativeParser->GetWSFileForms();
    wxArrayString* pWSProjFilenames = m_pNativeParser->GetWSFileProjFilenames();

    for (size_t i=0; i<pWSFiles->size(); i++)
    {
        ParserThreadF* thread = new ParserThreadF(pWSProjFilenames->Item(i), UnixFilename(pWSFiles->Item(i)), pTokens,
                                                  pWSFileForms->at(i), false, pIncludeDB);
        thread->Parse();
        delete thread;
    }
    s_NewTokensMutex.Lock();
    m_pNativeParser->GetParser()->SetNewTokens(pTokens);
    m_pNativeParser->GetParser()->SetNewIncludeDB(pIncludeDB);
    s_NewTokensMutex.Unlock();

    wxCommandEvent event( wxEVT_COMMAND_ENTER, m_idWSPThreadEvent );
    m_pNativeParser->AddPendingEvent(event);
}
