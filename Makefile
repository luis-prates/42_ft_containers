clear_terminal := clear
CXX = c++
CXXFLAGS := -std=c++98 -Wall -Wextra -Werror -g -fsanitize=address
FT = 0
FTFLAGS := "-D=FT $(FT)"
library_option := -l
NAME_STD = std_containers
NAME_FT = ft_containers
output_name_option := -o
remove_file := rm
remove_file_option := -f
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRCS := $(call rwildcard,./src,*.cpp)
INC_DIR = includes
INC := -I $(INC_DIR)
OBJS_STD = $(SRCS:cpp=std.o)
OBJS_FT = $(SRCS:cpp=ft.o)

default_rule: clear_terminal remove_program all

clear_terminal:
	@${clear_terminal}

# The "all", "${NAME}", "clean", "fclean" and "re" make rules are mandatory
# by 42's Norm (version 3 at the time of writting this comment).

debug: CXXFLAGS += -DDEBUG -g -fsanitize=address

debug: $(NAME_STD) $(NAME_FT)

ft: $(NAME_FT)

all: $(NAME_STD) $(NAME_FT) 

$(NAME_STD): $(OBJS_STD)
	$(CXX) $(CXXFLAGS) $(INC) -o $(NAME_STD) $(OBJS_STD)

$(NAME_FT): $(OBJS_FT)
	$(CXX) $(CXXFLAGS) $(INC) -o $(NAME_FT) $(OBJS_FT)

%.std.o: %.cpp
	$(eval FT=0)
	$(CXX) $(CXXFLAGS) "-D=FT 0" $(INC) -c $< -o $@

%.ft.o: %.cpp
	$(eval FT=1)
	$(CXX) $(CXXFLAGS) "-D=FT 1" $(INC) -c $< -o $@

clean:
	@${remove_file} ${remove_file_option} ${OBJS_FT}
	@${remove_file} ${remove_file_option} ${OBJS_STD}

fclean: clean
	@${remove_file} ${remove_file_option} ${NAME_FT}
	@${remove_file} ${remove_file_option} ${NAME_STD}

re: clear fclean all

clear:
	@clear

.PHONY: default_rule clear_terminal remove_program norminette compile execute_program all clean fclean re
