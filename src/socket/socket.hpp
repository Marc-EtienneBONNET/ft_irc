/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:52:18 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/20 15:05:04 by mbonnet          ###   ########.fr       */
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
	std::string			_password;
	int					_sockServer;
	struct sockaddr_in6	_addrServer;
	std::vector<pollfd>	_pfds;
	std::vector<Client>	_client;
	
	Server(void){};
	void	_init();										//programation du serveur
	void	_closedAndPreventClient(int i);						//previent le client de la fermeture, ferme le fd du client et suprime l element du tableau 
	void	_AddClient(void);									//ajoute les client 
	void	_protocol_Reception(int i);							//receptionne les message
	int		_Reception(std::string *line, int *len, int i);
	int		_parsing(int i, std::string line);					//traitement des information receptionner
	void	_print_Reception(int i, int len, std::string line);	//ecriture de la reception
	int		_managementOrdered(int i, std::string line);
	void	_sendMessage(pollfd pfd, int reply_code ,std::string user, std::string msg);
};

void	msgServer(std::string str);

#endif