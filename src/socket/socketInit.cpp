/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketInit.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 07:44:48 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/20 15:04:21 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"

//programation du serveur
void Server::_init(void)
{
	int rc;
	int on = 1;
	pollfd tmp;

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
	tmp.fd = this->_sockServer;
	tmp.events = POLLIN;
	this->_pfds.push_back(tmp);
	this->_client.push_back(Client());
	msgServer("Server correctement initialiser...");
}

//protocole d ajoue des fd et de reception des message
void Server::run(void)
{
	int rc, current_size;
	do
	{
		if ((rc = poll(&(*this->_pfds.begin()), this->_pfds.size(), TIME)) <= 0)
			throw std::runtime_error(RED"poll() failed/timeout"CLEAR);
		current_size = this->_pfds.size();
		for (int i = 0; i < current_size; i++)
		{
			if(this->_pfds[i].revents == 0)
				continue;
			if(this->_pfds[i].revents != POLLIN)
			{
				std::cout << RED << "Error! revents = " << this->_pfds[i].revents << CLEAR << std::endl;
				this->_closedAndPreventClient(i);
				break;
			}
			if (this->_pfds[i].fd == this->_sockServer)
				this->_AddClient();
			else
					this->_protocol_Reception(i);
		}
	} while (1);
}