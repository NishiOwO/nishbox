AM_CPPFLAGS = @NB_CPPFLAGS@ -DDRV_@NB_DRIVER@ -DUSE_@NB_BACKEND@ -I$(top_srcdir)/engine/include -I$(top_srcdir)/external/lua -I$(top_srcdir)/external/stb -I$(top_srcdir)/external/zlib -I$(top_srcdir)/deps/include
