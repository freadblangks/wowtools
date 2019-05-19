#include "COpenGLShaderManageComponent.h"

#include "COpenGLPCH.h"
#include "COpenGLDriver.h"
#include "CShaderUtil.h"
#include "CFileSystem.h"

COpenGLShaderManageComponent::COpenGLShaderManageComponent(const COpenGLDriver* driver)
	: Driver(driver), CurrentProgram(nullptr)
{

}

COpenGLShaderManageComponent::~COpenGLShaderManageComponent()
{
	Driver->GLExtension.extGlUseProgramObject(0);
}

COpenGLVertexShader* COpenGLShaderManageComponent::getVertexShader(const char* fileName, const std::set<std::string>& shaderMacro)
{
	std::string shaderMacroString = CShaderUtil::getShaderMacroString(shaderMacro);

	auto itr = VertexShaderMap.find(fileName);
	if (itr != VertexShaderMap.end())
	{
		const auto& macroMap = itr->second;	
		auto iter = macroMap.find(shaderMacroString);
		if (iter != macroMap.end())
			return iter->second;
	}

	COpenGLVertexShader* vshader = new COpenGLVertexShader(Driver, fileName, shaderMacro);
	if (!vshader->compile())
	{
		delete vshader;
		return nullptr;
	}

	VertexShaderMap[fileName][shaderMacroString] = vshader;

	return vshader;
}

COpenGLPixelShader* COpenGLShaderManageComponent::getPixelShader(const char* fileName, const std::set<std::string>& shaderMacro)
{
	std::string shaderMacroString = CShaderUtil::getShaderMacroString(shaderMacro);

	auto itr = PixelShaderMap.find(fileName);
	if (itr != PixelShaderMap.end())
	{
		const auto& macroMap = itr->second;
		auto iter = macroMap.find(shaderMacroString);
		if (iter != macroMap.end())
			return iter->second;
	}

	COpenGLPixelShader* pshader = new COpenGLPixelShader(Driver, fileName, shaderMacro);
	if (!pshader->compile())
	{
		delete pshader;
		return nullptr;
	}

	PixelShaderMap[fileName][shaderMacroString] = pshader;

	return pshader;
}

void COpenGLShaderManageComponent::addMacroByMaterial(const SMaterial& material, std::set<std::string>& shaderMacro) const
{
	if (material.isAlphaTest())
	{
		shaderMacro.insert("ALPHA_TEST");
	}
}

CGLProgram* COpenGLShaderManageComponent::findGLProgram(const COpenGLVertexShader* vshader, const COpenGLPixelShader* pshader) const
{
	ASSERT(vshader && pshader);
	auto itr1 = ProgramMap.find(vshader);
	if (itr1 != ProgramMap.end())
	{
		auto itr2 = itr1->second.find(pshader);
		if (itr2 != itr1->second.end())
			return itr2->second;
	}
	return nullptr;
}

CGLProgram* COpenGLShaderManageComponent::getGlProgram(const COpenGLVertexShader* vshader, const COpenGLPixelShader* pshader)
{
	CGLProgram* program = findGLProgram(vshader, pshader);
	if (!program)
	{
		program = createGLProgram(vshader, pshader);
		ProgramMap[vshader][pshader] = program;
	}

	return program;
}

CGLProgram* COpenGLShaderManageComponent::createGLProgram(const COpenGLVertexShader* vshader, const COpenGLPixelShader* pshader)
{
	if (!vshader || !pshader)
	{
		ASSERT(false);
		return nullptr;
	}

	GLhandleARB p = Driver->GLExtension.extGlCreateProgramObject();

	Driver->GLExtension.extGlAttachObject(p, (GLhandleARB)vshader->getGLShader());
	Driver->GLExtension.extGlAttachObject(p, (GLhandleARB)pshader->getGLShader());

	//bind ps output
	Driver->GLExtension.extGlBindFragDataLocation(p, 0, "COLOR0");
	Driver->GLExtension.extGlBindFragDataLocation(p, 1, "COLOR1");
	Driver->GLExtension.extGlBindFragDataLocation(p, 2, "COLOR2");
	Driver->GLExtension.extGlBindFragDataLocation(p, 3, "COLOR3");

	//link
	Driver->GLExtension.extGlLinkProgramARB(p);

	GLint status = 0;
	Driver->GLExtension.extGlGetObjectParameteriv(p, GL_OBJECT_LINK_STATUS_ARB, &status);

	if (!status)
	{
		g_FileSystem->writeLog(ELOG_GX, "GLSL shader program failed to link: ");
		// check error message and log it
		GLint maxLength = 0;
		GLsizei length;

		Driver->GLExtension.extGlGetObjectParameteriv(p, GL_OBJECT_INFO_LOG_LENGTH_ARB, &maxLength);

		GLcharARB *infoLog = new GLcharARB[maxLength];
		Driver->GLExtension.extGlGetInfoLog(p, maxLength, &length, infoLog);
		g_FileSystem->writeLog(ELOG_GX, "GLSL shader program failed to link: %s", reinterpret_cast<const char*>(infoLog));
		delete[] infoLog;

		//remove
		Driver->GLExtension.extGlDeleteObject(p);
		return nullptr;
	}

	CGLProgram* program = new CGLProgram(p);

	//get uniform info
	Driver->GLExtension.extGlUseProgramObject(p);

	GLint numUniforms = 0;
	Driver->GLExtension.extGlGetObjectParameteriv(p, GL_OBJECT_ACTIVE_UNIFORMS_ARB, &numUniforms);
	GLint maxLen = 0;
	Driver->GLExtension.extGlGetObjectParameteriv(p, GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB, &maxLen);

	//
	program->uniformList.resize(numUniforms);
	std::vector<char> buf;
	buf.resize(maxLen);
	for (int i = 0; i < (int)numUniforms; ++i)
	{
		SGLUniformInfo info;

		GLenum type;
		GLint length;
		GLint size;
		Driver->GLExtension.extGlGetActiveUniformARB(p, i, maxLen, &length, &size, &type, (GLcharARB*)buf.data());
		buf[length] = '\0';
		std::string name = buf.data();
		info.dimension = (uint8_t)size;
		info.type = type;
		info.location = Driver->GLExtension.extGlGetUniformLocationARB(p, name.c_str());

		//delete "[]" in array names
		std::size_t offset = name.find('[', 0);
		if (offset != std::string::npos)
		{
			name = name.substr(0, offset);
		}

		ASSERT(type != GL_SAMPLER_1D_ARB && type != GL_SAMPLER_3D_ARB);

		program->uniformList.emplace_back(info);
		program->uniformNameIndexMap[name] = (uint32_t)program->uniformList.size() - 1;
		
		if (info.isTexture())
		{
			info.textureIndex = (int)program->textureNameIndexMap.size();
			program->textureNameIndexMap[name] = (uint32_t)program->uniformList.size() - 1;
			//
			Driver->GLExtension.extGlUniform1iv(info.location, info.type, &(GLint)info.textureIndex);
		}
		else
		{
			info.textureIndex = -1;
		}
	}

	Driver->GLExtension.extGlUseProgramObject(0);

	return program;
}

void COpenGLShaderManageComponent::setShaderUniformF(uint32_t location, GLenum type, const float* srcData, uint32_t size)
{
	uint32_t count = size / sizeof(float);

	switch (type)
	{
	case GL_FLOAT:
		Driver->GLExtension.extGlUniform1fv(location, count, srcData);
		break;
	case GL_FLOAT_VEC2_ARB:
		Driver->GLExtension.extGlUniform2fv(location, count / 2, srcData);
		break;
	case GL_FLOAT_VEC3_ARB:
		Driver->GLExtension.extGlUniform3fv(location, count / 3, srcData);
		break;
	case GL_FLOAT_VEC4_ARB:
		Driver->GLExtension.extGlUniform4fv(location, count / 4, srcData);
		break;
	case GL_FLOAT_MAT2_ARB:
		Driver->GLExtension.extGlUniformMatrix2fv(location, count / 4, GL_FALSE, srcData);
		break;
	case GL_FLOAT_MAT3_ARB:
		Driver->GLExtension.extGlUniformMatrix3fv(location, count / 9, GL_FALSE, srcData);
		break;
	case GL_FLOAT_MAT4_ARB:
		Driver->GLExtension.extGlUniformMatrix4fv(location, count / 16, GL_FALSE, srcData);
		break;
	default:
		ASSERT(false);
		Driver->GLExtension.extGlUniform4fv(location, count / 4, srcData);
		break;
	}
}

COpenGLVertexShader::COpenGLVertexShader(const COpenGLDriver* driver, const char* filename, const std::set<std::string>& macroSet)
	: Driver(driver), AbsFileName(filename), MacroSet(macroSet)
{
	char name[QMAX_PATH];
	getFileNameNoExtensionA(filename, name, QMAX_PATH);
	Name = name;
}

COpenGLVertexShader::~COpenGLVertexShader()
{
	releaseVideoResources();
}

bool COpenGLVertexShader::compile()
{
	return buildVideoResources();
}

bool COpenGLVertexShader::buildVideoResources()
{
	if (VideoBuilt)
		return false;

	SShaderFile result;
	if (!CShaderUtil::loadFile_OpenGL(AbsFileName.c_str(), MacroSet, result))
		return false;

	const char* buffer = result.Buffer.data();

	GLhandleARB shaderHandle = Driver->GLExtension.extGlCreateShaderObject(GL_VERTEX_SHADER_ARB);
	Driver->GLExtension.extGlShaderSourceARB(shaderHandle, 1, &buffer, nullptr);
	Driver->GLExtension.extGlCompileShaderARB(shaderHandle);

	GLint status = 0;

	Driver->GLExtension.extGlGetObjectParameteriv(shaderHandle, GL_OBJECT_COMPILE_STATUS_ARB, &status);

	if (!status)
	{
		g_FileSystem->writeLog(ELOG_GX, "GLSL shader failed to compile: %s, %s", AbsFileName.c_str(), CShaderUtil::getShaderMacroString(MacroSet).c_str());
		// check error message and log it
		GLint maxLength = 0;
		GLsizei length;

		Driver->GLExtension.extGlGetObjectParameteriv(shaderHandle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &maxLength);

		GLcharARB* infoLog = new GLcharARB[maxLength];
		Driver->GLExtension.extGlGetInfoLog(shaderHandle, maxLength, &length, infoLog);
		g_FileSystem->writeLog(ELOG_GX, reinterpret_cast<const char*>(infoLog));
		delete[] infoLog;

		shaderHandle = 0;
		return false;
	}

	VertexShader = shaderHandle;
	VideoBuilt = true;
	return true;
}

void COpenGLVertexShader::releaseVideoResources()
{
	if (!VideoBuilt)
		return;

	Driver->GLExtension.extGlDeleteObject((GLhandleARB)VertexShader);

	VideoBuilt = false;
}

COpenGLPixelShader::COpenGLPixelShader(const COpenGLDriver* driver, const char* filename, const std::set<std::string>& macroSet)
	: Driver(driver), AbsFileName(filename), MacroSet(macroSet)
{
	char name[QMAX_PATH];
	getFileNameNoExtensionA(filename, name, QMAX_PATH);
	Name = name;
}

COpenGLPixelShader::~COpenGLPixelShader()
{
	releaseVideoResources();
}

bool COpenGLPixelShader::compile()
{
	return buildVideoResources();
}

bool COpenGLPixelShader::buildVideoResources()
{
	if (VideoBuilt)
		return false;

	SShaderFile result;
	if (!CShaderUtil::loadFile_OpenGL(AbsFileName.c_str(), MacroSet, result))
		return false;

	const char* buffer = result.Buffer.data();

	GLhandleARB shaderHandle = Driver->GLExtension.extGlCreateShaderObject(GL_VERTEX_SHADER_ARB);
	Driver->GLExtension.extGlShaderSourceARB(shaderHandle, 1, &buffer, nullptr);
	Driver->GLExtension.extGlCompileShaderARB(shaderHandle);

	GLint status = 0;

	Driver->GLExtension.extGlGetObjectParameteriv(shaderHandle, GL_OBJECT_COMPILE_STATUS_ARB, &status);

	if (!status)
	{
		g_FileSystem->writeLog(ELOG_GX, "GLSL shader failed to compile");
		// check error message and log it
		GLint maxLength = 0;
		GLsizei length;

		Driver->GLExtension.extGlGetObjectParameteriv(shaderHandle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &maxLength);

		GLcharARB* infoLog = new GLcharARB[maxLength];
		Driver->GLExtension.extGlGetInfoLog(shaderHandle, maxLength, &length, infoLog);
		g_FileSystem->writeLog(ELOG_GX, reinterpret_cast<const char*>(infoLog));
		delete[] infoLog;

		shaderHandle = 0;
		return false;
	}

	PixelShader = shaderHandle;
	VideoBuilt = true;
	return true;
}

void COpenGLPixelShader::releaseVideoResources()
{
	if (!VideoBuilt)
		return;

	Driver->GLExtension.extGlDeleteObject((GLhandleARB)PixelShader);

	VideoBuilt = false;
}

