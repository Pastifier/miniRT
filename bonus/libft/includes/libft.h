/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:17:38 by pastifier         #+#    #+#             */
/*   Updated: 2024/02/04 02:03:46 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>	// for malloc, free, size_t 
# include <stdbool.h>	// for true, false
# include <unistd.h>	// for write
# include <limits.h>	// for INT_MIN, INT_MAX
# include <stdint.h>	// for SIZE_MAX
# include <fcntl.h>		// for open, close,...

// Mainly for open(2) stuff.
# include <sys/types.h>
# include <sys/stat.h>

/************************************
 *                                  *
 *      SECTION 1.a: <ctype.h>      *
 *                                  *
 ************************************/

typedef unsigned long long	t_ull;
/*
* Returns `1` if `c` is an alphabet, and `0` otherwise.
*
* (ASCII REPRESENTED)
*/
int		ft_isalpha(int c);

/*
* Returns `1` if `c` is a digit, and `0` otherwise.
* 
* (ASCII REPRESENTED)
*/
int		ft_isdigit(int c);

/*
* Returns `1` if `c` is alphanumeric, and `0` otherwise.
* 
* (ASCII REPRESENTED)
*/
int		ft_isalnum(int c);

/*
* Returns `1` if `c` is within ASCII range, and `0` otherwise.
* 
* This is a legacy function, and is pretty much useless if you're not
* strictly operating on integers.

* (Although you could probably do some cool maths stuff with it).
*/
int		ft_isascii(int c);

/*
* Returns `1` if `c` represents a printable character
* according to the ASCII table, and `0` otherwise. 
*/
int		ft_isprint(int c);

/*
	Returns the uppercase variant of a lowercase character.
	If the character is not alphabetic, the same character
	is returned.

	(ASCII REPRESENTED)
*/
int		ft_toupper(int c);

/*
	Returns the lowercase variant of an uppercase character.
	If the character is not alphabetic, the same character
	is returned.

	(ASCII REPRESENTED)
*/
int		ft_tolower(int c);

/************************************
 *                                  *
 *      SECTION 1.b: <string.h>     *
 *                                  *
 ************************************/

/*
	Searches the string `s` for the first occurence of
 	the character `c`.

  	(`s` must be a true, null-terminated, C string).
   	(`c` is typecasted to `char`, so using non-ASCII values
    is pretty-much useless).
	(Violating the above warnings or feeding it invalid pointers
	is undefined behaviour).
*/
char	*ft_strchr(const char *s, int c);

/*
	Works exactly like `ft_strchr`, but locates the last
 	occurence of `c` (as opposed to its first occurence).
*/
char	*ft_strrchr(const char *s, int c);

/*
	Compares `n` bytes of `s1` and `s2` and returns the
 	difference of the first non-equal value
  	(difference of the first difference hehe).

   	This function is NOT safe, and you should use it only when
    you're sure of the size. Not using true C strings will
    cause undefined behaviour!!
*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*
	Returns the amount of characters in the
 	true C string `str` (null-terminated).

	(Not using a true C string will cause undefined behaviour).
 */
size_t	ft_strlen(const char *str);

/*
	Copies the input string into a destination string.
 	If the destination buffer, limited by its size, isn't
  	large enough to hold the copy, the resulting string is truncated
   	(but it is guaranteed to be null-terminated).
    It returns the length of the total string they tried to create.

    (The programmer is responsible for inputting an accurate size).
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t sz);

/*
	Catenates the input string into a destination string.
 	If the destination buffer, limited by its size, isn't
  	large enough to hold the copy, the resulting string is truncated
   	(but it is guaranteed to be null-terminated).
    It returns the length of the total string they tried to create.

    (The programmer is responsible for inputting an accurate size).
*/
size_t	ft_strlcat(char *dst, const char *src, size_t sz);

/*
	Searches `haystack` for the first occurence of `needle`, and
 	returns a pointer to that address, or NULL if `needle`
  	doesn't exist in `haystack`. If `needle` is empty,
   	a pointer to `haystack` is returned.
 	
  	This function uses ft_strncmp for its implementation, so
  	make sure the inputs are true C strings (see ft_strncmp).
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t haylen);

/************************************
 *                                  *
 *                   <string.h>     *
 *      SECTION 1.c:                *
 *                   <stdlib.h>     *
 *                                  *
 ************************************/

typedef struct s_error_int
{
	int		value;
	int		operations;
	bool	error;
}	t_eint;

typedef struct s_split_result
{
	char	**array;
	size_t	wordcount;
}	t_split;

/*
 * Fill the first `n` bytes of memory the memory region
 	pointed to by `s` with zeroes(value).
 
	This function is NOT safe! Only use it when you're
	sure `n` is within the range of memory you're allowed
	after `s`.
 * (It's on the user to provide valid inputs. Otherwise,
 	it's undefined behaviour).
 */
void	ft_bzero(void *s, size_t n);

/*
	Fills the first n bytes of the memory area pointed
	to by `s` with the constant byte `c`.
	
	This function is NOT safe! Only use it when you're
	sure `n` is within the range of memory you're allowed
	after `s`.
	(It's on the user to provide valid inputs. Otherwise,
	it's undefined behaviour).
*/
void	*ft_memset(void *s, int c, size_t n);

/*
	Searches the first `n` bytes of the memory region 
	pointed to by `s` for the first occurence of `c`, 
	and returns a pointer to that location.
	Returns a NULL pointer if fed an invalid `s` value.
	
	(`c` is casted into an `unsigned char`, so providing
	lower or higher values is undefined behaviour).
*/
void	*ft_memchr(const void *s, int c, size_t n);

/*
	Copies `n` bytes from memory area `src` to memory area `dst`.
	The memory areas must not overlap, and `n` has to be positive
	(see ft_memmove).

	Returns a pointer to `dst`.
	(Feeding it invalid pointers is undefined behaviour).
*/
void	*ft_memcpy(void *dst, const void *src, size_t n);

/*
	Copies `n` bytes from memory area `src` to memory area `dst`. 
	
	The memory areas may overlap: copying takes place as though the
	bytes in `src` are first copied into a temporary array that does
	not overlap `src` or `dst`, and the bytes are then copied
	from the temporary array to `dst`.

	Returns a pointer to `dst`.
	(Feeding it invalid pointers is undefined behaviour).
*/
void	*ft_memmove(void *dst, const void *src, size_t n);

/*
	Compares two memory regions of size `n`.

	Returns  an  integer less than, equal to, or greater than zero
	if the first n bytes of s1 is found, respectively, to be less than, to match,
	or be greater than the first n bytes of s2.

	(Feeding it invalid pointers is undefined behaviour).
*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/*
	Returns a duplicate to the string `str`

  	(`str` must be a true C string).
*/
char	*ft_strdup(const char *str);

/*
 * Allocates memory for an array of nmemb elements of `n` bytes each 
 * and returns a pointer to the allocated memory, and the memory is 
 * filled with zeroes (value). 
 * If `nmemb` or `n` is 0, NULL is returned.
 */
void	*ft_calloc(size_t nmemb, size_t n);

/*
 * Takes a true C string (null-terminated) and converts it to its
 * integer representation.
 * Whitespace at the start will be ignored, and non-digit characters will stop
 * execution if present anywhere within the string.
 * 
 * (If the resulting int representation is not within 
 * INT_MIN to INT_MAX, it's undefined behaviour).
 * 
 * 
 * EXAMPLE OF INVALID INPUT:
 * "   sdf -+29skj"
 * 
 * EXAMPLE OF VALID INPUT:
 * "       -20001"
 */
t_eint	ft_atoi(const char *str);

/************************************
 *                                  *
 *		SECTION 2: EPIC GUYS        *
 *                                  *
 ************************************/

/*
	Returns a new string of size `len` that starts from
 	`s[start]` and ends at `s[len - 1]`.

  	Providing invalid input (out-of-range) should be undefined
   	behaviour, but I handled those cases for my own future use:
    - Providing an index that's larger than the string length
      will result in an empty string.
	- Providing a size which is larger than the string length
 	  will force the size to shrink back to the string's true
      length (provided it's a true C string).
*/
char	*ft_substr(const char *s, unsigned int start, size_t len);

/*
	Returns a string which is the result of joining
 	`s1` and `s2`

  	(Both strings must be true C strings).
*/
char	*ft_strjoin(const char *s1, const char *s2);

/*
	Trims all successive-occurences of any character in
 	`set` from the start and end of the true C string `s`.
*/
char	*ft_strtrim(const char *s1, const char *set);

/*
	Takes a string `s`, and returns an array of all its substrings split
 	by the delimiter `c`.

	(E.g. "Hello, World!" would return {"Hello", " World!"}).
	@param s: The string to split.
	@param c: The delimiter character.
*/
t_split	ft_split(const char *s, char *charset);

/*
	Converts an integer `n` to its ASCII representation,
	and returns a string of that representation.

	(Feeding it a non-`int` value is undefined behaviour).
*/
char	*ft_itoa(int n);

/*
	Returns a new string which is the result of applying
 	the function `f` on each character of the string `s`.

  	(`s` must be a true C string, and `f` must be valid.)
*/
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));

/*
	Applies the function `f` on every character in
 	the character array: `s`.

  	(`s` must be a true C string, `f` must be valid).
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/*
	Writes the character `c` into the file descriptor `fd`.

	(Invalid `fd` values will cause it to do nothing). 
*/
void	ft_putchar_fd(char c, int fd);

/*
	Writes the string `s` into the file descriptor `fd`.

	(Invalid `fd` values will cause it to do nothing). 
*/
void	ft_putstr_fd(char *s, int fd);

/*
	Writes the string `s` into the file descriptor `fd`, 
	followed by a newline character.

	(Feeding it an invalid string or `fd` will cause it to do nothing).
*/
void	ft_putendl_fd(char *s, int fd);

/*
	Writes the integer `int` into the file descriptor `fd`.

	(Invalid `fd` values will cause it to do nothing). 
*/
void	ft_putnbr_fd(int n, int fd);

/************************************
 *                                  *
 *      SECTION 3: BONUS            *
 *                                  *
 ************************************/

/*
 * Node struct. I don't know why my boss didn't
 * just let me name it "node" or something...
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*
 * Initialises your list and returns a pointer to work with.
 * The node's value is represented by `content`.
 * (`content` can be of any base type).
 * The next node is set to NULL by default.
 * Returns NULL on allocation failure and thus makes the list invalid.

 * (Performing operations on an invalid list is undefined behaviour).
 */
t_list	*ft_lstnew(void *content);

/*
 * Takes a pointer to a list, and sets `new` as the head of that list.

 * (Previous content gets pushed after the new head).
 * (Feeding it an invalid `lst` pointer will cause it to do nothing).
 * (Feeding it an invalid node is undefined behaviour).
 */
void	ft_lstadd_front(t_list **lst, t_list *to_add);

/*
 * Takes the head and returns the number of nodes in the list.

 * (Feeding it an invalid head pointer is undefined behaviour).
 */
int		ft_lstsize(t_list *lst);

/*
 * Takes the head of a list and returns the last node in that list.

 * (The final node in your list should point to NULL)
 * (Feeding it an invalid head/list is undefined behaviour/infinite loop).
 */
t_list	*ft_lstlast(t_list *lst);

/*
 * Appends a node to the end of the list and sets its `next` value to
 * NULL by default.

 * (If `lst` is invalid, it does nothing).
 * (Feeding it an invalid node is undefined behaviour).
 */
void	ft_lstadd_back(t_list **lst, t_list *to_add);

/* 
 * Takes a node and applies `del` to its contents (usually a deleting function)
 * and frees the node `free(3)`

 * (Feeding it an invalid node or function pointer will cause it to do nothing).
 * (Using a non-deleting function is undefined behaviour).
 * (Deleting a node in the middle/start of the list, will cause a memory-leak
 * if you're not careful; always link the next node with the previous one.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/*
	Deletes and frees the given node and every
	successor of that node, using the function `del`
	and `free(3)`.

	(If either `del`, `lst`, or `*lst` are invalid, nothing happens).
	(Feeding it a non-deletion function is undefined behaviour).
*/
void	ft_lstclear(t_list **lst, void (*del)(void *));

/*
	Applies the function to `lst`'s contents, and
	all its subsequent nodes.

	(Feeding it an invalid node/function pointer will result in nothing).
*/
void	ft_lstiter(t_list *lst, void (*f)(void *));

/*
	Returns a new list with `f` applied on `lst` and
	all its subsequent nodes. Returns NULL, and frees
	memory on error.

	(`lst` must be a valid list).
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*--------- ADD. FUNCS ----------*/

/*-----const.defs-----*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif // !BUFFER_SIZE

/*--------GNL--------*/

typedef struct s_gnl
{
	char	*line;
	size_t	len;
	bool	error;
	bool	eof;
}	t_gnl;

// Takes in a file-descriptor and fetches
// data from it line-by-line, call-by-call,
// respectively.
//
// RETURN VALUES:
// - The next line starting from the file-descriptor's
// current read-offset
// (offset starts from `0`, beggining of file).
//
// - NULL if the file-descriptor's offset is at EOF
// or on error/failure.
// @param fd: The file-descriptor in question.
t_gnl	get_next_line(int fd);

#endif // !LIBFT_H
