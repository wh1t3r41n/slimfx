// sfx_gl.c -- our minimal OpenGL 3.3 Core function pointer loader.
// We bind exactly the functions slimfx uses; add more here if you need them.
#include "internal/sfx_gl.h"

#include <string.h>

// --- Globals (defined here, extern in header) -------------------------------
PFNGLVIEWPORTPROC              glViewport;
PFNGLCLEARCOLORPROC            glClearColor;
PFNGLCLEARPROC                 glClear;
PFNGLENABLEPROC                glEnable;
PFNGLDISABLEPROC               glDisable;
PFNGLCULLFACEPROC              glCullFace;
PFNGLFRONTFACEPROC             glFrontFace;
PFNGLDEPTHFUNCPROC             glDepthFunc;
PFNGLDEPTHMASKPROC             glDepthMask;
PFNGLBLENDFUNCPROC             glBlendFunc;
PFNGLBLENDEQUATIONPROC         glBlendEquation;
PFNGLCOLORMASKPROC             glColorMask;
PFNGLSTENCILFUNCPROC           glStencilFunc;
PFNGLSTENCILOPPROC             glStencilOp;
PFNGLSTENCILMASKPROC           glStencilMask;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC   glVertexAttribPointer;
PFNGLVERTEXATTRIBPOINTERIPROC  glVertexAttribIPointer;
PFNGLDRAWARRAYSPROC            glDrawArrays;
PFNGLDRAWELEMENTSPROC          glDrawElements;
PFNGLDRAWARRAYSINSTANCEDPROC   glDrawArraysInstanced;
PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced;
PFNGLCREATESHADERPROC          glCreateShader;
PFNGLSHADERSOURCEPROC          glShaderSource;
PFNGLCOMPILESHADERPROC         glCompileShader;
PFNGLGETSHADERIVPROC           glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC      glGetShaderInfoLog;
PFNGLDELETESHADERPROC          glDeleteShader;
PFNGLCREATEPROGRAMPROC         glCreateProgram;
PFNGLATTACHSHADERPROC          glAttachShader;
PFNGLLINKPROGRAMPROC           glLinkProgram;
PFNGLUSEPROGRAMPROC            glUseProgram;
PFNGLGETPROGRAMIVPROC          glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC     glGetProgramInfoLog;
PFNGLDELETEPROGRAMPROC         glDeleteProgram;
PFNGLGETUNIFORMLOCATIONPROC    glGetUniformLocation;
PFNGLUNIFORM1FPROC             glUniform1f;
PFNGLUNIFORM2FPROC             glUniform2f;
PFNGLUNIFORM3FPROC             glUniform3f;
PFNGLUNIFORM4FPROC             glUniform4f;
PFNGLUNIFORM1IPROC             glUniform1i;
PFNGLUNIFORM1UIVPROC           glUniform1ui;
PFNGLUNIFORM1FVPROC            glUniform1fv;
PFNGLUNIFORM2FVPROC            glUniform2fv;
PFNGLUNIFORM3FVPROC            glUniform3fv;
PFNGLUNIFORM4FVPROC            glUniform4fv;
PFNGLUNIFORMMATRIX3FVPROC      glUniformMatrix3fv;
PFNGLUNIFORMMATRIX4FVPROC      glUniformMatrix4fv;
PFNGLGENBUFFERSPROC            glGenBuffers;
PFNGLDELETEBUFFERSPROC         glDeleteBuffers;
PFNGLBINDBUFFERPROC            glBindBuffer;
PFNGLBUFFERDATAPROC            glBufferData;
PFNGLBUFFERSUBDATAPROC         glBufferSubData;
PFNGLGENVERTEXARRAYSPROC       glGenVertexArrays;
PFNGLDELETEVERTEXARRAYSPROC    glDeleteVertexArrays;
PFNGLBINDVERTEXARRAYPROC       glBindVertexArray;
PFNGLVERTEXATTRIBDIVISORPROC   glVertexAttribDivisor;
PFNGLGENTEXTURESPROC           glGenTextures;
PFNGLDELETETEXTURESPROC        glDeleteTextures;
PFNGLBINDTEXTUREPROC           glBindTexture;
PFNGLTEXIMAGE2DPROC            glTexImage2D;
PFNGLTEXPARAMETERIPROC         glTexParameteri;
PFNGLACTIVETEXTUREPROC         glActiveTexture;
PFNGLGENERATEMIPMAPPROC        glGenerateMipmap;
PFNGLGETSTRINGPROC             glGetString;
PFNGLGETSTRINGIPROC            glGetStringi;
PFNGLGETINTEGERVPROC           glGetIntegerv;
PFNGLSCISSORPROC               glScissor;
PFNGLREADPIXELSPROC            glReadPixels;
PFNGLPIXELSTOREIPROC           glPixelStorei;
PFNGLGENFRAMEBUFFERSPROC       glGenFramebuffers;
PFNGLDELETEFRAMEBUFFERSPROC    glDeleteFramebuffers;
PFNGLBINDFRAMEBUFFERPROC       glBindFramebuffer;
PFNGLFRAMEBUFFERTEXTURE2DPROC  glFramebufferTexture2D;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
PFNGLDRAWBUFFERSPROC           glDrawBuffers;
PFNGLBLITFRAMEBUFFERPROC       glBlitFramebuffer;

// --- Loader ----------------------------------------------------------------
static void* sfx__get(GLADloadfunc loader, const char* name) {
    return loader(name);
}

int sfx_gl_load(GLADloadfunc loader) {
    if (!loader) return 0;

    glViewport               = (PFNGLVIEWPORTPROC)              sfx__get(loader, "glViewport");
    glClearColor             = (PFNGLCLEARCOLORPROC)            sfx__get(loader, "glClearColor");
    glClear                  = (PFNGLCLEARPROC)                 sfx__get(loader, "glClear");
    glEnable                 = (PFNGLENABLEPROC)                sfx__get(loader, "glEnable");
    glDisable                = (PFNGLDISABLEPROC)               sfx__get(loader, "glDisable");
    glCullFace               = (PFNGLCULLFACEPROC)              sfx__get(loader, "glCullFace");
    glFrontFace              = (PFNGLFRONTFACEPROC)             sfx__get(loader, "glFrontFace");
    glDepthFunc              = (PFNGLDEPTHFUNCPROC)             sfx__get(loader, "glDepthFunc");
    glDepthMask              = (PFNGLDEPTHMASKPROC)             sfx__get(loader, "glDepthMask");
    glBlendFunc              = (PFNGLBLENDFUNCPROC)             sfx__get(loader, "glBlendFunc");
    glBlendEquation          = (PFNGLBLENDEQUATIONPROC)         sfx__get(loader, "glBlendEquation");
    glColorMask              = (PFNGLCOLORMASKPROC)             sfx__get(loader, "glColorMask");
    glStencilFunc            = (PFNGLSTENCILFUNCPROC)           sfx__get(loader, "glStencilFunc");
    glStencilOp              = (PFNGLSTENCILOPPROC)             sfx__get(loader, "glStencilOp");
    glStencilMask            = (PFNGLSTENCILMASKPROC)           sfx__get(loader, "glStencilMask");
    glEnableVertexAttribArray  = (PFNGLENABLEVERTEXATTRIBARRAYPROC)  sfx__get(loader, "glEnableVertexAttribArray");
    glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) sfx__get(loader, "glDisableVertexAttribArray");
    glVertexAttribPointer    = (PFNGLVERTEXATTRIBPOINTERPROC)   sfx__get(loader, "glVertexAttribPointer");
    glVertexAttribIPointer   = (PFNGLVERTEXATTRIBPOINTERIPROC)  sfx__get(loader, "glVertexAttribIPointer");
    glDrawArrays             = (PFNGLDRAWARRAYSPROC)            sfx__get(loader, "glDrawArrays");
    glDrawElements           = (PFNGLDRAWELEMENTSPROC)          sfx__get(loader, "glDrawElements");
    glDrawArraysInstanced    = (PFNGLDRAWARRAYSINSTANCEDPROC)   sfx__get(loader, "glDrawArraysInstanced");
    glDrawElementsInstanced  = (PFNGLDRAWELEMENTSINSTANCEDPROC) sfx__get(loader, "glDrawElementsInstanced");
    glCreateShader           = (PFNGLCREATESHADERPROC)          sfx__get(loader, "glCreateShader");
    glShaderSource           = (PFNGLSHADERSOURCEPROC)          sfx__get(loader, "glShaderSource");
    glCompileShader          = (PFNGLCOMPILESHADERPROC)         sfx__get(loader, "glCompileShader");
    glGetShaderiv            = (PFNGLGETSHADERIVPROC)           sfx__get(loader, "glGetShaderiv");
    glGetShaderInfoLog       = (PFNGLGETSHADERINFOLOGPROC)      sfx__get(loader, "glGetShaderInfoLog");
    glDeleteShader           = (PFNGLDELETESHADERPROC)          sfx__get(loader, "glDeleteShader");
    glCreateProgram          = (PFNGLCREATEPROGRAMPROC)         sfx__get(loader, "glCreateProgram");
    glAttachShader           = (PFNGLATTACHSHADERPROC)          sfx__get(loader, "glAttachShader");
    glLinkProgram            = (PFNGLLINKPROGRAMPROC)           sfx__get(loader, "glLinkProgram");
    glUseProgram             = (PFNGLUSEPROGRAMPROC)            sfx__get(loader, "glUseProgram");
    glGetProgramiv           = (PFNGLGETPROGRAMIVPROC)          sfx__get(loader, "glGetProgramiv");
    glGetProgramInfoLog      = (PFNGLGETPROGRAMINFOLOGPROC)     sfx__get(loader, "glGetProgramInfoLog");
    glDeleteProgram          = (PFNGLDELETEPROGRAMPROC)         sfx__get(loader, "glDeleteProgram");
    glGetUniformLocation     = (PFNGLGETUNIFORMLOCATIONPROC)    sfx__get(loader, "glGetUniformLocation");
    glUniform1f              = (PFNGLUNIFORM1FPROC)             sfx__get(loader, "glUniform1f");
    glUniform2f              = (PFNGLUNIFORM2FPROC)             sfx__get(loader, "glUniform2f");
    glUniform3f              = (PFNGLUNIFORM3FPROC)             sfx__get(loader, "glUniform3f");
    glUniform4f              = (PFNGLUNIFORM4FPROC)             sfx__get(loader, "glUniform4f");
    glUniform1i              = (PFNGLUNIFORM1IPROC)             sfx__get(loader, "glUniform1i");
    glUniform1ui             = (PFNGLUNIFORM1UIVPROC)           sfx__get(loader, "glUniform1ui");
    glUniform1fv             = (PFNGLUNIFORM1FVPROC)            sfx__get(loader, "glUniform1fv");
    glUniform2fv             = (PFNGLUNIFORM2FVPROC)            sfx__get(loader, "glUniform2fv");
    glUniform3fv             = (PFNGLUNIFORM3FVPROC)            sfx__get(loader, "glUniform3fv");
    glUniform4fv             = (PFNGLUNIFORM4FVPROC)            sfx__get(loader, "glUniform4fv");
    glUniformMatrix3fv       = (PFNGLUNIFORMMATRIX3FVPROC)      sfx__get(loader, "glUniformMatrix3fv");
    glUniformMatrix4fv       = (PFNGLUNIFORMMATRIX4FVPROC)      sfx__get(loader, "glUniformMatrix4fv");
    glGenBuffers             = (PFNGLGENBUFFERSPROC)            sfx__get(loader, "glGenBuffers");
    glDeleteBuffers          = (PFNGLDELETEBUFFERSPROC)         sfx__get(loader, "glDeleteBuffers");
    glBindBuffer             = (PFNGLBINDBUFFERPROC)            sfx__get(loader, "glBindBuffer");
    glBufferData             = (PFNGLBUFFERDATAPROC)            sfx__get(loader, "glBufferData");
    glBufferSubData          = (PFNGLBUFFERSUBDATAPROC)         sfx__get(loader, "glBufferSubData");
    glGenVertexArrays        = (PFNGLGENVERTEXARRAYSPROC)       sfx__get(loader, "glGenVertexArrays");
    glDeleteVertexArrays     = (PFNGLDELETEVERTEXARRAYSPROC)    sfx__get(loader, "glDeleteVertexArrays");
    glBindVertexArray        = (PFNGLBINDVERTEXARRAYPROC)       sfx__get(loader, "glBindVertexArray");
    glVertexAttribDivisor    = (PFNGLVERTEXATTRIBDIVISORPROC)   sfx__get(loader, "glVertexAttribDivisor");
    glGenTextures            = (PFNGLGENTEXTURESPROC)           sfx__get(loader, "glGenTextures");
    glDeleteTextures         = (PFNGLDELETETEXTURESPROC)        sfx__get(loader, "glDeleteTextures");
    glBindTexture            = (PFNGLBINDTEXTUREPROC)           sfx__get(loader, "glBindTexture");
    glTexImage2D             = (PFNGLTEXIMAGE2DPROC)            sfx__get(loader, "glTexImage2D");
    glTexParameteri          = (PFNGLTEXPARAMETERIPROC)         sfx__get(loader, "glTexParameteri");
    glActiveTexture          = (PFNGLACTIVETEXTUREPROC)         sfx__get(loader, "glActiveTexture");
    glGenerateMipmap         = (PFNGLGENERATEMIPMAPPROC)        sfx__get(loader, "glGenerateMipmap");
    glGetString              = (PFNGLGETSTRINGPROC)             sfx__get(loader, "glGetString");
    glGetStringi             = (PFNGLGETSTRINGIPROC)            sfx__get(loader, "glGetStringi");
    glGetIntegerv            = (PFNGLGETINTEGERVPROC)           sfx__get(loader, "glGetIntegerv");
    glScissor                = (PFNGLSCISSORPROC)               sfx__get(loader, "glScissor");
    glReadPixels             = (PFNGLREADPIXELSPROC)            sfx__get(loader, "glReadPixels");
    glPixelStorei            = (PFNGLPIXELSTOREIPROC)           sfx__get(loader, "glPixelStorei");
    glGenFramebuffers        = (PFNGLGENFRAMEBUFFERSPROC)       sfx__get(loader, "glGenFramebuffers");
    glDeleteFramebuffers     = (PFNGLDELETEFRAMEBUFFERSPROC)    sfx__get(loader, "glDeleteFramebuffers");
    glBindFramebuffer        = (PFNGLBINDFRAMEBUFFERPROC)       sfx__get(loader, "glBindFramebuffer");
    glFramebufferTexture2D   = (PFNGLFRAMEBUFFERTEXTURE2DPROC)  sfx__get(loader, "glFramebufferTexture2D");
    glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) sfx__get(loader, "glCheckFramebufferStatus");
    glDrawBuffers            = (PFNGLDRAWBUFFERSPROC)           sfx__get(loader, "glDrawBuffers");
    glBlitFramebuffer        = (PFNGLBLITFRAMEBUFFERPROC)       sfx__get(loader, "glBlitFramebuffer");

    // Sanity check: a few critical ones must be non-null
    if (!glViewport || !glClear || !glCreateShader || !glCreateProgram
        || !glGenBuffers || !glGenVertexArrays || !glGenTextures
        || !glGetString || !glGetIntegerv) {
        return 0;
    }
    return 1;
}

const char* sfx_gl_error_string(int err) { (void)err; return "see glGetError()"; }