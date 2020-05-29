//Debugging

GL_FUNC(glDebugMessageInsert, GLDEBUGMESSAGEINSERT);
GL_FUNC(glPushDebugGroup, GLPUSHDEBUGGROUP);
GL_FUNC(glPopDebugGroup, GLPOPDEBUGGROUP);
GL_FUNC(glObjectLabel, GLOBJECTLABEL);
GL_FUNC(glDebugMessageCallback, GLDEBUGMESSAGECALLBACK);

//Framebuffers

GL_FUNC(glBindFramebuffer, GLBINDFRAMEBUFFER);
GL_FUNC(glDeleteFramebuffers, GLDELETEFRAMEBUFFERS);
GL_FUNC(glCreateFramebuffers, GLCREATEFRAMEBUFFERS);
GL_FUNC(glNamedRenderbufferStorageMultisample, GLNAMEDRENDERBUFFERSTORAGEMULTISAMPLE);
GL_FUNC(glCreateRenderbuffers, GLCREATERENDERBUFFERS);
GL_FUNC(glDeleteRenderbuffers, GLDELETERENDERBUFFERS);
GL_FUNC(glNamedFramebufferRenderbuffer, GLNAMEDFRAMEBUFFERRENDERBUFFER);
GL_FUNC(glNamedFramebufferTexture, GLNAMEDFRAMEBUFFERTEXTURE);
GL_FUNC(glNamedFramebufferTextureLayer, GLNAMEDFRAMEBUFFERTEXTURELAYER);
GL_FUNC(glNamedFramebufferDrawBuffers, GLNAMEDFRAMEBUFFERDRAWBUFFERS);
GL_FUNC(glCheckNamedFramebufferStatus, GLCHECKNAMEDFRAMEBUFFERSTATUS);
GL_FUNC(glBlitNamedFramebuffer, GLBLITNAMEDFRAMEBUFFER);

//Buffers

GL_FUNC(glCreateBuffers, GLCREATEBUFFERS);
GL_FUNC(glDeleteBuffers, GLDELETEBUFFERS);
GL_FUNC(glBindBufferRange, GLBINDBUFFERRANGE);
GL_FUNC(glFlushMappedNamedBufferRange, GLFLUSHMAPPEDNAMEDBUFFERRANGE);
GL_FUNC(glNamedBufferStorage, GLNAMEDBUFFERSTORAGE);
GL_FUNC(glUnmapNamedBuffer, GLUNMAPNAMEDBUFFER);
GL_FUNC(glMapNamedBufferRange, GLMAPNAMEDBUFFERRANGE);
GL_FUNC(glNamedBufferSubData, GLNAMEDBUFFERSUBDATA);
GL_FUNC(glClearNamedBufferSubData, GLCLEARNAMEDBUFFERSUBDATA);
GL_FUNC(glBindBuffer, GLBINDBUFFER);
GL_FUNC(glCopyNamedBufferSubData, GLCOPYNAMEDBUFFERSUBDATA);

//VAOs

GL_FUNC(glVertexArrayElementBuffer, GLVERTEXARRAYELEMENTBUFFER);
GL_FUNC(glVertexArrayVertexBuffer, GLVERTEXARRAYVERTEXBUFFER);
GL_FUNC(glEnableVertexArrayAttrib, GLENABLEVERTEXARRAYATTRIB);
GL_FUNC(glVertexArrayAttribFormat, GLVERTEXARRAYATTRIBFORMAT);
GL_FUNC(glVertexArrayAttribBinding, GLVERTEXARRAYATTRIBBINDING);
GL_FUNC(glVertexArrayBindingDivisor, GLVERTEXARRAYBINDINGDIVISOR);
GL_FUNC(glCreateVertexArrays, GLCREATEVERTEXARRAYS);
GL_FUNC(glBindVertexArray, GLBINDVERTEXARRAY);
GL_FUNC(glDeleteVertexArrays, GLDELETEVERTEXARRAYS);
GL_FUNC(glDrawElementsInstancedBaseVertexBaseInstance, GLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCE);

//Shaders

GL_FUNC(glCreateProgram, GLCREATEPROGRAM);
GL_FUNC(glUseProgram, GLUSEPROGRAM);
GL_FUNC(glDeleteProgram, GLDELETEPROGRAM);
GL_FUNC(glCreateShader, GLCREATESHADER);
GL_FUNC(glShaderBinary, GLSHADERBINARY);
GL_FUNC(glSpecializeShader, GLSPECIALIZESHADER);
GL_FUNC(glAttachShader, GLATTACHSHADER);
GL_FUNC(glLinkProgram, GLLINKPROGRAM);
GL_FUNC(glDetachShader, GLDETACHSHADER);
GL_FUNC(glDeleteShader, GLDELETESHADER);
GL_FUNC(glGetProgramiv, GLGETPROGRAMIV);
GL_FUNC(glGetProgramInfoLog, GLGETPROGRAMINFOLOG);
GL_FUNC(glGetShaderiv, GLGETSHADERIV);
GL_FUNC(glGetShaderInfoLog, GLGETSHADERINFOLOG);

//Samplers

GL_FUNC(glCreateSamplers, GLCREATESAMPLERS);
GL_FUNC(glDeleteSamplers, GLDELETESAMPLERS);
GL_FUNC(glSamplerParameteri, GLSAMPLERPARAMETERI);
GL_FUNC(glSamplerParameterf, GLSAMPLERPARAMETERF);
GL_FUNC(glSamplerParameterfv, GLSAMPLERPARAMETERFV);
GL_FUNC(glBindSampler, GLBINDSAMPLER);

//Textures

GL_FUNC(glCreateTextures, GLCREATETEXTURES);
GL_FUNC(glTextureStorage2DMultisample, GLTEXTURESTORAGE2DMULTISAMPLE);
GL_FUNC(glTextureStorage3DMultisample, GLTEXTURESTORAGE3DMULTISAMPLE);
GL_FUNC(glTextureStorage1D, GLTEXTURESTORAGE1D);
GL_FUNC(glTextureStorage2D, GLTEXTURESTORAGE2D);
GL_FUNC(glTextureStorage3D, GLTEXTURESTORAGE3D);
GL_FUNC(glTextureSubImage1D, GLTEXTURESUBIMAGE1D);
GL_FUNC(glTextureSubImage2D, GLTEXTURESUBIMAGE2D);
GL_FUNC(glTextureSubImage3D, GLTEXTURESUBIMAGE3D);
GL_FUNC(glBindTextureUnit, GLBINDTEXTUREUNIT);
GL_FUNC(glBindImageTexture, GLBINDIMAGETEXTURE);
GL_FUNC(glTextureView, GLTEXTUREVIEW);

//GPU commands

GL_FUNC(glDrawArraysInstancedBaseInstance, GLDRAWARRAYSINSTANCEDBASEINSTANCE);
GL_FUNC(glDispatchCompute, GLDISPATCHCOMPUTE);
GL_FUNC(glDispatchComputeIndirect, GLDISPATCHCOMPUTEINDIRECT);
GL_FUNC(glClipControl, GLCLIPCONTROL);
GL_FUNC(glBlendEquationSeparate, GLBLENDEQUATIONSEPARATE);
GL_FUNC(glBlendFuncSeparate, GLBLENDFUNCSEPARATE);
GL_FUNC(glMinSampleShading, GLMINSAMPLESHADING);
GL_FUNC(glClearNamedFramebufferuiv, GLCLEARNAMEDFRAMEBUFFERUIV);
GL_FUNC(glClearNamedFramebufferiv, GLCLEARNAMEDFRAMEBUFFERIV);
GL_FUNC(glClearNamedFramebufferfv, GLCLEARNAMEDFRAMEBUFFERFV);
GL_FUNC(glClearNamedFramebufferfi, GLCLEARNAMEDFRAMEBUFFERFI);
GL_FUNC(glStencilOpSeparate, GLSTENCILOPSEPARATE);
GL_FUNC(glStencilFuncSeparate, GLSTENCILFUNCSEPARATE);

GL_FUNC(glFenceSync, GLFENCESYNC);
GL_FUNC(glClientWaitSync, GLCLIENTWAITSYNC);
GL_FUNC(glDeleteSync, GLDELETESYNC);

//Platform dependent calls

#ifdef _WIN32
	GL_FUNC(glBlendColor, GLBLENDCOLOR);
	GL_FUNC(wglChoosePixelFormatARB, WGLCHOOSEPIXELFORMATARB);
	GL_FUNC(wglCreateContextAttribsARB, WGLCREATECONTEXTATTRIBSARB);
	GL_FUNC(wglSwapIntervalEXT, WGLSWAPINTERVALEXT);
#endif