/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:52:09 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/20 14:57:15 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client(void) : _fd(-1), _channel(-1), _identify(false), _username(""), _nickname("") 
{}

Client::Client(int fd) : _fd(fd), _channel(-1), _identify(false), _username(""), _nickname("") 
{}

Client::~Client(void)
{};


int				Client::getFd(void)
{
	return (this->_fd);
}

int				Client::getChannel(void)
{
	return (this->_channel);
}

bool			Client::getIdentify(void)
{
	return (this->_identify);
}

std::string		Client::getUsername(void)
{
	return (this->_username);
}

std::string		Client::getNickname(void)
{
	return (this->_nickname);
}

void			Client::setFd(int fd)
{
	this->_fd = fd;
}

void			Client::setChannel(int channel)
{
	std::cout << GREEN << "Nouveau channel : " << channel << CLEAR << std::endl;this->_channel = channel;
}

void			Client::setIdentify(bool iden)
{
	if (this->_identify == false) std::cout << GREEN << "Moth de passe correcte" << CLEAR << std::endl; this->_identify = iden;
}

void			Client::setUsername(std::string username)
{
	std::cout << GREEN << "Nouveau username : " << username << CLEAR << std::endl;this->_username = username;
}

void			Client::setNickname(std::string nickname)
{
	std::cout << GREEN << "Nouveau nickname : " << nickname << CLEAR << std::endl;this->_nickname = nickname;
}

void	Client::printPara(void)
{ 
	std::cout << "Client : " << std::endl;
	std::cout << "\tfd       : " << this->_fd << std::endl;
	std::cout << "\tchannel  : " << this->_channel << std::endl;
	std::cout << "\tidentify : " << this->_identify << std::endl;
	std::cout << "\tusername : " << this->_username << std::endl;
	std::cout << "\tnickname : " << this->_nickname << std::endl;
}