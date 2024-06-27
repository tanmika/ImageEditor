//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_TOOLS_H
#define QT_PRJ_IMAGE_EDITOR_TOOLS_H


#include "Define.h"
#include "Shader.h"
#include "Timer.h"
#include <codecvt>
#include <locale>
#include <qopengl.h>
#include <QDir>

class FontTable;
std::ostream &operator<<(std::ostream &os, FontTable &fontTable);

inline std::ostream &operator<<(std::ostream &os, const Vec2 &vec)
{
    os << "Vec2(" << vec.x << ", " << vec.y << ")";
    return os;
}
inline std::ostream &operator<<(std::ostream &os, const Vec3 &vec)
{
    os << "Vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}
inline std::ostream &operator<<(std::ostream &os, const Vec4 &vec)
{
    os << "Vec4(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return os;
}
inline std::ostream &operator<<(std::ostream &os, const Mat4 &mat)
{
    os << "Mat4(" << std::endl;
    for ( int i = 0; i < 4; i++ )
    {
        os << "  ";
        for ( int j = 0; j < 4; j++ )
        {
            os << mat[i][j] << " ";
        }
        os << std::endl;
    }
    os << ")";
    return os;
}

namespace ToolsPrivate
{
    static char* GetAbsPath(const char* path)
    {
        char* absPath = new char[1024];
        if ( realpath(path, absPath) == nullptr )
        {
            std::cerr << "realpath():" << absPath << " error\n";
            return nullptr;
        }
        return absPath;
    }
}
namespace Tools
{
    template<typename T, typename... Args>
    inline static char* SpliceString(T str1, Args... args)
    {
        std::ostringstream oss;
        oss << str1;
        ((oss << args), ...);
        String resultString = oss.str();
        char* result = new char[resultString.size() + 1];
        strcpy(result, resultString.c_str());
        return result;
    }

    inline static String GetFileNameWithoutExtension(const String& path)
    {
        size_t lastSlashPos = path.find_last_of("/\\");
        size_t lastDotPos = path.find_last_of('.');
        String fileName = path.substr(lastSlashPos + 1, lastDotPos - lastSlashPos - 1);
        return fileName;
    }

    inline static char* LocalPath(const char* path = nullptr)
    {
        auto toRoot = TO_ROOT_PATH;
        if ( path == nullptr )
            return ToolsPrivate::GetAbsPath(toRoot);
        size_t len = strlen(toRoot) + strlen(path) + 1;
        char* fullPath = new char[len];
        strcpy(fullPath, toRoot);
        strcat(fullPath, path);
        return ToolsPrivate::GetAbsPath(fullPath);
    }

    inline static char* ShaderPath(const char* name = nullptr)
    {
        if(!name || std::strlen(name) == 0)
            return LocalPath(SHADER_PATH);
        return LocalPath(SpliceString(SHADER_PATH, name));
    }

    inline static char* TexturePath(const char* name = nullptr)
    {
        if(!name || std::strlen(name) == 0)
            return LocalPath(PICTURE_PATH);
        return LocalPath(SpliceString(PICTURE_PATH, name));
    }

    inline static void TraverseFolder(const QString& folderPath, Vector<String>& fileList)
    {
        QDir dir(folderPath);

        QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

        for (const QFileInfo& fileInfo: fileInfoList)
        {
            if ( fileInfo.isFile())
            {
                QString relativeFilePath = dir.relativeFilePath(fileInfo.filePath());
                fileList.push_back(relativeFilePath.toStdString());
            }
            else if ( fileInfo.isDir())
            {
                TraverseFolder(fileInfo.filePath(), fileList);
            }
        }
    }

    inline static void TraverseFolder(const char* folderPath, Vector<String>& fileList)
    {
        TraverseFolder(QString(folderPath), fileList);
    }

    inline static void GLBindBufferEBO(GLuint& EBO, Vector<GLuint>& index)
    {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(GLuint), index.data(), GL_STATIC_DRAW);
    }

    inline static SharedPtr<Shader> GetDefaultShapeShader()
    {
        static SharedPtr<Shader> shader = std::make_shared<Shader>();
        if ( !shader->IsInit())
            shader->InitShaderFromFile(
                    ShaderPath("DefaultShapeShaderVert.glsl"),
                    ShaderPath("DefaultShapeShaderFrag.glsl"));
        return shader;
    }

    inline static void StartTimer(const String& name)
    {
        TimerManager::Instance().StartTimer(name);
    }

    inline static void StopTimer(const String& name)
    {
        TimerManager::Instance().StopTimer(name);
    }

    inline static String char32_to_utf8(char32_t charStr)
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.to_bytes(charStr);
    }

    inline static String GetGlobalIDString()
    {
        static int id = 0;
        return std::to_string(id++);
    }

    inline static size_t StringToSize_tNoThrow(String argv)
    {
        size_t result = 0;
        for (int i = 0; i < argv.size(); i++){
            result = result * 10 + argv[i] - '0';
        }
        return result;
    }

    inline static int StringToIntNoThrow(String argv)
    {
        int result = 0;
        bool isNegative = argv[0] == '-';
        for(int i = isNegative; i < argv.size(); i++){
            result = result * 10 + argv[i] - '0';
        }
        return isNegative ? -result : result;
    }

    inline static bool StringToBoolNoThrow(String argv)
    {
        return argv == "true" || "True" || "1" || "TRUE" || "T";
    }

    inline static String Vec4ToString(Vec4 argv)
    {
        String result = "";
        for (int i = 0; i < 4; i++){
            result += std::to_string(argv[i]);
            if (i != 3){
                result += ",";
            }
        }
        return result;
    }

    inline static Vec4 StringToVec4NoThrow(String argv)
    {
        Vec4 result;
        int index = 0;
        for (int i = 0; i < argv.size(); i++){
            if (argv[i] == ','){
                index++;
                continue;
            }
            result[index] = result[index] * 10 + argv[i] - '0';
        }
        return result;
    }

    inline static String GetFontStyle(const String& fontFullStyleName, bool& bold, bool& italic)
    {
        bold = false;
        italic = false;

        String result = fontFullStyleName;
        if(result.empty())
            return "Regular";
        else if(result == "Bold"){
            bold = true;
            return "Regular";
        } else if(result == "Italic"){
            italic = true;
            return "Regular";
        }

        if(result.length() < 6)
            return result;
        std::size_t pos = result.find(" Bold ");
        if (pos != String::npos) {
            bold = true;
            result.erase(pos, 6);
        } else {
            // Check if "Bold" is at the start
            if (result.find("Bold ") == 0) {
                bold = true;
                result.erase(0, 5);
            }
            // Check if "Bold" is at the end
            pos = result.rfind(" Bold");
            if (pos == result.length() - 5) {
                bold = true;
                result.erase(pos, 5);
            }
        }

        if(result == "Italic")
        {
            italic = true;
            return "Regular";
        }
        if(result.length() < 6)
            return result;
        pos = result.find(" Italic ");
        if (pos != std::string::npos) {
            italic = true;
            result.erase(pos, 8);
        } else {
            if(result.length() < 7)
                return result;
            // Check if "Italic" is at the start
            if (result.find("Italic ") == 0) {
                italic = true;
                result.erase(0, 7);
            }
            // Check if "Italic" is at the end
            pos = result.rfind(" Italic");
            if (pos == result.length() - 7) {
                italic = true;
                result.erase(pos, 7);
            }
        }

        result.erase(0, result.find_first_not_of(' '));
        result.erase(result.find_last_not_of(' ') + 1);

        if (result.empty()) {
            return "Regular";
        }

        return result;
    }
}


#endif //QT_PRJ_IMAGE_EDITOR_TOOLS_H
