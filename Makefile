-include config.mk

INPUT       = Spearhead.dat
OUTPUT      = Spearhead.exe
LDS         = Spearhead.lds

LDFLAGS    ?= -Wl,--subsystem=windows -Wl,--disable-nxcompat -Wl,--disable-reloc-section -Wl,--enable-stdcall-fixup -static
ASFLAGS    ?= -Iinc
NFLAGS     ?= -Iinc -f elf
CFLAGS     ?= -Iinc -O2 -march=pentium4 -Wall -masm=intel
CXXFLAGS   ?= -Iinc -O2 -march=pentium4 -Wall -masm=intel

LIBS        = -lgdi32

OBJS        = \
				sym.o \
				rsrc.o \
				src/winmain.o

CC          = i686-w64-mingw32-gcc
CXX         = i686-w64-mingw32-g++
AS          = i686-w64-mingw32-as
STRIP      ?= i686-w64-mingw32-strip
WINDRES    ?= i686-w64-mingw32-windres
PETOOL     ?= petool
NASM       ?= nasm

IAT         = 12 0x657044 3824

all: $(OUTPUT)

%.o: %.asm
	$(NASM) $(NFLAGS) -o $@ $<

%.o: %.rc
	$(WINDRES) $(WFLAGS) $< $@

rsrc.o: $(INPUT)
	$(PETOOL) re2obj $< $@

$(OUTPUT): $(OBJS)
	$(CXX) $(LDFLAGS) -T $(LDS) -o "$@" $^ $(LIBS)
	$(PETOOL) setdd "$@" $(IAT) || ($(RM) "$@" && exit 1)
	$(PETOOL) setsc "$@" .p_text 0x60000020 || ($(RM) "$@" && exit 1)
	$(PETOOL) patch "$@" || ($(RM) "$@" && exit 1)
	$(STRIP) -R .patch "$@" || ($(RM) "$@" && exit 1)
#	$(PETOOL) dump "$(INPUT)"
#	$(PETOOL) dump "$@"

clean:
	$(RM) $(OUTPUT) $(OBJS)
