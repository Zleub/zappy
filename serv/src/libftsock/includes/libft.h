/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/15 17:10:04 by garm              #+#    #+#             */
/*   Updated: 2014/06/21 15:08:37 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <sys/types.h>
# include "libft_config.h"

/*
** Memory
*/
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memalloc(size_t size);
void		ft_memdel(void **ap);
void		*ft_memcpy(void *s1, const void *s2, size_t n);
void		*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void		*ft_memmove(void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memdup(const void *ptr, size_t size);

/*
** Strings
*/
char		*ft_strnew(size_t size);
void		ft_strdel(char **s);
void		ft_strclr(char *s);
size_t		ft_strlen(const char *s);
size_t		ft_strlenc(const char *s, char c);
char		*ft_strdup(const char *s);
char		*ft_strcpy(char *s1, const char *s2);
char		*ft_strncpy(char *s1, const char *s2, size_t n);
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strncat(char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strstr(const char *s1, const char *s2);
char		*ft_strnstr(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strequ(const char *s1, const char *s2);
int			ft_strnequ(const char *s1, const char *s2);
char		*ft_strsub(const char *s, unsigned int start, size_t len);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strtrim(const char *s);
char		*ft_strtrimc(const char *s, char c);
int			ft_findc(const char *s, char c);
int			ft_strcountc(const char *s, char c);
char		*ft_strdelmultic(const char *s, char c);
char		**ft_strsplit(const char *s, char c);
void		ft_splitdel(char ***split);

/*
** Digits, Numbers and characters
*/
int			ft_atoi(const char *str);
char		*ft_itoa(const int n);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isupper(int c);
int			ft_islower(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_iswhite(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_ban_neg(int n);

/*
** Print
*/
int			ft_putchar(const char c);
int			ft_putstr(const char *str);
int			ft_putendl(const char *str);
void		ft_putnbr(const int n);
char		*ft_putnstr(const char *str, size_t n);
int			ft_printf(const char *format, ...);

int			ft_putchar_fd(const char c, int fd);
int			ft_putstr_fd(const char *str, int fd);
int			ft_putendl_fd(const char *str, int fd);
void		ft_putnbr_fd(const int n, int fd);
char		*ft_putnstr_fd(const char *str, size_t n, int fd);
int			ft_fprintf(int fd, const char *format, ...);

int			ft_error(const char *str);
void		ft_fatal(const char *str);

#endif
