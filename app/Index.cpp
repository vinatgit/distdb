#include "absl/log/log.h"

#include "distdb/Index.h"

RETURN_CODE Index::add( const uint64_t& timestamp, const uint64_t& fileSize, const std::vector< uint32_t >& data ) {
	timestamps_.emplace_back( timestamp );
	sizes_.emplace_back( fileSize );
	data_.emplace_back( std::move( data ) );

	return RETURN_CODE::NO_ERROR;
}

RETURN_CODE Index::get( uint64_t& timestamp, uint64_t& fileSize, std::vector< uint32_t >& data ) const {
	if( data_.empty() ) {
		LOG(ERROR) << "INDEX: No data found";
		return RETURN_CODE::INDEX_NO_DATA;
	}

	timestamp = timestamps_.back();
	fileSize = sizes_.back();
	data = data_.back();
	if( data.empty() ) {
		LOG(ERROR) << "INDEX: File has been deleted";
                return RETURN_CODE::INDEX_FILE_DELETED;
	}

        return RETURN_CODE::NO_ERROR;
}

RETURN_CODE Index::remove( const uint64_t& timestamp ) {
        timestamps_.emplace_back( timestamp );
        data_.emplace_back( std::vector< uint32_t >() );

        return RETURN_CODE::NO_ERROR;
}

