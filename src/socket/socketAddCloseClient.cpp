/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketAddCloseClient.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 07:38:13 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/20 15:35:44 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"

//ajoute les client 
void	Server::_add_client(void)
{
	int tmps;
	do
	{
		if ((tmps = accept(this->_sockServer, NULL, NULL)) < 0)
		{
			if (errno != EWOULDBLOCK)
				throw std::runtime_error(RED"accept() failed"CLEAR);
			break;
		}
		Client client(_create_pfd(tmps));
		this->_client.push_back(client);
		INFO("someone is triying to connect to the server... Waiting for identification");
	} while (tmps != -1);
}

void	Server::_close_and_prevent_client(int i)
{
	close(this->_pfds[i].fd);
	this->_pfds.erase((this->_pfds.begin() + i));
	this->_client.erase((this->_client.begin() + i));
}