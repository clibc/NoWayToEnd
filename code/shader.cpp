#include "shader.h"

static const GLchar *default_vs = {
    "#version 330 core\n"
    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec2 texCoord;\n"
    "out vec2 TexCoord;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position, 1.0);\n"
    "TexCoord = texCoord;\n"
    "}\0"};
static const GLchar *default_fs = {
    "#version 330 core\n"
    "in vec2 TexCoord;\n"
    "out vec4 color;\n"
    "uniform sampler2D texture;\n"
    "void main()\n"
    "{\n"
    "color = texture2D(texture, TexCoord);\n"
    "}\0"};

void create_shader(shader &sh, const char *vs, const char *fs)
{
    GLuint program = load_shader(vs, fs);
    sh.programID = program;
}

GLint get_uniform_location(shader &shdr, const char *name)
{
    return glGetUniformLocation(shdr.programID, name);
}

bool set_uniform_mat4(shader &shdr, const char *name, const glm::mat4 &matrix)
{
    glUseProgram(shdr.programID);
    auto loc = get_uniform_location(shdr, name);
    if (loc == -1)
    {
        debug("Error setting uniform: " << name);
        return false;
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
    return true;
}

bool set_uniform_vec2(shader &shdr, const char *name, const glm::vec2 &vector)
{
    glUseProgram(shdr.programID);
    auto loc = get_uniform_location(shdr, name);
    if (loc == -1)
    {
        debug("Error setting uniform: " << name);
        return false;
    }
    glUniform2f(loc, vector.x, vector.y);
    return true;
}

bool set_uniform_vec3(shader &shdr, const char *name, const glm::vec3 &vector)
{
    glUseProgram(shdr.programID);
    auto loc = get_uniform_location(shdr, name);
    if (loc == -1)
    {
        debug("Error setting uniform: " << name);
        return false;
    }
    glUniform3f(loc, vector.x, vector.y, vector.z);
    return true;
}

shader load_default_shader()
{
    GLuint vsID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fsID = glCreateShader(GL_FRAGMENT_SHADER);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    debug("Compiling Default Vertex Shader...");
    glShaderSource(vsID, 1, &default_vs, NULL);
    glCompileShader(vsID);

    glGetShaderiv(vsID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vsID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(vsID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        debug(&VertexShaderErrorMessage[0]);
    }

    debug("Compiling Default Fragment Shader...");
    glShaderSource(fsID, 1, &default_fs, NULL);
    glCompileShader(fsID);

    glGetShaderiv(fsID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fsID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(fsID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        debug(&VertexShaderErrorMessage[0]);
    }

    debug("Linking Default program");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, vsID);
    glAttachShader(ProgramID, fsID);
    glLinkProgram(ProgramID);

    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        debug(ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, vsID);
    glDetachShader(ProgramID, fsID);

    glDeleteShader(vsID);
    glDeleteShader(fsID);

    shader sh = {ProgramID};
    return sh;
}

GLuint load_shader(const char *vs, const char *fs)
{
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vs, std::ios::in);
    if (VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        debug("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !");
        getchar();
        return 0;
    }

    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fs, std::ios::in);
    if (FragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    debug("Compiling shader : " << vs);
    char const *VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        debug(&VertexShaderErrorMessage[0]);
    }

    debug("Compiling shader : " << fs);
    char const *FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        debug(&FragmentShaderErrorMessage[0]);
    }

    debug("Linking program");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        debug(ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}
