#include "ProtoEngine/Platform/FilePath.h"
#include "ProtoEngine/Core/Core.h"

namespace ProtoEngine::Platform {
FilePath::FilePath(const std::string &path) :
    m_Path(path)
{
    if (!Exists()) PE_LOG_WARNING("FilePath {} does not exist!", path);
}

FilePath::~FilePath()
{
}

bool FilePath::Exists() const
{
    return std::filesystem::exists(m_Path);
}

std::string FilePath::GetAbsolutePath() const
{
    return std::filesystem::absolute(m_Path).string();
}

std::string FilePath::GetExtension() const
{
    return std::filesystem::path(m_Path).extension().string();
}

std::string FilePath::GetName() const
{
    return std::filesystem::path(m_Path).stem().string();
}

bool FilePath::IsDirectory() const
{
    return std::filesystem::is_directory(m_Path);
}

bool FilePath::IsFile() const
{
    return std::filesystem::is_regular_file(m_Path);
}
} // namespace ProtoEngine::Platform
