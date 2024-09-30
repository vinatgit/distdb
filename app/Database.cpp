#include "absl/log/log.h"

#include "distdb/Database.h"

RETURN_CODE Database::add( const std::string& path, const uint64_t& timestamp, const uint64_t& fileSize, const std::vector< uint32_t >& data ) {
	std::unique_lock< std::shared_mutex > lock( mutex_ );
	
	std::shared_ptr< Index > indexPtr = nullptr;
	{
		auto dataIt = data_.find( path );
		if( dataIt == data_.end() ) {
			dataIt = data_.insert( { path, std::make_shared< Index >() } ).first;
		}

		indexPtr = dataIt->second;
	}

	RETURN_CODE rc = indexPtr->add( timestamp, fileSize, data );
	if( rc != RETURN_CODE::NO_ERROR ) {
		return rc;
	}

	return RETURN_CODE::NO_ERROR;
}

RETURN_CODE Database::get( const std::string& path, uint64_t& timestamp, uint64_t& fileSize, std::vector< uint32_t >& data ) const {
	std::shared_lock< std::shared_mutex > lock( mutex_ );

	std::shared_ptr< Index > indexPtr = nullptr;
        {
                auto dataIt = data_.find( path );
                if( dataIt == data_.end() ) {
			LOG(ERROR) << "DATABASE: Path " << path << " does not exist"; 
			return RETURN_CODE::DATABASE_PATH_NOT_FOUND;
                }

                indexPtr = dataIt->second;
        }
        
        RETURN_CODE rc = indexPtr->get( timestamp, fileSize, data );
        if( rc != RETURN_CODE::NO_ERROR ) {
                return rc;
        }

        return RETURN_CODE::NO_ERROR;
}

RETURN_CODE Database::remove( const std::string& path, const uint64_t& timestamp ) {
        std::unique_lock< std::shared_mutex > lock( mutex_ );

        std::shared_ptr< Index > indexPtr = nullptr;
        {
                auto dataIt = data_.find( path );
                if( dataIt == data_.end() ) {
			LOG(ERROR) << "DATABASE: Path " << path << " does not exist";
                        return RETURN_CODE::DATABASE_PATH_NOT_FOUND;
                }

                indexPtr = dataIt->second;
        }

        RETURN_CODE rc = indexPtr->remove( timestamp );
        if( rc != RETURN_CODE::NO_ERROR ) {
                return rc;
        }

        return RETURN_CODE::NO_ERROR;
}
