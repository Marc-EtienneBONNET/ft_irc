/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketAddCloseClient.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 07:38:13 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/20 15:03:58 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"

//ajoute les client 
void	Server::_AddClient(void)
{
	pollfd tmp;

	msgServer("Listening socket is readable");
	do
	{
		tmp.events = POLLIN;
		if ((tmp.fd = accept(this->_sockServer, NULL, NULL)) < 0)
		{
			if (errno != EWOULDBLOCK)
				throw std::runtime_error(RED"accept() failed"CLEAR);
			break;
		}
		std::cerr << PURPLE << "---SERVER---  Connection" << GREEN << " open " << PURPLE << "fd : " << tmp.fd << CLEAR << std::endl;
		this->_pfds.push_back(tmp);
		this->_client.push_back(tmp.fd);
	} while (tmp.fd != -1);
}

void	Server::_closedAndPreventClient(int i)
{
	send(this->_pfds[i].fd, "/end", sizeof("/end"), 0);
	close(this->_pfds[i].fd);
	std::cerr << PURPLE << "---SERVER---  Connection" << RED << " closed " << PURPLE << "fd : " << this->_pfds[i].fd << CLEAR << std::endl;
	this->_pfds.erase((this->_pfds.begin() + i));
	this->_client.erase((this->_client.begin() + i));
}