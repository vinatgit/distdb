#ifndef INDEX_SERVER_H
#define INDEX_SERVER_H

#define DATA_DIMENSION 2

#include <vector>

#include "absl/log/log.h"

class Index {
public:
        uint32_t add( const std::vector< int >& data ) {
		if( data.size() % dimension_ != 0 ) {
			LOG(ERROR) << "INDEX: Data has incorrect dimensions, expected dimension = " << dimension_;
			return 1;
		}

		data_.insert( data_.end(), data.begin(), data.end() );
		return 0;
	}

private:
	uint32_t dimension_ = DATA_DIMENSION;
	std::vector< int > data_;
};

# endif // INDEX_SERVER_H
