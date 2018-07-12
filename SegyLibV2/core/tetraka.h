#ifndef TETRAKA_H
#define TETRAKA_H

#include <string>
#include <cstring>
#include <stdlib.h>
#include <cctype>
#include <algorithm>
#include <cmath>

#if defined(_WIN32) || defined(_WIN64)
    #include <sys/types.h>
    #include <sys/stat.h>
	#include <direct.h>
    #define stat _stat
#elif defined(__unix__)
    #include <sys/stat.h>
    #include <unistd.h>
    #include <linux/limits.h>
#endif

#define ldn Utility::longDescriptiveName

namespace tetraka{

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

static void replace(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

static inline bool is_number(const std::string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != HUGE_VAL;
}

static inline bool is_uint(const std::string& s){
    char* end = 0;
    unsigned long val=strtoul(s.c_str(), &end,10);
    return end != s.c_str() && val != HUGE_VAL;
}

static inline bool is_int(const std::string& s)
{
    if(is_uint(s))return true;
    else{
        char* end = 0;
        long val=strtol(s.c_str(), &end,10);
        return end != s.c_str() && val != HUGE_VAL;
    }
}

static inline bool isFileExist(const char* name) {
  struct stat buffer;
  return (stat (name, &buffer) == 0);
}

static inline bool isFileExist(const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

static inline bool isDirectoryExist(const char* path){
    struct stat buffer;
    if(stat (path, &buffer) == 0) return false;
    if(buffer.st_mode & S_IFDIR) return false;
    return true;
}

static inline bool isDirectoryExist(const std::string& path){
    return isDirectoryExist(path.c_str());
}

static inline bool isAbsolutePath(const char* path){
    if(strlen(path)<2)return false;
    #if defined(_WIN32) || defined(_WIN64)
        if(path[1]==':' && ((path[0]>='a' && path[0]<='z') || (path[0]>='A' && path[0]<='Z'))) return true;
        else return false;
    #elif defined(__unix__)
        return path[0]=='/';
    #endif
}

static inline bool isAbsolutePath(const std::string& path){
    return isAbsolutePath(path.c_str());
}

static inline bool fullPath(const std::string& path,std::string &fullPath){
#if defined(_WIN32) || defined(_WIN64)
    char full[_MAX_PATH];
    if(_fullpath(full,path.c_str(),_MAX_PATH)==NULL)return false;
    fullPath=full;
    return true;
#elif defined(__unix__)
    char full [PATH_MAX+1];
    char *ptr=realpath(path.c_str(), full);
    if(ptr==NULL)return false;
    fullPath=ptr;
    return true;
#endif
}

static inline bool createDirectory(const char* dirPath){
    int nError = 0;
    #if defined(_WIN32) || defined(_WIN64)
      nError = _mkdir(dirPath);
    #else
	  mode_t nMode = 0733;
      nError = mkdir(dirPath,nMode);
    #endif
    return nError==0;
}

static inline bool createDirectory(const std::string& dirPath){
    return createDirectory(dirPath.c_str());
}

static inline char getPathSeparator(){
#if defined(_WIN32) || defined(_WIN64)
    return '\\';
#elif defined(__unix__)
    return '/';
#endif
}

static inline void getPathToParentFolder(const std::string& path,std::string &parentFolderPath){
    size_t pos=path.find_last_of("/\\");
    if(pos==std::string::npos){
        parentFolderPath="";
    }else{
        parentFolderPath=path.substr(0,pos);
    }
}

static inline void getFileName(const std::string& path,std::string &fileName){
    size_t pos=path.find_last_of("/\\");
    if(pos==std::string::npos){
        fileName=path;
    }else{
        fileName=path.substr(pos+1);
    }
}

#if defined(_WIN32) || defined(_WIN64)

    static inline std::wstring utf8FilePathToPlatformFilePath(const std::string& utf8Path){
        std::wstring ret;
        int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
        if (len > 0)
        {
            ret.resize(len);
            MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &ret[0], len);
        }
        return ret;
    }
    
#elif defined(__unix__)

    static inline std::string utf8FilePathToPlatformFilePath(const std::string& utf8Path){
        return utf8Path;
    }

#endif


}

#endif // TETRAKA_H
