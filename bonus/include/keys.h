/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:00:13 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/31 22:10:42 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifdef __linux__

enum e_keysyms
{
	MSCROLL_UP = 4,
	MSCROLL_DOWN,
	KEY_A = 97,
	KEY_D = 100,
	KEY_R = 114,
	AKEY_L = 65361,
	AKEY_U,
	AKEY_R,
	AKEY_D,
	KEY_ESC = 65307
};
# endif // !__linux__

# ifdef __MACH__

enum e_keysyms
{
	MSCROLL_UP = 4,
	MSCROLL_DOWN,
	KEY_ESC = 53,
	KEY_A = 0,
	KEY_D = 2,
	KEY_R = 15,
	AKEY_L = 123,
	AKEY_R,
	AKEY_D,
	AKEY_U
};

enum e_events
{
	ON_KEYDOWN = 2,
	ON_KEYUP,
	ON_MOUSEDOWN,
	ON_MOUSEUP,
	ON_MOUSEMOVE,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

# endif // !__MACH__