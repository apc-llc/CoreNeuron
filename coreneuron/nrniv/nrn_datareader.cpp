#include "coreneuron/utils/endianness.h"
#include "coreneuron/utils/swap_endian.h"
#include "coreneuron/nrniv/nrn_datareader.h"
#include "coreneuron/nrniv/nrn_assert.h"


data_reader::data_reader(const char *filename, bool reorder) {
    this->open(filename,reorder);
    checkpoint(0);
}

void data_reader::open(const char *filename, bool reorder) {
    reorder_on_read=reorder;

    close();
    F.open(filename);
    nrn_assert(!F.fail());
}

static const int max_line_length=100;

int data_reader::read_int() {
    char line_buf[max_line_length];

    F.getline(line_buf,sizeof(line_buf));
    nrn_assert(!F.fail());

    int i;
    int n_scan=sscanf(line_buf,"%d",&i);
    nrn_assert(n_scan==1);
    
    return i;
}

void data_reader::read_checkpoint_assert() {
    char line_buf[max_line_length];

    F.getline(line_buf,sizeof(line_buf));
    nrn_assert(!F.fail());

    int i;
    int n_scan=sscanf(line_buf,"chkpnt %d\n",&i);
    nrn_assert(n_scan==1);
    nrn_assert(i==chkpnt);
    ++chkpnt;
}


template <typename T>
T *data_reader::parse_array(T *p,size_t count,parse_action flag) {
    if (count>0 && flag!=seek) nrn_assert(p!=0);

    read_checkpoint_assert();
    switch (flag) {
    case seek:
        F.seekg(count*sizeof(T),std::ios_base::cur);
        break;
    case read:
        F.read((char *)p,count*sizeof(T));
        if (reorder_on_read) endian::swap_endian_range(p,p+count);
        break;
    }

    nrn_assert(!F.fail());
    return p;
}

/** Explicit instantiation of parse_array<in> */
template int *data_reader::parse_array<int>(int *,size_t,parse_action);

/** Explicit instantiation of parse_array<double> */
template double *data_reader::parse_array<double>(double *,size_t,parse_action);

void data_reader::close() {
    F.close();
}
