/* http://www.cisco.com/en/US/products/sw/netmgtsw/ps1964/products_implementation_design_guide09186a00800d6a11.html#17629 */

struct p_header
{
  uint16_t	version;
  uint16_t	count;
  uint32_t	sysUptime;
  uint32_t	unix_secs;
  uint32_t	unix_nsecs;
  uint32_t	flow_sequence;
  uint8_t	engine_type;
  uint8_t	engine_id;
  uint16_t	samping_interval;
} p_header;

struct flowdata
{
  uint32_t	ipaddr;
  uint64_t	input;
  uint64_t	output;
  uint32_t	input25;
  uint32_t	output25;
  uint64_t	input80;
  uint64_t	output80;
  uint64_t	input119;
  uint64_t	output119;
  uint32_t	input445;
  uint32_t	output445;
  uint64_t	inputtcp;
  uint64_t	outputtcp;
  uint64_t	inputudp;
  uint64_t	outputudp;
  uint32_t	inputsyn;
  uint32_t	outputsyn;
  uint32_t	lastreset;
  struct flowdata	*higher;
  struct flowdata	*lower;
  struct flowdata	*parent;
} flowdata;
 
struct p_flow
{
  uint32_t	srcaddr;
  uint32_t	dstaddr;
  uint32_t	nexthop;
  uint16_t	input;
  uint16_t	output;
  uint32_t	dPkts;
  uint32_t	dOctets;
  uint32_t	First;
  uint32_t	Last;
  uint16_t	srcport;
  uint16_t	dstport;
  uint8_t	pad1;	
  uint8_t	tcp_flags;
  uint8_t	prot;
  uint8_t	tos;
  uint16_t	src_as;
  uint16_t	dst_as;
  uint8_t	src_mask;
  uint8_t	dst_mask;
  uint16_t	pad2;
} p_flow;

