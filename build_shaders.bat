@echo off
Tools\shader2c\bin\shader2c.exe --in=GammaRay/Core/Renderer/Shaders/default.glsl --out=GammaRay/Core/Renderer/Shaders/default.gen.h --class=Default --inherits=RendererShaderOpenGL3 --inheritshpath=Drivers/OpenGL3/RendererShaderOpenGL3.h
echo Done
pause
