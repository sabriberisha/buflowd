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
#include <unistd.h>

void start_traffic_read();
void init_flowdata();

int main(int argc, char *argv[])
{
  init_flowdata();
  start_traffic_read();
  sleep(600);
  exit(0);
}
