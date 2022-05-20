/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketSend.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 07:38:13 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/20 15:07:42 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"
#include "../irc.hpp"

void	Server::_send_message(pollfd pfd, int reply_code ,std::string user, std::string msg)
{
	int c;

	std::string str = std::to_string(reply_code);
	str += ":127.0.0.1 " + user + " :" + msg + "\r\n";

	if ((c = send(pfd.fd, str.c_str() , str.size() , 0)) < 0)
			throw std::runtime_error(RED"Send() failed"CLEAR);
}
