#include <windows.h>

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;
std::wstring quoteArgument(const std::wstring& argument)
{
    if (argument.empty())
        return L"\"\"";

    bool needsQuotes = false;

    for (wchar_t c : argument)
    {
        if (c == L' ' || c == L'\t' || c == L'"')
        {
            needsQuotes = true;
            break;
        }
    }

    if (!needsQuotes)
        return argument;

    std::wstring result = L"\"";
    unsigned int backslashes = 0;

    for (wchar_t c : argument)
    {
        if (c == L'\\')
        {
            backslashes++;
        }
        else if (c == L'"')
        {
            result.append(backslashes * 2 + 1, L'\\');
            result += L'"';
            backslashes = 0;
        }
        else
        {
            result.append(backslashes, L'\\');
            result += c;
            backslashes = 0;
        }
    }

    result.append(backslashes * 2, L'\\');
    result += L'"';

    return result;
}

bool fileExists(const std::wstring& path)
{
    std::error_code error;
    return fs::is_regular_file(fs::path(path), error);
}

// Bir Bash adayını test eder
bool testBash(const std::wstring& bashPath)
{
    std::wstring commandLine =
        quoteArgument(bashPath) +
        L" -c \"exit 0\"";

    std::vector<wchar_t> commandBuffer(
        commandLine.begin(),
        commandLine.end()
    );

    commandBuffer.push_back(L'\0');

    STARTUPINFOW startupInfo{};
    PROCESS_INFORMATION processInfo{};

    startupInfo.cb = sizeof(startupInfo);
    startupInfo.dwFlags = STARTF_USESHOWWINDOW;
    startupInfo.wShowWindow = SW_HIDE;

    BOOL created = CreateProcessW(
        nullptr,
        commandBuffer.data(),
        nullptr,
        nullptr,
        FALSE,
        CREATE_NO_WINDOW,
        nullptr,
        nullptr,
        &startupInfo,
        &processInfo
    );

    if (!created)
        return false;

    WaitForSingleObject(processInfo.hProcess, 5000);

    DWORD exitCode = 1;

    if (!GetExitCodeProcess(processInfo.hProcess, &exitCode))
    {
        TerminateProcess(processInfo.hProcess, 1);
        exitCode = 1;
    }

    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    return exitCode == 0;
}

std::wstring getEnvironmentVariableValue(const wchar_t* name)
{
    DWORD size = GetEnvironmentVariableW(name, nullptr, 0);

    if (size == 0)
        return L"";

    std::vector<wchar_t> buffer(size);

    GetEnvironmentVariableW(
        name,
        buffer.data(),
        size
    );

    return std::wstring(buffer.data());
}

// Kullanılabilecek Bash yollarını toplar
std::vector<std::wstring> getBashCandidates()
{
    std::vector<std::wstring> candidates;

    std::wstring programFiles = getEnvironmentVariableValue(L"ProgramFiles");
    std::wstring localAppData = getEnvironmentVariableValue(L"LOCALAPPDATA");
    std::wstring userProfile = getEnvironmentVariableValue(L"USERPROFILE");

    // Git Bash
    if (!programFiles.empty())
    {
        candidates.push_back(
            programFiles + L"\\Git\\bin\\bash.exe"
        );

        candidates.push_back(
            programFiles + L"\\Git\\usr\\bin\\bash.exe"
        );
    }

    if (!localAppData.empty())
    {
        candidates.push_back(
            localAppData + L"\\Programs\\Git\\bin\\bash.exe"
        );

        candidates.push_back(
            localAppData + L"\\Programs\\Git\\usr\\bin\\bash.exe"
        );
    }

    // MSYS2
    candidates.push_back(L"C:\\msys64\\usr\\bin\\bash.exe");
    candidates.push_back(L"C:\\msys32\\usr\\bin\\bash.exe");

    // Cygwin
    candidates.push_back(L"C:\\cygwin64\\bin\\bash.exe");
    candidates.push_back(L"C:\\cygwin\\bin\\bash.exe");

    // PATH içindeki bash.exe
    wchar_t pathBuffer[MAX_PATH];

    DWORD result = SearchPathW(
        nullptr,
        L"bash.exe",
        nullptr,
        MAX_PATH,
        pathBuffer,
        nullptr
    );

    if (result > 0 && result < MAX_PATH)
    {
        std::wstring pathFromEnvironment(pathBuffer);

        // WindowsApps içindeki WSL başlatıcısını kullanma
        if (pathFromEnvironment.find(L"WindowsApps") == std::wstring::npos)
        {
            candidates.push_back(pathFromEnvironment);
        }
    }

    return candidates;
}

// İlk çalışan Bash'i bulur
std::wstring findWorkingBash(const std::wstring& ownPath)
{
    std::vector<std::wstring> candidates = getBashCandidates();

    for (const std::wstring& candidate : candidates)
    {
        if (!fileExists(candidate))
            continue;
        try
        {
            if (fs::equivalent(
                    fs::path(candidate),
                    fs::path(ownPath)))
            {
                continue;
            }
        }
        catch (...)
        {
          
        }

        std::wcout << L"Bash test ediliyor: "
                   << candidate << std::endl;

        if (testBash(candidate))
        {
            return candidate;
        }
    }

    return L"";
}

int launchBash(
    const std::wstring& bashPath,
    int argc,
    wchar_t* argv[]
)
{
    std::wstring commandLine = quoteArgument(bashPath);
    for (int i = 1; i < argc; i++)
    {
        commandLine += L" ";
        commandLine += quoteArgument(argv[i]);
    }

    std::vector<wchar_t> commandBuffer(
        commandLine.begin(),
        commandLine.end()
    );

    commandBuffer.push_back(L'\0');

    STARTUPINFOW startupInfo{};
    PROCESS_INFORMATION processInfo{};

    startupInfo.cb = sizeof(startupInfo);

    BOOL created = CreateProcessW(
        nullptr,
        commandBuffer.data(),
        nullptr,
        nullptr,
        TRUE,
        0,
        nullptr,
        nullptr,
        &startupInfo,
        &processInfo
    );

    if (!created)
    {
        std::wcerr << L"Bash başlatılamadı. Windows hatası: "
                   << GetLastError() << std::endl;

        return 1;
    }

    WaitForSingleObject(
        processInfo.hProcess,
        INFINITE
    );

    DWORD exitCode = 1;

    GetExitCodeProcess(
        processInfo.hProcess,
        &exitCode
    );

    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    return static_cast<int>(exitCode);
}

int wmain(int argc, wchar_t* argv[])
{
    wchar_t ownPathBuffer[MAX_PATH];

    GetModuleFileNameW(
        nullptr,
        ownPathBuffer,
        MAX_PATH
    );

    std::wstring ownPath(ownPathBuffer);

    std::wstring bashPath = findWorkingBash(ownPath);

    if (bashPath.empty())
    {
        std::wcerr << std::endl;
        std::wcerr << L"Kullanılabilir bir Bash bulunamadı."
                   << std::endl;
        std::wcerr << L"Git Bash, MSYS2 veya Cygwin kurulumu gerekli."
                   << std::endl;

        return 1;
    }

    std::wcout << std::endl;
    std::wcout << L"Kullanılacak Bash: "
               << bashPath << std::endl;

    return launchBash(
        bashPath,
        argc,
        argv
    );
}
