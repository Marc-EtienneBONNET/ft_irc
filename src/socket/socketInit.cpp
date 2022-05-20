/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketInit.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 07:44:48 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/20 15:36:49 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"

//programation du serveur
void Server::_init(void)
{
	int rc;
	int on = 1;

	if ((this->_sockServer = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
		throw std::runtime_error(RED"socket() failed"CLEAR);
	if ((rc = setsockopt(this->_sockServer, SOL_SOCKET,  SO_REUSEADDR,(char *)&on, sizeof(on))) < 0)
		throw std::runtime_error(RED"setsockopt() failed"CLEAR);
	if ((rc = ioctl(this->_sockServer, FIONBIO, (char *)&on)) < 0)
		throw std::runtime_error(RED"ioctl() failed"CLEAR);
	memset(&this->_addrServer, 0, sizeof(this->_addrServer));
	this->_addrServer.sin6_family      = AF_INET6;
	memcpy(&this->_addrServer.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	this->_addrServer.sin6_port        = htons(this->_port);
	if ((rc = bind(this->_sockServer,(struct sockaddr *)&this->_addrServer, sizeof(this->_addrServer))) < 0)
			throw std::runtime_error(RED"bind() failed"CLEAR);
	if ((rc = listen(this->_sockServer, 32)) < 0)
			throw std::runtime_error(RED"listen() failed"CLEAR);

	Client client(_create_pfd(this->_sockServer));
	this->_client.push_back(client);
	SUCCESS("init is sucess !");
}

//protocole d ajoue des fd et de reception des message
void Server::run(void)
{
	SUCCESS("is runing !");
	do
	{
		if ((poll(&(*this->_pfds.begin()), this->_pfds.size(), TIME)) <= 0)
			throw std::runtime_error(RED"poll() failed/timeout"CLEAR);
		for (size_t i = 0; i < this->_pfds.size(); i++)
		{
			if(this->_pfds[i].revents == 0)
				continue;
			if(this->_pfds[i].revents != POLLIN)
			{
				ERROR("Impossible de lire le socket");
				this->_close_and_prevent_client(i);
				break;
			}
			if (this->_pfds[i].fd == this->_sockServer)
				this->_add_client();
			else
				this->_protocol_reception(i);
		}
	} while (1);
}