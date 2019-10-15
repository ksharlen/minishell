/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 12:19:12 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/13 20:50:19 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/xattr.h>
# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <sys/acl.h>
# include <sys/ioctl.h>

/*
**ERRORS
*/
# define EOPENDIR_EACCES			EACCES
# define EOPENDIR_EMFILE			EMFILE
# define EOPENDIR_ENFILE			ENFILE
# define EOPENDIR_ENOENT			ENOENT
# define EOPENDIR_ENOMEM			ENOMEM
# define EOPENDIR_ENOTDIR			ENOTDIR

# define EREADDIR_ENBADF			EBADF

# define ESTATE_EBADF 				EBADF
# define ESTATE_ENOENT 				ENOENT
# define ESTATE_ENOTDIR				ENOTDIR
# define ESTATE_ELOOP				ELOOP
# define ESTATE_EFAULT				EFAULT
# define ESTATE_EACCES				EACCES
# define ESTATE_ENOMEM				ENOMEM
# define ESTATE_ENAMETOOLONG		ENAMETOOLONG

# define D_TYPE						DT_DIR
# define L_TYPE						DT_LNK

/*
**Access permission
*/
# define U_R						S_IRUSR
# define U_W						S_IWUSR
# define U_X						S_IXUSR
# define U_S						S_ISUID

# define G_R						S_IRGRP
# define G_W						S_IWGRP
# define G_X						S_IXGRP
# define G_S						S_ISGID

# define O_R						S_IROTH
# define O_W						S_IWOTH
# define O_X						S_IXOTH
# define O_T						S_ISVTX

# define PERMISS_UX(x) (((x) & U_S) ? -1 : ((x) & U_X))
# define PERMISS_GX(x) (((x) & G_S) ? -1 : ((x) & G_X))
# define PERMISS_OX(x) (((x) & O_T) ? -1 : ((x) & O_X))

# define EFLAGS	"usage: ft_ls [-acfglrtuR] [file ...]\n"
# define FILE_ERROR(filename)	ft_printf("%vft_ls: %s: ", 2, filename)

# define MAX_LEN_FILENAME 255
# define DEFAULT_STYLE	"\e[39;49;22m"
# define NUM_FLAGS		53
# define FLAGS			"afglrtucR"
# define FLAG_ON		1
# define FLAG_OFF		0
# define FLAG_LOW_REG(x) ((x) >= 'a' && (x) <= 'z')
# define FLAG_UPP_REG(x) ((x) >= 'A' && (x) <= 'Z')
# define FLAG_VALID(x) (FLAG_LOW_REG((x)) || FLAG_UPP_REG((x)))
# define CHECK_KEY(x) ((*(x) == '-') && (*(x + 1) != 0))
# define GET_FLAG(flag) ((flag) >= 'a' && ((flag) <= 'z') ? ('a' - 1) : 38)
# define FIND_FLAG(flag) ((flag) - GET_FLAG(flag))

# define MAJOR(x) ((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x) ((int32_t)((x) & 0xffffff))

# define CHECK_ALLOC(x) !(x) ? sys_errors() : 1

# define CURRENT_DIR "."
# define PREV_DIR ".."

typedef	int8_t			t_byte;
typedef uint8_t			t_ubyte;
typedef	uint64_t		t_len;

enum					e_typefile
{
	DIRF = 0,
	LINK = 2,
	SOCKET = 4,
	PIPE = 6,
	EX = 8,
	BLKF = 10,
	SYMF = 12,
	SUID = 14,
	SGID = 16,
	DSCKB = 18,
	DSCKNB = 20
};

typedef struct			s_filename
{
	struct s_filename	*next;
	struct stat			*buf;
	const char			*filename;
	const char			*dirname;
	char				*path;
	const char			*pw_name;
	const char			*gr_name;
	uint8_t				f_type;
}						t_filename;

struct					s_num
{
	int					max_num_link;
	int					max_num_size_file;
	int					max_len_user;
	int					max_len_group;
	int					max_len_little_dev;
	int					max_len_big_dev;
	quad_t				total;
};

struct					s_print
{
	off_t				size_file;
	const char			*filename;
	const char			*user;
	const char			*group;
	const char			*permission;
	const char			*date;
	nlink_t				num_link;
	char				acl_xattr;
	char				filetype;
	const char			*ls_color;
	const char			*color;
	const char			*val_link;
};

struct					s_sort
{
	t_filename			*begin_list;
	t_filename			*prev;
	t_filename			*end;
	t_filename			*tmp;
};

typedef struct			s_column
{
	int			width;
	int			col;
	int			col_files;
	int			col_files_whl;
	int			col_iter;
	int			poz;
}						t_column;

int						ft_ls(size_t argc, char *const argv[]);

/*
**Lists filename
*/
void					list_filename_add_end(t_filename **beg,
	const char *filename, uint8_t f_type, const char *dirname);
void					push_list_filename_dir_content(DIR *dir,
	t_filename **beg, t_ubyte *flags, const char *dirname);

/*
**Lists fullinfo
*/
void					push_buf_stat_to_filename(t_filename *beg);

/*
**Validation
*/
DIR						*valid_opendir(const char *filename);
struct dirent			*valid_readdir(DIR *dir);
void					valid_stat(const char *filename,
	struct stat *buf, uint8_t f_type);
char					*valid_readlink(const char *path_link);

/*
**Errors
*/
void					sys_errors(void);
void					file_errors(const char *filename);
void					flag_error(t_ubyte sym);

/*
**Sorts
*/
t_filename				*sort_list_by_flags(t_filename **beg, t_ubyte *flags);
t_filename				*list_filename_merge(t_filename *l_one,
	t_filename *l_two, int (*key)(t_filename *, t_filename *));

/*
**Other
*/
int						chk_flags_for_print_fullinfo(t_ubyte *flags);
size_t					collect_flags(size_t argc, char *const argv[],
	t_ubyte *flags);
void					list_revers(t_filename **beg);
char					*cat_path_filename(const char *dirname,
	const char *filename);
void					max_len_elem(const t_filename *beg,
	struct s_num *align);
const char				*cut_date(const time_t sec);
void					max_len_little_big_dev(const t_filename *beg,
	struct s_num *align);
t_filename				*list_end_elem(t_filename *beg);

/*
**Compare
*/
int						cmp_atime(t_filename *one, t_filename *two);
int						cmp_mtime(t_filename *one, t_filename *two);
int						cmp_name(t_filename *one, t_filename *two);

/*
**print_list
*/
void					print_list(t_filename *beg, t_ubyte *flags);
void					print_fullinfo(const t_filename *beg,
	const t_ubyte *flags, const char *ls_color);
size_t					pull_size_list(const t_filename *beg);

/*
**pull_info
*/
char					pull_filetype(const mode_t st_mode);
char					*pull_access_permission(const mode_t st_mode);
char					pull_acl_xattr(const char *path);
const char				*pull_date(const t_filename *beg,
	const t_ubyte *flags);
const char				*pull_val_link(const char *path_link);
void					pull_dir(t_filename *beg, t_ubyte *flags);

/*
**Garbage_collector
*/
void					clear_filename(t_filename **beg);
void					clean_mem(struct s_print print_info);

/*
**color
*/
const char				*push_color(const mode_t st_mode,
	const char *ls_color);
void					def_font(char *color, const char ls_color);
void					def_backgrnd(char *color, const char ls_color);
void					def_color(char *color, const char ls_color);

void					column(int argc, char **files);

#endif
