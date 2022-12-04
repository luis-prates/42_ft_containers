clear_terminal := clear
CXX = c++
CXXFLAGS := -std=c++98 -Wall -Wextra -Werror
enable_debug := #-g -fsanitize=address
#header_file := ./minishell.h
library_option := -l
NAME := ft_containers
#norminette := norminette
output_name_option := -o
program_file := ./${NAME}
remove_file := rm
remove_file_option := -f
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRCS := $(call rwildcard,./,*.cpp)
INC := *.hpp
OBJS := $(SRCS:.cpp=.o)
#include_dirs := includes libs/libft/
#includes := $(addprefix -I, $(include_dirs))
#turn_warnings_into_errors := -Werror

default_rule: clear_terminal remove_program all

clear_terminal:
	@${clear_terminal}

remove_program:
	@${remove_file} ${remove_file_option} ${program_file}

#execute_program:
#	@${program_file}

# The "all", "${NAME}", "clean", "fclean" and "re" make rules are mandatory
# by 42's Norm (version 3 at the time of writting this comment).

debug: CXXFLAGS += -DDEBUG -g -fsanitize=address

debug: $(NAME) 

all: ${NAME} #${program_file}

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
$(OBJS): $(SRCS) $(INC) Makefile

clean:
	@${remove_file} ${remove_file_option} ${OBJS}

fclean: clean
	@${remove_file} ${remove_file_option} ${program_file}

re: fclean all

.PHONY: default_rule clear_terminal remove_program norminette compile execute_program all clean fclean re
