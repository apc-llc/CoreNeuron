#ifndef NRN_DATA_LAYOUT_HPP
#define NRN_DATA_LAYOUT_HPP

#define SOA_LAYOUT 0
#define AOS_LAYOUT 1
struct Memb_list;
int getDataIndex(int node_index, int variable_index, int mtype, Memb_list* ml);

#endif