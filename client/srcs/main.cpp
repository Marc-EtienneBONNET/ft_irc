/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:11:23 by mbonnet           #+#    #+#             */
/*   Updated: 2022/05/18 11:40:47 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/irc.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <map>

int	main()
{
	int	socketClient = socket(AF_INET6, SOCK_STREAM, 0);
	struct sockaddr_in6 addrClient;
	memset(&addrClient, 0, sizeof(addrClient));
  	memcpy(&addrClient.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	addrClient.sin6_family      = AF_INET6;
	addrClient.sin6_port = htons(10000);
	connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient));
	std::cout << "connected" << std::endl;
	std::string test;
	char str[4];
	while (1)
	{
		std::getline(std::cin, test);
		test[test.c_str()] = '\0';
		send(socketClient, test.c_str(), test.size(), 0);
		std::cout << "ici : " << test << std::endl;
		if (test == "end")
		{
			recv(socketClient, str, sizeof(str), 0);
			test = str;
			if (test == "end")
				break;
		}
	}
	close(socketClient);
	return (0);
}