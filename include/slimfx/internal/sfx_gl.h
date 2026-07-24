// sfx_gl.h -- our own minimal OpenGL 3.3 Core function loader
// No external GLAD. We only declare what slimfx actually calls.
// If you need more, add the function here + bind it in sfx_gl.c.

#ifndef SFX_GL_H
#define SFX_GL_H

#include <stdint.h>

#if defined(_WIN32)
#  include <windows.h>
typedef int32_t GLsizei;
typedef int32_t GLenum;
typedef uint32_t GLuint;
typedef int32_t GLint;
typedef int32_t GLbitfield;
typedef float   GLfloat;
typedef double  GLdouble;
typedef int8_t  GLboolean;
typedef int8_t  GLbyte;
typedef uint8_t GLubyte;
typedef uint16_t GLhalf;
typedef int16_t GLshort;
typedef uint16_t GLushort;
typedef char    GLchar;
typedef void    GLvoid;
typedef int64_t GLint64;
typedef uint64_t GLuint64;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
#else
#  include <GL/glcorearb.h>
#endif

typedef void* (*GLADloadfunc)(const char*);

typedef void (*PFNGLVIEWPORTPROC)             (GLint, GLint, GLsizei, GLsizei);
typedef void (*PFNGLCLEARCOLORPROC)           (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (*PFNGLCLEARPROC)                (GLbitfield);
typedef void (*PFNGLENABLEPROC)               (GLenum);
typedef void (*PFNGLDISABLEPROC)              (GLenum);
typedef void (*PFNGLCULLFACEPROC)             (GLenum);
typedef void (*PFNGLFRONTFACEPROC)            (GLenum);
typedef void (*PFNGLDEPTHFUNCPROC)            (GLenum);
typedef void (*PFNGLDEPTHMASKPROC)            (GLboolean);
typedef void (*PFNGLBLENDFUNCPROC)            (GLenum, GLenum);
typedef void (*PFNGLBLENDEQUATIONPROC)        (GLenum);
typedef void (*PFNGLCOLORMASKPROC)            (GLboolean, GLboolean, GLboolean, GLboolean);
typedef void (*PFNGLSTENCILFUNCPROC)          (GLenum, GLint, GLuint);
typedef void (*PFNGLSTENCILOPPROC)            (GLenum, GLenum, GLint, GLuint);
typedef void (*PFNGLSTENCILMASKPROC)          (GLuint);
typedef void (*PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (*PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (*PFNGLVERTEXATTRIBPOINTERPROC)   (GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void (*PFNGLVERTEXATTRIBPOINTERIPROC)  (GLuint, GLint, GLenum, GLsizei, GLsizei);
typedef void (*PFNGLDRAWARRAYSPROC)           (GLenum, GLint, GLint);
typedef void (*PFNGLDRAWELEMENTSPROC)         (GLenum, GLsizei, GLenum, const void*);
typedef void (*PFNGLDRAWARRAYSINSTANCEDPROC)  (GLenum, GLint, GLint, GLsizei);
typedef void (*PFNGLDRAWELEMENTSINSTANCEDPROC)(GLenum, GLsizei, GLenum, const void*, GLsizei);

typedef GLuint (*PFNGLCREATESHADERPROC)       (GLenum);
typedef void   (*PFNGLSHADERSOURCEPROC)       (GLuint, GLsizei, const GLchar* const*, const GLint*);
typedef void   (*PFNGLCOMPILESHADERPROC)      (GLuint);
typedef void   (*PFNGLGETSHADERIVPROC)        (GLuint, GLenum, GLint*);
typedef void   (*PFNGLGETSHADERINFOLOGPROC)   (GLuint, GLsizei, GLsizei*, GLchar*);
typedef void   (*PFNGLDELETESHADERPROC)       (GLuint);
typedef GLuint (*PFNGLCREATEPROGRAMPROC)      (void);
typedef void   (*PFNGLATTACHSHADERPROC)       (GLuint, GLuint);
typedef void   (*PFNGLLINKPROGRAMPROC)        (GLuint);
typedef void   (*PFNGLUSEPROGRAMPROC)         (GLuint);
typedef void   (*PFNGLGETPROGRAMIVPROC)       (GLuint, GLenum, GLint*);
typedef void   (*PFNGLGETPROGRAMINFOLOGPROC)  (GLuint, GLsizei, GLsizei*, GLchar*);
typedef void   (*PFNGLDELETEPROGRAMPROC)      (GLuint);
typedef GLint  (*PFNGLGETUNIFORMLOCATIONPROC) (GLuint, const GLchar*);
typedef void   (*PFNGLUNIFORM1FPROC)          (GLint, GLfloat);
typedef void   (*PFNGLUNIFORM2FPROC)          (GLint, GLfloat, GLfloat);
typedef void   (*PFNGLUNIFORM3FPROC)          (GLint, GLfloat, GLfloat, GLfloat);
typedef void   (*PFNGLUNIFORM4FPROC)          (GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void   (*PFNGLUNIFORM1IPROC)          (GLint, GLint);
typedef void   (*PFNGLUNIFORM1UIVPROC)        (GLint, GLuint);
typedef void   (*PFNGLUNIFORM1FVPROC)         (GLint, GLsizei, const GLfloat*);
typedef void   (*PFNGLUNIFORM2FVPROC)         (GLint, GLsizei, const GLfloat*);
typedef void   (*PFNGLUNIFORM3FVPROC)         (GLint, GLsizei, const GLfloat*);
typedef void   (*PFNGLUNIFORM4FVPROC)         (GLint, GLsizei, const GLfloat*);
typedef void   (*PFNGLUNIFORMMATRIX3FVPROC)   (GLint, GLsizei, const GLfloat*);
typedef void   (*PFNGLUNIFORMMATRIX4FVPROC)   (GLint, GLsizei, const GLfloat*);

typedef void (*PFNGLGENBUFFERSPROC)           (GLsizei, GLuint*);
typedef void (*PFNGLDELETEBUFFERSPROC)        (GLsizei, const GLuint*);
typedef void (*PFNGLBINDBUFFERPROC)           (GLenum, GLuint);
typedef void (*PFNGLBUFFERDATAPROC)           (GLenum, GLsizeiptr, const void*, GLenum);
typedef void (*PFNGLBUFFERSUBDATAPROC)        (GLenum, GLintptr, GLsizeiptr, const void*);
typedef void (*PFNGLGENVERTEXARRAYSPROC)      (GLsizei, GLuint*);
typedef void (*PFNGLDELETEVERTEXARRAYSPROC)   (GLsizei, const GLuint*);
typedef void (*PFNGLBINDVERTEXARRAYPROC)      (GLuint);
typedef void (*PFNGLVERTEXATTRIBDIVISORPROC)  (GLuint, GLuint);

typedef void (*PFNGLGENTEXTURESPROC)          (GLsizei, GLuint*);
typedef void (*PFNGLDELETETEXTURESPROC)       (GLsizei, const GLuint*);
typedef void (*PFNGLBINDTEXTUREPROC)          (GLenum, GLuint);
typedef void (*PFNGLTEXIMAGE2DPROC)           (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
typedef void (*PFNGLTEXPARAMETERIPROC)        (GLenum, GLenum, GLint);
typedef void (*PFNGLACTIVETEXTUREPROC)        (GLenum);
typedef void (*PFNGLGENERATEMIPMAPPROC)       (GLenum);
typedef GLint (*PFNGLGETUNIFORMLOCATIONPROC_P) (GLuint, const GLchar*);

typedef const GLubyte* (*PFNGLGETSTRINGPROC)   (GLenum);
typedef const GLubyte* (*PFNGLGETSTRINGIPROC)  (GLenum, GLuint);
typedef void (*PFNGLGETINTEGERVPROC)          (GLenum, GLint*);
typedef void (*PFNGLSCISSORPROC)              (GLint, GLint, GLsizei, GLsizei);
typedef void (*PFNGLREADPIXELSPROC)           (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void*);
typedef void (*PFNGLPIXELSTOREIPROC)          (GLenum, GLint);

typedef void (*PFNGLGENFRAMEBUFFERSPROC)      (GLsizei, GLuint*);
typedef void (*PFNGLDELETEFRAMEBUFFERSPROC)   (GLsizei, const GLuint*);
typedef void (*PFNGLBINDFRAMEBUFFERPROC)      (GLenum, GLuint);
typedef void (*PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum, GLenum, GLenum, GLuint, GLint);
typedef GLenum (*PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum);
typedef void (*PFNGLDRAWBUFFERSPROC)          (GLsizei, const GLenum*);
typedef void (*PFNGLBLITFRAMEBUFFERPROC)      (GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);

// Enums (subset we need)
#define SFX_GL_DEPTH_BUFFER_BIT               0x00000100
#define SFX_GL_STENCIL_BUFFER_BIT             0x00000400
#define SFX_GL_COLOR_BUFFER_BIT               0x00004000
#define SFX_GL_TRIANGLES                      0x0004
#define SFX_GL_TRIANGLE_STRIP                 0x0005
#define SFX_GL_TRIANGLE_FAN                   0x0006
#define SFX_GL_LINES                          0x0001
#define SFX_GL_POINTS                         0x0000
#define SFX_GL_UNSIGNED_BYTE                  0x1401
#define SFX_GL_UNSIGNED_SHORT                 0x1403
#define SFX_GL_UNSIGNED_INT                   0x1405
#define SFX_GL_FLOAT                          0x1406
#define SFX_GL_RGBA                           0x1908
#define SFX_GL_RGB                            0x1907
#define SFX_GL_DEPTH_COMPONENT                0x1902
#define SFX_GL_DEPTH_COMPONENT24              0x81A6
#define SFX_GL_RED                            0x1903
#define SFX_GL_RG                             0x8227
#define SFX_GL_LINEAR                         0x2601
#define SFX_GL_NEAREST                        0x2600
#define SFX_GL_LINEAR_MIPMAP_LINEAR           0x2703
#define SFX_GL_TEXTURE_2D                     0x0DE1
#define SFX_GL_TEXTURE_3D                     0x806F
#define SFX_GL_TEXTURE_CUBE_MAP               0x8513
#define SFX_GL_TEXTURE0                       0x84C0
#define SFX_GL_TEXTURE_WRAP_S                 0x2802
#define SFX_GL_TEXTURE_WRAP_T                 0x2803
#define SFX_GL_TEXTURE_MIN_FILTER             0x2801
#define SFX_GL_TEXTURE_MAG_FILTER             0x2800
#define SFX_GL_REPEAT                         0x2901
#define SFX_GL_CLAMP_TO_EDGE                  0x812F
#define SFX_GL_ARRAY_BUFFER                   0x8892
#define SFX_GL_ELEMENT_ARRAY_BUFFER           0x8893
#define SFX_GL_STATIC_DRAW                    0x88E4
#define SFX_GL_DYNAMIC_DRAW                   0x88E8
#define SFX_GL_STREAM_DRAW                    0x88E0
#define SFX_GL_STREAM_READ                    0x88E1
#define SFX_GL_STREAM_COPY                    0x88E2
#define SFX_GL_FRAGMENT_SHADER                0x8B30
#define SFX_GL_VERTEX_SHADER                  0x8B31
#define SFX_GL_COMPILE_STATUS                 0x8B81
#define SFX_GL_LINK_STATUS                    0x8B82
#define SFX_GL_INFO_LOG_LENGTH                0x8B84
#define SFX_GL_FRAMEBUFFER                    0x8D40
#define SFX_GL_READ_FRAMEBUFFER               0x8CA8
#define SFX_GL_DRAW_FRAMEBUFFER               0x8CA9
#define SFX_GL_COLOR_ATTACHMENT0              0x8CE0
#define SFX_GL_DEPTH_ATTACHMENT               0x8D00
#define SFX_GL_STENCIL_ATTACHMENT             0x8D20
#define SFX_GL_FRAMEBUFFER_COMPLETE           0x8CD5
#define SFX_GL_BACK                           0x0405
#define SFX_GL_FRONT                          0x0404
#define SFX_GL_FRONT_AND_BACK                 0x0408
#define SFX_GL_CCW                            0x0901
#define SFX_GL_CW                             0x0900
#define SFX_GL_BACK                           0x0405
#define SFX_GL_CULL_FACE                      0x0B44
#define SFX_GL_DEPTH_TEST                     0x0B71
#define SFX_GL_STENCIL_TEST                   0x0B90
#define SFX_GL_BLEND                          0x0BE2
#define SFX_GL_SCISSOR_TEST                   0x0C11
#define SFX_GL_SRC_ALPHA                      0x0302
#define SFX_GL_ONE_MINUS_SRC_ALPHA            0x0303
#define SFX_GL_ZERO                           0
#define SFX_GL_ONE                            1
#define SFX_GL_FUNC_ADD                       0x8006
#define SFX_GL_LEQUAL                         0x0203
#define SFX_GL_LESS                           0x0201
#define SFX_GL_ALWAYS                         0x0207
#define SFX_GL_KEEP                           0x1E00
#define SFX_GL_REPLACE                        0x1E01
#define SFX_GL_VENDOR                         0x1F00
#define SFX_GL_RENDERER                       0x1F01
#define SFX_GL_VERSION                        0x1F02
#define SFX_GL_SHADING_LANGUAGE_VERSION       0x8B8C
#define SFX_GL_EXTENSIONS                     0x1F03
#define SFX_GL_NUM_EXTENSIONS                 0x821D
#define SFX_GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#define SFX_GL_MAX_VERTEX_ATTRIBS             0x8869
#define SFX_GL_MAX_VERTEX_UNIFORM_COMPONENTS  0x8B4A
#define SFX_GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B4D
#define SFX_GL_MAX_VARYING_COMPONENTS         0x8B4B
#define SFX_GL_TEXTURE0                       0x84C0
#define SFX_GL_TEXTURE1                       0x84C1
#define SFX_GL_FALSE                          0
#define SFX_GL_TRUE                           1

// Extern function pointers (filled by sfx_gl_load)
extern PFNGLVIEWPORTPROC              glViewport;
extern PFNGLCLEARCOLORPROC            glClearColor;
extern PFNGLCLEARPROC                 glClear;
extern PFNGLENABLEPROC                glEnable;
extern PFNGLDISABLEPROC               glDisable;
extern PFNGLCULLFACEPROC              glCullFace;
extern PFNGLFRONTFACEPROC             glFrontFace;
extern PFNGLDEPTHFUNCPROC             glDepthFunc;
extern PFNGLDEPTHMASKPROC             glDepthMask;
extern PFNGLBLENDFUNCPROC             glBlendFunc;
extern PFNGLBLENDEQUATIONPROC         glBlendEquation;
extern PFNGLCOLORMASKPROC             glColorMask;
extern PFNGLSTENCILFUNCPROC           glStencilFunc;
extern PFNGLSTENCILOPPROC             glStencilOp;
extern PFNGLSTENCILMASKPROC           glStencilMask;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC   glVertexAttribPointer;
extern PFNGLVERTEXATTRIBPOINTERIPROC  glVertexAttribIPointer;
extern PFNGLDRAWARRAYSPROC            glDrawArrays;
extern PFNGLDRAWELEMENTSPROC          glDrawElements;
extern PFNGLDRAWARRAYSINSTANCEDPROC   glDrawArraysInstanced;
extern PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced;
extern PFNGLCREATESHADERPROC          glCreateShader;
extern PFNGLSHADERSOURCEPROC          glShaderSource;
extern PFNGLCOMPILESHADERPROC         glCompileShader;
extern PFNGLGETSHADERIVPROC           glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC      glGetShaderInfoLog;
extern PFNGLDELETESHADERPROC          glDeleteShader;
extern PFNGLCREATEPROGRAMPROC         glCreateProgram;
extern PFNGLATTACHSHADERPROC          glAttachShader;
extern PFNGLLINKPROGRAMPROC           glLinkProgram;
extern PFNGLUSEPROGRAMPROC            glUseProgram;
extern PFNGLGETPROGRAMIVPROC          glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC     glGetProgramInfoLog;
extern PFNGLDELETEPROGRAMPROC         glDeleteProgram;
extern PFNGLGETUNIFORMLOCATIONPROC    glGetUniformLocation;
extern PFNGLUNIFORM1FPROC             glUniform1f;
extern PFNGLUNIFORM2FPROC             glUniform2f;
extern PFNGLUNIFORM3FPROC             glUniform3f;
extern PFNGLUNIFORM4FPROC             glUniform4f;
extern PFNGLUNIFORM1IPROC             glUniform1i;
extern PFNGLUNIFORM1UIVPROC           glUniform1ui;
extern PFNGLUNIFORM1FVPROC            glUniform1fv;
extern PFNGLUNIFORM2FVPROC            glUniform2fv;
extern PFNGLUNIFORM3FVPROC            glUniform3fv;
extern PFNGLUNIFORM4FVPROC            glUniform4fv;
extern PFNGLUNIFORMMATRIX3FVPROC      glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC      glUniformMatrix4fv;
extern PFNGLGENBUFFERSPROC            glGenBuffers;
extern PFNGLDELETEBUFFERSPROC         glDeleteBuffers;
extern PFNGLBINDBUFFERPROC            glBindBuffer;
extern PFNGLBUFFERDATAPROC            glBufferData;
extern PFNGLBUFFERSUBDATAPROC         glBufferSubData;
extern PFNGLGENVERTEXARRAYSPROC       glGenVertexArrays;
extern PFNGLDELETEVERTEXARRAYSPROC    glDeleteVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC       glBindVertexArray;
extern PFNGLVERTEXATTRIBDIVISORPROC   glVertexAttribDivisor;
extern PFNGLGENTEXTURESPROC           glGenTextures;
extern PFNGLDELETETEXTURESPROC        glDeleteTextures;
extern PFNGLBINDTEXTUREPROC           glBindTexture;
extern PFNGLTEXIMAGE2DPROC            glTexImage2D;
extern PFNGLTEXPARAMETERIPROC         glTexParameteri;
extern PFNGLACTIVETEXTUREPROC         glActiveTexture;
extern PFNGLGENERATEMIPMAPPROC        glGenerateMipmap;
extern PFNGLGETSTRINGPROC             glGetString;
extern PFNGLGETSTRINGIPROC            glGetStringi;
extern PFNGLGETINTEGERVPROC           glGetIntegerv;
extern PFNGLSCISSORPROC               glScissor;
extern PFNGLREADPIXELSPROC            glReadPixels;
extern PFNGLPIXELSTOREIPROC           glPixelStorei;
extern PFNGLGENFRAMEBUFFERSPROC       glGenFramebuffers;
extern PFNGLDELETEFRAMEBUFFERSPROC    glDeleteFramebuffers;
extern PFNGLBINDFRAMEBUFFERPROC       glBindFramebuffer;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC  glFramebufferTexture2D;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
extern PFNGLDRAWBUFFERSPROC           glDrawBuffers;
extern PFNGLBLITFRAMEBUFFERPROC       glBlitFramebuffer;

// Our loader: pass glfwGetProcAddress. Returns 1 on success, 0 on failure.
int sfx_gl_load(GLADloadfunc loader);
const char* sfx_gl_error_string(int err);

#endif // SFX_GL_H