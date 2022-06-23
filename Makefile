# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbouma <tbouma@student.42.fr>                +#+                      #
#                                                    +#+                       #
#    Created: 2022/06/16 15:32:12 by tiemen        #+#    #+#                  #
#    Updated: 2022/06/23 13:47:01 by tiemen        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := philo
OBJFILES := obj/main.o obj/src/utils.o obj/src/eat_sleep_die.o obj/src/debug.o \
obj/src/init.o obj/src/mutex.o obj/src/timer.o obj/src/print.o
OBJFILES_DEBUG := 
LIBFT := includes/libft/libft.a
HEADERS := -I includes/libft/
CFLAGS := -Wall -Wextra -Werror #-fsanitize=thread -g3
LFLAGS := -pthread #-lpthread 
FLAGS_DEBUG := -fsanitize=address -g3 -fsanitize=thread -g3
CC := gcc

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C ./includes/libft

$(NAME): $(OBJFILES)
	cp $(LIBFT) $(NAME)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJFILES) $(LIBFT) $(HEADERS) -o $(NAME)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(LFLAGS) -o $@ $<

clean:
	rm -f $(OBJFILES)
	make clean -C ./includes/libft

fclean:	clean
	rm -f $(NAME)
	make fclean -C ./includes/libft

re: fclean all

.PHONY: clean all fclean re