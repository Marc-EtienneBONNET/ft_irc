/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:52:09 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/20 18:17:36 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client(pollfd *pfd) : _pfd(pfd), _channel(-1), _identify(false), _username(""), _nickname("") 
{}

Client::~Client(void)
{};


int				Client::getFd(void)
{
	return (this->_pfd->fd);
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
	std::cout << "\tfd       : " << this->_pfd->fd << std::endl;
	std::cout << "\tchannel  : " << this->_channel << std::endl;
	std::cout << "\tidentify : " << this->_identify << std::endl;
	std::cout << "\tusername : " << this->_username << std::endl;
	std::cout << "\tnickname : " << this->_nickname << std::endl;
}

std::string	Client::reception()
{
	char buffer[BUFFER_SIZE];
	std::string line;
	int rc;

	memset(&buffer, 0, BUFFER_SIZE);
	if ((rc = recv(_pfd->fd, buffer, (sizeof(char) * BUFFER_SIZE), 0)) < 0)
	{
		if (errno != EWOULDBLOCK)
			throw std::runtime_error(RED"recv() failed"CLEAR);
		line = "";
	}
	buffer[rc - 2] = '\0';
	line = buffer;
	return (line);
}

void	Client::parsing(std::string line)
{
	char tmp[512];

	int x;
	int y = 0;	
	_data.first = "";
	for(size_t v = 0; v < _data.second.size(); v++)
		_data.second.pop_back();
	for (x = 0; line[x]; x++, y++)
	{
		if (whitesapece(line[x]) == true || line[x + 1] == '\0')
		{
			if (line[x + 1] == '\0')
				tmp[y++] = line[x];
			tmp[y] = '\0';
			y = 0;
			if (_data.first.size() == 0)
				_data.first = tmp;
			else
				_data.second.push_back(tmp);
			memset(&tmp, 0, 512);
			x++;
		}
		tmp[y] = line[x];
	}
}