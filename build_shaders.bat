@echo off
Tools\shader2c\bin\shader2c.exe --in=GammaRay/Core/Renderer/Shaders/default.glsl --out=GammaRay/Core/Renderer/Shaders/default.gen.h --class=Default --inherits=RendererShaderOpenGL --inheritshpath=Drivers/OpenGL/RendererShaderOpenGL.h
Tools\shader2c\bin\shader2c.exe --in=GammaRay/Drivers/OpenGL/Shaders/depth.glsl --out=GammaRay/Drivers/OpenGL/Shaders/depth.gen.h --class=Depth --inherits=RendererShaderOpenGL --inheritshpath=Drivers/OpenGL/RendererShaderOpenGL.h
echo Done
pause
