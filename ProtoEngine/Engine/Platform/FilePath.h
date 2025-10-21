#pragma once

#include <filesystem>

namespace ProtoEngine::Platform {

class FilePath {
public:
    FilePath(const std::string &path);
    ~FilePath();

    std::string GetAbsolutePath() const;
    bool Exists() const;
    bool IsDirectory() const;
    bool IsFile() const;

    std::string GetName() const;
    std::string GetExtension() const;

private:
    std::filesystem::path m_Path;
};
} // namespace ProtoEngine::Platform