/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:52:18 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/24 14:06:42 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "../irc.hpp"

#define BUFFER_SIZE 512

/**
 * @brief 
 * Pas de Kamelcase pour les fonctions !
 * exemple: 
 * 		- get_fd()
 * 		- get_channel()
 * invalide:
 * 		- GetFd()
 * 		- GetChannel()
 */

class Server
{
public:
	Server(std::string port, std::string password);
	~Server(void);
	
	void	run(void);

private:
	int					_port;
	int					_sock_server;
	struct sockaddr_in6	_addr_server;

	std::string						_password;
	
	std::vector<pollfd>				_pfds;
	std::vector<Client>				_clients;
	std::map<std::string, Channel>	_channels;
	
	static int						_nb_channel;

	void			_init();
	void			_new_client(void);
	void			_client_handler(std::vector<Client>::iterator& it);
	void			_disconnect(std::vector<Client>::iterator& it);
	std::string		_uuid();
	pollfd*	_create_pfd(int fd);
};



#endif