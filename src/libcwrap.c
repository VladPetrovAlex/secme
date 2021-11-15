#include "../inc/libcwrap.h"

#define SECME_IOFAIL(r) \
  ((((r) < 0) && (EAGAIN != errno)) || ((r) == 0))

ssize_t secme_sendto(int fd, const char *buf, size_t size, const struct sockaddr *addr, socklen_t addrlen)
{
  size_t total = 0;
  ssize_t c = -1;
  int flags = MSG_NOSIGNAL;
  
  while(total < size) {
    c = TEMP_FAILURE_RETRY(sendto(fd, buf + total, size - total, flags, addr, addrlen));
    if(c > 0) {
      total += c;
    } else {
      break;
    } 
  }
  
  return SECME_IOFAIL(c) ? -1 : (ssize_t)total;
}

ssize_t secme_recvfrom(int fd, char *buf, size_t size, struct sockaddr *addr, socklen_t *addrlen)
{
  size_t total = 0;
  ssize_t c = -1;
  int flags = MSG_NOSIGNAL;
  
  while(total < size) {
    c = TEMP_FAILURE_RETRY(recvfrom(fd, buf + total, size - total, flags, addr, addrlen));
    if(c > 0) {
      total += c;
    } else {
      break;
    } 
  }
  
  return SECME_IOFAIL(c) ? -1 : (ssize_t)total;
}

int secme_epoll_wait(int epfd, struct epoll_event *events, size_t eventmax, int timeout)
{
  return TEMP_FAILURE_RETRY(epoll_wait(epfd, events, (int)eventmax, timeout));
}
