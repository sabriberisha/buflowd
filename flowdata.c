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

// uint32_t max = 4294967295;	/* I hate useless warnings */
uint32_t max = 4096;		/* I hate useless warnings */
void addleaf();

void init_flowdata()
{
  uint32_t tmp;
  flowdata.ipaddr = max / 2;
  flowdata.parent = malloc(sizeof(struct flowdata));
  flowdata.lower = malloc(sizeof(struct flowdata));
  flowdata.higher = malloc(sizeof(struct flowdata));
  tmp = flowdata.ipaddr / 2;
  flowdata.lower->ipaddr = tmp;
  flowdata.lower->lower = '\0';
  flowdata.lower->parent = &flowdata;
  flowdata.higher->ipaddr = flowdata.ipaddr + tmp;
  flowdata.higher->parent = &flowdata;
  flowdata.higher->lower = '\0';
  return;
}

struct flowdata *find_flowdata(uint32_t ipaddr)
{
  struct flowdata *treeptr = &flowdata;
  do
  {
    if (treeptr->ipaddr != ipaddr)
      if (treeptr->ipaddr > ipaddr)
	if (treeptr->lower != '\0')
	  treeptr = treeptr->lower;
	else
	  return ('\0');
      else if (treeptr->higher != '\0')
	treeptr = treeptr->higher;
      else
	return ('\0');
    else
      return (treeptr);
    if (treeptr->ipaddr == 1 || treeptr->ipaddr == max)
      treeptr = '\0';
  } while (treeptr);
  return ('\0');
}

struct flowdata *add_flowdata(uint32_t ipaddr)
{
  uint32_t tmp;
  struct flowdata *treeptr = &flowdata;
  if (ipaddr == treeptr->ipaddr)
    return (treeptr);
  do
  {
    if (ipaddr == treeptr->ipaddr)
      return (treeptr);
    if (ipaddr < treeptr->ipaddr)
    {
      printf("%u lower than %u\n", ipaddr, treeptr->ipaddr);
      if (treeptr->lower == '\0' && treeptr->higher == '\0')
      {
	treeptr->lower = malloc(sizeof(struct flowdata));
	treeptr->higher = malloc(sizeof(struct flowdata));
	tmp = treeptr->ipaddr / 2;
	treeptr->lower->ipaddr = tmp;
	treeptr->lower->lower = '\0';
	treeptr->lower->parent = treeptr;
	treeptr->higher->ipaddr = treeptr->ipaddr + tmp;
	treeptr->higher->parent = treeptr;
	treeptr->higher->lower = '\0';
	printf("%u new subtree lower\n", treeptr->lower->ipaddr);
      }
      treeptr = treeptr->lower;
    } else
    {
      printf("%u higher than %u\n", ipaddr, treeptr->ipaddr);
      if (treeptr->lower == '\0' && treeptr->higher == '\0')
      {
	treeptr->lower = malloc(sizeof(struct flowdata));
	treeptr->higher = malloc(sizeof(struct flowdata));
	tmp = treeptr->ipaddr / 4;
	treeptr->lower->ipaddr = tmp;
	treeptr->lower->lower = '\0';
	treeptr->lower->parent = treeptr;
	treeptr->higher->ipaddr = treeptr->ipaddr + tmp;
	treeptr->higher->parent = treeptr;
	treeptr->higher->lower = '\0';
	printf("%u new subtree higher\n", treeptr->higher->ipaddr);
      }
      treeptr = treeptr->higher;
    }
  } while (treeptr);
  printf("Aieee aborting\n");
  exit(0);
}

#ifdef test
int main(int argc, char *argv[])
{
  struct flowdata *flowdataptr;
  init_flowdata();
  flowdataptr = find_flowdata(atoi(argv[1]));
  if (flowdataptr == '\0')
    flowdataptr = add_flowdata(atoi(argv[1]));
  printf("flowdataptr found!! %u\n", flowdataptr->ipaddr);
  exit(0);
}
#endif
