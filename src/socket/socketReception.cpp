/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketReception.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 07:38:13 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/20 15:04:54 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"


//receptionne les message 
void	Server::_protocol_Reception(int i)
{
	int rc;
	do
	{
		std::string line;
		int len = 0;
		rc = this->_Reception(&line, &len, i);
		int pars = this->_parsing(i, line);
		if (pars == 1)
			this->_print_Reception(i, len, line);
		else if (pars == -1)
		{
			this->_closedAndPreventClient(i);
			break ;
		}
		else if (pars == -2)
		{
			std::cout << "ERROR commande channel" << std::endl;
			break ;
		}
		if (rc < 0)
		{
			if (errno != EWOULDBLOCK)
				throw std::runtime_error(RED"recv() failed"CLEAR);
			break;
		}
		
	} while(true);
}

int	Server::_Reception(std::string *line, int *len, int i)
{
	char buffer[1];
	int rc = 0;

	memset(&buffer, 0, 1);
	while ((rc = recv(this->_pfds[i].fd, buffer, sizeof(char), 0)) >= 0)
	{
		if (buffer[0] == 13 || buffer[0] == 10)
			buffer[0] = '\0';
		(*line) += buffer[0];
		*len += rc; 
		memset(&buffer, 0, 1);
	}
	std::cout << std::endl;
	return (rc);
} 

int	Server::_parsing(int i, std::string line)
{
	if (this->_client[i].getIdentify() == false)
		return (this->_managementOrdered(i, line));
	else if (this->_client[i].getIdentify() == true)
		return (this->_managementOrdered(i, line));
	else if (this->_client[i].getIdentify() == true)
		return (1);
	//else if (this->_client[i].getIdentify() == true && line == "/end")
	//	return (-1);
	return (-1);
}

int		Server::_managementOrdered(int i, std::string line)
{
	std::string cmd;
	std::string parametre;
	size_t y = 0;

	for (y = 0; y < line.size(); y++)
		if (whitesapece(line[y]) == true)
			break;
	char tmp[y];
	line.copy(tmp, y ,0);
	tmp[y] = '\0';
	cmd = tmp;
	while (whitesapece(line[y]) == true)
		y++;
	char tmp2[line.size() - y];
	line.copy(tmp2, line.size() - y ,y);
	tmp2[line.size() - y] = '\0';
	parametre = tmp2;
	if (cmd == "PASS" && parametre == this->_password)
		this->_client[i].setIdentify(true);
	else if (cmd == "PASS" && parametre != this->_password)
		return (-1);
	else if (cmd == "USER")
		this->_client[i].setUsername(parametre);
	else if (cmd == "NICK")
		this->_client[i].setNickname(parametre);
	else if (cmd == "CHANNEL")
	{
		for (size_t x = 0; x < parametre.size(); x++)
			if (parametre[x] < 48 || parametre[x] > 57)
				return (-2);
		this->_client[i].setChannel(std::atoi(parametre.c_str()));
	}
	else if (cmd == "MESSAGE")
		return (1);
	return (0);
}


void	Server::_print_Reception(int i, int len, std::string line)
{
	std::cerr << BLUE << "------------------------------------------------"<< CLEAR << std::endl;
	std::cerr << BLUE << "RECEPTION"<< CLEAR << std::endl;
	std::cerr << BLUE << "Username  : " << this->_client[i].getUsername() << " Nickname  : " << this->_client[i].getNickname() << CLEAR << std::endl;
	std::cerr << BLUE << "Channel   : " << this->_client[i].getChannel() << " Fd        : " << this->_pfds[i].fd  << CLEAR << std::endl;
	std::cerr << BLUE << "taille    : ("<< len << "bits)"<< CLEAR << std::endl;
	std::cerr << BLUE << "message   : "<< line << CLEAR << std::endl;
	std::cerr << BLUE << "------------------------------------------------"<< CLEAR << std::endl;
}