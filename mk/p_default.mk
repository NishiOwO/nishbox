ifeq ($(PLATFORM),)
BACKEND = GLX

ODE_CFLAGS = `pkg-config --cflags ode`
ODE_LIBS = `pkg-config --libs ode`
ifeq ($(BACKEND),GLX)
GL_CFLAGS = `pkg-config --cflags x11` `pkg-config --cflags gl` `pkg-config --cflags glu`
GL_LIBS = `pkg-config --libs x11` `pkg-config --libs gl` `pkg-config --libs glu`
endif
ifeq ($(BACKEND),GLFW)
GL_CFLAGS = `pkg-config --cflags glfw3` `pkg-config --cflags glu`
GL_LIBS = `pkg-config --libs glfw3` `pkg-config --libs glu`
endif
SOCKET_LIBS = 
MATH_LIBS = -lm

EXEC =
endif
