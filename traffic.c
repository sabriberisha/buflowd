/*
 * bloody useless flowdaemon
 *
 * buflowd version very alpha
 *
 * do not try this at home
 *
 * written by Sabri Berisha <sabri@cluecentral.net>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include "data.h"

void handle_flow();

void traffic_read()
{
  int fd, tmp, nread = 0;
  struct sockaddr_in mysockaddrin;
  struct hostent *myhostent;
  char *offsetptr;
  char buf[1500];		/* as only on reading thread will be started,
				 * this is threadsafe */

  myhostent = gethostbyname("0.0.0.0");	/* same here */
  memcpy((char *)&mysockaddrin.sin_addr, myhostent->h_addr_list[0], myhostent->h_length);
  inet_aton("0.0.0.0", &mysockaddrin.sin_addr);
  mysockaddrin.sin_family = myhostent->h_addrtype;
  mysockaddrin.sin_port = htons(9800);
  fd = socket(AF_INET, SOCK_DGRAM, 0);
  bind(fd, (struct sockaddr *)&mysockaddrin, sizeof(mysockaddrin));
  while (fd)
  {

    nread = recv(fd, &buf, 1500, 0);
    memcpy(&p_header, &buf, 24);
    printf("output: %d %d %d %u\n", nread, ntohs(p_header.version), ntohs(p_header.count), ntohl(p_header.unix_secs));
    offsetptr = buf + 24;
    for (tmp = 0; tmp < (ntohs(p_header.count)); tmp++)
    {
      //struct in_addr inaddr;
      memcpy(&p_flow, offsetptr, 48);
      handle_flow();
      printf("output: %u %u %hu %hu %u %u\n", p_flow.srcaddr, p_flow.dstaddr, ntohs(p_flow.srcport), ntohs(p_flow.dstport), ntohl(p_flow.First), ntohl(p_flow.dOctets));
      //inaddr.s_addr = p_flow.srcaddr;
      //printf("out: %s\n", inet_ntoa(inaddr));
      offsetptr = offsetptr + 48;
    }
  }

  pthread_exit(0);
}

void start_traffic_read()
{
  pthread_t thr1;
  if (!(pthread_create(&thr1, NULL, (void *)traffic_read, NULL)) == 0)
  {
    fprintf(stderr, "Fatal error: unable to start the reading thread\n");
    exit(1);
  }
  return;
}
