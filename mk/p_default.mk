ifeq ($(PLATFORM),)
ODE_CFLAGS = `pkg-config --cflags ode`
ODE_LIBS = `pkg-config --libs ode`
AMX_CFLAGS = `pkg-config --cflags amx`
AMX_LIBS = `pkg-config --libs amx`
PAWNC_CFLAGS = `pkg-config --cflags pawnc`
PAWNC_LIBS = `pkg-config --libs pawnc`
GL_CFLAGS = `pkg-config --cflags gl` `pkg-config --cflags glu`
GL_LIBS = `pkg-config --libs gl` `pkg-config --libs glu`
SOCKET_LIBS = 

BACKEND = GLX

EXEC =
endif
