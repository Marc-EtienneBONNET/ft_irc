/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:53:33 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/20 18:04:49 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../irc.hpp"

class Client
{
public:
	Client(pollfd *pfd);
	~Client(void);
	int				getFd(void);
	int				getChannel(void);
	bool			getIdentify(void);
	std::string		getUsername(void);
	std::string		getNickname(void);
	void			setFd(int fd);
	void			setChannel(int channel);
	void			setIdentify(bool iden);
	void			setUsername(std::string username);
	void			setNickname(std::string nickname);
	void			printPara(void);

	std::string		reception();
	void			parsing(std::string line);



	std::pair<std::string, std::vector<std::string> > _data;
private:
	Client(void){};
	pollfd		*_pfd;
	int			_channel;
	bool		_identify;
	std::string	_username;
	std::string	_nickname;
};


#endif