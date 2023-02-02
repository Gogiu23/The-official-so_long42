# minimal color codes
END=$'\x1b[0m
BOLD=$'\x1b[1m
UNDER=$'\x1b[4m
REV=$'\x1b[7m
GREY=$'\x1b[30m
RED=$'\x1b[31m
GREEN=$'\x1b[32m
YELLOW=$'\x1b[33m
BLUE=$'\x1b[34m
PURPLE=$'\x1b[35m
CYAN=$'\x1b[36m
WHITE=$'\x1b[37m

MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)

SRC= interface.swift $(MODULE_SRC)
OBJ=$(SRC:.swift=.o)

C_SRC= mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ=$(C_SRC:.c=.o)
CFLAGS=-O3 -w
NAME=libmlx.dylib
INC=-I.
#OPTI=-Ounchecked

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
	@swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz
	@echo "\n$(YELLOW) Minilibx compiled!!! ✅ ${END}"

%.o : %.c
	@cc $(CFLAGS) -c $< -o $@ -I .
	@/bin/echo -n 🟩

%.o: %.swift
	@swiftc $(OPTI) -suppress-warnings $(INC) -parse-as-library -c $< -o $@
	@/bin/echo -n 🟩

%.swiftmodule: %.swift
	@swiftc $(OPTI) -suppress-warnings $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)
	@/bin/echo -n 🟩

clean:
	@rm -f $(NAME) $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *~
	@rm -f *.swiftsourceinfo *~

