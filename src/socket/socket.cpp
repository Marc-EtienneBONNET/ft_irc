/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:52:15 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/20 15:27:35 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"

//initialisation avec un controle du port et du password donner
Server::Server(std::string port, std::string password) : _password(password)
{
	for (size_t i = 0; i < port.size(); i++)
	{
		if (port[i] < 48 || port[i] > 57)
			throw std::runtime_error(RED"Port incorrecte"CLEAR);
		if (i > 5)
			throw std::runtime_error(RED"Port incorrecte"CLEAR);
		this->_port = atoi(port.c_str());
		if (this->_port > 65536)
			throw std::runtime_error(RED"Port incorrecte"CLEAR);
	}
	this->_init();
}

Server::~Server()
{
	for (int i = 0; this->_pfds[i].fd > 0; i++)
		close(this->_pfds[i].fd);
}

pollfd *Server::_create_pfd(int fd)
{
	pollfd pfd;

	pfd.fd = fd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	this->_pfds.push_back(pfd);
	return ((this->_pfds.end() - 1).base());
}
