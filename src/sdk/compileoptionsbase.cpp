/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 *
 * $Revision: 11887 $
 * $Id: compileoptionsbase.cpp 11887 2019-10-26 09:12:28Z fuscated $
 * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/branches/release-20.xx/src/sdk/compileoptionsbase.cpp $
 */

#include "sdk_precomp.h"

#ifndef CB_PRECOMP
    #include "compileoptionsbase.h"
    #include "sdk_events.h"
    #include "manager.h"
    #include "macrosmanager.h"
#endif

namespace { static const bool s_case_sensitive = platform::windows ? false : true; }

CompileOptionsBase::CompileOptionsBase()
    : m_Platform(spAll),
    m_LinkerExecutable(LinkerExecutableOption::AutoDetect),
    m_Modified(false),
    m_AlwaysRunPostCmds(false)
{
    //ctor
}

CompileOptionsBase::~CompileOptionsBase()
{
    //dtor
}

void CompileOptionsBase::AddPlatform(int platform)
{
    if (m_Platform & platform)
        return;
    m_Platform |= platform;
    SetModified(true);
}

void CompileOptionsBase::RemovePlatform(int platform)
{
    if (!(m_Platform & platform))
        return;
    m_Platform &= ~platform;
    SetModified(true);
}

void CompileOptionsBase::SetPlatforms(int platforms)
{
    if (m_Platform == platforms)
        return;
    m_Platform = platforms;
    SetModified(true);
}

int CompileOptionsBase::GetPlatforms() const
{
    return m_Platform;
}

bool CompileOptionsBase::SupportsCurrentPlatform() const
{
    if(platform::windows)
        return m_Platform & spWindows;
    if(platform::Unix)
        return m_Platform & spUnix;
    if(platform::macosx)
        return m_Platform & spMac;

    return false;
}

void CompileOptionsBase::SetLinkerOptions(const wxArrayString& linkerOpts)
{
    if (m_LinkerOptions == linkerOpts)
        return;
    m_LinkerOptions = linkerOpts;
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetLinkerOptions() const
{
    return m_LinkerOptions;
}

void CompileOptionsBase::SetLinkLibs(const wxArrayString& linkLibs)
{
    if (m_LinkLibs == linkLibs)
        return;
    m_LinkLibs = linkLibs;
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetLinkLibs() const
{
    return m_LinkLibs;
}

void CompileOptionsBase::SetCompilerOptions(const wxArrayString& compilerOpts)
{
    if (m_CompilerOptions == compilerOpts)
        return;
    m_CompilerOptions = compilerOpts;
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetCompilerOptions() const
{
    return m_CompilerOptions;
}

void CompileOptionsBase::SetResourceCompilerOptions(const wxArrayString& resourceCompilerOpts)
{
    if (m_ResourceCompilerOptions == resourceCompilerOpts)
        return;
    m_ResourceCompilerOptions = resourceCompilerOpts;
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetResourceCompilerOptions() const
{
    return m_ResourceCompilerOptions;
}

void CompileOptionsBase::SetIncludeDirs(const wxArrayString& includeDirs)
{
    if (m_IncludeDirs == includeDirs)
        return;

    // make sure we don't have duplicate entries
    // that's why we don't assign the array but rather copy it entry by entry...

    m_IncludeDirs.Clear();
    for (size_t i = 0; i < includeDirs.GetCount(); ++i)
    {
        wxString entry = UnixFilename(includeDirs[i]);
        if (m_IncludeDirs.Index(entry, s_case_sensitive) == wxNOT_FOUND)
            m_IncludeDirs.Add(entry);
    }
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetIncludeDirs() const
{
    return m_IncludeDirs;
}

void CompileOptionsBase::SetResourceIncludeDirs(const wxArrayString& resIncludeDirs)
{
    if (m_ResIncludeDirs == resIncludeDirs)
        return;

    // make sure we don't have duplicate entries
    // that's why we don't assign the array but rather copy it entry by entry...

    m_ResIncludeDirs.Clear();
    for (size_t i = 0; i < resIncludeDirs.GetCount(); ++i)
    {
        wxString entry = UnixFilename(resIncludeDirs[i]);
        if (m_ResIncludeDirs.Index(entry, s_case_sensitive) == wxNOT_FOUND)
            m_ResIncludeDirs.Add(entry);
    }
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetResourceIncludeDirs() const
{
    return m_ResIncludeDirs;
}

void CompileOptionsBase::SetLibDirs(const wxArrayString& libDirs)
{
    if (m_LibDirs == libDirs)
        return;

    // make sure we don't have duplicate entries
    // that's why we don't assign the array but rather copy it entry by entry...

    m_LibDirs.Clear();
    for (size_t i = 0; i < libDirs.GetCount(); ++i)
    {
        wxString entry = UnixFilename(libDirs[i]);
        if (m_LibDirs.Index(entry, s_case_sensitive) == wxNOT_FOUND)
            m_LibDirs.Add(entry);
    }
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetLibDirs() const
{
    return m_LibDirs;
}

void CompileOptionsBase::SetBuildScripts(const wxArrayString& scripts)
{
    if (m_Scripts == scripts)
        return;

    // make sure we don't have duplicate entries
    // that's why we don't assign the array but rather copy it entry by entry...

    m_Scripts.Clear();
    for (size_t i = 0; i < scripts.GetCount(); ++i)
    {
        wxString entry = UnixFilename(scripts[i]);
        if (m_Scripts.Index(entry, s_case_sensitive) == wxNOT_FOUND)
            m_Scripts.Add(entry);
    }
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetBuildScripts() const
{
    return m_Scripts;
}

void CompileOptionsBase::SetCommandsBeforeBuild(const wxArrayString& commands)
{
    if (m_CmdsBefore == commands)
        return;
    m_CmdsBefore = commands;
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetCommandsBeforeBuild() const
{
    return m_CmdsBefore;
}

void CompileOptionsBase::SetCommandsAfterBuild(const wxArrayString& commands)
{
    if (m_CmdsAfter == commands)
        return;
    m_CmdsAfter = commands;
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetCommandsAfterBuild() const
{
    return m_CmdsAfter;
}

bool CompileOptionsBase::GetAlwaysRunPostBuildSteps() const
{
    return m_AlwaysRunPostCmds;
}

void CompileOptionsBase::SetAlwaysRunPostBuildSteps(bool always)
{
    if (m_AlwaysRunPostCmds == always)
        return;
    m_AlwaysRunPostCmds = always;
    SetModified(true);
}

bool CompileOptionsBase::GetModified() const
{
    return m_Modified;
}

void CompileOptionsBase::SetModified(bool modified)
{
    m_Modified = modified;
}

void CompileOptionsBase::AddLinkerOption(const wxString& option)
{
    if (m_LinkerOptions.Index(option, s_case_sensitive) == wxNOT_FOUND)
    {
        m_LinkerOptions.Add(option);
        SetModified(true);
    }
}

void CompileOptionsBase::AddLinkLib(const wxString& option)
{
    if (m_LinkLibs.Index(option, s_case_sensitive) == wxNOT_FOUND)
    {
        m_LinkLibs.Add(option);
        SetModified(true);
    }
}

void CompileOptionsBase::AddCompilerOption(const wxString& option)
{
    if (m_CompilerOptions.Index(option, s_case_sensitive) == wxNOT_FOUND)
    {
        m_CompilerOptions.Add(option);
        SetModified(true);
    }
}

void CompileOptionsBase::AddResourceCompilerOption(const wxString& option)
{
    if (m_ResourceCompilerOptions.Index(option, s_case_sensitive) == wxNOT_FOUND)
    {
        m_ResourceCompilerOptions.Add(option);
        SetModified(true);
    }
}

void CompileOptionsBase::AddIncludeDir(const wxString& option)
{
    wxString entry = UnixFilename(option);
    if (m_IncludeDirs.Index(entry, s_case_sensitive) == wxNOT_FOUND)
    {
        m_IncludeDirs.Add(entry);
        SetModified(true);
    }
}

void CompileOptionsBase::AddResourceIncludeDir(const wxString& option)
{
    wxString entry = UnixFilename(option);
    if (m_ResIncludeDirs.Index(entry, s_case_sensitive) == wxNOT_FOUND)
    {
        m_ResIncludeDirs.Add(entry);
        SetModified(true);
    }
}

void CompileOptionsBase::AddLibDir(const wxString& option)
{
    wxString entry = UnixFilename(option);
    if (m_LibDirs.Index(entry, s_case_sensitive) == wxNOT_FOUND)
    {
        m_LibDirs.Add(entry);
        SetModified(true);
    }
}

void CompileOptionsBase::AddCommandsBeforeBuild(const wxString& command)
{
    m_CmdsBefore.Add(command);
    SetModified(true);
}

void CompileOptionsBase::AddCommandsAfterBuild(const wxString& command)
{
    m_CmdsAfter.Add(command);
    SetModified(true);
}

void CompileOptionsBase::AddBuildScript(const wxString& script)
{
    wxString envopt = UnixFilename(script);
    if (m_Scripts.Index(envopt, s_case_sensitive) == wxNOT_FOUND)
    {
        m_Scripts.Add(envopt);
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceLinkerOption(const wxString& option, const wxString& new_option)
{
    int idx = m_LinkerOptions.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_LinkerOptions.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceLinkLib(const wxString& option, const wxString& new_option)
{
    int idx = m_LinkLibs.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_LinkLibs.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceCompilerOption(const wxString& option, const wxString& new_option)
{
    int idx = m_CompilerOptions.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_CompilerOptions.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceResourceCompilerOption(const wxString& option, const wxString& new_option)
{
    int idx = m_ResourceCompilerOptions.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_ResourceCompilerOptions.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceIncludeDir(const wxString& option, const wxString& new_option)
{
    int idx = m_IncludeDirs.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_IncludeDirs.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceResourceIncludeDir(const wxString& option, const wxString& new_option)
{
    int idx = m_ResIncludeDirs.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_ResIncludeDirs.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceLibDir(const wxString& option, const wxString& new_option)
{
    int idx = m_LibDirs.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_LibDirs.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveLinkerOption(const wxString& option)
{
    int idx = m_LinkerOptions.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_LinkerOptions.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveLinkLib(const wxString& option)
{
    int idx = m_LinkLibs.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_LinkLibs.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveCompilerOption(const wxString& option)
{
    int idx = m_CompilerOptions.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_CompilerOptions.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveResourceCompilerOption(const wxString& option)
{
    int idx = m_ResourceCompilerOptions.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_ResourceCompilerOptions.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveIncludeDir(const wxString& option)
{
    wxString entry = UnixFilename(option);
    int idx = m_IncludeDirs.Index(entry, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_IncludeDirs.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveResourceIncludeDir(const wxString& option)
{
    wxString entry = UnixFilename(option);
    int idx = m_ResIncludeDirs.Index(entry, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_ResIncludeDirs.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveLibDir(const wxString& option)
{
    wxString entry = UnixFilename(option);
    int idx = m_LibDirs.Index(entry, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_LibDirs.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveCommandsBeforeBuild(const wxString& command)
{
    m_CmdsBefore.Remove(command);
    SetModified(true);
}

void CompileOptionsBase::RemoveCommandsAfterBuild(const wxString& command)
{
    m_CmdsAfter.Remove(command);
    SetModified(true);
}

void CompileOptionsBase::RemoveBuildScript(const wxString& script)
{
    wxString envopt = UnixFilename(script);
    int idx = m_Scripts.Index(envopt, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_Scripts.RemoveAt(idx);
        SetModified(true);
    }
}

bool CompileOptionsBase::SetVar(const wxString& key, const wxString& value, bool onlyIfExists)
{
    if (onlyIfExists)
    {
        StringHash::iterator it = m_Vars.find(key);
        if (it == m_Vars.end())
            return false;
        it->second = value;
        return true;
    }

    m_Vars[key] = value;
    SetModified(true);
    return true;
}

bool CompileOptionsBase::UnsetVar(const wxString& key)
{
    StringHash::iterator it = m_Vars.find(key);
    if (it != m_Vars.end())
    {
        m_Vars.erase(it);
        SetModified(true);
        return true;
    }
    return false;
}

void CompileOptionsBase::UnsetAllVars()
{
    m_Vars.clear();
}

bool CompileOptionsBase::HasVar(const wxString& key) const
{
    StringHash::const_iterator it = m_Vars.find(key);
    if (it != m_Vars.end())
        return true;

    return false;
}

const wxString& CompileOptionsBase::GetVar(const wxString& key) const
{
    StringHash::const_iterator it = m_Vars.find(key);
    if (it != m_Vars.end())
        return it->second;

    static wxString emptystring = wxEmptyString;
    return emptystring;
}

const StringHash& CompileOptionsBase::GetAllVars() const
{
    return m_Vars;
}

void CompileOptionsBase::SetLinkerExecutable(LinkerExecutableOption option)
{
    if (m_LinkerExecutable == option)
        return;

    // We need to do this range check because this function could be called from scripting and there
    // is no range checking done by the compiler.
    if (option>= LinkerExecutableOption::First && option <= LinkerExecutableOption::Last)
    {
        m_LinkerExecutable = option;
        SetModified(true);
    }
    else if (m_LinkerExecutable != LinkerExecutableOption::AutoDetect)
    {
        m_LinkerExecutable = LinkerExecutableOption::AutoDetect;
        SetModified(true);
    }
}

LinkerExecutableOption CompileOptionsBase::GetLinkerExecutable() const
{
    return m_LinkerExecutable;
}
