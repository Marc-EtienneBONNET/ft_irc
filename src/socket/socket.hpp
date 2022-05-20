/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:52:18 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/20 15:55:11 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "../irc.hpp"

class Server
{
public:
	Server(std::string port, std::string password);
	~Server(void);
	void	run(void);											//protocole d ajoue des fd et de reception des message

private:
	int					_port;
	int					_sockServer;
	struct sockaddr_in6	_addrServer;

	std::string			_password;
	std::vector<pollfd>	_pfds;
	std::vector<Client>	_client;
	
	Server(void){};
	void		_init();										//programation du serveur
	void		_close_and_prevent_client(int i);						//previent le client de la fermeture, ferme le fd du client et suprime l element du tableau 
	void		_add_client(void);									//ajoute les client 
	void		_protocol_reception(int i);							//receptionne les message
	// std::string	_reception( int i);

	int		_parsing(int i, std::string line);					//traitement des information receptionner
	void	_print_reception(int i, int len, std::string line);	//ecriture de la reception
	int		_management_ordered(int i, std::string line);
	void	_send_message(pollfd pfd, int reply_code ,std::string user, std::string msg);
	pollfd	*_create_pfd(int fd);
};


#endif