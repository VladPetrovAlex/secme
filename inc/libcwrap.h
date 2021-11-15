#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/ip.h>

__attribute__((warn_unused_result))
extern ssize_t secme_sendto(int fd, const char *buf, size_t size, const struct sockaddr *addr, socklen_t addrlen);

__attribute__((warn_unused_result))
extern ssize_t secme_recvfrom(int fd, char *buf, size_t size, struct sockaddr *addr, socklen_t *addrlen);

__attribute__((warn_unused_result))
extern int secme_epoll_wait(int epfd, struct epoll_event *events, size_t eventmax, int timeout);
