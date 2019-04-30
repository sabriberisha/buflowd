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
#include "data.h"

struct flowdata *find_flowdata();
struct flowdata *add_flowdata();

void handle_flow()
{
  struct flowdata *flowdataptr;
  flowdataptr = find_flowdata(p_flow.srcaddr);
  if (flowdataptr == '\0')
    flowdataptr = add_flowdata(p_flow.srcaddr);
  printf("flowdataptr found!! %u\n", flowdataptr->ipaddr);
  return;
}
