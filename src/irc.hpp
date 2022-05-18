#ifndef IRC_HPP
#define IRC_HPP

# define BLEU "\e[1;36m"
# define BLEU_2 "\e[1;34m"
# define ROUGE "\e[1;31m"
# define VERT "\e[1;32m"
# define JAUNE "\e[1;33m"
# define VIOLET "\e[1;35m"
# define BLANC "\e[0m"
#define SERVER_PORT 10000
#define TIME 3 * 60 * 1000

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <map>
#include "utils/utils.hpp"
#include "socket/socket.hpp"

#endif