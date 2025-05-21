// Fill out your copyright notice in the Description page of Project Settings.


#include "JavaCodeCompilerLibrary.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include <string>

const FString testName = "Test.java";
const FString charName = "Character.java";
const FString logName = "cmd_log.txt";

FString UJavaCodeCompilerLibrary::CompileCode(FString fileName, FString code, FString testCode) {
    const FString savePath = FPaths::ProjectSavedDir();
    const FString filePath = FPaths::ProjectSavedDir() / fileName;
    const FString testPath = FPaths::ProjectSavedDir() / testName;
    const FString logPath = FPaths::ProjectSavedDir() / logName;
    
    if (!FFileHelper::SaveStringToFile(code, *filePath)) {
        return "File Error";
    }

    if (!FFileHelper::SaveStringToFile(testCode, *testPath)) {
        return "File Error";
    }

    std::string s1 = TCHAR_TO_UTF8(*savePath);
    std::string s2 = TCHAR_TO_UTF8(*filePath);
    std::string s3 = TCHAR_TO_UTF8(*logPath);
    std::string cmd = "cd \"" + s1 + "\" && javac -d . \"" + s2 + "\">\"" + s3 + "\" 2>&1";

    std::system(cmd.c_str());

    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*logPath)) {
        return "File Error";
    }

    FString fileLog;

    if (!FFileHelper::LoadFileToString(fileLog, *logPath)) {
        return "File Error";
    }

    s2 = TCHAR_TO_UTF8(*testPath);
    cmd = "cd \"" + s1 + "\" && javac -d . \"" + s2 + "\">\"" + s3 + "\" 2>&1";

    std::system(cmd.c_str());

    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*logPath)) {
        return "File Error";
    }

    FString testLog;

    if (!FFileHelper::LoadFileToString(testLog, *logPath)) {
        return "File Error";
    }

    FString log = fileLog + testLog;

    if (log == "") {
        return "Success";
    } else {
        FString path;
        FString rpl = fileName;
        FString slash = "/";
        FString backslash = "\\";
        path = filePath.Replace(*slash, *backslash, ESearchCase::CaseSensitive);
        log = log.Replace(*path, *rpl, ESearchCase::CaseSensitive);
        rpl = "Test.java";
        path = testPath.Replace(*slash, *backslash, ESearchCase::CaseSensitive);
        log = log.Replace(*path, *rpl, ESearchCase::CaseSensitive);
        return log;
    }
}

FString UJavaCodeCompilerLibrary::TestCode() {
    const FString filePath = FPaths::ProjectSavedDir();
    const FString logPath = FPaths::ProjectSavedDir() / logName;

    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*filePath) && 
            !FPlatformFileManager::Get().GetPlatformFile().FileExists(*logPath)) {
        return "File Error";
    }

    std::string s1 = TCHAR_TO_UTF8(*filePath);
    std::string s2 = TCHAR_TO_UTF8(*logPath);
    std::string cmd = "cd \"" + s1 + "\" && java fyp.Test >\"" + s2 + "\" 2>&1";

    std::system(cmd.c_str());

    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*logPath)) {
        return "File Error";
    }

    FString log;

    if (!FFileHelper::LoadFileToString(log, *logPath)) {
        return "File Error";
    }

    return log;
}

void UJavaCodeCompilerLibrary::CompileCharacter(FString code) {
    const FString savePath = FPaths::ProjectSavedDir();
    const FString filePath = FPaths::ProjectSavedDir() / charName;
    const FString logPath = FPaths::ProjectSavedDir() / logName;

    FFileHelper::SaveStringToFile(code, *filePath);

    std::string s1 = TCHAR_TO_UTF8(*savePath);
    std::string s2 = TCHAR_TO_UTF8(*filePath);
    std::string s3 = TCHAR_TO_UTF8(*logPath);
    std::string cmd = "cd \"" + s1 + "\" && javac -d . \"" + s2 + "\">\"" + s3 + "\" 2>&1";

    std::system(cmd.c_str());
}

FString UJavaCodeCompilerLibrary::RunCode(FString levelName) {
    const FString filePath = FPaths::ProjectSavedDir();
    const FString logPath = FPaths::ProjectSavedDir() / logName;

    std::string s1 = TCHAR_TO_UTF8(*filePath);
    std::string s2 = TCHAR_TO_UTF8(*levelName);
    std::string s3 = TCHAR_TO_UTF8(*logPath);
    std::string cmd = "cd \"" + s1 + "\" && java fyp." + s2 + " >\"" + s3 + "\" 2>&1";

    std::system(cmd.c_str());

    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*logPath)) {
        return "File Error";
    }

    FString log;

    if (!FFileHelper::LoadFileToString(log, *logPath)) {
        return "File Error";
    }

    return log;
}
