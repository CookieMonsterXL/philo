# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 15:32:12 by tiemen            #+#    #+#              #
#    Updated: 2022/07/19 14:48:52 by tbouma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
OBJFILES := obj/src/main.o \
			obj/src/eat_sleep_die.o \
			obj/src/init.o \
			obj/src/mutex_lock.o \
			obj/src/fork_lock.o \
			obj/src/timer.o \
			obj/src/print.o \
			obj/src/check_set_var.o \
			obj/src/threads.o \
			obj/src/input_check.o \
			obj/src/libft.o \
			obj/src/libft2.o
OBJFILES_DEBUG := 
HEADERS := -I includes/libft/
CFLAGS := -Wall -Wextra -Werror
LFLAGS := -pthread
FLAGS_DEBUG := -fsanitize=address -g3 -fsanitize=thread
CC := gcc

all: $(NAME)

$(NAME): $(OBJFILES)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJFILES) $(HEADERS) -o $(NAME)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(LFLAGS) -o $@ $<

clean:
	rm -f $(OBJFILES)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all fclean re