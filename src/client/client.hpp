/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:53:33 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/20 09:00:09 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../irc.hpp"

class Client
{
public:
	Client(void);
	Client(int fd);
	// template<typename T>
	// T				get(std::string arg)
	// {
	// 	if (arg == "_fd")
	// 		return (this->_fd);
	// 	else if (arg == "_channel")
	// 		return (this->_channel);
	// 	else if (arg == "_identify")
	// 		return (this->_identify);
	// 	else if (arg == "_username")
	// 		return (this->_username);
	// 	else if (arg == "_nickname")
	// 		return (this->_nickname);
	// };
	int				getFd(void);
	int				getChannel(void);
	bool			getIdentify(void);
	std::string		getUsername(void);
	std::string		getNickname(void);
	//template<typename T>
	// void			set(std::string arg, T newVal)
	// {
	// 	if (arg == "_fd")
	// 		this->_fd = newVal;
	// 	else if (arg == "_channel")
	// 		this->_channel = newVal;
	// 	else if (arg == "_identify")
	// 		this->_identify = newVal;
	// 	else if (arg == "_username")
	// 		this->_username = newVal;
	// 	else if (arg == "_nickname")
	// 		this->_nickname = newVal;
	// };
	void			setFd(int fd);
	void			setChannel(int channel);
	void			setIdentify(bool iden);
	void			setUsername(std::string username);
	void			setNickname(std::string nickname);
	void			printPara(void);

	~Client(void);
private:
	int			_fd;
	int			_channel;
	bool		_identify;
	std::string	_username;
	std::string	_nickname;
};

void	msgServer(std::string str);

#endif