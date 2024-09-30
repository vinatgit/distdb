#ifndef DATABASE_INDEX_H
#define DATABASE_INDEX_H

#include <vector>

#include "absl/log/log.h"

#include "Consts.h"

class Index {
public:
	RETURN_CODE add( const uint64_t& timestamp, const uint64_t& fileSize, const std::vector< uint32_t >& data );
	RETURN_CODE get( uint64_t& timestamp, uint64_t& fileSize, std::vector< uint32_t >& data ) const;
	RETURN_CODE remove( const uint64_t& timestamp );

private:
	std::vector< uint64_t > timestamps_;
	std::vector< uint64_t > sizes_;
	std::vector< std::vector< uint32_t > > data_;
};

# endif // DATABASE_INDEX_H
